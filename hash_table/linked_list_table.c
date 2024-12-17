#include "hash_table.h"
#include<stdio.h>
#include<stdlib.h>
#include "../lists/linked_list.h"

typedef struct CasillaHash {
    void *dato;
} CasillaHash;

struct _TablaHash {
    CasillaHash *elems;
    unsigned numElems;
    unsigned capacidad;
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

void *tablahash_buscar(TablaHash tabla, void *dato) {}

void tablahash_destruir(TablaHash tabla) {}

void tablahash_eliminar(TablaHash tabla, void *dato) {}

void tablahash_insertar(TablaHash tabla, void *dato) {

    unsigned idx = tabla->hash(dato) % tabla->capacidad;

    if (tabla->elems[idx].dato == NULL) {
        SList list = new_slist();
        slist_insert(&list, dato, tabla->copia);
        tabla->elems[idx].dato = list;
        return;
    }

    slist_insert(((SList*)&tabla->elems[idx].dato), dato, tabla->copia);

}

void tablahash_imprimir(TablaHash tabla) {}

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
        tabla->tablahash_buscar = tablahash_buscar;
        tabla->tablahash_destruir = tablahash_destruir;
        tabla->tablahash_eliminar = tablahash_eliminar;
        tabla->tablahash_insertar = tablahash_insertar;
        tabla->tablahash_imprimir = tablahash_imprimir;


        for (int i = 0; i < capacidad; i++) {
            tabla->elems[i].dato = NULL;
        }
}