#include<stdio.h>
#include<stdlib.h>
#include "avl_tree.h"
#include "../queue/queue.h"

static int max(int a, int b) {
    return (a > b) ? a : b;
}

static int avl_node_altura(AVL_NODE *t) {

    if (t == NULL) return -1;

    return 1 + max(avl_node_altura(t->izq), avl_node_altura(t->der));

}

static int avl_tree_factor_balance(AVL_NODE *t) {
    return avl_node_altura(t->der) - avl_node_altura(t->izq);
}

AVL new_avl_tree(FuncionComparadora comp, FuncionCopiadora copia, FuncionDestructora destr, FuncionVisitante visit) {

    AVL t = malloc(sizeof(struct _AVL));
    t->comp = comp;
    t->copia = copia;
    t->destr = destr;
    t->visit = visit;
    t->raiz = NULL;

    return t;
}

AVL_NODE *avl_node_create(void *dato, FuncionCopiadora copia) {

    AVL_NODE *node = malloc(sizeof(AVL_NODE));
    node->dato = copia(dato);
    node->izq = NULL;
    node->der = NULL;
    node->altura = 0;

    return node;

}

static AVL_NODE *avl_node_insert(AVL_NODE *t, void *dato, FuncionCopiadora copia, FuncionComparadora comp) {

    if (t == NULL) return avl_node_create(dato, copia);

    int c = comp(dato, t->dato);

    if (c > 0) {

        t->der = avl_node_insert(t->der, dato, copia, comp);

        int fact_b = avl_tree_factor_balance(t);

        if (fact_b == 2) {

            if (avl_tree_factor_balance(t->der) == 1) {
                //hacer la rotacion simple
                AVL_NODE *temp = t->der;
                t->der = temp->izq;
                temp->izq = t;
                t = temp;
                t->izq->altura = avl_node_altura(t->izq);
            } else {
                // hacer rotacion doble
                AVL_NODE *temp = t->der->izq;
                t->der->izq = temp->der;
                temp->der = t->der;
                t->der = temp;
                t->der->altura = avl_node_altura(t->der);
                t->der->der->altura = avl_node_altura(t->der->der);
                temp = t->der;
                t->der = temp->izq;
                temp->izq = t;
                t = temp;
                t->izq->altura = avl_node_altura(t->izq);
            }

        }

        t->altura = avl_node_altura(t);
        return t;

    } else if (c < 0) {

        t->izq = avl_node_insert(t->izq, dato, copia, comp);

        int fact_b = avl_tree_factor_balance(t);

        if (fact_b == -2) {

            if (avl_tree_factor_balance(t->izq) == 1) {
                // hacer rotacion doble
                AVL_NODE *temp = t->izq->der;
                t->izq->der = temp->izq;
                temp->izq = t->izq;
                t->izq = temp;
                temp->izq->altura = avl_node_altura(temp->izq);
                temp->altura = avl_node_altura(temp);
                temp = t->izq;
                t->izq = temp->der;
                temp->der = t;
                t = temp;
                t->der->altura = avl_node_altura(t->der);
            } else {
                // hacer rotacion simple
                AVL_NODE *temp = t->izq;
                t->izq = temp->der;
                temp->der = t;
                t = temp;
                t->der->altura = avl_node_altura(t->der);
            }

        }

        t->altura = avl_node_altura(t);

        return t;

    }

    return t;
    
}

void avl_tree_insert(AVL t, void *dato) {
    t->raiz = avl_node_insert(t->raiz, dato, t->copia, t->comp);
}

void avl_tree_preorder(AVL_NODE *t, FuncionVisitante visit) {

    if (t == NULL) return;

    visit(t->dato);

    avl_tree_preorder(t->izq, visit);

    avl_tree_preorder(t->der, visit);

}

void avl_tree_inorder(AVL_NODE *t, FuncionVisitante visit) {

    if (t == NULL) return;

    avl_tree_inorder(t->izq, visit);

    visit(t->dato);

    avl_tree_inorder(t->der, visit);

}

