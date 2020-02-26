#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define TAILLE_MAX 1000

//#include "dico.txt"

/*void my_putchar(char c)
{
    write(1, &c, 1);
}*/


char lireCaractere() 
{ 
    char caractere = 0;
 
    caractere = getchar();
    caractere = toupper(caractere); 
    // On met la lettre en majuscule si elle ne l'est pas déjà
    //On lit les autres caractères mémorisés un à un jusqu'au \n
    while (getchar() != '\n') ;
 
    return caractere; 
}

void charEtoile(char motSecret[], char *motCache)
{
    int i = 0;
    while ( i < strlen(motSecret))
    {
        motCache[i]  = '*';
        i++;
    }
    motCache[i] = '\0';
}

int recherche(char maLettre, char motSecret[], char *motCache) {
    int trouver = 0;

    for (int i = 0; motSecret[i] != '\0'; i++) {
        if (maLettre == motSecret[i]) {
            motCache[i] = maLettre;
            trouver = 1;
        }
    }
    return (trouver);
}

char* choisirmot() {
    int choix = 0;
    char chaine[TAILLE_MAX] = "";
    FILE* dico = NULL;
    dico = fopen("dico.txt", "r");
    if (dico != NULL)
    {
        fgets(chaine, TAILLE_MAX, dico);
        printf("%s", chaine);
        fclose(dico); 
    }
    else
        printf("Impossible d'ouvrir le fichier dico.txt");
    return (chaine);
}

int main (int argc, char*  argv[]) 
{
    char maLettre = 0;
    char *motSecret = choisirmot();
    char *motCache = malloc(sizeof(char) * strlen(motSecret) + 1);
    int coupsRestants = 10;
    int i = 0;
 
    charEtoile(motSecret, motCache);
    printf("Bienvenue dans le jeu du Pendu\n\n");

    while (coupsRestants > 0 && strcmp(motCache, motSecret)){
        printf("il vous reste %d chances\n", coupsRestants);
        printf("%s\n\n", motCache);
        printf("\nProposez une lettre : ");
        maLettre = lireCaractere();
        printf("%c\n", maLettre);
        if(!recherche(maLettre, motSecret, motCache)) {
            coupsRestants--;
        }
    }
    if (coupsRestants == 0)
        printf("\n\nPerdu ! Le mot etait : %s\n", motSecret);
    else
        printf("\n\nGagné ! Le mot etait bien : %s\n", motSecret); 
    return 0;
}
