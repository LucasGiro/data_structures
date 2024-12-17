#include<stdio.h>
#include<stdlib.h>
#include "hash_table/hash_table.h"

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

int hash(void *dato) {

    int truncado = *(double*)dato;

    if ((*(double*)dato - .5) >= truncado) return truncado + 1;

    return truncado;

}

int main() {

    //TablaHash tabla = nueva_tabla(10, "linked_list", copia, comp, destr, hash);

    double *n = malloc(sizeof(double));
    *n = 0.5;

    free(n);

    return 0;
}