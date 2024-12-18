#include "hash_table.h"
#include<stdio.h>
#include<stdlib.h>
#include "../lists/linked_list.h"

int tablahash_buscar(TablaHash tabla, void *dato) {

    unsigned idx = tabla->hash(dato) % tabla->capacidad;

    if (tabla->elems[idx].dato != NULL) {
        void *elem = slist_search(tabla->elems[idx].dato, dato, tabla->comp);
        if (elem != NULL) return 1;
        return 0;
    }

    return 0;

}

void tablahash_destruir(TablaHash tabla) {

    for (int i = 0; i < tabla->capacidad; i++) {
        
        slist_destroy(tabla->elems[i].dato, tabla->destr);

    }

    free(tabla->elems);
    free(tabla);

}

void tablahash_eliminar(TablaHash tabla, void *dato) {

    unsigned idx = tabla->hash(dato) % tabla->capacidad;

    int r = slist_delete((SList*)&tabla->elems[idx].dato, dato, tabla->comp, tabla->destr);

    if (r) tabla->numElems--;

}

void tablahash_imprimir(TablaHash tabla) {

    printf("Numero de elementos: %d\n", tabla->numElems);

    for (int i = 0; i < tabla->capacidad; i++) {

        printf("[ id: %d ] --> ", i);
        slist_imprimir((SList)tabla->elems[i].dato, tabla->visit);
        printf("\n");

    }

}

/** Necesario por dependencia circular  **/ 

TablaHash createDoubleLinkedListHashTable(
    unsigned capacidad,
    FuncionCopiadora copia,
    FuncionComparadora comp, 
    FuncionDestructora destr,
    FuncionVisitante visit,
    FuncionHash hash
);

TablaHash tablahash_redimensionar(TablaHash tabla);

void tablahash_insertar(TablaHash *tabla, void *dato);

/** **/

TablaHash createDoubleLinkedListHashTable(
    unsigned capacidad,
    FuncionCopiadora copia,
    FuncionComparadora comp, 
    FuncionDestructora destr,
    FuncionVisitante visit,
    FuncionHash hash
) {
    
        TablaHash tabla = malloc(sizeof(struct _TablaHash));

        tabla->capacidad = capacidad;
        tabla->elems = malloc(sizeof(CasillaHash)*capacidad);
        tabla->numElems = 0;
        tabla->comp = comp;
        tabla->copia = copia;
        tabla->destr = destr;
        tabla->visit = visit;
        tabla->hash = hash;
        tabla->tablahash_buscar = tablahash_buscar;
        tabla->tablahash_destruir = tablahash_destruir;
        tabla->tablahash_eliminar = tablahash_eliminar;
        tabla->tablahash_insertar = tablahash_insertar;
        tabla->tablahash_imprimir = tablahash_imprimir;

        for (int i = 0; i < capacidad; i++) {
            tabla->elems[i].dato = NULL;
        }

        return tabla;
}

TablaHash tablahash_redimensionar(TablaHash tabla) {

    TablaHash nueva_tabla = createDoubleLinkedListHashTable(
        tabla->capacidad * 2,
        tabla->copia,
        tabla->comp,
        tabla->destr,
        tabla->visit,
        tabla->hash
    );

    for (int i = 0; i < tabla->capacidad; i++) {

        SList temp = (SList)tabla->elems[i].dato;

        while (temp != NULL) {
            nueva_tabla->tablahash_insertar(&nueva_tabla, temp->dato);
            temp = temp->sig;
        }

    }

    tabla->tablahash_destruir(tabla);
    return nueva_tabla;

}

void tablahash_insertar(TablaHash *tabla, void *dato) {

    float numElems = (*tabla)->numElems;
    float capacidad = (*tabla)->capacidad;

    if (numElems / capacidad >= 0.69) {
        *tabla = tablahash_redimensionar(*tabla);
    }

    unsigned idx = (*tabla)->hash(dato) % (*tabla)->capacidad;

    if ((*tabla)->elems[idx].dato == NULL) {
        SList list = new_slist();
        slist_insert(&list, dato, (*tabla)->copia);
        (*tabla)->elems[idx].dato = list;
        (*tabla)->numElems++;
        return;
    }

    slist_insert(((SList*)&(*tabla)->elems[idx].dato), dato, (*tabla)->copia);
    (*tabla)->numElems++;

}