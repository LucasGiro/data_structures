typedef void *(*FuncionCopiadora)(void *dato);
typedef int (*FuncionComparadora)(void *dato1, void *dato2);
typedef void (*FuncionDestructora)(void *dato);
typedef void (*FuncionVisitante) (void *dato);

struct _BHeap {
    void **arr;
    int capacidad;
    int ultimo;
    FuncionComparadora comp;
};

typedef struct _BHeap *BHeap;