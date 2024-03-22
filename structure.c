#include "structure.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

bool cheminValide(char *s) {
    if(strlen(s)==2 && s[0]=='.' && s[1]=='.') return true;
    if(strlen(s)==1 && s[0]=='/') return true;
    //On crée une copie du string du chemin 
    char* copyS = malloc(sizeof(char)*(strlen(s)+1));
    strcpy(copyS, s);
    //On créer un pointeur vers les fils du noeud_courant
    liste_noeud* tmp = noeud_courant->fils;
    //Si le chemin est un chemin absolu, on part de la racine pour faire le chemin correspondant
    if (s[0]=='/') {
        tmp = noeud_courant->racine->fils;
        memmove(copyS, copyS+1, strlen(copyS));
    }
    //On récupère le nom du premier dossier du chemin
    char *tmp2 = SubStringFirstFolder(copyS);
    //On retire du chemin passé en argument le nom du premier dossier 
    //ex : chemin/du/fichier -> du/fichier
    strncpy(copyS, copyS+strlen(tmp2), strlen(copyS) - strlen(tmp2)+1);
    if(copyS[0]=='/') memmove(copyS, copyS+1, strlen(copyS));
    
    //On vérifie pour chaque fils de tmp s'il y en a un qui correspond si oui, on change le pointeur tmp vers le fils correspondant
    //et on continue la boucle avec ce même fils en coupant à chaque fois le nom du dossier correspondant dans copyS jusqu'a ce qu'il soit vide
    //Si la boucle s'arrête on return false puisqu'on a pas trouvé de fils correspondant sinon si le copyS est vide cela veut dire que l'on a 
    //fait tout le chemin sans faute donc on return true
    while(tmp!=NULL) {
        if (strcmp(tmp->no->nom, tmp2)==0) {
            if(strlen(copyS)==0) {
                free(copyS);
                free(tmp2);
                return true;
            }
            free(tmp2);
            tmp2 = SubStringFirstFolder(copyS);
            if(strcmp(tmp2,copyS)==0) {
                free(copyS);
                free(tmp2);
                return true;
            }
            strncpy(copyS, copyS+strlen(tmp2), strlen(copyS) - strlen(tmp2)+1);
            if(copyS[0]=='/') {
                memmove(copyS, copyS+1, strlen(copyS));
            }
            tmp = tmp->no->fils;
        } else tmp=tmp->succ;
    }
    free(copyS);
    free(tmp2);
    return false;
}

bool cheminIndiqueParent(char* chemin) {
    // On récupere le chemin absolu du noeud_courant
    char *tmp1 = cheminAbsolu();
    // On vérifie si le chemin que l'on veut comparé est plus grand que le chemin du noeud_courant pour éviter une comparaison inutile
    if(strlen(chemin)<strlen(tmp1)) {
        // On vérifie si le chemin passé en argument est égale au chemin du noeud_courant
        // exemple : chemin = chemin/du
        // noeud_courant = chemin/du/fichier 
        // Si on prend les n premier caractere de noeud_courant avec n = strlen(chemin) et qu'ils sont égale a chemin cela veut dire que chemin indique un parent du noeud_courant
        // Ici chemin indique bien un parent de noeud_courant
        if(strncmp(tmp1, chemin, strlen(chemin))==0) {
            free(tmp1);
            return true;
        } 
    }
    free(tmp1);
    return false;
}

bool cheminCorrespondFilsDansNoeudCourant(char* chemin) {
    char parent[100]; 
    for(int i=0; i<strlen(chemin); i++) {
        if(chemin[i]!='/') {
            parent[i] = chemin[i];
        }
    }
    liste_noeud* tmp = noeud_courant->fils;
    while(tmp!=NULL) {
        if(strcmp(tmp->no->nom, parent)==0) {
            return true;
        }
        tmp = tmp -> succ;
    }
    return false;
}

