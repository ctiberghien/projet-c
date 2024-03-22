all : ProjetC
structure.o : structure.c structure.h
	gcc -Wall -c structure.c
ProjetC.o : ProjetC.c ProjetC.h structure.h
	gcc -Wall -c ProjetC.c
Arborescence.o : Arborescence.c ProjetC.h structure.h
	gcc -Wall -c Arborescence.c
ProjetC : Arborescence.o ProjetC.o structure.o
	gcc -Wall -o ProjetC Arborescence.o ProjetC.o structure.o