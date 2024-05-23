#include <stdio.h>
#include <stdbool.h>

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

int TLista_Trocar_Item(TLista *pLista, TApontador index_item1, TApontador index_item2)
{
    if(TLista_EhVazia(pLista)) 
    {
        return 0;
    }

    TItem item_auxiliar = pLista->Item[index_item2];

    pLista->Item[index_item2] = pLista->Item[index_item1];
    pLista->Item[index_item1] = item_auxiliar;

    return 1;
}

int TLista_Ordenar_Impar_Par(TLista *pLista)
{
    if(TLista_EhVazia(pLista)) 
    {
        return 0;
    }

    // Par

    int counter = 0;

    while(counter != pLista->Ultimo)
    {   
        counter = 0;
        
        // Impar
        // O(n)
        for(int i = 0; i <= (pLista->Ultimo - 1); i ++) 
        {
            if(i % 2 != 0) 
            {
                if(pLista->Item[i].Chave > pLista->Item[i + 1].Chave)
                {
                    TLista_Trocar_Item(pLista, i, i + 1);
                }
            }
        }

        // Par
        // O(n)
        for(int i = 0; i <= (pLista->Ultimo - 1); i ++) 
        {
            if(i % 2 == 0) 
            {
                if(pLista->Item[i].Chave > pLista->Item[i + 1].Chave)
                {   
                    TLista_Trocar_Item(pLista, i, i + 1);
                }
            }
        }

        for(int i = 0; i <= (pLista->Ultimo - 1); i ++) 
        {
            printf("%d ", pLista->Item[i].Chave);
        }

        printf("\n");

        // O(n)
        // Verificando se o vetor esta ordenado
        for(int i = 0; i <= (pLista->Ultimo - 1); i ++) 
        {   
            if(pLista->Item[i].Chave <= pLista->Item[i+1].Chave) {
                counter++;
            } 
        }
    }

    return 1;
}

int main() {

    TLista lista;

    TLista_Inicia(&lista);

    // Criando a lista para teste

    TItem item1, item2, item3, item4, item5, item6, item7, item8, item9, item10, item11, item12, item13, item14, item15, item16, item17, item18, item19, item20;

    item1.Chave = 1;
    item2.Chave = 2;
    item3.Chave = 3;
    item4.Chave = 4;
    item5.Chave = 5;
    item6.Chave = 6;
    item7.Chave = 7;
    item8.Chave = 8;
    item9.Chave = 9;
    item10.Chave = 10;

    item11.Chave = 11;
    item12.Chave = 12;
    item13.Chave = 13;
    item14.Chave = 14;
    item15.Chave = 15;
    item16.Chave = 16;
    item17.Chave = 17;
    item18.Chave = 18;
    item19.Chave = 19;
    item20.Chave = 20;

    TLista_Insere(&lista, 0, item1);
    TLista_Insere(&lista, 1, item3);
    TLista_Insere(&lista, 2, item6);
    TLista_Insere(&lista, 3, item4);
    TLista_Insere(&lista, 4, item7);
    TLista_Insere(&lista, 5, item5);
    TLista_Insere(&lista, 6, item8);
    TLista_Insere(&lista, 7, item2);
    TLista_Insere(&lista, 8, item10);
    TLista_Insere(&lista, 9, item9);

    TLista_Insere(&lista, 10, item11);
    TLista_Insere(&lista, 11, item14);
    TLista_Insere(&lista, 12, item13);
    TLista_Insere(&lista, 13, item15);
    TLista_Insere(&lista, 14, item12);
    TLista_Insere(&lista, 15, item18);
    TLista_Insere(&lista, 16, item16);
    TLista_Insere(&lista, 17, item17);
    TLista_Insere(&lista, 18, item20);
    TLista_Insere(&lista, 19, item19);

    printf("Antes da ordenação: \n");

    for(int i = 0; i <= (lista.Ultimo- 1); i ++) 
    {
        printf("%d ", lista.Item[i].Chave);
    }

    printf("\n-------------------------------- \n");

    TLista_Ordenar_Impar_Par(&lista);

    printf("Depois da ordenação: \n");

    for(int i = 0; i <= (lista.Ultimo- 1); i ++) 
    {
        printf("%d ", lista.Item[i].Chave);
    }

    return 0;
}