void avl_tree_postorder(AVL_NODE *t, FuncionVisitante visit) {

    if (t == NULL) return;

    avl_tree_postorder(t->izq, visit);

    avl_tree_postorder(t->der, visit);

    visit(t->dato);

}

void avl_tree_bfs(AVL t, FuncionVisitante visit) {

    if (t == NULL || t->raiz == NULL) return;

    Queue queue = new_queue();

    enqueue(queue, t->raiz);

    while(!queue_isEmpty(queue)) {

        AVL_NODE *root = (AVL_NODE*)dequeue(queue);
        visit(root->dato);
        if (root->izq != NULL) enqueue(queue, root->izq);
        if (root->der != NULL) enqueue(queue, root->der);
        
    }

    queue_destroy(queue, NULL);

}

void avl_tree_destroy(AVL_NODE *t, FuncionDestructora destr) {

    if (t == NULL) return;

    avl_tree_destroy(t->izq, destr);

    avl_tree_destroy(t->der, destr);

    destr(t->dato);
    free(t);

}

AVL_NODE *minimo_nodo_arbol(AVL_NODE *t) {

    if (t == NULL) return NULL;

    if (t->izq == NULL) return t;

    return minimo_nodo_arbol(t->izq);

}

AVL_NODE *avl_node_delete(AVL_NODE *t, void *dato, FuncionComparadora comp, FuncionDestructora destr, FuncionCopiadora copia) {

    if (t == NULL) return NULL;

    if (comp(t->dato, dato) < 0) {

        t->der = avl_node_delete(t->der, dato, comp, destr, copia);

        int fact_b = avl_tree_factor_balance(t);

        if (fact_b == -2) {

            if (avl_tree_factor_balance(t->izq) == 1) {
                // hacer rotacion doble
                AVL_NODE *temp = t->izq->der;
                t->izq->der = temp->izq;
                temp->izq = t->izq;
                t->izq = temp;
                temp->izq->altura = avl_node_altura(temp->izq);
                temp->altura = avl_node_altura(temp);
                temp = t->izq;
                t->izq = temp->der;
                temp->der = t;
                t = temp;
                t->der->altura = avl_node_altura(t->der);
            } else {
                // hacer rotacion simple
                AVL_NODE *temp = t->izq;
                t->izq = temp->der;
                temp->der = t;
                t = temp;
                t->der->altura = avl_node_altura(t->der);
            }

        }

        t->altura = avl_node_altura(t);

        return t;

    } else if(comp(t->dato, dato) > 0) {

        t->izq = avl_node_delete(t->izq, dato, comp, destr, copia);

        int fact_b = avl_tree_factor_balance(t);

        if (fact_b == 2) {

            if (avl_tree_factor_balance(t->der) == 1) {
                //hacer la rotacion simple
                AVL_NODE *temp = t->der;
                t->der = temp->izq;
                temp->izq = t;
                t = temp;
                t->izq->altura = avl_node_altura(t->izq);
            } else {
                // hacer rotacion doble
                AVL_NODE *temp = t->der->izq;
                t->der->izq = temp->der;
                temp->der = t->der;
                t->der = temp;
                t->der->altura = avl_node_altura(t->der);
                t->der->der->altura = avl_node_altura(t->der->der);
                temp = t->der;
                t->der = temp->izq;
                temp->izq = t;
                t = temp;
                t->izq->altura = avl_node_altura(t->izq);
            }

        }

        t->altura = avl_node_altura(t);

        return t;

    }

    if (t->izq == NULL && t->der == NULL) {

        destr(t->dato);
        free(t);
        return NULL;

    }

    if (t->izq == NULL && t->der != NULL) {

        AVL_NODE *temp = t->der;
        destr(t->dato);
        free(t);
        return temp;

    }

    if (t->izq != NULL && t->der == NULL) {

        AVL_NODE *temp = t->izq;
        destr(t->dato);
        free(t);
        return temp;

    }

    AVL_NODE *temp = minimo_nodo_arbol(t->der);
    AVL_NODE *node = avl_node_create(temp->dato, copia);
    node->izq = t->izq;
    node->der = avl_node_delete(t->der, temp->dato, comp, destr, copia);
    destr(t->dato);
    free(t);
    return node;

}

