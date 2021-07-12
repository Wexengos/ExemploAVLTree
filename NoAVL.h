#ifndef NOAVL_H
#define NOAVL_H

class NoAVL
{
public:
    NoAVL()                   {};
    ~NoAVL()                  {};
    void setInfo(int val)     { info = val;       };
    void setEsq(NoAVL *p)     { esq = p;          };
    void setDir(NoAVL *p)     { dir = p;          };
    int getAltura(NoAVL *p)   { if (p == NULL)
                                    return 0;
                                return p->altura; };
    void setAltura(int x)     { altura = x;       };   
    int getInfo()             { return info;      };
    NoAVL* getEsq()           { return esq;       };
    NoAVL* getDir()           { return dir;       };

private:
    int info;     // informação do No (int)
    NoAVL *esq;   // ponteiro para o filho a esquerda
    NoAVL *dir;   // ponteiro para o filho a direita
    int altura;   // altura da arvore a partir do no
};

#endif //NOAVL_H