bool cheminEstFichier(char *s) {
    //On crée une copie du string du chemin 
    char* copyS = malloc(sizeof(char)*(strlen(s)+1));
    strcpy(copyS, s);
    //On créer un pointeur vers les fils du noeud_courant
    liste_noeud* tmp = noeud_courant->fils;
    //Si le chemin est un chemin absolu, on part de la racine pour faire le chemin correspondant
    if (s[0]=='/') {
        tmp = noeud_courant->racine->fils;
    }
    //On récupère le nom du premier dossier du chemin
    char *tmp2 = SubStringFirstFolder(copyS);
    //On retire du chemin passé en argument le nom du premier dossier 
    //ex : chemin/du/fichier -> du/fichier
    memmove(copyS, copyS + strlen(tmp2), strlen(copyS) - strlen(tmp2)+1);
    if(copyS[0]=='/') memmove(copyS, copyS+1, strlen(copyS)+1);
    //Ici on fait pareil que cheminValide mais on vérifie aussi que copyS est vide et aussi que le noeud est un fichier puisque 
    //copyS est vide que si on a fait le chemin entier, si tmp est un fichier c'est que le chemin indique un fichier a sa fin
    while(tmp!=NULL) {
        if (strcmp(tmp->no->nom, tmp2)==0) {
            if(strlen(copyS)==0) {
                if(!tmp->no->est_dossier) {
                    free(tmp2);
                    free(copyS);
                    return true;
                }
                free(tmp2);
                free(copyS);
                return false;
            }
            free(tmp2);
            tmp2 = SubStringFirstFolder(copyS);
            memmove(copyS, copyS + strlen(tmp2), strlen(copyS) - strlen(tmp2));
            if(copyS[0]=='/') {
                memmove(copyS, copyS+1, strlen(copyS)+1);
            }
            tmp = tmp->no->fils;
        } else tmp=tmp->succ;
    }
    free(copyS);
    free(tmp2);
    return false;
}

char* cheminAbsolu() {
    if(noeud_courant==noeud_courant->racine) {
        char* chemin = malloc(sizeof(char)*2);
        chemin[0] = '/';
        chemin[1] = '\0';
        return chemin;
    }
    char* chemin = malloc(sizeof(char)*1);
    chemin[0] = '\0';
    noeud* tmp = noeud_courant;
    while (tmp!=noeud_courant->racine) {
        char temp[100];
        strcpy(temp, tmp->nom);
        strcat(temp, "/");
        strcat(temp, chemin);
        chemin = realloc(chemin, strlen(chemin)*sizeof(char)+strlen(temp)*sizeof(char));
        strcpy(chemin, temp);
        tmp = tmp->pere;
    }
    memmove(chemin + 1, chemin, strlen(chemin)-1);
    chemin[0] = '/';
    return chemin;
}

bool verifAlphaNumerique(char* s) {
    int i = 0;
    while(s[i]!='\0') {
        if (!(s[i]>47 && s[i]<58) || !(s[i]>64 && s[i]<91) || !(s[i]>96 || s[i]<123)) return true;
    }
    return false;
}

bool verifSiExiste(char* s) {
    liste_noeud* tmp = noeud_courant->fils;
    if(tmp!=NULL) {
        while(tmp->succ!=NULL) {
            if (strcmp(tmp->no->nom, s)==0) return true;
            tmp=tmp->succ;
        }
    }
    return false;
}

//Coupe le premier dossier du chemin passé en argument et le renvoi dans un char*
//Il n'y a pas d'assert car les fonctions qui utilisent cette fonction sont censé avoir fait les vérifications en amont
char* SubStringFirstFolder(char *s) {
    int tmp = 0;
    for(int i=0;i<strlen(s)+1; i++) {
        if(s[i]!='/' && s[i]!='\0') {
            tmp+=1;
        } else {
            break;
        }
    }
    char *res = malloc(sizeof(char)*tmp+1);
    // memmove(res, s, tmp);
    for(int j=0; j<tmp;j++) {
        res[j] = s[j];
    }
    res[tmp] = '\0';
    return res;
}


//Retourne le chemin passé en argument sans le dernier dossier/fichier
char* SubStringPath(char *s) {
    int n = strlen(s);
    int tmp = 0;
    for(int i=n-1;i>=0; i--) {
        if(s[i]!='/') {
            tmp+=1;
        } else {
            break;
        }
    }
    if(strlen(s)==tmp) {
        char *res = malloc(sizeof(char));
        res[0] = '\0';
        return res;
    } 
    char *res = malloc(sizeof(char)*(strlen(s)-tmp+1));
    strncpy(res, s, strlen(s)-tmp);
    res[strlen(s)-tmp] = '\0';
    return res;
}

char* substring(char *s) {
    char *res = malloc(sizeof(char)*(strlen(s)+1));
    for(int i=0; i<strlen(s)+1; i++) {
        if(s[i]!=' ') res[i] = s[i];
        else {
            res[i]='\0';
            break;
        }
    }
    return res;
}
