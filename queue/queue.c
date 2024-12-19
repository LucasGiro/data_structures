#include<stdlib.h>
#include<stdio.h>
#include "queue.h"
#include "../lists/linked_list.h"

Queue new_queue() {
    Queue queue = malloc(sizeof(struct _Queue));
    queue->first = NULL;
    queue->last = NULL;
}

void *no_copia(void *dato) {
    return dato;
}

void enqueue(Queue queue, void *dato) {

    if (queue->first == NULL) {
        slist_insert(&queue->first, dato, no_copia);
        queue->last = queue->first;
        return;
    }

    slist_insert(&queue->last, dato, no_copia);
    queue->last = queue->last->sig;

}

void *dequeue(Queue queue) {

    if (queue->first == NULL) return NULL;

    SList temp = queue->first;
    void *e = temp->dato;
    queue->first = queue->first->sig;
    if (temp == queue->last) queue->last = NULL;
    free(temp);
    return e;

}

int queue_isEmpty(Queue queue) {
    return queue == NULL || queue->first == NULL;
}

void queue_imprimir(Queue queue, FuncionVisitante visit) {
    if (queue == NULL) return;
    slist_imprimir(queue->first, visit);
}
