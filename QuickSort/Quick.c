#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define MAX 60000l
#define MLD 1000000000.0 //10**9

int tabA[10000];
int tabB[10000];
int pom[10000];

void Babelkowe(int p, int r)
{
  for(int i=p;i<r;i++)
    for(int j=i+1;j<=r;j++)
    {
      if(tabA[j]<tabA[i]){
        int temp;
        temp = tabA[i];
        tabA[i] = tabA[j];
        tabA[j] = temp;
      }
  }
}

int Partition(int p, int r)
{
  int x = tabA[r]; //el wyznaczajacy podzial
  int i = p-1;
  for(int j=p;j<=r;j++)
  {
    if(tabA[j]<=x)
    {
     	i=i+1;
     	int temp;
  	temp = tabA[i];
  	tabA[i] = tabA[j];
  	tabA[j] = temp;
    }
  }
  if(i<r) return i;
  else return i-1;
}

void Quicksort(int p, int r, int c)
{
  if(p<r)
    if((r-p+1)>c)
    {
      int q = Partition(p,r);
      Quicksort(p,q,c);
      Quicksort(q+1,r,c);
    }
    else Babelkowe(p,r);
}

int main()
{
  int l = 1;
  int c = 0;
  double Tn, Tn1, Fn, x;
  struct timespec tp0, tp1, tp2, tp3;
  FILE *f1 = fopen("losowe.txt", "r");
  //FILE *f1 = fopen("malejace.txt", "r");
  FILE *f2 = fopen("wynik.txt", "w");

  for(int i=0;i<10000;i++)
  {
    fscanf(f1, "%i", tabA+i);
  }
  for(int k=0;k<10000;k++)
  {
    tabB[k] = tabA[k];
    pom[k] = tabA[k];
  }

  printf("%15s | %9s | %9s |\n", "ROZMIAR TABLICY", "CZAS 1","CZAS 2");
  for(int n=250;n<=10000;n+=250)
  {
     for(int m=0;m<n;m++)
     {
       tabA[m] = pom[m];
     }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
    Quicksort(0,n-1,c);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
    Tn=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
     for(int m=0;m<n;m++)
     {
       tabA[m] = pom[m];
     }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp2);
    Quicksort(0,n-1,0);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp3);
    Tn1=(tp3.tv_sec+tp3.tv_nsec/MLD)-(tp2.tv_sec+tp2.tv_nsec/MLD);
    
    printf("%2i.  %-9i | %9f | %9f |\n",l++, n, Tn, Tn1);
    
  }
  for(int j=0;j<10000;j++)
  {
    fprintf(f2,"%i\n", tabA[j]);
  }
  fclose(f1);
  fclose(f2);
}