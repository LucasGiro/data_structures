#include<stdio.h>
#include<stdlib.h>
#include "linked_list.h"

struct _Node {
    void *dato;
    struct _Node *sig;
};

SList new_slist() {
    return NULL;
}

void slist_insert(SList *list, void *dato, void *(*copia)(void*)) {

    if (*list == NULL) {
        *list = malloc(sizeof(struct _Node));
        (*list)->sig = NULL;
        (*list)->dato = copia(dato);
        return;
    }

    return slist_insert((&(*list)->sig), dato, copia);

}