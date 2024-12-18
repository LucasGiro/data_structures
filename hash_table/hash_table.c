#include "hash_table.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "linked_list_table.h"

TablaHash nueva_tabla(
    unsigned capacidad,
    char *implementacion, 
    FuncionCopiadora copia,
    FuncionComparadora comp, 
    FuncionDestructora destr,
    FuncionVisitante visit,
    FuncionHash hash
    ) {

        if (strcmp(implementacion, "linked_list") == 0) {
            return createDoubleLinkedListHashTable(capacidad, copia, comp, destr, visit, hash);
        } else if (strcmp(implementacion, "avl_tree") == 0) {
            return NULL;
        } else {
            printf("Implementacion no valida\n");
            return NULL;
        }

    }