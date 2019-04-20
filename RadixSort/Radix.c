#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MLD 1000000000.0

void Heapify(char *A[], int i, int heapsize)
{
    int l = (2 * i) + 1;
    int r = (2 * i) + 2;
    int largest;
    char *c = malloc(100);
    if (l <= heapsize - 1 && strcmp(A[l], A[i]) <= 0)
    {
        largest = l;
    }
    else
        largest = i;
    if (r <= heapsize - 1 && strcmp(A[r], A[largest]) <= 0)
    {
        largest = r;
    }
    if (largest != i)
    {
        c = A[i];
        A[i] = A[largest];
        A[largest] = c;
        Heapify(A, largest, heapsize);
    }
}

void BuildHeap(char *A[], int n, int heapsize)
{
    for (int i = (n / 2); i >= 1; i--)
        Heapify(A, i - 1, heapsize);
}

void HeapSort(char *A[], int n, int heapsize)
{
    BuildHeap(A, n, heapsize);
    char *c = malloc(100);
    for (int i = n; i >= 2; i--)
    {
        c = A[heapsize - 1];
        A[heapsize - 1] = A[0];
        A[0] = c;
        heapsize--;
        Heapify(A, 0, heapsize);
    }
}

void counting(char *A[], int n, int p)
{
    char *temp[n];
    int zakres = 255;
    int licznik[zakres + 1];

    for (int i = 0; i <= zakres; i++)
        licznik[i] = 0;

    for (int i = 0; i < n; i++)
        ++licznik[A[i][p]];

    for (int i = 1; i <= zakres; i++)
        licznik[i] += licznik[i - 1];

    for (int i = n - 1; i >= 0; i--)
    {
        temp[licznik[A[i][p]] - 1] = A[i];
        --licznik[A[i][p]];
    }

    for (int i = 0; i < n; i++)
        A[i] = temp[i];
}

void Radix(char *A[], int n, int p)
{
    for (int i = p - 1; i >= 0; i--)
        counting(A, n, i);
}

int main()
{
    struct timespec tp0, tp1;
    double tn1, tn2;
    char nazwisko[100];
    int liczby;
    int n = 0;
    int max = 0;
    char *nazwiska1[20000];
    char *nazwiska2[20000];

    FILE *f1 = fopen("nazwiska.txt", "r");
    FILE *f2 = fopen("posortowane.txt", "w");
    while (fscanf(f1, "%d %s\n", &liczby, nazwisko) != EOF)
    {
        nazwiska1[n] = malloc(23);
        nazwiska2[n] = malloc(23);
        strcpy(nazwiska1[n], nazwisko);
        strcpy(nazwiska2[n], nazwisko);
        n++;
    }

    for (int j = 0; j <= n - 1; j++)
    {
        if (strlen(nazwiska1[j]) > max)
            max = strlen(nazwiska1[j]);
    }
    fclose(f1);
    /*timery*/
    printf("                  CZAS\n");
    printf("---------------------------\n");
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp0);
    Radix(nazwiska1, n, max);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp1);
    tn1 = (tp1.tv_sec + tp1.tv_nsec / MLD) - (tp0.tv_sec + tp0.tv_nsec / MLD);
    printf("|Radix-sort:\t%lf s|\n", tn1);

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp0);
    HeapSort(nazwiska2, n, n - 1);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp1);
    tn2 = (tp1.tv_sec + tp1.tv_nsec / MLD) - (tp0.tv_sec + tp0.tv_nsec / MLD);
    printf("|Heap-sort:\t%lf s|\n", tn2);
    printf("---------------------------\n");

    for (int i = 0; i < n; i++)
    {
        fprintf(f2, "%s\n", nazwiska1[i]);
    }

    fclose(f2);
    return 0;
}