#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstddef>
#include <vector>

#define M 2
#define MM (2 * M)

typedef int TChave;

typedef struct {
    TChave Chave;
} TItem;

typedef int TIndice;
typedef struct SNo *TArvoreB;

typedef struct SNo {
    TItem Item[MM];
    TArvoreB Pagina[MM + 1];
    TIndice n;
} TNo;

typedef struct {
    TItem Item;
    TArvoreB Pagina;
} TInfo;

int EhInterno(TArvoreB No)
{
    return (No != NULL) && (No->Pagina[0] != NULL);
}

int EhExterno(TArvoreB No)
{
    return (No != NULL) && (No->Pagina[0] == NULL);
}

TArvoreB Inicializa()
{
    return NULL;
}

TChave LeChave(TIndice i, TArvoreB No)
{
    return No->Item[i].Chave;
}

TInfo LeInfo(TIndice i, TArvoreB No)
{
    TInfo Info;
    Info.Item = No->Item[i];
    Info.Pagina = No->Pagina[i + 1];
    return Info;
}

void EscreveInfo(TIndice i, TArvoreB No, TInfo Info)
{
    No->Item[i] = Info.Item;
    No->Pagina[i + 1] = Info.Pagina;
}

TInfo LePromo(TIndice i, TArvoreB Pai, TIndice j, TArvoreB Filho)
{
    TInfo Info;
    Info.Item = Pai->Item[i];
    Info.Pagina = Filho->Pagina[j];
    return Info;
}

void EscrevePromo(TIndice i, TArvoreB Pai, TIndice j, TArvoreB Filho, TInfo Info)
{
    Pai->Item[i] = Info.Item;
    Filho->Pagina[j] = Info.Pagina;
}

TIndice PesquisaBinaria(TArvoreB No, TChave x)
{
    TIndice meio, esq, dir;
    esq = 0;
    dir = No->n - 1;
    while (esq <= dir) {
        meio = (esq + dir) / 2;
        if (x > LeChave(meio, No))
            esq = meio + 1;
        else if (x < LeChave(meio, No))
            dir = meio - 1;
        else
            return meio;
    }
    return esq;
}

TArvoreB Pesquisa(TArvoreB Raiz, TChave x)
{
    TArvoreB No;
    TIndice i;
    No = Raiz;
    while (No != NULL) {
        i = PesquisaBinaria(No, x);
        if ((i < No->n) && (x == LeChave(i, No)))
            return No;
        No = No->Pagina[i];
    }
    return NULL;
}

void InserePagina(TIndice i, TArvoreB No, TInfo Info)
{
    TIndice j;
    for (j = No->n - 1; j >= i; j--)
        EscreveInfo(j + 1, No, LeInfo(j, No));
    EscreveInfo(i, No, Info);
    No->n++;
}

void Divide(TIndice i, TArvoreB velhoNo, TInfo *Info)
{
    TArvoreB novoNo;
    TIndice j;

    novoNo = (TArvoreB) malloc(sizeof(TNo));
    novoNo->n = 0;

    for (j = M + 1; j < MM; j++)
        InserePagina(j - M - 1, novoNo, LeInfo(j, velhoNo));

    velhoNo->n = M + 1;

    if (i <= M + 1) {
        InserePagina(i, velhoNo, *Info);
        InserePagina(0, novoNo, LeInfo(M + 1, velhoNo));
    }
    else
        InserePagina(i - M - 1, novoNo, *Info);

    velhoNo->n = M;
    novoNo->Pagina[0] = velhoNo->Pagina[M + 1];

    (*Info).Item = velhoNo->Item[M];
    (*Info).Pagina = novoNo;
}

int InsereRecursivo(TItem x, TArvoreB No, TInfo *Info)
{
    TIndice i;
    if (No == NULL) {
        (*Info).Item = x;
        (*Info).Pagina = NULL;
        return 1;
    }
    else {
        i = PesquisaBinaria(No, x.Chave);
        if ((i < No->n) && (x.Chave == LeChave(i, No)))
            return 0; // retorna 0 caso o item ja estiver na arvore
        if (InsereRecursivo(x, No->Pagina[i], Info)) { // arvore aumentou na altura
        if (No->n < MM)
            { InserePagina(i, No, *Info); return 0; }
            else
            { Divide(i, No, Info); return 1; }
        }
        return 0;
    }
}

void Insere(TArvoreB *pRaiz, TItem x)
{
    TInfo Info;
    if (InsereRecursivo(x, *pRaiz, &Info)) {
        // arvore aumentou na altura
        TArvoreB No = (TArvoreB) malloc(sizeof(TNo));
        No->Pagina[0] = *pRaiz;
        EscreveInfo(0, No, Info);
        No->n = 1;
        *pRaiz = No;
    }
}

int main() {

    TArvoreB arvoreB = Inicializa();

    std::vector<int> values = { 13, 4, 8, 17, 21, 1, 2, 3, 5, 6, 7, 9, 10, 11, 12, 14, 15, 18, 19, 20, 22, 23 };

    for (int i = 0; i < values.size(); ++i) {
        TItem item;
        item.Chave = values[i];

        Insere(&arvoreB, item);
    }

    return 0;
}