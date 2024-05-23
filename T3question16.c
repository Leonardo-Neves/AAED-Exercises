#include <stdio.h>

#define INICIO 0
#define MAXTAM 1000

typedef int TChave;
typedef int TApontador;

typedef struct {
    TChave Chave;
} TItem;

typedef struct {
    TItem Item[MAXTAM];
    TApontador Primeiro, Ultimo;
} TLista;

void TLista_Inicia(TLista *pLista)
{
    pLista->Primeiro = INICIO;
    pLista->Ultimo = pLista->Primeiro;
}

int TLista_EhVazia(TLista *pLista)
{
    return (pLista->Primeiro == pLista->Ultimo);
}

int TLista_Tamanho(TLista *pLista) 
{
    return (pLista->Ultimo - pLista->Primeiro);
}

int TLista_Insere(TLista *pLista, TApontador p, TItem x)
{
    TApontador q;

    if((pLista->Ultimo == MAXTAM) || (p < pLista->Primeiro) || (p > pLista->Ultimo)) 
    {
        return 0;
    } 

    for(q = pLista->Ultimo - 1; q >= p; q--) 
    {
        pLista->Item[q+1] = pLista->Item[q];
    }

    pLista->Item[p] = x;
    pLista->Ultimo++;

    return 1;
}

int TLista_Retira(TLista *pLista, TApontador p, TItem *pX)
{
    TApontador q;

    if(TLista_EhVazia(pLista) || (p < pLista->Primeiro) || (p >= pLista->Ultimo)) 
    {
        return 0;
    }

    *pX = pLista->Item[p];

    for(q = p + 1; q < pLista->Ultimo; q++)
    {
        pLista->Item[q-1] = pLista->Item[q];
    }

    pLista->Ultimo--;

    return 1;
}

int TLista_Inverter(TLista *pLista) {

    if(TLista_EhVazia(pLista)) 
    {
        return 0;
    }

    int comeco = 0;
    int fim = pLista->Ultimo - 1;

    TItem auxiliar;
    
    while (comeco < fim) 
    {
        auxiliar = pLista->Item[comeco];
        pLista->Item[comeco] = pLista->Item[fim];
        pLista->Item[fim] = auxiliar;
        
        comeco++;
        fim--;
    }
    
    return 1;
}

int main() {

    TLista lista;

    TLista_Inicia(&lista);

    TItem item1, item2, item3;

    item1.Chave = 1;
    item2.Chave = 2;
    item3.Chave = 3;

    TLista_Insere(&lista, 0, item1);
    TLista_Insere(&lista, 1, item2);
    TLista_Insere(&lista, 2, item3);

    TLista_Inverter(&lista);

    for(int i = 0; i <= (lista.Ultimo- 1); i ++) 
    {
        printf("%d \n", lista.Item[i].Chave);
    }

    return 0;
}