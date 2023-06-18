#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void* Objet;

typedef struct Cellule* Pcellule;
typedef struct Cellule
{
    Objet valeur;
    Pcellule suivant;
} Liste;

typedef struct Fi* LFile;
typedef struct Fi
{
    Pcellule tete;
    Pcellule que;
};

Pcellule Empiler(Pcellule l, Objet donne)
{
    Pcellule tete;
    tete=malloc(sizeof(Pcellule));
    tete->valeur=donne;
    tete->suivant=l;
    return tete;
}

Objet* Depiler(Pcellule *l)
{
    Objet* donne;
    Pcellule p;
    donne=(*l)->valeur;
    p=*l;
    *l=(*l)->suivant;
    free(p);
    return donne;
}

Pcellule CreerMaPile(Pcellule p, int n)
{
    int i,donne;
    for(i=0; i<n; i++)
    {

        printf("\nEntrer l element a ajouter a la pile : ");
        scanf("%d",&donne);
        p=Empiler(p,donne);
    }
    return p;
}

int estFileVide(LFile Fi)
{
    if(Fi->tete!=NULL && Fi->que!=NULL)
        return 0;
    else
        return 1;
}

void InitialiserFile(LFile Fi)
{
    Fi->tete=NULL;
    Fi->que=NULL;
}

void enfiler(LFile Fi,Objet donne)
{
    Pcellule nouveau=malloc(sizeof(Pcellule));
    nouveau->valeur=donne;
    nouveau->suivant=NULL;
    if(estFileVide(Fi)!=1)
    {
        Fi->que->suivant=nouveau;
    }
    else
    {
        Fi->tete=nouveau;
    }
    Fi->que=nouveau;
}
Objet* Defiler(LFile Fi)
{
    Objet* donne=NULL;
    Pcellule p;
    if(estFileVide(Fi)!=1)
    {
        donne=Fi->tete->valeur;
        p=Fi->tete;
        Fi->tete=Fi->tete->suivant;
        free(p);
    }
    if(Fi->tete==NULL)
        Fi->que=NULL;
    return donne;
}

void CreerFile(LFile *f,int n)
{
    int i, donne;
    for(i=0; i<n; i++)
    {
        printf("\nEntrez l element a ajouter a la file : ");
        scanf("%d",&donne);
        enfiler(*f,donne);
    }
}


int main()
{
    printf("Hello world!\n");
    return 0;
}
