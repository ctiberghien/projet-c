#ifndef PROJETC_H
#define PROJETC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "structure.h"

extern noeud* noeud_courant;
extern noeud* noeud_courant_actuel;

extern void cd(char *s);
extern void cd_b();
extern void cp(char*s);
extern void cp_aux(noeud* noeudACopier, noeud* nouveauNoeud);
extern void mv_b(noeud* src,noeud* dest);
extern void ls();
extern void pwd();
extern void print();
extern void touch(char *s);
extern void mkdir(char *s);
extern void rm(char *s);
extern void mv(char *s);
extern void rmToutLarbre();
#endif