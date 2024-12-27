#include<stdio.h>
#include<stdlib.h>
#include <assert.h>
#include "./bheap.h"

BHeap bheap_crear(int capacidad, FuncionComparadora comp, FuncionDestructora destr, FuncionCopiadora copia) {

    BHeap bheap = malloc(sizeof(struct _BHeap));
    assert(bheap != NULL);
    bheap->capacidad = capacidad;
    bheap->numElem = 0;
    bheap->arr = calloc(capacidad, sizeof(void*));
    assert(bheap->arr != NULL);
    bheap->comp = comp;
    bheap->destr = destr;
    bheap->copia = copia;
    return bheap;
}

void bheap_destruir(BHeap bheap) {

    for (int i = 0; i < bheap->numElem; i++) {
        bheap->destr(bheap->arr[i]);
    }

    free(bheap->arr);
    free(bheap);

}

int bheap_es_vacio(BHeap bheap) {
    return (bheap->numElem == 0) ? 1 : 0;
}

void bheap_recorrer(BHeap bheap, FuncionVisitante visit) {

    if (bheap_es_vacio(bheap)) return;

    for (int i = 0; i < bheap->numElem; i++) {
        visit(bheap->arr[i]);
    }

}

