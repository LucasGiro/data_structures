typedef struct _TablaHash *TablaHash;

typedef void *(*FuncionCopiadora)(void *dato);
typedef int (*FuncionComparadora)(void *dato1, void *dato2);
typedef void (*FuncionDestructora)(void *dato);
typedef unsigned (*FuncionHash)(void *dato);

typedef TablaHash (*TablaHashCrear)(
    unsigned capacidad,
    FuncionCopiadora copia,
    FuncionComparadora comp,
    FuncionDestructora destr,
    FuncionHash hash
    );

typedef void (*TablaHashDestruir)(TablaHash tabla);
typedef void (*TablaHashInsertar)(TablaHash tabla, void *dato);
typedef void *(*TablaHashBuscar)(TablaHash tabla, void *dato);
typedef void (*TablaHashEliminar)(TablaHash tabla, void *dato);
typedef void (*TablaHashImprimir)(TablaHash tabla);

TablaHash nueva_tabla(
    unsigned capacidad,
    char *implementacion, 
    FuncionCopiadora copia,
    FuncionComparadora comp, 
    FuncionDestructora destr,
    FuncionHash hash
);

