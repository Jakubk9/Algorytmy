#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MLD 1000000000.0

#define RED 1
#define BLACK 0  

typedef struct Wezel *Wskwezla;
typedef struct Wezel
{
  int value;
  int kolor;
  struct Wezel* left;
  struct Wezel* right;
  struct Wezel* p;
} Wezel ;

Wskwezla nil;

void nilInit(void) //funkcja budująca drzewo
{
  nil = (Wskwezla) malloc(sizeof(Wezel));
  nil->p = nil;
  nil->kolor = BLACK;
  nil->left = nil->right = nil;
}

void Left_Rotate(Wezel** korzen, Wezel** z)
{
  Wezel* x = *z;
  Wezel* y = x->right;
  Wezel* c;

  if(y != nil)
  {
    c = x->p;
    x->right = y->left;
    if(x->right != nil)
      x->right->p = x;
    y->left = x;
    y->p = c;
    x->p = y;
    if(c != nil)
      if(c->left == x)
        c->left = y;
      else
        c->right = y;
    else
      *korzen = y;
  }
}

void Right_Rotate(Wezel** korzen, Wezel** z)
{
  Wezel* x = *z;
  Wezel* y = x->left;
  Wezel* c;

  if(y != nil)
  {
    c = x->p;
    x->left = y->right;
    if(x->left != nil)
      x->left->p = x;
    y->right = x;
    y->p = c;
    x->p = y;

    if(c != nil)
      if(c->left == x)
        c->left = y;
      else
        c->right = y;
    else
      *korzen = y;
  }
}

void przypadki_wstaw(Wezel** korzen, Wezel** z)
{
  Wezel* pom = *z;
  if(pom == *korzen)
  {
    pom->kolor = BLACK;
  }
  else
  if(pom->p->kolor == RED)
  {
    Wezel* gf = pom->p->p; 
    // przypadek 1
    if(gf->left->kolor == RED && gf->right->kolor == RED)
    {
      gf->left->kolor = BLACK;
      gf->right->kolor = BLACK;
      gf->kolor = RED;
      przypadki_wstaw(korzen,&gf);
    }
    // przypadek 2
    else
    if(gf->left->kolor == RED && gf->left->right == pom)
    {
      Left_Rotate(korzen,&(pom->p));
      przypadki_wstaw(korzen,&(pom->left));
    }
    else if(gf->right->kolor == RED && gf->right->left == pom)
    {
      Right_Rotate(korzen,&(pom->p));
      przypadki_wstaw(korzen,&(pom->right));
    }
    // przypadek 3
    else
    if(gf->left->kolor == RED && gf->left->left == pom)
    {
      Right_Rotate(korzen,&gf);
      pom->p->kolor = BLACK;
      gf->kolor = RED;
    }
    else
    if(gf->right->kolor == RED && gf->right->right == pom)
    {
      Left_Rotate(korzen,&gf);
      pom->p->kolor = BLACK;
      gf->kolor = RED;
    }
  }
}

void wstaw(Wezel** korzen, int a)
{
  Wezel* pom = (Wezel*)malloc(sizeof(Wezel));
  pom->kolor = RED;
  pom->value = a;
  pom->left = nil;
  pom->right = nil;

  if(*korzen == nil)
  {
    pom->p = nil;
    *korzen = pom;
    przypadki_wstaw(korzen, &pom);
  }
  else
  {
    Wezel* pom2 = *korzen;
    while((a < pom2->value && pom2->left != nil) || (a > pom2->value && pom2->right != nil))
    {
      if(a < pom2->value)
        pom2 = pom2->left;
      else
        pom2 = pom2->right;
    }

    pom->p = pom2;
    if(a < pom2->value)
      pom2->left = pom;
    else
      pom2->right = pom;

    przypadki_wstaw(korzen, &pom);
  }
}

int ilosc_czerwonych(Wezel* korzen, int *ile) //ilość czerwonych węzłów
{
  if(korzen != nil)
  {
    if(korzen->kolor == RED)
      (*ile)++;
    ilosc_czerwonych(korzen->left, ile);
    ilosc_czerwonych(korzen->right, ile);
  }
  return *ile;
}

