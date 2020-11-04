#ifndef LISPURE_LIST_H
#define LISPURE_LIST_H

#include <malloc.h>

#define LIST_GENERIC_H(TYPE, LCTYPE)                                            \
typedef struct TYPE##List {                                                     \
    TYPE* elements;                                                             \
    unsigned int size;                                                          \
    unsigned int capacity;                                                      \
} TYPE##List;                                                                   \
                                                                                \
void LCTYPE##list_realloc(TYPE##List* list);                                    \
void LCTYPE##list_append(TYPE##List* list, TYPE element);                       \
typedef void (*LCTYPE##consumer_t)(TYPE*);                                      \
void LCTYPE##list_foreach(TYPE##List* list, LCTYPE##consumer_t fn);             \
TYPE##List LCTYPE##list_new();                                                  \
void LCTYPE##list_free(TYPE##List* list);                                       \



#define LIST_GENERIC_C(TYPE, LCTYPE)                                            \
void LCTYPE##list_realloc(TYPE##List* list) {                                   \
    list->capacity = list->capacity * 3 / 2;                                    \
    list->elements = realloc(list->elements, list->capacity * sizeof(TYPE));    \
}                                                                               \
                                                                                \
void LCTYPE##list_append(TYPE##List* list, TYPE element) {                      \
    if (list->size == list->capacity)                                           \
        LCTYPE##list_realloc(list);                                             \
    list->elements[list->size++] = element;                                     \
}                                                                               \
                                                                                \
void LCTYPE##list_foreach(TYPE##List* list, LCTYPE##consumer_t fn) {            \
    for (int i = 0; i < list->size; i++) {                                      \
        fn(list->elements + i);                                                 \
    }                                                                           \
}                                                                               \
                                                                                \
TYPE##List LCTYPE##list_new() {                                                 \
    TYPE##List list;                                                            \
    list.size = 0;                                                              \
    list.capacity = 20;                                                         \
    list.elements = malloc(list.capacity * sizeof(TYPE));                       \
    return list;                                                                \
}                                                                               \
                                                                                \
void LCTYPE##list_free(TYPE##List* list) {                                      \
    list->size = 0;                                                             \
    list->capacity = 0;                                                         \
    free(list->elements);                                                       \
    list->elements = NULL;                                                      \
}

#endif //LISPURE_LIST_H
