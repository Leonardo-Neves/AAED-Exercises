#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAXTAM 1000

typedef char TChave;
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

TPilha TPilha_Inverter(TPilha *pPilha)
{
    TPilha pPilhaAuxiliar;

    for(int i = (pPilha->Topo - 1); i >= 0; i --) 
    {
        TPilha_Empilha(&pPilhaAuxiliar, pPilha->Item[i]);
    }

    return pPilhaAuxiliar;
}

int main() {
    
    TPilha pilha;

    char palavra[30] = "arara";

    TPilha_Inicia(&pilha);

    char * letras = strtok(palavra, "");

    for(int i = 0; i <= strlen(letras); i ++) 
    {
        if(letras[i]) 
        {
            TItem item;
            item.Chave = letras[i];

            TPilha_Empilha(&pilha, item);
        }        
    }

    TPilha pilhaInvertida;

    pilhaInvertida = TPilha_Inverter(&pilha);

    bool isPalindromo = true;

    for(int i = (pilha.Topo - 1); i >= 0; i --) 
    {
        if(pilha.Item[i].Chave != pilhaInvertida.Item[i].Chave) {
            isPalindromo = false;
        }
    }

    if(isPalindromo) {
        printf("É um palíndromo\n");
    } else {
        printf("Não é um palíndromo\n");
    }

    return 0;
}