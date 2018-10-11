## Compilation automatique de source C
# Compilteur
CC := gcc
#options de compilation
CFLAGS := -std=c99 -Wall -Wextra -pedantic -ggdb
# Règle de compilation

main_g : main_g.o huffman_g.o arbre_g.o list/liste_generique.o list/noeud_generique.o 
	$(CC) $(CFLAGS) -o $@ $^ 

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< 

test : main_g
	./main_g

