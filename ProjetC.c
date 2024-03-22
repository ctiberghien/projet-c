#include <string.h>
#include "ProjetC.h"
#include "structure.h"
#include <stdlib.h>
#include <stdio.h>

void mv(char *s) {
    char* arg1 = substring(s);
    char* arg2 = malloc(sizeof(char)*(strlen(s)-strlen(arg1)));
    strncpy(arg2, s+strlen(arg1)+1, strlen(s)-strlen(arg1));

    assert(cheminValide(arg1));
    
    char* arg2Dossier = SubStringPath(arg2);
    char *aRenommer = malloc(strlen(arg2)-strlen(arg2Dossier));
    memmove(aRenommer, arg2+strlen(arg2Dossier), strlen(arg2)-strlen(arg2Dossier)+1);
    
    if(!strlen(arg2Dossier)==0) {
        if(arg2Dossier[0]!='/' || strlen(arg2Dossier)!=1) {
            assert(cheminValide(arg2Dossier));
            assert(!cheminEstFichier(arg2Dossier));
        }
    }
    
    noeud_courant_actuel=noeud_courant;
    cd(arg1);
    noeud* noeudSrc = noeud_courant;
    
    noeud_courant = noeud_courant_actuel;
     if(!strlen(arg2Dossier)==0) {
        if(arg2Dossier[0]!='/' || strlen(arg2Dossier)!=1) cd(arg2Dossier);
        else cd_b();
    }
    noeud* noeudDest = noeud_courant;
    
    noeud_courant=noeud_courant_actuel;

    mv_b(noeudSrc, noeudDest);
    noeudSrc->pere = noeudDest;
    strcpy(noeudSrc->nom,aRenommer);
    free(arg1);
    free(arg2);
    free(aRenommer);
    free(arg2Dossier);
}

void mv_b(noeud* src,noeud* dest) {
    //deplacement dans la destination
    liste_noeud* destAPlacer = dest->fils;
    if (destAPlacer!=NULL) {
        while (destAPlacer->succ!=NULL) {
            destAPlacer=destAPlacer->succ;
        }
        destAPlacer->succ = malloc(sizeof(liste_noeud));
        destAPlacer->succ->no = src;
    } else{
        destAPlacer=malloc(sizeof(liste_noeud));
        destAPlacer->no = src;
    }
    //on retire la listeNoeud du pere de src
    liste_noeud* noeudAretirer = src->pere->fils;
    liste_noeud* precedent = NULL;
    while(noeudAretirer!=NULL) {
        if(noeudAretirer->no==src) {
            if(precedent==NULL) {
                src->pere->fils = noeudAretirer->succ;
            } else {
                precedent->succ = noeudAretirer->succ;
            }
        }
        precedent = noeudAretirer;
        noeudAretirer = noeudAretirer->succ;
    }
}

void cp(char *s) {
    char* arg1 = substring(s);
    char* arg2 = malloc(sizeof(char)*(strlen(s)-strlen(arg1)));
    strncpy(arg2, s+strlen(arg1)+1, strlen(s)-strlen(arg1));

    char* arg2Dossier = SubStringPath(arg2);

    assert(cheminValide(arg1));
    
    if(!strlen(arg2Dossier)==0) {
        if(arg2Dossier[0]!='/' || strlen(arg2Dossier)!=1) {
            assert(cheminValide(arg2Dossier));
            assert(!cheminEstFichier(arg2Dossier));
        }
    }
    
    noeud_courant_actuel=noeud_courant;
    cd(arg1);
    noeud* noeudSrc = noeud_courant;
    
    noeud_courant = noeud_courant_actuel;

    if(!strlen(arg2Dossier)==0) {
        if(arg2Dossier[0]!='/' || strlen(arg2Dossier)!=1) cd(arg2Dossier);
        else cd_b();
    }

    noeud* noeudDest = noeud_courant;

    char *aRenommer = malloc(strlen(arg2)-strlen(arg2Dossier));
    memmove(aRenommer, arg2+strlen(arg2Dossier), strlen(arg2)-strlen(arg2Dossier)+1);

    if (noeudSrc->fils!=NULL) {
        mkdir(aRenommer);
        liste_noeud* tmp = noeud_courant->fils;
        while (tmp->succ!=NULL) 
        {
            tmp=tmp->succ;
        }
        tmp->no->fils=malloc(sizeof(liste_noeud));
        noeudDest=tmp->no;
        cp_aux(noeudSrc, noeudDest);
    } else if (noeudSrc->est_dossier) {
        mkdir(aRenommer);
    } else {
        touch(aRenommer);
    }

    //cp cours /td

    noeud_courant=noeud_courant_actuel;

    free(arg1);
    free(arg2);
    free(arg2Dossier);
    free(aRenommer);
}

