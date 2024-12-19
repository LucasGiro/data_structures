#include "../lists/linked_list.h"

typedef struct _Queue {
    SList first;
    SList last;
} *Queue;

typedef void *(*FuncionCopiadora)(void *dato);
typedef int (*FuncionComparadora)(void *dato1, void *dato2);
typedef void (*FuncionDestructora)(void *dato);
typedef void (*FuncionVisitante) (void *dato);

Queue new_queue();
void enqueue(Queue queue, void *dato);
void *dequeue(Queue queue);
int queue_isEmpty(Queue queue);
void queue_imprimir(Queue queue, FuncionVisitante visit);