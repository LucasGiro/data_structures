typedef void *(*FuncionCopiadora)(void *dato);
typedef int (*FuncionComparadora)(void *dato1, void *dato2);
typedef void (*FuncionDestructora)(void *dato);
typedef void (*FuncionVisitante) (void *dato);
typedef void (*FuncionVisitanteExtra)(void *dato, void *extra);

typedef struct _AVL_NODE {
    void *dato;
    struct _AVL_NODE *der;
    struct _AVL_NODE *izq;
    int altura;
} AVL_NODE;

struct _AVL {
    AVL_NODE *raiz;
    FuncionCopiadora copia;
    FuncionComparadora comp;
    FuncionDestructora destr;
    FuncionVisitante visit;
};

typedef struct _AVL *AVL;

AVL new_avl_tree(FuncionComparadora comp, FuncionCopiadora copia, FuncionDestructora destr, FuncionVisitante visit);
void avl_tree_insert(AVL t, void *dato);
void avl_tree_preorder(AVL_NODE *t, FuncionVisitante visit);
void avl_tree_inorder(AVL_NODE *t, FuncionVisitante visit);
void avl_tree_postorder(AVL_NODE *t, FuncionVisitante visit);
void avl_tree_bfs(AVL t, FuncionVisitante visit);
void avl_tree_destroy(AVL_NODE *t, FuncionDestructora destr);
void avl_tree_delete(AVL t, void *dato);
int avl_tree_nnodes(AVL_NODE *root);
int avl_tree_search(AVL t, void *dato);
AVL avl_tree_copy(AVL t);
int avl_nnodos_profundidad(AVL_NODE *t, int k);
int avl_tree_profundidad(AVL t, void *dato);
void *avl_tree_k_esimo_menor(AVL t, int k);