void cp_aux(noeud* noeudACopier, noeud* endroitACopier) {
    liste_noeud* listDesFils=noeudACopier->fils;
    liste_noeud* listDesFilsDest=endroitACopier->fils;
    if (listDesFils!=NULL) {
        while(listDesFils->succ!=NULL) {
        noeud* nouveauNoeud = malloc(sizeof(noeud));
        nouveauNoeud->pere=endroitACopier;
        nouveauNoeud->est_dossier=listDesFils->no->est_dossier;
        strcpy(nouveauNoeud->nom, listDesFils->no->nom);
        nouveauNoeud->racine=listDesFils->no->racine;
        if (listDesFils->no->fils!=NULL) {
            nouveauNoeud->fils=malloc(sizeof(liste_noeud));
            cp_aux(listDesFils->no, nouveauNoeud);
        } else {
            nouveauNoeud->fils=NULL;
        }
        listDesFilsDest->no=malloc(sizeof(noeud));
        listDesFilsDest->no=nouveauNoeud;
        listDesFilsDest->succ=malloc(sizeof(liste_noeud));
        listDesFilsDest=listDesFilsDest->succ;
        listDesFils=listDesFils->succ;
        }
    }
    noeud* nouveauNoeud = malloc(sizeof(noeud));
    nouveauNoeud->pere=endroitACopier;
    nouveauNoeud->est_dossier=listDesFils->no->est_dossier;
    strcpy(nouveauNoeud->nom, listDesFils->no->nom);
    nouveauNoeud->racine=listDesFils->no->racine;
    if (listDesFils->no->fils!=NULL) {
        nouveauNoeud->fils=malloc(sizeof(liste_noeud));
        cp_aux(listDesFils->no, nouveauNoeud);
    } else {
        nouveauNoeud->fils=NULL;
    }
    listDesFilsDest->no=malloc(sizeof(noeud));
    listDesFilsDest->no=nouveauNoeud;
    listDesFilsDest->succ=NULL;
}
 
void mkdir(char* s){
    //verif format du nom
    assert(strcmp(s, ""));
    assert(verifAlphaNumerique(s));
    //char *chemin = SubStringPath(s);
    
    assert(!verifSiExiste(s));
    liste_noeud* tmp = noeud_courant->fils;
    noeud* newFile = malloc(sizeof(noeud));
    newFile->est_dossier=true;
    newFile->pere=noeud_courant;
    newFile->racine=noeud_courant->racine;
    newFile->fils=NULL;
    strcpy(newFile->nom, s);
    if(tmp!=NULL) {
        while(tmp->succ!=NULL) {
            tmp=tmp->succ;
        }
        liste_noeud* list = malloc(sizeof(liste_noeud));
        list->no=newFile;
        list->succ=NULL;
        tmp->succ=list;
    } else {
        liste_noeud* list = malloc(sizeof(liste_noeud));
        list->no=newFile;
        list->succ=NULL;
        noeud_courant->fils = list;
    }
}

void print_aux(noeud* l) {
    liste_noeud* tmp = l->fils;
    if (tmp!=NULL) {
        while(tmp->succ!=NULL) {    
            char type = 'D';
            if (!tmp->no->est_dossier) {
                type = 'F';
            }
            if (tmp->no->pere==noeud_courant->racine) {
                printf("Noeud %s (%c), pere %s\n", tmp->no->nom, type, "/");
            } else {
                printf("Noeud %s (%c), pere %s\n", tmp->no->nom, type, tmp->no->pere->nom);
            }
            if (tmp->no->est_dossier) {
                print_aux(tmp->no);
            }
            tmp=tmp->succ;
        }
        char type = 'D';
        if (!tmp->no->est_dossier) {
            type = 'F';
        }
        if (tmp->no->pere==noeud_courant->racine) {
            printf("Noeud %s (%c), pere %s\n", tmp->no->nom, type, "/");
        } else {
            printf("Noeud %s (%c), pere %s\n", tmp->no->nom, type, tmp->no->pere->nom);
        }
        if (tmp->no->est_dossier) {
            print_aux(tmp->no);
        }
    }
}

