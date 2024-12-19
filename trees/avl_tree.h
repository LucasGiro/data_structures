typedef void *(*FuncionCopiadora)(void *dato);
typedef int (*FuncionComparadora)(void *dato1, void *dato2);
typedef void (*FuncionDestructora)(void *dato);
typedef void (*FuncionVisitante) (void *dato);

struct AVL_NODE {
    void *dato;
    struct AVL_NODE *der;
    struct AVL_NODE *izq;
};

typedef struct AVL_NODE *AVL_TREE;

AVL_TREE new_avl_tree();
void avl_tree_insert(AVL_TREE *t, void *dato, FuncionCopiadora copia, FuncionComparadora comp);
void avl_tree_preorder(AVL_TREE t, FuncionVisitante visit);
void avl_tree_inorder(AVL_TREE t, FuncionVisitante visit);
void avl_tree_postorder(AVL_TREE t, FuncionVisitante visit);
void avl_tree_bfs(AVL_TREE t, FuncionVisitante visit);