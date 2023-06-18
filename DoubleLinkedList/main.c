#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


typedef void Object;
typedef struct CelluleDbl* PCelluleDbl;
typedef struct CelluleDbl
{
    int valeur ;
    PCelluleDbl suivant ;
    PCelluleDbl precedent ;
} Listable;

int menu(int vide)
{
    int choix;
    printf("1. Creer une liste chainee d'entier \n2. Ajouter un element en tete de liste \n3. Ajouter un element en queue de liste \n4. Tier une liste \n5. Supprimer un element donne de la liste \n6. Supprimer les doublons de la liste \n7. Supprimer le dernier element de la liste \n8. Fusionner deux listes \n9. Inverser une liste \n10.Verifier si une liste est un palindrome \n11. Concatener deux listes\n12.Quitter\n");
    scanf("%d",&choix);
    if(choix != 1 && choix != 12 && vide == 1)
    {
        printf("\n\nVotre liste est vide\n\n") ;
        menu(vide) ;
    }
    else
        return choix;
}

void creerListe(PCelluleDbl l,int n)
{
    PCelluleDbl tete;
    PCelluleDbl p;
    int i;
    int donne;
    printf("Entrez le premier element: ");
    scanf("%d",&donne);
    tete=l;
    tete->valeur=donne;
    tete->suivant=NULL;
    tete->precedent=NULL;
    for(i=2; i<=n; i++)
    {
        p=malloc(sizeof(PCelluleDbl));
        printf("entrez l'element suivant : ");
        scanf("%d",&donne);
        p->valeur=donne;
        p->suivant=NULL;
        p->precedent=tete;
        tete->suivant=p;
        tete=p;
    }
}

void afficherliste(PCelluleDbl l)
{
    PCelluleDbl p;
    p=l;
    while(p!=NULL)
    {
        printf("%d   ",p->valeur);
        p=p->suivant;
    }
}

PCelluleDbl ajouter_tete_liste(PCelluleDbl l,int n)
{
    PCelluleDbl tete ;
    tete = malloc(sizeof(PCelluleDbl)) ;
    tete->valeur=n ;
    tete->precedent=NULL ;
    tete->suivant=l ;
    l->precedent=tete ;

    return tete ;
}

void ajouter_queu_liste(PCelluleDbl l,int n)
{
    PCelluleDbl queu ;
    PCelluleDbl p ;
    p=l ;
    queu = malloc(sizeof(PCelluleDbl)) ;
    queu->valeur=n ;
    queu->suivant=NULL ;
    while(p->suivant!=NULL)
    {
        p=p->suivant ;
    }
    p->suivant=queu ;
    queu->precedent=p ;
}

int rechercherListeDbl(PCelluleDbl l,Object*valeurRechercher,PCelluleDbl* addRecherche)
{
    PCelluleDbl p;
    int trouver=0;
    p=l;
    while(trouver==0 && p!=NULL)
    {
        if(p->valeur==valeurRechercher)
        {
            trouver=1;
            *addRecherche=p;
        }
        p=p->suivant;
    }
    return trouver;
}

PCelluleDbl supprimerElement(PCelluleDbl l, Object* donne)
{
    PCelluleDbl p=NULL ;

    if(l->valeur == donne)
    {
        p=l;
        l=l->suivant;
        l->precedent = NULL ;
        free(p);
        return l;

    }
    else
    {
        if(rechercherListeDbl(l,donne,&p))
        {
            if(p->suivant != NULL)
                p->suivant->precedent = p->precedent ;

            p->precedent->suivant = p->suivant ;
            free(p);
        }
        return l;
    }
}