void avl_tree_delete(AVL t, void *dato) {

    t->raiz = avl_node_delete(t->raiz, dato, t->comp, t->destr, t->copia);

}

int avl_tree_nnodes(AVL_NODE *root) {

    if (root == NULL) return 0;

    int nnodes = 0;

    nnodes += avl_tree_nnodes(root->izq);
    nnodes += avl_tree_nnodes(root->der);

    return nnodes + 1;

}

int avl_node_search(AVL_NODE *t, void *dato, FuncionComparadora comp) {

    if (t == NULL) return 0;

    if (comp(t->dato, dato) == 0) return 1;

    if (comp(t->dato, dato) < 0) return avl_node_search(t->der, dato, comp);

    return avl_node_search(t->izq, dato, comp);

}

int avl_tree_search(AVL t, void *dato) {
    return avl_node_search(t->raiz, dato, t->comp);
}

//btree copiar: que retorne un nuevo árbol que sea una copia del árbol dado.

AVL_NODE *avl_node_copy(AVL_NODE *node, FuncionCopiadora copia) {

    if (node == NULL) return NULL;

    AVL_NODE *new_node = avl_node_create(node->dato, copia);
    new_node->izq = avl_node_copy(node->izq, copia);
    new_node->der = avl_node_copy(node->der, copia);

    return new_node;

}

AVL avl_tree_copy(AVL t) {

    if (t == NULL) return NULL;

    AVL new_tree = new_avl_tree(t->comp, t->copia, t->destr, t->visit);
    new_tree->raiz = avl_node_copy(t->raiz, t->copia);
    return new_tree;
}

int avl_nnodos_profundidad(AVL_NODE *t, int k) {

    if (t == NULL) return 0;

    if (k == 0) return 1;

    return avl_nnodos_profundidad(t->izq, k-1) + avl_nnodos_profundidad(t->der, k-1);

}

/*btree profundidad: retorna la profundidad del nodo que contiene el dato dado, y -1 si el
dato no se encuentra en el árbol.*/

int avl_node_profundidad(AVL_NODE *t, void *dato, FuncionComparadora comp) {

    if (t == NULL) return -1;

    if (comp(dato, t->dato) == 0) return 0;

    if (comp(dato, t->dato) < 0) {

        int p = avl_node_profundidad(t->izq, dato, comp);

        if (p == -1) return p;

        return 1 + p;

    }

    if (comp(dato, t->dato) > 0) {

        int p = avl_node_profundidad(t->der, dato, comp);

        if (p == -1) return p;

        return 1 + p;

    }

}

int avl_tree_profundidad(AVL t, void *dato) {
    return avl_node_profundidad(t->raiz, dato, t->comp);
}

void *k_esimo_menor_impl(AVL_NODE *t, int *k) {

    if (t->izq == NULL) {

        if (*k == 1) return t->dato;

        *k = *k - 1;

        if (t->der != NULL) return k_esimo_menor_impl(t->der, k);

        *k = *k + 1;

        return t->dato;

    }

    void *menor = k_esimo_menor_impl(t->izq, k);
    
    if (*k == 1) return menor;

    *k = *k - 1;

    if (*k == 1) return t->dato;

    *k = *k - 1;

    if (t->der == NULL) {
        *k = *k + 1;
        return t->dato; 
    }

    menor = k_esimo_menor_impl(t->der, k);

    return menor;

}

void *k_esimo_menor_impl_v2(AVL_NODE *t, int *k) {

    if (t == NULL) return NULL;

    void *menor = k_esimo_menor_impl_v2(t->izq, k);

    if (menor != NULL) return menor;

    *k = *k - 1;

    if (*k == 0) return t->dato;

    return k_esimo_menor_impl_v2(t->der, k);

}

void *avl_tree_k_esimo_menor(AVL t, int k) {
    if (t == NULL) return NULL;
    int copia_k = k;
    return k_esimo_menor_impl(t->raiz, &copia_k);
}