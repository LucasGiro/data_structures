#include "hash_table.h"
#include<stdio.h>
#include<stdlib.h>

typedef struct CasillaHash {
    void *dato;
    int eliminado;
} CasillaHash;

struct _TablaHash {
    CasillaHash *elems;
    unsigned numElems;
    unsigned capacidad;
    TablaHashCrear tablahash_crear;
    TablaHashBuscar tablahash_buscar;
    TablaHashDestruir tablahash_destruir;
    TablaHashEliminar tablahash_eliminar;
    TablaHashInsertar tablahash_insertar;
    TablaHashImprimir tablahash_imprimir;
    FuncionCopiadora copia;
    FuncionComparadora comp;
    FuncionDestructora destr;
    FuncionHash hash;
};

TablaHash createDoubleLinkedListHashTable(
    unsigned capacidad,
    FuncionCopiadora copia,
    FuncionComparadora comp, 
    FuncionDestructora destr,
    FuncionHash hash
) {
    
        TablaHash tabla = malloc(sizeof(struct _TablaHash));

        tabla->capacidad = capacidad;
        tabla->elems = malloc(sizeof(CasillaHash)*capacidad);
        tabla->numElems = 0;
        tabla->comp = comp;
        tabla->copia = copia;
        tabla->destr = destr;
        tabla->hash = hash;
}