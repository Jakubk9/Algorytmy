#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MLD 1000000000.0
typedef struct Wezel
{
  int liczba;
  struct Wezel* lewy;
  struct Wezel* prawy;
  struct Wezel* ojciec;
} Wezel ;

void wstaw(Wezel** korzen, int a)
{
  Wezel* pom = (Wezel*)malloc(sizeof(Wezel));
  pom->lewy = NULL;
  pom->prawy = NULL;
  pom->liczba = a;

  if(*korzen == NULL)
  {
    pom->ojciec = NULL;
    *korzen = pom;
  }
  else
  {
    Wezel* pom2 = *korzen;
    while((a < pom2->liczba && pom2->lewy != NULL) || (a > pom2->liczba && pom2->prawy != NULL))
    {
      if(a < pom2->liczba)
        pom2 = pom2->lewy;
      else
        pom2 = pom2->prawy;
    }

    pom->ojciec = pom2;

    if(a < pom2->liczba)
      pom2->lewy = pom;
    else
      pom2->prawy = pom;
  }
}

Wezel* szukaj(Wezel** korzen, int a)
{
  if(*korzen == NULL)
    return NULL;
  Wezel* pom = *korzen;
  while((a < pom->liczba && pom->lewy != NULL) || (a > pom->liczba && pom->prawy != NULL))
  {
    if(a < pom->liczba)
      pom = pom->lewy;

    else
      pom = pom->prawy;
	
  }
  if(a == pom->liczba)
    return pom;
  return NULL;
}

Wezel* tree_min(Wezel* korzen)
{
  Wezel* pom = korzen;
  while(pom->lewy != NULL)
    pom = pom->lewy;
  return pom;
}

void usun(Wezel** korzen, Wezel* z)
{
  if(z == NULL)
  {
    printf("Nie udalo sie usunac!\n");
  }
  else
  if(z->lewy == NULL && z->prawy == NULL)
  {
    if(*korzen == z)
      *korzen = NULL;
    else
    if(z == z->ojciec->lewy)
      z->ojciec->lewy = NULL;
    else
    if(z == z->ojciec->prawy)
      z->ojciec->prawy = NULL;
  }
  else
  if(z->lewy != NULL && z->prawy != NULL)
  {
    Wezel* y = tree_min(z->prawy);
    z->liczba = y->liczba;
    usun(korzen, y);
  }
  else
  if(z->lewy != NULL)
  {
    z->lewy->ojciec = z->ojciec;
    if(z == *korzen)
      *korzen = z->lewy;
    else
    if(z == z->ojciec->lewy)
      z->ojciec->lewy = z->lewy;
    else
      z->ojciec->prawy = z->lewy;
  }
  else
  {
    z->prawy->ojciec = z->ojciec;
    if(z == *korzen)
      *korzen = z->prawy;
    else
    if(z == z->ojciec->lewy)
      z->ojciec->lewy = z->prawy;
    else
      z->ojciec->prawy = z->prawy;
  }
}

void drukuj(Wezel* korzen)
{
  if(korzen != NULL)
  {
    drukuj(korzen->lewy);
    drukuj(korzen->prawy);
    printf("XX%i ", korzen->liczba);
  }
}

int main()
{
  Wezel* korzen = NULL;
  Wezel* szukana = NULL;
struct timespec tp0, tp1;
double tn1, Fn, x;
 // wstaw(&korzen, 10);
  //wstaw(&korzen, 20);
 // wstaw(&korzen, 15);
 // wstaw(&korzen, 14);
 // wstaw(&korzen, 18);
 // wstaw(&korzen, 17);
 // wstaw(&korzen, 19);
 // szukana = szukaj(&korzen, 20);
 // if(szukana != NULL)
 //   printf("%i\n", szukana->lewy->liczba);
 // drukuj(korzen);
 // printf("\n");
 // usun(&korzen, szukaj(&korzen, 15));
 // drukuj(korzen);
 // printf("\n");
clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp0);
	for(long int i=1; i<100000; i++)
		wstaw(&korzen, i);
 	szukaj(&korzen, 555444);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp1);
    tn1 = (tp1.tv_sec + tp1.tv_nsec / MLD) - (tp0.tv_sec + tp0.tv_nsec / MLD);
    printf("Czas:\t%lf s\n", tn1);
}