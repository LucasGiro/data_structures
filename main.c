#include<stdio.h>
#include<stdlib.h>
#include "hash_table/hash_table.h"
#include "lists/linked_list.h"
#include "trees/avl_tree.h"
#include "queue/queue.h"
#include "heap/bheap.h"
#include <time.h>

//gcc trees/avl_tree.c queue/queue.c lists/linked_list.c hash_table/hash_table.c hash_table/avl_tree_table.c hash_table/linked_list_table.c main.c -o main

void *copia(void *n) {
    float *m = malloc(sizeof(float));
    *m = *(float*)n;
}

int comp(void *dato1, void *dato2) {
    
    if (*(float*)dato1 < *(float*)dato2) return -1;
    if (*(float*)dato1 > *(float*)dato2) return 1;

    return 0;

}

void destr(void *dato) {
    free((float*)dato);
}

unsigned hash(void *dato) {

    unsigned truncado = *(float*)dato;

    if ((*(float*)dato - .5) >= truncado) return truncado + 1;

    return truncado;

}

void visitante(void *dato) {
    printf("%f\n", *(float*)dato);
}

int main() {

    float data[] = { 2.2, 0.6, 2.9, 0.8, 0.1, 66.7, 1051.45, 1793.4, 17.6, 470.45, 5.6, 4.4, 20.6, 19.3, 14.2 };

    AVL t = new_avl_tree(comp, copia, destr, visitante);

    for (int i = 0; i < 15; i++) {
        avl_tree_insert(t, &data[i]);
    }

    for (int i = 1; i < 16; i++) {
        float *menor = avl_tree_k_esimo_menor(t, i);
        printf("2-er menor: %f\n", *(float*)menor);
    }

    avl_tree_destroy(t->raiz, destr);

    free(t);

    return 0;
}