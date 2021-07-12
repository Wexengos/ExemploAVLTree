#ifndef ArvoreAVL_H
#define ArvoreAVL_H
#include <iostream>
#include <cstdlib>
#include <math.h>
#include "NoAVL.h"

using namespace std;

class ArvoreAVL
{
public:
    ArvoreAVL();
    ~ArvoreAVL();
    int max(int, int);
    int altura();
    int alturaNo(NoAVL*);
    int getBalanceada(NoAVL*);
    NoAVL* rotacaoSimplesEsquerda(NoAVL*);
    NoAVL* rotacaoSimplesDireita(NoAVL*);
    NoAVL* veOBalanceio(NoAVL*);
    void insere(int x);
    NoAVL* noMenorValor(NoAVL*);
    NoAVL* remove(NoAVL*, int);
    NoAVL* busca(NoAVL*, int);

private:
    NoAVL *raiz;
    bool balanceado;
    // funcoes auxiliares
    int auxAltura(NoAVL* p);
    NoAVL* auxInsere(NoAVL *p, int x);
    
    
};

#endif //ArvoreAVL_H