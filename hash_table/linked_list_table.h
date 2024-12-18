#ifndef LINKED_LIST_TABLE_H
#define LINKED_LIST_TABLE_H 

#include "hash_table.h"

TablaHash createDoubleLinkedListHashTable(
    unsigned capacidad,
    FuncionCopiadora copia,
    FuncionComparadora comp, 
    FuncionDestructora destr,
    FuncionVisitante visit,
    FuncionHash hash
);

#endif