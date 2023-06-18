#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Cellule* PCellule ;
typedef struct Cellule
{
    int valeur;
    PCellule suivant ;
} liste;

int menu()
{
    int choix;
    printf("1. Creer une liste chainee d'entier \n2. Ajouter un element en tete de liste \n3. Ajouter un element en queue de liste \n4. Tier une liste \n5. Supprimer un element donne de la liste \n6. Supprimer les doublons de la liste \n7. Supprimer le dernier element de la liste \n8. Fusionner deux listes \n9. Inverser une liste \n10.Verifier si une liste est un palindrome \n11.Quitter\n");
    scanf("%d",&choix);
    return choix;
}

void creerliste(PCellule l,int n)
{
    int i,donnee;
    PCellule tete ;
    PCellule p;
    tete=l ;
    printf("Entrer le premier element ") ;
    scanf("%d",&donnee);
    tete->valeur=donnee ;
    tete->suivant=NULL ;
    for(i=2; i<=n; i++)
    {
        p = malloc(sizeof(PCellule)) ;
        printf("Entrer l'element suivant ") ;
        scanf("%d",&donnee) ;
        p->valeur=donnee ;
        p->suivant=NULL ;
        tete->suivant=p ;
        tete=p ;
    }
}

int tailleliste(PCellule l, PCellule *d)
{
    int taille=1;
    while(l->suivant!=NULL)
    {
        taille++;
        l=l->suivant;
    }
    *d=l;
    return taille;
}

void afficherliste(PCellule l)
{
    PCellule p ;
    p=l ;
    while(p!=NULL)
    {
        printf("%d-> ",p->valeur) ;
        p=p->suivant ;
    }
}

PCellule ajouter_tete_liste(PCellule l,int n)
{
    PCellule tete ;
    tete = malloc(sizeof(PCellule)) ;
    tete->valeur=n ;
    tete->suivant=l ;
    return tete ;
}

void ajouter_queu_liste(PCellule l,int n)
{
    PCellule queu ;
    PCellule p ;
    p=l ;
    queu = malloc(sizeof(PCellule)) ;
    queu->valeur=n ;
    queu->suivant=NULL ;
    while(p->suivant!=NULL)
    {
        p=p->suivant ;
    }
    p->suivant=queu ;
}

void supprimerelement(PCellule l,int n)
{
    PCellule p ;
    p=l ;
    while(l->suivant!=NULL)
    {
        p=l->suivant ;
        if(p->valeur==n)
        {
            l->suivant=p->suivant ;
            free(p) ;
        }
        else
        {
            l=l->suivant ;
        }

    }
}

PCellule supprimertete(PCellule l)
{
    PCellule p ;
    p=l ;
    l=p->suivant ;
    free(p) ;
    return l ;
}

PCellule supprimerdoublons(PCellule l)
{
    PCellule p,q;
    if(l!=NULL)
    {
        p=l;
        while(p->suivant!=NULL)
        {
            q=p->suivant;
            while(p->valeur ==q->valeur)
            {
                p->suivant=q->suivant;
                free(q);
                q=p->suivant;
                if(q==NULL) return l;
            }
            p=p->suivant;
        }
    }
    return l;
}

void supprimer_dernierelement(PCellule l)
{
    PCellule p ;
    PCellule precedent ;
    p=l ;
    if(p!=NULL)
    {
        while(p->suivant!=NULL)
        {
            precedent=p ;
            p=p->suivant ;
        }
        precedent->suivant=NULL ;
        free(p) ;
    }
}

PCellule fusionliste(PCellule l,PCellule s)
{
    PCellule Debut,tete,p;
    if(l->valeur > s->valeur)
    {
        Debut = s ;
        s=s->suivant ;
    }
    else if(l->valeur == s->valeur)
    {
        Debut=l ;
        l=l->suivant ;
        s=s->suivant ;
    }
    else
    {
        Debut = l ;
        l=l->suivant ;
    }
    tete=Debut ;
    while(l!=NULL || s!=NULL)
    {
        if(l!=NULL && s!=NULL)
        {
            if(l->valeur > s->valeur)
            {
                p=s ;
                s=s->suivant ;
            }
            else if(l->valeur == s->valeur)
            {
                p=l ;
                l=l->suivant ;
                s=s->suivant ;
            }
            else
            {
                p=l ;
                l=l->suivant ;
            }
        }
        else if(l!=NULL && s==NULL)
        {
            p=l ;
            l=l->suivant ;
        }
        else
        {
            p=s ;
            s=s->suivant ;
        }
        tete->suivant=p ;
        tete=p ;
    }
    tete->suivant=NULL ;
    return Debut ;
}