void print(){
    noeud* tmp = noeud_courant->racine;
    print_aux(tmp);
}

void ls() {
    liste_noeud* tmp = noeud_courant->fils;
    while(tmp!=NULL) {
        printf("%s\n", tmp->no->nom);
        tmp=tmp->succ;
    }
}

void touch(char* s) {
    //verif format du nom
    assert(strcmp(s, ""));
    assert(verifAlphaNumerique(s));
    //char *chemin = SubStringPath(s);
    
    assert(!verifSiExiste(s));
    liste_noeud* tmp = noeud_courant->fils;
    noeud* newFile = malloc(sizeof(noeud));
    newFile->est_dossier=false;
    newFile->pere=noeud_courant;
    newFile->racine=noeud_courant->racine;
    newFile->fils=NULL;
    strcpy(newFile->nom, s);
    if(tmp!=NULL) {
        while(tmp->succ!=NULL) {
            tmp=tmp->succ;
        }
        liste_noeud* list = malloc(sizeof(liste_noeud));
        list->no=newFile;
        list->succ=NULL;
        tmp->succ=list;
    } else {
        liste_noeud* list = malloc(sizeof(liste_noeud));
        list->no=newFile;
        list->succ=NULL;
        noeud_courant->fils = list;
    }
}

//Dans cette fonction, on va se déplacer dans l'arbre a l'aide du chemin dossier par dossier
//La fonction cd ci dessous est récursive et va prendre le chemin et couper le premier dossier du chemin
//et se déplacer dans le dossier correspondant puis va réappeller cd(s) avec le chemin coupé du premier chemin
//et continuer jusqu'a ce que chemin est vide
//Pour le cas avec un chemin absolu on va vérifier si le chemin possède un "/" au début, si oui c'est qu'on est 
//sur un chemin absolu, on va donc directement aller a la racine et effectuer le chemin à partir de là
void cd(char *s) {   
    //Vérifie si le chemin est valide
    if(!cheminValide(s)) {
        printf("erreur : %s\n",s);
    }
    assert(cheminValide(s));
    //Vérifie si le chemin pointe sur un fichier a la fin
    assert(!cheminEstFichier(s));

    char* copyS = malloc(sizeof(char)*(strlen(s)+1));
    strcpy(copyS, s);
    if (copyS[0]=='/') {
        noeud_courant = noeud_courant -> racine;
        memmove(copyS, copyS + 1, strlen(s));
    }
    if (copyS[0]=='.'&&copyS[1]=='.') {
        noeud_courant = noeud_courant -> pere;
        return;
    }
    char* dossier = SubStringFirstFolder(copyS);
    liste_noeud* tmp = noeud_courant->fils;
    while(tmp!=NULL) {
        if(strcmp(tmp->no->nom,dossier)==0) {
            noeud_courant = tmp->no;
            memmove(copyS, copyS + strlen(dossier), strlen(copyS)-strlen(dossier)+1);
            if(strlen(copyS)>0) memmove(copyS, copyS + 1, strlen(s));
            break;
        }
        tmp=tmp->succ;
    }
    free(dossier);
    if(strlen(copyS)==0) return;
    else cd(copyS);
    free(copyS);
}

void cd_b() {
    noeud_courant = noeud_courant->racine;
}



//On appelle la fonction qui creer un string avec le chemin absolu du noeud_courant et on l'affiche
void pwd() {
    char* chemin = cheminAbsolu();
    printf("%s\n", chemin);
}




