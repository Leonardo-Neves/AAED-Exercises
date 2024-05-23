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

// Pilha

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

void TFila_Enfileira_Usando_Pilha(TPilha *pPilha, TItem x) 
{
    TPilha_Empilha(pPilha, x);
}

void TFila_Desenfileira_Usando_Pilha(TPilha *pPilha, TPilha *pPilhaAuxiliar, TItem *outputItem) 
{
    for(int i = (pPilha->Topo - 1); i >= 0; i--) 
    {
        TPilha_Empilha(pPilhaAuxiliar, pPilha->Item[i]);
        TPilha_Desempilha(pPilha, &pPilha->Item[i]);
    }

    *outputItem = pPilhaAuxiliar->Item[pPilhaAuxiliar->Topo - 1];
    TPilha_Desempilha(pPilhaAuxiliar, &pPilhaAuxiliar->Item[pPilhaAuxiliar->Topo - 1]);

    for(int i = (pPilhaAuxiliar->Topo - 1); i >= 0; i--) 
    {
        TPilha_Empilha(pPilha, pPilhaAuxiliar->Item[i]);
        TPilha_Desempilha(pPilhaAuxiliar, &pPilhaAuxiliar->Item[i]);
    }
}

int main() {
    
    TPilha pilha1;
    TPilha pilha2;

    TPilha_Inicia(&pilha1);
    TPilha_Inicia(&pilha2);

    TItem item1, item2, item3;
    
    item1.Chave = 1;
    item2.Chave = 2;
    item3.Chave = 3;
    
    TFila_Enfileira_Usando_Pilha(&pilha1, item1);
    TFila_Enfileira_Usando_Pilha(&pilha1, item2);
    TFila_Enfileira_Usando_Pilha(&pilha1, item3);
    for(int i = (pilha1.Topo - 1); i >= 0; i--) 
    {
        printf("Item Antes: %d \n", pilha1.Item[i].Chave);
    }

    TItem outputItem;

    printf("=================================== \n");
    
    TFila_Desenfileira_Usando_Pilha(&pilha1, &pilha2, &outputItem);

    for(int i = (pilha1.Topo - 1); i >= 0; i--) 
    {
        printf("Item Depois: %d \n", pilha1.Item[i].Chave);
    }

    printf("Valor que estava na frente da fila: %d", outputItem.Chave);

    return 0;
}