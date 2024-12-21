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

void avl_tree_insert(AVL t, void *dato, FuncionCopiadora copia, FuncionComparadora comp) {
    t->raiz = avl_node_insert(t->raiz, dato, copia, comp);
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