PCelluleDbl trierListe(PCelluleDbl l)
{
    PCelluleDbl p,q;
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

PCelluleDbl supprimerDoublons(PCelluleDbl l)
{
    PCelluleDbl p,q ;
    if(l != NULL)
    {
        p = l ;
        while(p->suivant != NULL)
        {
            q = p->suivant ;
            while(p->valeur == q->valeur)
            {
                p->suivant = q->suivant ;
                if(q->suivant != NULL)
                    q->suivant->precedent = p ;
                free(q) ;
                q = p->suivant ;
                if(q == NULL)
                    return l ;
            }
            p = p->suivant ;
        }
    }
    return l ;
}

void supprimer_dernierElement(PCelluleDbl l)
{
    PCelluleDbl p ;
    PCelluleDbl precedent ;
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


PCelluleDbl fusionliste(PCelluleDbl l,PCelluleDbl s)
{
    PCelluleDbl Debut,tete,p;
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
        p->precedent=tete ;
        tete=p ;
    }
    tete->suivant=NULL ;
    return Debut ;
}

PCelluleDbl inverseliste(PCelluleDbl l)
{
    PCelluleDbl tete ,tmp;

    while(l != NULL)
    {
        tmp=l->precedent ;
        l->precedent=l->suivant ;
        l->suivant=tmp ;

        tete=l ;
        l=l->precedent ;
    }

    return tete ;
}

void concatenerListe(PCelluleDbl *firstListe , PCelluleDbl secondListe)
{
    PCelluleDbl p ;
    if(*firstListe == NULL)
        *firstListe = secondListe ;
    else
    {
        p = *firstListe ;
        while(p->suivant != NULL)
            p = p->suivant ;
    }
    p->suivant = secondListe ;
    secondListe->precedent = p ;
}

int NombreElements(PCelluleDbl l,PCelluleDbl *dernier)
{
    int nbr=1;
    while(l->suivant!=NULL)
    {
        nbr++;
        l=l->suivant;
    }
    *dernier=l;
    return nbr;
}

int Palindrome(PCelluleDbl l)
{
    PCelluleDbl premier=l,dernier;

    int i,valeurParcours=NombreElements(l,&dernier)/2;

    for(i=1; i<=valeurParcours; i++)
    {
        if(premier->valeur!=dernier->valeur)
            return 0;

        premier = premier->suivant ;
        dernier = dernier->precedent ;
    }
    return 1;

}

void main()
{
    PCelluleDbl Debutliste ;
    Debutliste = malloc(sizeof(PCelluleDbl));
    int retour_menu;
    retour_menu=menu(1);
    while(retour_menu!=12)
    {
        switch(retour_menu)
        {
        case 1 :
            printf("Votre liste comporte combien d'entier ? ");
            scanf("%d",&retour_menu);
            creerListe(Debutliste,retour_menu);
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
            Debutliste=trierListe(Debutliste);
            break;
        case 5 :
            printf("Element a supprimer : ");
            scanf("%d",&retour_menu);
            Debutliste = supprimerElement(Debutliste,retour_menu);
            break;
        case 6 :
            Debutliste=supprimerDoublons(trierListe(Debutliste));
            break;
        case 7 :
            supprimer_dernierElement(Debutliste);
            break ;
        case 8 :
            printf("Votre deuxieme liste comporte combien d'element ") ;
            scanf("%d",&retour_menu);
            PCelluleDbl Secondeliste ;
            Secondeliste = malloc(sizeof(PCelluleDbl)) ;
            creerListe(Secondeliste,retour_menu);
            Debutliste=supprimerDoublons(trierListe(Debutliste)) ;
            Secondeliste=supprimerDoublons(trierListe(Secondeliste)) ;
            Debutliste=fusionliste(Debutliste,Secondeliste) ;
            break;
        case 9 :
            Debutliste=inverseliste(Debutliste);
            break;
        case 10 :
            retour_menu=Palindrome(Debutliste);
            if(retour_menu==1)
                printf("\nLa liste est palyndrome") ;
            else
            {
                printf("\nLa liste n'est pas palyndrome") ;
            }
            retour_menu=12 ;
            break;
        case 11 :
            printf("Votre deuxieme liste comporte combien d'element ") ;
            scanf("%d",&retour_menu);
            PCelluleDbl Troisiemeliste ;
            Troisiemeliste = malloc(sizeof(PCelluleDbl)) ;
            creerListe(Troisiemeliste,retour_menu);
            concatenerListe(&Debutliste , Troisiemeliste) ;
            break ;
        default :
            printf("\nError veuillez entrer un nombre du menu") ;
        }
        printf("\n") ;
        if(retour_menu!=12)
            afficherliste(Debutliste);
        printf("\n\n") ;
        retour_menu=menu(0);
    }

}

