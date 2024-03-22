#include "ProjetC.h"
#include "structure.h"

noeud* noeud_courant;
noeud* noeud_courant_actuel;

int main(int argc, char **argv) {
    /*
     bool est_dossier;
    char nom[100];
    struct noeud* pere;
    struct noeud* racine;
    struct liste_noeud* fils;*/
    noeud* n = malloc(sizeof(noeud));
    n->est_dossier=true;
    n->pere=n;
    n->racine=n;
    n->fils=NULL;
    noeud_courant = n;

    FILE *fichier;
    char* ligne = malloc(sizeof(char)*100);
    assert(argc!=1);
    fichier = fopen(argv[1], "r");


    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.");
        return 1;
    }

    while (fgets(ligne, 100, fichier) != NULL) {
        int longueur = strlen(ligne)-1;
        if (ligne[longueur]==10) {
            ligne[longueur]='\0';
        }
        char* commande = substring(ligne);
        char* contenu = malloc(sizeof(char)*100);
        strncpy(contenu, ligne + strlen(commande), strlen(ligne)-strlen(commande)+1);
        memmove(contenu, contenu + 1, strlen(contenu));
        char* path = SubStringPath(contenu);
        char* name = malloc(sizeof(char)*100);
        strncpy(name, contenu+strlen(path), strlen(contenu)-strlen(path));
        name[strlen(contenu)-strlen(path)]='\0';

        printf("Commande :%s\n",commande);
        if (strcmp(commande, "ls")==0) {
            ls();
        }
        else if (strcmp(commande, "pwd")==0) {
            pwd();
        }
        else if (strcmp(commande, "print")==0) {
            print();
        }
        else if (strcmp(commande, "cd")==0 && strlen(ligne)==2) {
            cd_b();
        }
        else if (strcmp(commande, "touch")==0) {
            touch(name);
        }
        else if (strcmp(commande, "cd")==0 && strlen(ligne)>2) {
            cd(contenu);
        }
        else if (strcmp(commande, "mkdir")==0) {
            mkdir(name);
        }
        else if (strcmp(commande, "rm")==0) {
            rm(contenu);
        }
        else if (strcmp(commande, "cp")==0) {
            cp(contenu);
        }
        else if (strcmp(commande, "mv")==0) {
            mv(contenu);
        }
        free(path);
        free(contenu);
        free(name);
        free(commande);
    }
    free(ligne);
    fclose(fichier);
    free(fichier);
    rmToutLarbre();
}
