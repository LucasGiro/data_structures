#include<stdio.h>
#include<stdlib.h>
#include <assert.h>
#include "./bheap.h"

int padre_nodo_k(int k) {
    return (k-1)/2;
}

int hijo_izq_nodo_k(int k) {
    return (k*2)+1;
}

int hijo_der_nodo_k(int k) {
    return (k*2)+2;
}

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

void bheap_insertar(BHeap bheap, void *dato) {

    if (bheap->capacidad == bheap->numElem) {
        bheap->arr = realloc(bheap->arr, sizeof(void*) * bheap->capacidad * 2);
        bheap->capacidad = bheap->capacidad * 2;
    }

    bheap->arr[bheap->numElem] = bheap->copia(dato);
    bheap->numElem++;

    // Hago flotar el elemento

    int k = bheap->numElem - 1;

    while (bheap->comp(bheap->arr[k], bheap->arr[padre_nodo_k(k)]) > 0) {

        void *temp = bheap->arr[padre_nodo_k(k)];
        bheap->arr[padre_nodo_k(k)] = bheap->arr[k];
        bheap->arr[k] = temp;
        k = padre_nodo_k(k);

    }


}
  
void bheap_eliminar(BHeap bheap) {

    if (bheap_es_vacio(bheap)) return;
    bheap->destr(bheap->arr[0]);
    bheap->arr[0] = bheap->arr[bheap->numElem-1];
    bheap->arr[bheap->numElem-1] = NULL;
    bheap->numElem--;

    // Hago undir el elemento

    int k = 0;
    int max_pos = 0;
    int posicion_encontrada = 0;

    while (!posicion_encontrada) {

        if (hijo_izq_nodo_k(k) < bheap->numElem && bheap->comp(bheap->arr[k], bheap->arr[hijo_izq_nodo_k(k)]) < 0) max_pos = hijo_izq_nodo_k(k);

        if (hijo_der_nodo_k(k) < bheap->numElem && bheap->comp(bheap->arr[max_pos], bheap->arr[hijo_der_nodo_k(k)]) < 0) max_pos = hijo_der_nodo_k(k);

        if (max_pos == k) posicion_encontrada = 1;

        void *temp = bheap->arr[max_pos];
        bheap->arr[max_pos] = bheap->arr[k];
        bheap->arr[k] = temp;

        k = max_pos;

    }

}

