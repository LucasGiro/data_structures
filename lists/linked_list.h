#ifndef LINKED_LIST_H
#define LINKED_LIST_H 

struct Node {
    void *dato;
    struct Node *sig;
};

typedef struct Node *SList;

typedef void *(*FuncionCopiadora)(void *dato);
typedef int (*FuncionComparadora)(void *dato1, void *dato2);
typedef void (*FuncionDestructora)(void *dato);
typedef void (*FuncionVisitante) (void *dato);

SList new_slist();
void slist_insert(SList *list, void *dato, void *(*copia)(void*));
void *slist_search(SList list, void *dato, FuncionComparadora comp);
int slist_delete(SList *list, void *dato, FuncionComparadora comp, FuncionDestructora destr);
void slist_imprimir(SList list, FuncionVisitante visit);
void slist_destroy(SList list, FuncionDestructora destr);

#endif