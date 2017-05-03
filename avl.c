#include<stdlib.h>

typedef struct
{
    int chave;
    int altura;
    struct Arv * esq;
    struct Arv * dir;
} Arv;


int altura (Arv * r)
{
    if (r == NULL)
        return 0;
    else
    {
        int ae = altura (r->esq);
        int ad = altura (r->dir);
        if (ae < ad) return ad + 1;
        else return ae + 1;
    }
}


void roda_dir(Arv ** p)
{
    if((*p)->esq==NULL) return;
    Arv * q = (*p) -> esq;

    (*p) -> esq = q -> dir;
    q -> dir = (*p);

    (*p)->altura=altura(*p);
    q->altura=altura(q);

    *p=q;
}

void roda_esq(Arv ** p)
{
    if((*p)->dir==NULL) return;

    Arv * q = (*p) -> dir;

    (*p) -> dir = q -> esq;
    q -> esq = (*p);

    (*p)->altura=altura(*p);
    q->altura=altura(q);

    *p=q;
}

//retorna altura de um no nao nulo
int getaltura(Arv* p)
{
    return p!=NULL ? p -> altura : 0;
}

void balanco(Arv ** p)
{
    Arv * aux;
    int fb=getaltura((*p) -> esq ) - getaltura((*p) -> dir);

    if  (fb>= 2 )
    {
        aux=(*p) -> esq;
        fb=getaltura(aux -> esq)-getaltura(aux -> dir);
        if (fb<0)
            roda_esq(&((*p) -> esq));

        roda_dir(p);

    }
    else if (fb <= -2 )
    {
        aux=(*p) -> dir;
        fb=getaltura(aux -> esq)-getaltura(aux -> dir);
        if (fb>0)
            roda_dir(&((*p) -> dir));

        roda_esq(p);
    }


}

void insere(Arv ** raiz, int chave)
{

    if((*raiz)==NULL)
    {
        Arv * arv=(Arv*)malloc(sizeof(Arv));
        arv->esq=NULL;
        arv->dir=NULL;
        arv->chave=chave;
        *raiz=arv;
    }
    else if(chave<(*raiz)->chave)
        insere(&((*raiz)->esq),chave);
    else if(chave>(*raiz)->chave)
        insere(&((*raiz)->dir),chave);

    (*raiz)->altura=altura(*raiz);
    balanco(raiz);
}

Arv * menorvalor(Arv * raiz)
{
    if(raiz->esq==NULL)
        return raiz;
    else
        return menorvalor(raiz->esq);
}

void exclusao(Arv ** raiz,int chave)
{

    if ((*raiz) == NULL) return;

    //se a chave a ser excluida for menor que a chave da raiz
    //então ele vai ser excluido na subarvore esquerda
    if (chave < (*raiz)->chave)
        exclusao(&((*raiz)->esq), chave);

    //se a chave a ser excluida for maior que a chave da raiz
    //então ele vai ser excluido na subarvore direita
    else if (chave > (*raiz)->chave)
        exclusao(&((*raiz)->dir), chave);

    // se a chave for o mesmo da raiz então será deletado
    else
    {
        // nó com um ou nenhum filho
        if ((*raiz)->esq == NULL)
        {
            Arv *temp = (*raiz)->dir;
            free(*raiz);
            *raiz=temp;
            return;
        }
        else if ((*raiz)->dir == NULL)
        {
            Arv *temp = (*raiz)->esq;
            free(*raiz);
            *raiz=temp;
            return;
        }
        // nó com dois filhos: pega o menor dos maiores
        Arv* temp = menorvalor((*raiz)->dir);
        // copia a chave do menor dos maiores para a raiz
        (*raiz)->chave = temp->chave;

        // exclui o menor dos maiores
        exclusao(&((*raiz)->dir), temp->chave);
    }
    (*raiz)->altura=altura(*raiz);
    balanco(raiz);
}
