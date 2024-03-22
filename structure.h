#ifndef STRUCTURE_H
#define STRUCTURE_H
#include <stdbool.h>

struct noeud;
struct liste_noeud;

struct noeud{
    bool est_dossier;
    char nom[100];
    struct noeud* pere;
    struct noeud* racine;
    struct liste_noeud* fils;
};

struct liste_noeud{
    struct noeud* no;
    struct liste_noeud* succ;
};

typedef struct noeud noeud;
typedef struct liste_noeud liste_noeud;

extern noeud* noeud_courant;
extern noeud* noeud_courant_actuel;

extern bool cheminEstFichier(char *s);
extern bool cheminIndiqueParent(char* chemin);
extern char* cheminAbsolu();
extern bool cheminValide(char *s);
extern bool verifAlphaNumerique(char* s);
extern bool verifSiExiste(char* s);
extern char* SubStringPath(char* s);
extern char* SubStringFirstFolder(char* s);
extern char* substring(char *s);

#endif