void supprimer(char* nomdufichier) {
    assert(noeud_courant != NULL);

    liste_noeud* courant = noeud_courant->fils;
    liste_noeud* precedent = NULL;
    while (courant != NULL) {
        if (strcmp(courant->no->nom, nomdufichier) == 0) {
            if (precedent == NULL) {
                noeud_courant->fils = courant->succ;
            } else {
                precedent->succ = courant->succ;
            }
            free(courant->no); 
            free(courant);
            return;
        }
        precedent = courant;
        courant = courant->succ;
    }
}

//Cette fonction ne sert que pour rm et pour supprimer un dossier et est récursif,
//Dans un premier temps elle va vérifier si le noeud_courant est un fichier puis va le supprimer si c'est le cas
//Sinon, elle va creer un pointeur vers les fils du noeud courant, et un pointeur suivant qui va servir a aller dans 
//la listeNoeud suivant après que l'on ai supprimé tmp. 
//Ensuite on va recursivement faire la même chose avec les fils et supprimer quand on arrive a la fin
void rmRecursif() {
    liste_noeud* tmp = noeud_courant->fils;
    liste_noeud* suivant = NULL;
    while(tmp!=NULL) {
        suivant = tmp->succ;
        noeud_courant = tmp->no;
        rmRecursif();
        free(tmp->no);
        free(tmp);
        tmp=suivant;
    }
}


//Cette fonction permet de supprimer tout le sous arbre du noeud passé en argument et est récursif
void supprimer_fils(noeud* n) {
    if (n->fils==NULL) { // Si le noeud n'a pas de fils, on ne fait rien
        return;
    }
    liste_noeud* courant = n->fils;
    while (courant != NULL) { // On parcourt tous les fils du noeud
        supprimer_fils(courant->no); // On supprime récursivement les fils de chaque fils
        liste_noeud* temp = courant; // On supprime le fils courant
        courant = courant->succ;
        free(temp->no);
        free(temp);
    }
    n->fils = NULL; // On met à jour le pointeur fils du noeud courant
}


//Le principe de cette fonction est qu'elle va d'abord couper le chemin passé en argument en enlevant le dernier noeud
//donc si on a chemin/du/fichier cela donne chemin/du on a ensuite deux cas, 
//Premier cas, si le chemin pointe sur un fichier, on va dans le dossier qui contient le fichier puis on le supprime directement
//Deuxieme cas, si le chemin pointe sur un dossier, on va directement dans ce dossier et on supprime tout le sous arbre de ce 
//dossier a l'aide de rm recursif.
//Suite a cela, puisque l'on change le noeud_courant, on va retourner sur le dossier de base à l'aide de cd et si le noeud que
//l'on a supprimé était un dossier, on supprime ce dossier puisque rm recursif ne supprime que l'intérieur du dossier
void rm(char* s) {
    assert(cheminValide(s));
    if(s[0]=='/') {
        assert(!cheminIndiqueParent(s));
    }
    char *chemin = SubStringPath(s);
    char *cheminActuel = cheminAbsolu();
    char *nomdunoeud;
    if(strlen(chemin)==0) {
        nomdunoeud = malloc(strlen(s)+1);
        strcpy(nomdunoeud,s);
    } else {
        nomdunoeud = malloc(strlen(s)-strlen(chemin)+1);
        memmove(nomdunoeud, s+strlen(chemin), strlen(s)-strlen(chemin)+1);
    }
    if(cheminEstFichier(s)) {
        //ici on vérifie si le chemin va directement sur le fichier ex : rm fichier
        //on aura donc pas besoin de changer de dossier
        if(strlen(chemin)!=0) {
            cd(chemin);
        }
        supprimer(nomdunoeud);
    } else {
        cd(s);
        supprimer_fils(noeud_courant);
        if(strlen(chemin)==0) {
            cd(cheminActuel);
        } else if(strcmp(chemin,"/")==0) cd_b();
        else cd(chemin);
        supprimer(nomdunoeud);
    }
    //on vérifie si le dossier où l'on était à la base était la racine
    if(strlen(cheminActuel)>1)cd(cheminActuel);
    else cd_b();
    free(chemin);
    free(cheminActuel);
    free(nomdunoeud);
}


void rmToutLarbre() {
    cd_b();
    supprimer_fils(noeud_courant);
    free(noeud_courant);
}


