/************************************************
 * Nom : Estalella
 * Kevin : Kevin
 * Date: 04.05.2015
 * Version: 1.0
 * Titre: Tri avec piles
 * Description: Trier les éléments d'un tableau
 *              à l'aide des piles.
 ***********************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct Element Element;
struct Element
{
    int nombre;
    Element *suivant;
};

typedef struct Pile Pile;
struct Pile
{
    Element *premier;
};

Pile *initialiser();
void empiler(Pile *pile, int nvNombre);
int depiler(Pile *pile);
void afficherPile(Pile *pile);
int valeurPile(Pile *pile);
void remplirTableau(int MAX, int tableauValeur[MAX]);
void trierInserer(Pile *PileGauche, Pile *PileDroite, int valeur);

int main()
{
    int MAX = 10;
    int tableauValeur[MAX];

    remplirTableau(MAX, tableauValeur);

    Pile *PileGauche = initialiser();
    Pile *PileDroite = initialiser();

    int i=0;
    for(i=0;i<MAX;i++)
    {
        trierInserer(PileGauche, PileDroite, tableauValeur[i]);
    }

    while(valeurPile(PileDroite) != 0) {
        empiler(PileGauche, depiler(PileDroite));
    }

    printf("\nEtat de la pile :\n");
    afficherPile(PileGauche);

    return 0;
}

/*
 * Titre: trierElement
 *
 * Description: Trie un élément en se servant des piles
 *
 * Retour: Aucun
 */
void trierInserer(Pile *PileGauche, Pile *PileDroite, int valeur)
{
    while (valeurPile(PileDroite) > valeur) {
        empiler(PileGauche, depiler(PileDroite));
    }

    while ((valeurPile(PileGauche) < valeur) && (valeurPile(PileGauche) != 0)){
        empiler(PileDroite, depiler(PileGauche));
    }

    empiler(PileGauche, valeur);
}

/*
 * Titre: remplirTableau
 *
 * Description: Rempli un tableau avec des valeurs aléatoire de 1 à 100
 *
 * Retour: Aucun
 */
void remplirTableau(int MAX, int tableauValeur[MAX])
{
    srand(time(NULL));
    int i=0;
    for(i=0;i<MAX;i++)
        tableauValeur[i] = (rand() % 100) + 1;
}

/*
 * Titre: valeurPile
 *
 * Description: Permet de savoir quel est le premier nombre de la pile donnée en paramètre
 *
 * Retour: Entier. Retourne 0 si la pile est vide.
 */
int valeurPile(Pile *pile)
{
    if (pile->premier == NULL)
        return 0;
    else
        return pile->premier->nombre;
}

/*
 * Titre: *initialiser
 *
 * Description: Permet d'initialiser une pile
 *
 * Retour: Pile. Le premier élément de la pile ne pointe sur rien.
 */
Pile *initialiser()
{
    Pile *pile = malloc(sizeof(*pile));
    pile->premier = NULL;
    return pile;
}

/*
 * Titre: empiler
 *
 * Description: Empile l'élément passé dans paramètre dans la pile spécifiée
 *
 * Retour: Aucun
 */
void empiler(Pile *pile, int nvNombre)
{
    Element *nouveau = malloc(sizeof(*nouveau));
    if (pile == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }

    nouveau->nombre = nvNombre;
    nouveau->suivant = pile->premier;
    pile->premier = nouveau;
}

/*
 * Titre: dépiler
 *
 * Description: Dépile le premier élément de la pile passée en paramètre
 *
 * Retour: Entier. Retourne le nombre de l'élément que l'on dépile.
 */
int depiler(Pile *pile)
{
    if (pile == NULL)
    {
        exit(EXIT_FAILURE);
    }

    int nombreDepile = 0;
    Element *elementDepile = pile->premier;

    if (pile != NULL && pile->premier != NULL)
    {
        nombreDepile = elementDepile->nombre;
        pile->premier = elementDepile->suivant;
        free(elementDepile);
    }

    return nombreDepile;
}

/*
 * Titre: afficherPile
 *
 * Description: Affiche toutes la valeure de la pile passée en paramètre
 *
 * Retour: Aucun
 */
void afficherPile(Pile *pile)
{
    if (pile == NULL)
    {
        exit(EXIT_FAILURE);
    }
    Element *actuel = pile->premier;

    while (actuel != NULL)
    {
        printf("%d\n", actuel->nombre);
        actuel = actuel->suivant;
    }

    printf("\n");
}

