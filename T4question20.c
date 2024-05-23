#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXTAM 1000

typedef char TChave;
typedef int TApontador;

typedef struct {
    TChave Chave;
} TItem;

// esq -> raiz do elemento que violou o heap
// dir -> tamanho do vetor

void heapRefaz(TItem *A, int esq, int dir)
{
    TItem aux;
    int i, j;
    i = esq;
    j = i * 2 + 1;
    aux = A[i];

    while (j <= dir)
    {
        if ((j < dir) && (A[j].Chave < A[j + 1].Chave))
            j++;
        if (aux.Chave >= A[j].Chave)
            break;
        A[i] = A[j];
        i = j;
        j = i * 2 + 1;
    }
    
    A[i] = aux;
}

// void heapRefaz(TItem *A, int esq, int dir)
// {
//     TItem aux;
//     int i, j;

//     i = esq;
//     j = i * 2 + 1;

//     if (j <= dir) {
//         aux = A[i];
//         if ((j < dir) && (A[j].Chave < A[j + 1].Chave))
//             j++;
//         if (aux.Chave < A[j].Chave) {
//             A[i] = A[j];
//             A[j] = aux;
//             heapRefaz(A, j, dir);
//         } 
//     }
// }

void heapConstroi(TItem *A, int n)
{
    int esq;
    esq = (n / 2) - 1;
    while (esq >= 0)
    {
        heapRefaz(A, esq, n-1);
        esq--;
    }
}

void heapSort(TItem *A, int n)
{
    TItem aux;
    int m;

    heapConstroi(A, n);

    m = n - 1;

    while (m > 0)
    {
        aux = A[m];
        A[m] = A[0];
        A[0] = aux;
        m = m - 1;
        heapRefaz(A, 0, m);
    }
}

void acharMaiorValorQueKEmHeapArvore(TItem *A, int k)
{
    

    int counter = 0;

    for(int i = 0; i <= sizeof(A); i ++) 
    {
        if(A[i].Chave >= k)
        {
            counter++;
        }
    }

    TItem *A_aux;
    
    A_aux = (TItem *) malloc((counter - 1) * sizeof(TItem));
    
    printf("%d", sizeof(A_aux));

    counter = 0;

    for(int i = 0; i <= sizeof(A); i ++)
    {
        if(A[i].Chave >= k)
        {
            // printf("%d ", A[i].Chave);
            A_aux[counter] = A[i];
            counter++;
        }
    }

    // *A_aux = counter;
    printf("\n");
    for(int i = 0; i <= sizeof(A_aux); i ++) 
    {
        printf("%d ", A_aux[i].Chave);
    }
    printf("\n");

    heapSort(A_aux, sizeof(A_aux));

    A = A_aux;

    free(A_aux);
}

int main() {
    
    TItem *itens = (TItem *)malloc(6 * sizeof(TItem));

    // TItem itens[6];

    TItem item1, item2, item3, item4, item5, item6, item7;

    item1.Chave = 1;
    item2.Chave = 2;
    item3.Chave = 3;
    item4.Chave = 4;
    item5.Chave = 5;
    item6.Chave = 6;
    item7.Chave = 7;

    itens[0] = item3;
    itens[1] = item1;
    itens[2] = item2;
    itens[3] = item5;
    itens[4] = item6;
    itens[5] = item4;
    itens[6] = item7;

    for(int i = 0; i <= sizeof(itens); i ++) 
    {
        printf("%d ", itens[i].Chave);
    }

    printf("\n------------------------------\n");

    heapSort(itens, sizeof(itens));

    for(int i = 0; i <= sizeof(itens); i ++) 
    {
        printf("%d ", itens[i].Chave);
    }

    

    return 0;
}