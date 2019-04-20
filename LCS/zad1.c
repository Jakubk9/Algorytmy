#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int c[1000][1000];
unsigned char b[250][250];
unsigned char pom[1000];

void look_for(char x[50], char y[50])
{
  int m = strlen(x);
  int n = strlen(y);
  for(int i=0;i<=m;i++)
    c[i][0] = 0;
  for(int i=0;i<=n;i++)
    c[0][i] = 0;
  for(int i=1;i<=m;i++)
    for(int j=1;j<=n;j++)
      if(x[i-1] == y[j-1])
      {
        c[i][j] = c[i-1][j-1]+1;
        b[i][j] = '\\';
      }
      else if(c[i-1][j] > c[i][j-1])
      {
        c[i][j] = c[i-1][j];
        b[i][j] = '|';
      }
      else
      {
        c[i][j] = c[i][j-1];
        b[i][j] = '-';
      }
}

void print1(char x[50], char y[50], int i, int j, int *h)
{
   if(b[i][j] == '\\')
  {  
   pom[*h] = x[i-1];
     *h = *h + 1;
    print1(x,y,i-1,j-1,h);

    //printf("%c",x[i-1]);
  }
  else if(b[i][j] == '|')
    print1(x,y,i-1,j,h);
  else if(b[i][j] == '-')
    print1(x,y,i,j-1,h);
}

// void printall(char x[50], char y[50], int i, int j, int *h)
// {
//   if(b[i][j] == '\\')
//   {
//     printall(x,y,i-1,j-1,h);
//     pom[*h] = x[i-1];
//     *h = *h + 1;
//   }
//   else if(b[i][j] == '|')
//     print(x,y,i-1,j,h);
//   else if(b[i][j] == '-')
//     print(x,y,i,j-1,h);
// }

int main()
{
 unsigned char x[250], y[250];
FILE *f1 = fopen("A.txt", "r");
fscanf(f1, "%s", x);
FILE *f2 = fopen("B.txt", "r");
fscanf(f2, "%s", y);
 fclose(f1);
 fclose(f2);
 // scanf("%s", x);
 // scanf("%s", y);
  look_for(x,y);
  int i = strlen(x);
  int j = strlen(y);
  int h = 0;
  printf("Najdłuższy wspólny podciag: ");
  print1(x,y,i,j,&h);
 for(int k=c[i][j];k>=0;k--)
	{  
		printf("%c",pom[k-1]);
	}

//printf("%s",pom);
printf("\n%d\n",c[i][j]);
//printf("\n");
}
