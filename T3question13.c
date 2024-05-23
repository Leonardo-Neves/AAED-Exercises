#include <stdio.h>

#define MAXTAM 1000

typedef int TChave;
typedef int TApontador;

typedef struct {
    TChave Chave;
} TItem;

typedef struct {
    TItem Item[MAXTAM];
    TApontador Frente, Tras;
} TFila;

void TFila_Inicia(TFila *pFila)
{
    pFila->Frente = 0;
    pFila->Tras = pFila->Frente;
}

int TFila_EhVazia(TFila *pFila)
{
    return (pFila->Frente == pFila->Tras);
}

int TFila_Tamanho(TFila *pFila)
{
    return ((pFila->Tras >= pFila->Frente) ? (pFila->Tras - pFila->Frente) : (MAXTAM + pFila->Tras - pFila->Frente));
}

int TFila_Enfileira(TFila *pFila, TItem x)
{
    if (pFila->Frente == (pFila->Tras + 1) % MAXTAM) {
        return 0;
    }
    
    pFila->Item[pFila->Tras] = x;
    pFila->Tras = (pFila->Tras + 1) % MAXTAM;
    
    return 1;
}

int TFila_Desenfileira(TFila *pFila, TItem *pX)
{
    if (TFila_EhVazia(pFila)) {
        return 0;
    }
    
    *pX = pFila->Item[pFila->Frente];
    pFila->Frente = (pFila->Frente + 1) % MAXTAM;
    
    return 1;
}

void TPilha_Empilha_Usando_Fila(TFila *pFila, TItem x)
{
    TFila_Enfileira(pFila, x);
}

TItem TPilha_Desempilha_Usando_Fila(TFila *pFila, TFila *pFilaAuxiliar)
{
    TItem output_item;
    
    for(int i = 0; i <= (pFila->Tras); i++) 
    {
        if(i == (pFila->Tras - 1)) 
        {
            output_item = pFila->Item[i];
            TFila_Desenfileira(pFila, &pFila->Item[i]);
        } 
        else 
        {
            TPilha_Empilha_Usando_Fila(pFilaAuxiliar, pFila->Item[i]);
            TFila_Desenfileira(pFila, &pFila->Item[i]);
        }
    }

    TFila_Inicia(pFila);

    for(int i = 0; i < (pFilaAuxiliar->Tras); i++) 
    {
        TPilha_Empilha_Usando_Fila(pFila, pFila->Item[i]);
    }

    return output_item;
}

int main() {
    
    TFila fila1;
    TFila fila2;
    
    // Adicionando elementos para o teste
    TFila_Inicia(&fila1);
    TFila_Inicia(&fila2);
    
    TItem item1, item2, item3;
    
    item1.Chave = 1;
    item2.Chave = 2;
    item3.Chave = 3;
    
    TFila_Enfileira(&fila1, item1);
    TFila_Enfileira(&fila1, item2);

    // Desmostração da implementação

    TPilha_Empilha_Usando_Fila(&fila1, item3);

    printf("Tamanho: %d \n", TFila_Tamanho(&fila1));

    for(int i = 0; i < (fila1.Tras); i++) 
    {
        printf("Resultado após empilhar - Item: %d \n", fila1.Item[i]);
    }

    printf("============================================ \n");

    TItem output_item;

    output_item = TPilha_Desempilha_Usando_Fila(&fila1, &fila2);

    for(int i = 0; i < (fila1.Tras - 1); i++) 
    {
        printf("Resultado após desempilhado - Item: %d \n", fila1.Item[i]);
    }

    printf("Item desempilhado - Item: %d \n", output_item.Chave);

    return 0;
}