#include "ArvoreAVL.h"
#include "NoAVL.h"
#include <cmath>


ArvoreAVL::ArvoreAVL()
{
    raiz = NULL;
}

ArvoreAVL::~ArvoreAVL()
{
    // destrutor vazio (só para avaliação)
}

int ArvoreAVL::max(int a, int b) 
{ 
    return (a > b)? a : b; 
}

//(*)alturas calculadas dinamicamente:
int ArvoreAVL::altura()
{
    if(raiz == NULL)
    {
        cout << "Arvore Vazia!" << endl;
        return -1;
    }
    else
        return auxAltura(raiz);
}
//(*)
int ArvoreAVL::alturaNo(NoAVL *p)
{
    if(p == NULL)
    {
        return -1;
    }
    else
        return auxAltura(p);
}
//(*)
int ArvoreAVL::auxAltura(NoAVL *p)
{
    if(p!=NULL)
    {
        int he = auxAltura(p->getEsq());
        int hd = auxAltura(p->getDir());

        return 1 + (he > hd ? he : hd);
    }
    else return -1;
}

int ArvoreAVL::getBalanceada(NoAVL *N) 
{ 
    if (N == NULL) 
        return 0;
    else 
        return N->getAltura(N->getDir()) - N->getAltura(N->getEsq()); 
} 

NoAVL* ArvoreAVL::rotacaoSimplesEsquerda(NoAVL *p)
{
    /*rotSimplesEsq(p)
        r = p->dir
        p->dir = r->esq
        r->esq = p */

    NoAVL* r = p->getDir();
    p->setDir(r->getEsq());

    r->setEsq(p);

    //atualiza alturas
    p->setAltura(max(p->getAltura(p->getEsq()), p->getAltura(p->getDir())) + 1);
    r->setAltura(max(r->getAltura(r->getEsq()), r->getAltura(r->getDir())) + 1);

    //raiz = q;
    return r;
}

NoAVL* ArvoreAVL::rotacaoSimplesDireita(NoAVL *p)
{
    /*rotSimplesDir(p)
        r = p->esq
        p->esq = r->dir
        r->dir = p */

    NoAVL* r = p->getEsq();
    p->setEsq(r->getDir());

    r->setDir(p);

    //atualiza alturas
    p->setAltura(max(p->getAltura(p->getEsq()), p->getAltura(p->getDir())) + 1);
    r->setAltura(max(r->getAltura(r->getEsq()), r->getAltura(r->getDir())) + 1);

    //raiz = q;
    return r;
}

NoAVL* ArvoreAVL::veOBalanceio(NoAVL* p)
{
    
    if((getBalanceada(p) == 2) && (  getBalanceada(p->getDir()) == 1  || 
                                    getBalanceada(p->getDir()) == 0  ))
    {
        balanceado = false;
        return rotacaoSimplesEsquerda(p);
    }
    // Rotacao simples a direita:

    if((getBalanceada(p) ==-2) && (  getBalanceada(p->getEsq()) == -1  ||
                                     getBalanceada(p->getEsq()) == 0  ))
        balanceado = false;
        return rotacaoSimplesDireita(p);

    // Rotacao dupla a esquerda:
    
    if((getBalanceada(p) == 2) && (  getBalanceada(p->getDir()) ==-1  ))
    {
        balanceado = false;
        p->setDir(rotacaoSimplesDireita(p->getDir()));
        return rotacaoSimplesEsquerda(p);
    }
        //p->setDir(rotacaoSimplesDireita(p->getDir()));
        //return rotacaoSimplesEsquerda(p);

    // Rotacao dupla a direita:

    if((getBalanceada(p) ==-2) && (  getBalanceada(p->getEsq()) == 1  ))
    {
        balanceado = false;
        p->setEsq(rotacaoSimplesEsquerda(p->getEsq()));
        return rotacaoSimplesDireita(p);
    }
        //p->setEsq(rotacaoSimplesEsquerda(p->getEsq()));
        //return rotacaoSimplesDireita(p);

    balanceado = true;
    return p;
}

void ArvoreAVL::insere(int x)
{
    raiz = auxInsere(raiz, x);
}

NoAVL* ArvoreAVL::auxInsere(NoAVL *p, int x)
{   
    if(p == NULL)
    {
        p = new NoAVL();
        p->setInfo(x);
        p->setEsq(NULL);
        p->setDir(NULL);
        p->setAltura(1);
    } 

    if(x < p->getInfo())
        p->setEsq(auxInsere(p->getEsq(), x));
    else if(x > p->getInfo())
        p->setDir(auxInsere(p->getDir(), x));
    else //valor igual, retorna pois não pode na AVL
        return p;
    
    // atualiza altura desse no ancestral:
    p->setAltura(1 + max(p->getAltura(p->getEsq()), p->getAltura(p->getDir())));
    
    // checa se o No esta balanceado
    
    return veOBalanceio(p);
}

NoAVL* ArvoreAVL::noMenorValor(NoAVL* p)
{
    NoAVL* atual = p;

    //desce até achar o nó mais à esquerda (i.e., cuja chave tem o menor valor)
    while(atual->getEsq() != NULL)
        atual = atual->getEsq();

    return atual;
}

//Função que remove o nó localizado na sub-árvore de raiz "raiz", e com valor "x"
NoAVL* ArvoreAVL::remove(NoAVL* raiz, int x)
{
    if(raiz == NULL)
        return raiz;
    
    //busca o no a ser removido na arvore:
    if(x < raiz->getInfo())
        raiz->setEsq(remove(raiz->getEsq(), x));

    if(x > raiz->getInfo())
        raiz->setDir(remove(raiz->getDir(), x));

    else
    {
        //no com apenas um filho ou nenhum filho.
        if((raiz->getEsq() == NULL) ||
           (raiz->getDir() == NULL))
        {
            NoAVL* temp = raiz->getEsq() ?
                          raiz->getEsq() :
                          raiz->getDir();

            //caso não tenha filho
            if(temp == NULL)
            {
                temp = raiz;
                raiz = NULL;
            }
            else //caso tenha apenas um filho
            raiz->setInfo(temp->getInfo());

            delete [] temp;
        }
        else
        {
            //no com dois filhos, pega o menor no da subarvore direita (sucessor em-ordem)
            NoAVL* temp = noMenorValor(raiz->getDir());
            //copia o sucessor em-ordem para o no atual
            raiz->setInfo(temp->getInfo());
        }
    }

    //se vazio:
    if(raiz == NULL)
        return raiz;

    raiz->setAltura(1 + max(raiz->getAltura(raiz->getEsq()), 
                            raiz->getAltura(raiz->getEsq())));

    //verifica balanceamento, e faz as rotaçoes
    return veOBalanceio(raiz);
}

NoAVL* ArvoreAVL::busca(NoAVL* raiz, int x)
{
    //casos base: arvore vazia/chave na raiz
    if(raiz == NULL || raiz->getInfo() == x)
        return raiz;
    
    if(raiz->getInfo() < x)
        return busca(raiz->getDir(), x);

    return busca(raiz->getEsq(), x);
}