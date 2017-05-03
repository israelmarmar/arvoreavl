#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<math.h>
#include"avl.c"

//move o cursor para a cordenada xy
void gotoxy(int x, int y)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD)
    {
        x-1,y-1
    });
}


//imprime as ligacoes da esquerda
void printlinkl(int x0, int x1, int y0, int y1)
{
    if(y0<y1+1)
    {
        gotoxy(x0,y0);
        printf("/");
        printlinkl(x0-1,x1,y0+1,y1);
    }
    else if(x0>x1)
    {
        gotoxy(x0,y0);
        printf("___");
        printlinkl(x0-1,x1,y0,y1);
    }
}

//imprime as ligacoes da direita
void printlinkr(int x0, int x1, int y0, int y1)
{
    if(y0+1<y1)
    {
        gotoxy(x0,y0);
        printf("\\");
        printlinkr(x0+1,x1,y0+1,y1);
    }
    else if (x0<x1)
    {
        gotoxy(x0,y0);
        printf("___");
        printlinkr(x0+1,x1,y0,y1);
    }
}

//imprimir prefixado arvore a partir da coordenada xy
void prefix(Arv * arv,int x,int y)
{
    if(arv!=NULL)
    {
        gotoxy(x,y);
        printf("(%d)",arv->chave);

        if(arv->esq!=NULL)
            printlinkl(x+1, x-8-pow(arv->altura,2), y+1, y+8);

        if(arv->dir!=NULL)
            printlinkr(x+2, x+8+pow(arv->altura,2), y+1, y+8);

        prefix(arv->esq,x-8-pow(arv->altura,2),y+8);
        prefix(arv->dir,x+8+pow(arv->altura,2),y+8);
    }
    printf("\n\n\n\n\n");
}

void inserearq(Arv ** raiz)
{
    int n;

    FILE*arq=fopen("nos.txt","r");

    if(arq==NULL)
    {
        printf("arquivo nao encontrado");
        return;
    }
    else
    {
        while(fscanf(arq,"%d\n",&n)!=EOF)
        {
            insere(raiz,n);
        }
    }
}

void exclusaoarq(Arv ** raiz)
{
    int n;

    FILE*arq=fopen("delnos.txt","r");

    if(arq==NULL)
    {
        printf("arquivo nao encontrado");
        return;
    }
    else
    {
        while(fscanf(arq,"%d\n",&n)!=EOF)
        {
            exclusao(raiz,n);
        }
    }
}

void printmenu()
{
    printf("1: inserir nos do arquivo\n");
    printf("2: excluir do arquivo\n");
    printf("3: imprimir\n");
}

int main()
{
    int cmd=1;
    Arv * arv=NULL;

    printmenu();

    while(cmd<=3 && cmd>=1)
    {
        printf("comando: ");
        scanf("%d", &cmd);
        switch (cmd)
        {
        case 1 :
            inserearq(&arv);
            printf("inseridos\n");
            break;

        case 2 :
            exclusaoarq(&arv);
            printf("excluido\n");
            break;

        case 3 :
            system("cls");
            system("mode con:cols=300 lines=100");
            prefix(arv,90,1);
            printmenu();
            break;

        default :
            printf ("saindo!\n");
        }
    }

}
