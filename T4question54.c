#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int TChave;

typedef struct {
    TChave Chave;
} TItem;

void Contagem(TItem *A, int n, int k)
{
    TItem *B;
    TChave *C;
    
    int i, j;
    
    B = (TItem *) malloc(n * sizeof(TItem));
    C = (TChave *) malloc((k + 1) * sizeof(TChave));
    
    for(i = 0; i <= k; i++)
        C[i] = 0;

    for(j = 0; j < n; j++)
        C[A[j].Chave]++;   
    
    for(i = 1; i <= k; i++)
        C[i] += C[i - 1];

    for(j = n - 1; j >= 0; j--)
        B[--C[A[j].Chave]] = A[j];
    
    for(j = 0; j < n; j++)
        A[j] = B[j];
    
    free(B);
    free(C);
}

int main() {

    srand(time(NULL));

    const int n = 10;
    const int expressao = (n*n)-1;
    TItem *itens = (TItem *)malloc(expressao * sizeof(TItem));

    for(int i = 0; i < (n*n - 1); i ++) 
    {   
        int valor_randomico = rand();

        if(valor_randomico != 0) 
        {
            itens[i].Chave = rand();
        }
    }

    int valor_maximo = 0;

    for(int i = 0; i < (n*n - 1); i ++) 
    {   
        if(valor_maximo < itens[i].Chave) 
        {
            valor_maximo = itens[i].Chave;
        }
    }

    printf("Antes da ordenação: \n");
    for(int i = 0; i < (n*n - 1); i ++)
    {
        printf("%d ", itens[i].Chave);
    }

    Contagem(itens, n*n - 1, valor_maximo);

    printf("\n-----------------------\n");
    printf("Depois da ordenação: \n");
    for(int i = 0; i < (n*n - 1); i ++)
    {
        printf("%d ", itens[i].Chave);
    }

    return 0;
}