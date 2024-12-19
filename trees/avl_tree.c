#include<stdio.h>
#include<stdlib.h>
#include "avl_tree.h"
#include "../queue/queue.h"

AVL_TREE new_avl_tree() {
    return NULL;
}

void avl_tree_insert(AVL_TREE *t, void *dato, FuncionCopiadora copia, FuncionComparadora comp) {

    if (*t == NULL) {
        struct AVL_NODE *nuevo_nodo = malloc(sizeof(struct AVL_NODE));
        nuevo_nodo->dato = copia(dato);
        nuevo_nodo->der = NULL;
        nuevo_nodo->izq = NULL;
        *t = nuevo_nodo;
        return;
    }

    if (comp(dato, (*t)->dato) < 0) return avl_tree_insert(&(*t)->izq, dato, copia, comp);
    if (comp(dato, (*t)->dato) > 0) return avl_tree_insert(&(*t)->der, dato, copia, comp);
    return; // Si el dato ya existe en el arbol no lo inserta
}

void avl_tree_preorder(AVL_TREE t, FuncionVisitante visit) {

    if (t == NULL) return;

    visit(t->dato);

    avl_tree_preorder(t->izq, visit);

    avl_tree_preorder(t->der, visit);

}

void avl_tree_inorder(AVL_TREE t, FuncionVisitante visit) {

    if (t == NULL) return;

    avl_tree_inorder(t->izq, visit);

    visit(t->dato);

    avl_tree_inorder(t->der, visit);

}

void avl_tree_postorder(AVL_TREE t, FuncionVisitante visit) {

    if (t == NULL) return;

    avl_tree_postorder(t->izq, visit);

    avl_tree_postorder(t->der, visit);

    visit(t->dato);

}

void avl_tree_bfs(AVL_TREE t, FuncionVisitante visit) {

    if (t == NULL) return;

    Queue queue = new_queue();

    enqueue(queue, t);

    while(!queue_isEmpty(queue)) {

        AVL_TREE root = (AVL_TREE)dequeue(queue);
        visit(root->dato);
        if (root->izq != NULL) enqueue(queue, root->izq);
        if (root->der != NULL) enqueue(queue, root->der);
        
    }

}