int MAX(Wezel* korzen, int *sum, int *m) //maksymalna głębokość liści
{
  int a;
  if(korzen != nil)
  {
    (*sum)++;
    if(korzen->left == nil || korzen->right == nil)
      if(*sum > *m)
        *m = *sum;
    a = *sum;
    MAX(korzen->left, sum, m);
    *sum = a;
    MAX(korzen->right, sum, m);
  }
  return *m;
}

int MIN(Wezel* korzen, int *sum, int *m) //minimalna głębokość liści
{
  int a;
  if(korzen != nil)
  {
    (*sum)++;
    if(korzen->left == nil || korzen->right == nil)
      if(*sum < *m)
        *m = *sum;
    a = *sum;
    MIN(korzen->left, sum, m);
    *sum = a;
    MIN(korzen->right, sum, m);
  }
  return *m;
}

int SEARCH_PRO(Wezel** korzen, int a, int w, int c)
{
 if(*korzen == nil)
   // return nil;
	printf("BRAK");
  Wezel* pom = *korzen;
  while((a < pom->value && pom->left != nil) || (a > pom->value && pom->right != nil))
  {
    if(a < pom->value){
      pom = pom->left;
	w++;
	if(pom->kolor == BLACK)
		c++;	
	}
    else{
      pom = pom->right;
	if(pom->kolor == BLACK)
		c++;	
	w++;
	}
  }
  if(a == pom->value)
   // return pom;
	printf("Kolor szukanego elementu dla ciebie = %i\n",pom->kolor);
	printf("Głębokość szukanego elementu = %i\n", w);
	printf("Czarna wysokość szukanego elementu = %i\n", c);
//  return nil;
}

void drukuj(Wskwezla w) //Druk w pre-order
{
	if(w != nil)
	{
    printf("%i   -   %i\n", w->value, w->kolor);
		drukuj(w->left);
		drukuj(w->right);
	}
}

int main(void) {
  int ile=1, m=1;
  nilInit();
  Wskwezla korzen;
  korzen = nil;
wstaw(&korzen, 4);
wstaw(&korzen, 8);
wstaw(&korzen, 2);
wstaw(&korzen, 12);
wstaw(&korzen, 6);
wstaw(&korzen, 14);
wstaw(&korzen, 10);
wstaw(&korzen, 9);

 //wstaw(&korzen, 30);
//  drukuj(korzen);
// printf("\n");
 // wstaw(&korzen, 20);
 // printf("\n");
 // drukuj(korzen);
 // wstaw(&korzen, 40);
 // printf("\n");
 // drukuj(korzen);
 // wstaw(&korzen, 10); //następuje przypadek 1
 // printf("\n");
 // drukuj(korzen);
  //wstaw(&korzen, 5); //następuje przypadek 3
 // printf("\n");
 // drukuj(korzen);
 // wstaw(&korzen, 3); //następuje przypadek 1
 // printf("\n");
 // drukuj(korzen);
 // wstaw(&korzen, 4); //następuje przypadek 2
 // printf("\n");
//	wstaw(&korzen, 30);
 // drukuj(korzen);
struct timespec tp0, tp1;
double tn1, Fn, x;
clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp0);
	//for(long long int i=1; i<1000000; i++)
	//	wstaw(&korzen, i);
printf("--------\n");
	SEARCH_PRO(&korzen,9,m,ile);
clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp1);
    tn1 = (tp1.tv_sec + tp1.tv_nsec / MLD) - (tp0.tv_sec + tp0.tv_nsec / MLD);
    printf("Czas:\t%lf s\n", tn1);
	printf("root = %i\n", korzen->value);

//SEARCH_PRO(&korzen,9,m,ile);
  //printf("Ilość węzłow czerwonych = %d\n", ilosc_czerwonych(korzen, &ile));
  
 // ile=1;
  //printf("Maksymalna głębokość liści = %d\n", MAX(korzen, &ile, &m));
  
 // ile=1;
 // m = MAX(korzen, &ile, &m);
 // ile=1;
 // printf("Minimalna głębokość liści = %d\n", MIN(korzen, &ile, &m));
}