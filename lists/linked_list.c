#include<stdio.h>
#include<stdlib.h>
#include "linked_list.h"

SList new_slist() {
    return NULL;
}

void slist_insert(SList *list, void *dato, void *(*copia)(void*)) {

    if (*list == NULL) {
        *list = malloc(sizeof(struct Node));
        (*list)->sig = NULL;
        (*list)->dato = copia(dato);
        return;
    }

    return slist_insert((&(*list)->sig), dato, copia);

}

void *slist_search(SList list, void *dato, FuncionComparadora comp) {

    if (list != NULL) {
        
        if (comp(list->dato, dato) == 0) {
            return list->dato;
        } else {
            return slist_search(list->sig, dato, comp);
        }

    }

    return NULL;

}

int slist_delete(SList *list, void *dato, FuncionComparadora comp, FuncionDestructora destr) {

    if (*list != NULL) {

        if (comp((*list)->dato, dato) == 0) {
            destr((*list)->dato);
            SList temp = (*list);
            (*list) = (*list)->sig;
            free(temp);
            return 1;
        }

    } else { return 0; }

    SList temp = *list;

    for (; temp->sig != NULL && comp(temp->sig->dato, dato) != 0; temp = temp->sig);

    if (temp->sig != NULL && comp(temp->sig->dato, dato) == 0) {
        destr(temp->sig->dato);
        SList to_eliminate = temp->sig;
        temp->sig = to_eliminate->sig;
        free(to_eliminate);
        return 1;
    }

    return 0;

}

void slist_destroy(SList list, FuncionDestructora destr) {

    while (list != NULL) {

        SList temp = list->sig;
        destr(list->dato);
        free(list);
        list = temp;

    }

}

void slist_imprimir(SList list, FuncionVisitante visit) {

    for (; list != NULL; list = list->sig) {
        printf("[ address: %p, dato: ", list);
        visit(list->dato);
        printf(", next: %p ] --> ", list->sig);
    }

}