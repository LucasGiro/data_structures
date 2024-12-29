typedef void *(*FuncionCopiadora)(void *dato);
typedef int (*FuncionComparadora)(void *dato1, void *dato2);
typedef void (*FuncionDestructora)(void *dato);
typedef void (*FuncionVisitante) (void *dato);

struct _BHeap {
    void **arr;
    int capacidad;
    int numElem;
    FuncionComparadora comp;
    FuncionDestructora destr;
    FuncionCopiadora copia;
};

typedef struct _BHeap *BHeap;

BHeap bheap_crear(int capacidad, FuncionComparadora comp, FuncionDestructora destr, FuncionCopiadora copia);
void bheap_destruir(BHeap bheap);
int bheap_es_vacio(BHeap bheap);
void bheap_recorrer(BHeap bheap, FuncionVisitante visit);
void bheap_insertar(BHeap bheap, void *dato);
void bheap_eliminar(BHeap bheap);
void bheap_crear_desde_arr(void **arr, int largo, FuncionComparadora comp);
void heapsort(void **arr, int largo, FuncionComparadora comp);