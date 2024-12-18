#ifndef HASH_TABLE_H
#define HASH_TABLE_H 

typedef void *(*FuncionCopiadora)(void *dato);
typedef int (*FuncionComparadora)(void *dato1, void *dato2);
typedef void (*FuncionDestructora)(void *dato);
typedef void (*FuncionVisitante) (void *dato);
typedef unsigned (*FuncionHash)(void *dato);

typedef struct CasillaHash {
    void *dato;
} CasillaHash;

typedef struct _TablaHash {
    CasillaHash *elems;
    unsigned numElems;
    unsigned capacidad;
    int (*tablahash_buscar)(struct _TablaHash *tabla, void *dato);
    void (*tablahash_destruir)(struct _TablaHash *tabla);
    void (*tablahash_eliminar)(struct _TablaHash *tabla, void *dato);
    void (*tablahash_insertar)(struct _TablaHash **tabla, void *dato);
    void (*tablahash_imprimir)(struct _TablaHash *tabla);
    FuncionCopiadora copia;
    FuncionComparadora comp;
    FuncionDestructora destr;
    FuncionVisitante visit;
    FuncionHash hash;
} _TablaHash;

typedef struct _TablaHash *TablaHash;

TablaHash nueva_tabla(
    unsigned capacidad,
    char *implementacion, 
    FuncionCopiadora copia,
    FuncionComparadora comp, 
    FuncionDestructora destr,
    FuncionVisitante visit,
    FuncionHash hash
);

#endif