#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef void Object;

typedef struct Noeud* PNoeud;
typedef struct Noeud
{
    Object *valeur;
    PNoeud filsGauche;
    PNoeud filsdroit;
} Arbre;

typedef struct Cellule* PCellule;
typedef struct Cellule
{
    PNoeud valeur;
    PCellule suivant;
} Liste;

typedef struct
{
    Liste * tete;
    Liste * que;
} LFile;

int estFileVide(LFile* fl)
{
    if(fl->tete!=NULL && fl->que!=NULL) return 0;
    else return 1;
}

void enfiler(LFile *fl, PNoeud noeud)
{
    PCellule nouveau=malloc(sizeof(PCellule));
    nouveau->valeur=noeud;
    nouveau->suivant=NULL;
    if(estFileVide(fl)!=1) fl->que->suivant=nouveau;
    else fl->tete=nouveau;
    fl->que= nouveau;
}

PNoeud defiler(LFile *fl)
{
    PNoeud noeud=NULL;
    if(estFileVide(fl)!=1)
    {
        noeud=fl->tete->valeur;
        fl->tete=fl->tete->suivant;
    }
    if(fl->tete==NULL) fl->que=NULL;
    return noeud;
}

PNoeud creationNoeud(Object *obj,PNoeud fgauche,PNoeud fdroit)
{
    PNoeud nouveau= malloc(sizeof(PNoeud));
    nouveau->valeur=obj;
    nouveau->filsGauche=fgauche;
    nouveau->filsdroit=fdroit;
    return nouveau;
}

PNoeud creationFeuille(Object *obj)
{
    return creationNoeud(obj,NULL, NULL);
}

Object* renvoyerNoeud(PNoeud noeud)
{
    return noeud->valeur;
}

void parcoursPostfixe(PNoeud noeud)
{
    if(noeud!=NULL)
    {
        parcoursPostfixe(noeud->filsGauche);
        parcoursPostfixe(noeud->filsdroit);
        printf("%d ",renvoyerNoeud(noeud));
    }


}
void parcoursPrefixe(PNoeud noeud)
{
    if(noeud !=NULL)
    {
        printf("%d ",renvoyerNoeud(noeud));
        parcoursPrefixe(noeud->filsGauche);
        parcoursPrefixe(noeud->filsdroit);
    }

}
void parcoursInfixe(PNoeud noeud)
{
    if (noeud!=NULL)
    {
        parcoursInfixe (noeud->filsGauche);
        printf("%d ",renvoyerNoeud(noeud));
        parcoursInfixe(noeud->filsdroit);
    }
}
void parcoursLargeur(PNoeud noeud)
{
    LFile * fl = malloc(sizeof(LFile*));
    fl->tete=NULL;
    fl->que=NULL;
    enfiler(fl,noeud);
    PNoeud extrait;
    while(estFileVide(fl)!=1)
    {
        extrait =defiler(fl);
        printf("%d ",extrait->valeur);
        if(extrait->filsGauche != NULL) enfiler(fl,extrait->filsGauche);
        if(extrait->filsdroit !=NULL)   enfiler(fl,extrait->filsdroit);
    }
}

int rechercheBinaire(PNoeud n,Object * valeur)
{
    if (n != NULL)
    {
        if(renvoyerNoeud(n) == valeur) return 1;
        else
        {
            if(renvoyerNoeud(n) > valeur) rechercheBinaire(n->filsGauche,valeur);
            else rechercheBinaire(n->filsdroit,valeur);
        }
    }
    else return 0;
}

int main()
{
    PNoeud arbre = creationNoeud(15,
                                 creationNoeud(10,creationFeuille(8) ,creationFeuille(12)),
                                 creationNoeud(18,NULL,creationNoeud(19 , creationFeuille(17) , creationFeuille(20))));
    printf("\nLe parcours postfixe de l'arbre est :  ");
    parcoursPostfixe(arbre);
    printf("\nLe parcours prefixe de l'arbre est :  ");
    parcoursPrefixe(arbre);
    printf("\nLe parcours infixe de l'arbre est est :  ");
    parcoursInfixe(arbre);
    printf("\nLe parcours en largeur de l'arbre est:  ");
    parcoursLargeur(arbre);
    if (rechercheBinaire(arbre,9)) printf("\n\nElement retrouve");
    else printf("\nElement non retrouve");
    return 0;
}
