#include <stdio.h>

#define MAXTAM 1000

typedef int TChave;
typedef int TApontador;

typedef struct {
    TChave Chave;
} TItem;

typedef struct {
    TItem Item[MAXTAM];
    TApontador Topo;
} TPilha;

void TPilha_Inicia(TPilha *pPilha)
{
    pPilha->Topo = 0;
}

int TPilha_EhVazia(TPilha *pPilha)
{
    return (pPilha->Topo == 0);
}

int TPilha_Empilha(TPilha *pPilha, TItem x)
{
    if (pPilha->Topo == MAXTAM) {
        return 0;
    }
    
    pPilha->Item[pPilha->Topo] = x;
    pPilha->Topo++;
    
    return 1;
}

int TPilha_Desempilha(TPilha *pPilha, TItem *pX)
{
    if (TPilha_EhVazia(pPilha))
        return 0;
        
    pPilha->Topo--;
    *pX = pPilha->Item[pPilha->Topo];
    return 1;
}

int TPilha_Tamanho(TPilha *pPilha)
{
    return (pPilha->Topo);
}

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

int main() {
    
    TPilha pilha;
    TFila fila;
    
    // Adicionando elementos para o teste
    TFila_Inicia(&fila);
    TPilha_Inicia(&pilha);
    
    TItem item1, item2, item3;
    
    item1.Chave = 1;
    item2.Chave = 2;
    item3.Chave = 3;
    
    TFila_Enfileira(&fila, item1);
    TFila_Enfileira(&fila, item2);
    TFila_Enfileira(&fila, item3);

    TItem aux;

    // Salvando o objeto em outro vetor
    aux = fila.Item[fila.Frente];
    
    TPilha_Empilha(&pilha, aux);
    TFila_Desenfileira(&fila, &aux);
    
    aux = fila.Item[fila.Frente];
    
    TPilha_Empilha(&pilha, aux);
    TFila_Desenfileira(&fila, &aux);

    aux = fila.Item[fila.Frente];
    
    TPilha_Empilha(&pilha, aux);
    TFila_Desenfileira(&fila, &aux);

    // Enfileirando invertendo a ordem

    TFila_Inicia(&fila);

    aux = pilha.Item[pilha.Topo - 1];

    TFila_Enfileira(&fila, aux);
    TPilha_Desempilha(&pilha, &aux);

    aux = pilha.Item[pilha.Topo - 1];
    
    TPilha_Desempilha(&pilha, &aux);
    TFila_Enfileira(&fila, aux);

    aux = pilha.Item[pilha.Topo - 1];

    TFila_Enfileira(&fila, aux);
    TPilha_Desempilha(&pilha, &aux);

    for(int i = 0; i <= (fila.Tras - 1); i ++) {
        printf("Item: %d \n", fila.Item[i].Chave);
    }

    return 0;
}