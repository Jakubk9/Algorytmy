#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int tab[500];

void Heapify(int tab[], int i, int x, int heapsize)
{
  int l = (2*i)+1-(x-1);
  int r = (2*i)+2-(x-1);
  int largest;
  int c;
  if(l<=heapsize-1&&tab[l]>tab[i])
  {
    largest = l;
  }
  else largest = i;
  if(r<=heapsize-1&&tab[r]>tab[largest])
  {
    largest = r;
  }
  if(largest!=i)
  {
    c = tab[i];
    tab[i] = tab[largest];
    tab[largest] = c;
    Heapify(tab,largest,x,heapsize);
  }
}

void BuildHeap(int tab[], int x, int y, int heapsize)
{
  for(int i=((y+x)/2);i>=x;i--)
  Heapify(tab,i-1,x,heapsize);
}

void HeapSort(int tab[], int x, int y, int heapsize)
{
  BuildHeap(tab,x,y,heapsize);
  int c;
  for(int i=y-x+1;i>=2;i--)
  {
    c = tab[heapsize-1];
    tab[heapsize-1] = tab[x-1];
    tab[x-1] = c;
    heapsize--;
    Heapify(tab,x-1,x,heapsize);
  }
}

int main(){
  int n=0;
  int heapsize;
  int x,y;
  FILE *fp;
  FILE *fp2;
  if((fp=fopen("liczby2.txt", "r"))==NULL)
  {
          printf("Nie mozna otworzyc pliku!\n");
          exit(1);
  }
  if((fp2=fopen("wynik2.txt", "w"))==NULL)
  {
          printf("Nie mozna otworzyc pliku!\n");
          exit(1);
  }
  fscanf(fp, "%i", &x);
  fscanf(fp, "%i", &y);
  while(fscanf(fp, "%i", tab+n)!=EOF)
  {
    n++;
  }
  heapsize = y;
  HeapSort(tab,x,y,heapsize);
  for(int i=x-1;i<y;i++)
    fprintf(fp2, "%i\n", tab[i]);
  fclose(fp);
  fclose(fp2);
}
