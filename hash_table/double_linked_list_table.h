#include "hash_table.h"

TablaHash createDoubleLinkedListHashTable(
    unsigned capacidad,
    FuncionCopiadora copia,
    FuncionComparadora comp, 
    FuncionDestructora destr,
    FuncionHash hash
);