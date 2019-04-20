// struktura wezla B-drzewa i przyklad zapisu i odczytu na plik
// budowanie B-drzewa o zadanej wysokosci i drukowanie

#include <stdio.h>
#define T 3   // stopien B-drzewa

int pozycja=0; // wolna pozycja w pliku, pozycja-1 = ostatnia pozycja

typedef struct{
  short n;        //ilosc kluczy (-1 oznacza wezel usuniety)
  short leaf;     // czy lisc
  int k[2*T-1];   // klucze
  int c[2*T];     // wskazniki do synow (pozycje w pliku: 0,1,2 ...)
  int info[2*T-1];  // wskazniki do informacji skojarzonej z kluczem
                    // (pozycje w innym pliku); tutaj nie beda uzyte
} Wezel;
int rozmiarw = sizeof(Wezel); // rozmiar wezla w bajtach
FILE *drzewo;  // plik drzewa (zawierajacy wezly)

void zapisz(int i,Wezel *w){
  // zapisuje *w jako i-ty zapis w pliku drzewa
  fseek(drzewo,(long)i*rozmiarw,SEEK_SET);
  fwrite(w,rozmiarw,1,drzewo);
  //  printf("z%d ",i);
}

void odczytaj(int i,Wezel *w){
  // odczytuje i-ty zapis w pliku drzewa i wpisuje do *w
  fseek(drzewo,(long)i*rozmiarw,SEEK_SET);
  fread(w,rozmiarw,1,drzewo);
  //  printf("o%d ",i);
}

int budujB(int g, int n){
  // buduje B-drzewo o wysokosci g, w kazdym wezle jest n kluczy
  // wynikiem jest pozycja korzenia w pliku - jest to ostatni
  // zapis w pliku, co jest wazne dla dalszych zapisow do pliku
  // ktore trzeba robic zaczynajac od kolejnej pozycji
  static int klucz=0; // kolejny klucz
  Wezel w;
  w.n=n;
  int i;
  if (g==0){  // lisc
    for (i=0;i<n;i++){
      w.c[i]= -1; // w lisc
      w.k[i]= klucz++;
    }
    w.c[n]= -1;
    w.leaf=1;
  } else {  // wezel wewnetrzny
    for (i=0;i<n;i++){
      w.c[i]= budujB(g-1,n);
      w.k[i]= klucz++;
    }
    w.c[n]= budujB(g-1,n);;
    w.leaf=0;
  }
  zapisz(pozycja++,&w);
  return pozycja-1;
}

int szukajB(int x, int k){
  // szuka klucza k w poddrzewie o korzeniu r
  Wezel w;
  odczytaj(x,&w);
  int i=0;
  while(i<w.n && k>w.k[i])
    i=i+1;
  if(k==w.k[i])
    return w.k[i];
  if(w.leaf == 1)
    return -1;
  else
    return szukajB(w.c[i],k);
}

void rozbij(int x, int i, int y){
  // rozbija węzeł y, który jest i-tym synem węzła x
  Wezel z,w,w1;
  odczytaj(x,&w);
  odczytaj(y,&w1);
  z.leaf = w1.leaf;
  z.n = T-1;
  for(int j=0;j<T-1;j++)
    z.k[j] = w1.k[j+T];
  if(w1.leaf == 0)
  {
    for(int j=0;i<T;j++)
      z.c[j] = w1.c[j+T];
  }
  w1.n=T-1;
  for(int j=w.n;j>=i+1;j--)
    w.c[j+1]=w.c[j];
  w.c[i+1]=pozycja;
  for(int j=w.n-1;j>=i;j--)
    w.k[j+1]=w.k[j];
  w.k[i]=w1.k[T-1];
  w.n=w.n+1;
  zapisz(y,&w1);
  zapisz(pozycja++,&z);
  zapisz(x,&w);
}

void wstawniepelnyB(int x, int k){
// wstawia klucz k do poddrzewa o korzeniu x
// węzeł x jest niepełny (x.n < 2*t-1)
  Wezel w,z;
  odczytaj(x,&w);
  int i = w.n-1;
  if(w.leaf == 1)
  {
    while(i >= 0 && k < w.k[i])
    {
      w.k[i+1] = w.k[i];
      i--;
    }
    w.k[i+1] = k;
    w.n = w.n+1;
    zapisz(x,&w);
  }
  else
  {
    while(i >= 0 && k < w.k[i])
      i--;
    i++;
    odczytaj(w.c[i],&z);
    if(z.n == 2*T-1)
    {
      rozbij(x,i,w.c[i]);
      odczytaj(x,&w);
      if(k > w.k[i])
        i++;
    }
    wstawniepelnyB(w.c[i],k);
  }
}

int wstawB(int r, int k){
  // wstawia klucz k do drzewa r
  if(r == -1)
  {
    Wezel w;
    w.k[0] = k;
    w.n = 1;
    w.leaf = 1;
    zapisz(pozycja++,&w);
    return pozycja-1;
  }
  else
  {
    Wezel root;
    int pom;
    odczytaj(r,&root);
    if(root.n == 2*T-1)
    {
      Wezel s;
      s.leaf = 0;
      s.n = 0;
      s.c[0] = r;
      zapisz(pozycja++,&s);
      pom = pozycja;
      rozbij(pozycja-1,0,r);
      wstawniepelnyB(pozycja-1,k);
      return pom-1;
    }
    else
    {
      wstawniepelnyB(r,k);
      return r;
    }
  }
}

void drukujB(int r, int p){
  // drukuje B-drzewo o korzeniu r (pozycja w pliku)
  // wydruk przesuniety o p w prawo
  Wezel w;
  int i,j;
  odczytaj(r,&w);
  if (w.leaf == 1){
    for (i=0;i<p;i++) printf(" ");
    for (i=0;i<w.n;i++) printf("%d ",w.k[i]);
    printf("\n");
  } else {
    drukujB(w.c[w.n],p+4);
    for (i=w.n-1;i>=0;i--){
      for (j=0;j<p;j++) printf(" ");
      printf("%d\n",w.k[i]);
      drukujB(w.c[i],p+4);
    }
  }
}

int main(){
    drzewo = fopen("bdrzewo","w+");
    Wezel wezel;
    int root=-1;
    root = wstawB(root,1);
    root = wstawB(root,2);
    root = wstawB(root,3);
    root = wstawB(root,4);
    root = wstawB(root,5);
    drukujB(root,0);
    // root = wstawB(root,6);
    // drukujB(root,0);
    // root = wstawB(root,7);
    // drukujB(root,0);
    // root = wstawB(root,8);
    root = wstawB(root,9);
    drukujB(root,0);
    if( szukajB(root,5) == 5 )
            printf("Znaleziono!\n");

    fclose(drzewo);
}
