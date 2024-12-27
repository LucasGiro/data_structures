#include<stdio.h>
#include<stdlib.h>
#include "hash_table/hash_table.h"
#include "lists/linked_list.h"
#include "trees/avl_tree.h"
#include "queue/queue.h"

//gcc trees/avl_tree.c queue/queue.c lists/linked_list.c hash_table/hash_table.c hash_table/avl_tree_table.c hash_table/linked_list_table.c main.c -o main

void *copia(void *n) {
    double *m = malloc(sizeof(double));
    *m = *(double*)n;
}

int comp(void *dato1, void *dato2) {
    
    if (*(double*)dato1 < *(double*)dato2) return -1;
    if (*(double*)dato1 > *(double*)dato2) return 1;

    return 0;

}

void destr(void *dato) {
    free((double*)dato);
}

unsigned hash(void *dato) {

    unsigned truncado = *(double*)dato;

    if ((*(double*)dato - .5) >= truncado) return truncado + 1;

    return truncado;

}

void visitante(void *dato) {
    printf("%f\n", *(double*)dato);
}

int main() {

    double data[] = { 2.2, 0.6, 2.9, 0.8, 0.1, 66.7, 1051.45, 1793.4, 17.6, 470.45, 5.6, 4.4, 20.6, 19.3, 14.2 };

    AVL t = new_avl_tree(comp, copia, destr, visitante);

    for (int i = 0; i < 15; i++) {
        avl_tree_insert(t, &data[i], copia, comp);
    }
    printf("profundidad del nodo 14.2: %d\n", avl_tree_profundidad(t, &data[14]));
    avl_tree_delete(t, &data[5]);
    avl_tree_delete(t, &data[7]);
    AVL new_t = avl_tree_copy(t);


    avl_tree_destroy(t->raiz, destr);
    avl_tree_destroy(new_t->raiz, destr);

    free(t);
    free(new_t);

    return 0;
}