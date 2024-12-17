typedef struct _Node *SList;

SList new_slist();
void slist_insert(SList *list, void *dato, void *(*copia)(void*));