PCellule inverseliste(PCellule l)
{
    PCellule p,temp,Debut;
    Debut=l ;
    p=Debut->suivant ;
    Debut->suivant=NULL ;
    while(p!=NULL)
    {
        temp=p->suivant ;
        p->suivant=Debut ;
        Debut=p ;
        p=temp ;
    }
    return Debut ;
}

PCellule trierliste(PCellule l)
{
    PCellule p,q;
    int permut=0 ;
    int temp ;
    do
    {
        p=l ;
        permut=0 ;
        while(p!=NULL)
        {
            q=p->suivant ;
            while(q!=NULL)
            {
                if(p->valeur > q->valeur)
                {
                    temp=p->valeur ;
                    p->valeur=q->valeur ;
                    q->valeur=temp ;
                }
                q=q->suivant ;
            }
            p=p->suivant;
        }
    }
    while(permut==1) ;
    return l ;
}

int palindrome(PCellule l)
{
    PCellule p, premier=l, dernier;
    int i, taille=tailleliste(l,&dernier)/2;
    for(i=1; i<=taille; i++)
    {
        if(premier->valeur!=dernier->valeur) return 0;
        if(i<taille)
        {
            premier=premier->suivant;
            p=premier;
            while(p->suivant!=dernier)
            {
                p=p->suivant;
            }
            dernier=p;
        }
    }
    return 1;
}


void main()
{
    PCellule Debutliste;
    Debutliste = malloc(sizeof(PCellule));
    int retour_menu;
    retour_menu=menu();
    while(retour_menu!=11)
    {
        switch(retour_menu)
        {
        case 1 :
            printf("Votre liste comporte combien d'entier ? ");
            scanf("%d",&retour_menu);
            creerliste(Debutliste,retour_menu);
            break;
        case 2 :
            printf("Vous voulez ajouter quel element ? ");
            scanf("%d",&retour_menu);
            Debutliste=ajouter_tete_liste(Debutliste,retour_menu);
            break;
        case 3 :
            printf("Vous voulez ajouter quel element ? ");
            scanf("%d",&retour_menu);
            ajouter_queu_liste(Debutliste,retour_menu);
            break;
        case 4 :
            Debutliste=trierliste(Debutliste);
            break;
        case 5 :
            printf("Element a supprimer : ");
            scanf("%d",&retour_menu);
            if(Debutliste->valeur==retour_menu)
                Debutliste=supprimertete(Debutliste) ;
            supprimerelement(Debutliste,retour_menu);
            break;
        case 6 :
            Debutliste=supprimerdoublons(trierliste(Debutliste));
            break;
        case 7 :
            supprimer_dernierelement(Debutliste);
            break ;
        case 8 :
            printf("Votre deuxieme liste comporte combien d'element ") ;
            scanf("%d",&retour_menu);
            PCellule Secondeliste ;
            Secondeliste = malloc(sizeof(PCellule)) ;
            creerliste(Secondeliste,retour_menu);
            Debutliste=supprimerdoublons(trierliste(Debutliste)) ;
            Secondeliste=supprimerdoublons(trierliste(Secondeliste)) ;
            Debutliste=fusionliste(Debutliste,Secondeliste) ;
            break;
        case 9 :
            Debutliste=inverseliste(Debutliste);
            break;
        case 10 :
            retour_menu=palindrome(Debutliste);
            if(retour_menu==1)
                    printf("\nLa liste est palyndrome") ;
            else
            {
                 printf("\nLa liste n'est pas palyndrome") ;
            }
            retour_menu=11 ;
        break;
        default :
        printf("\nError veuillez entrer un nombre du menu") ;
        }
        printf("\n") ;
        if(retour_menu!=11)
            afficherliste(Debutliste);
        printf("\n\n") ;
        retour_menu=menu();
    }

}
