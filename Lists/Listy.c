#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct SList
{
    char data[25];
    struct SList *next;
} SList;

SList *dodaj(SList *root, char x[25])
{
    SList *nowy = (SList *)malloc(sizeof(SList));
    strcpy(nowy->data, x);
    nowy->next = root;
    return nowy;
}

SList *dodajNaKoniec(SList *root, char x[25])
{

    if (root == NULL)
    {
        return dodaj(root, x);
    }

    SList *nowy = (SList *)malloc(sizeof(SList));
    SList *ptr = root;
    while (ptr->next != NULL)
    {
        ptr = ptr->next;
    }

    strcpy(nowy->data, x);
    nowy->next = NULL;
    ptr->next = nowy;

    return root;
}

void wypisz(SList *root)
{
    SList *ptr = root;
    if (root == NULL)
    {
        printf("Lista jest pusta\n");
    }
    while (ptr != NULL)
    {
        printf("Element %s \n", ptr->data);
        ptr = ptr->next;
    }
}

SList *znajdz(SList *root, char x[25])
{
    SList *ptr = root;
    if (root == NULL)
    {
        printf("Lista jest pusta\n");
    }
    while (ptr != NULL)
    {
        if (strcmp(ptr->data, x) == 0)
        {
            printf("Element %s jest na pozycji\n", x);
            return ptr;
        }
        else
        {
            ptr = ptr->next;
        }
    }
    printf("Nie ma takiego elementu!\n");
    return NULL;
}

void usun(SList **root, char x[25])
{
    SList *przed = NULL;
    SList *ptr = *root;
    if (strcmp(ptr->data, x) == 0)
    {
        przed = ptr;
        ptr = ptr->next;
        *root = ptr;
        free(przed);
        printf("Usunieto dany Element!\n");
    }
    else
    {
        while (ptr != NULL)
        {
            przed = ptr;
            ptr = ptr->next;
            if (strcmp(ptr->data, x) == 0)
            {

                przed->next = ptr->next;
                free(ptr);
                printf("Usunieto dany Element!\n");
            }
        }
        printf("Brak danego elementu!\n");
    }
}

void kasuj(SList **root)
{
    SList *ptr = *root;
    while (*root != NULL)
    {
        ptr = *root;
        *root = (*root)->next;
        free(ptr);
    }
}

SList *bezpowtorzen(SList *root)
{
    SList *newL = NULL;
    SList *temp = newL;
    SList *ptr = root;
    bool F;
    while (ptr != NULL)
    {
        F = true;
        while (temp != NULL)
        {
            if (strcmp(ptr->data, temp->data) == 0)
                F = false;
            temp = temp->next;
        }
        if (F)
        {
            newL = dodaj(newL, ptr->data);
            temp = newL;
        }
        ptr = ptr->next;
    }
    return newL;
}

SList *scal(SList **root, SList **root2)
{
    SList *newL = *root;
    SList *ptr = *root;
    while (ptr->next != NULL)
        ptr = ptr->next;
    ptr->next = *root2;
    
	*root = NULL;
	*root2 = NULL;
	return newL;
}

int main()
{
    SList *root = NULL;
    SList *root2 = NULL;
    SList *root3 = NULL;

    root = dodaj(root, "raz");
    root = dodaj(root, "dwa");
    root = dodaj(root, "trzy");
    wypisz(root);
    printf("--------------\n");
    printf("%p\n", znajdz(root, "dwa"));
    printf("%p\n", znajdz(root, "qwe"));
    printf("--------------\n");
    wypisz(root);
    usun(&root, "trzy");
    wypisz(root);
    printf("--------------\n");
    wypisz(root);
    kasuj(&root);
    wypisz(root);
    printf("--------------\n");
    root = dodaj(root, "raz");
    root = dodaj(root, "dwa");
    root = dodaj(root, "trzy");
    root = dodaj(root, "raz");
    root = dodaj(root, "trzy");
    printf("-------2. Bezpowtórzeń-------\n");
    printf("--------------\n");
    wypisz(root);
    printf("--------------\n");
    root2 = bezpowtorzen(root);
    wypisz(root2);
    printf("-------3. Scalanie-------\n");
    printf("--------------\n");
    printf("--------------\n");
    kasuj(&root2);
    root2 = dodaj(root2, "cztery");
    root2 = dodaj(root2, "piec");
    root2 = dodaj(root2, "szesc");
    root3 = scal(&root, &root2);
    wypisz(root3);
    printf("--------------\n");
    wypisz(root);
    printf("--------------\n");
    wypisz(root2);
}