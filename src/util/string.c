#include "string.h"

#include <malloc.h>
#include <string.h>

typedef struct InternsList {
    String* interns;
    unsigned int size;
    unsigned int capacity;
} InternsList;

static InternsList internsList;

void string_intern_init() {
    internsList.size = 0;
    internsList.capacity = 20;
    internsList.interns = malloc(internsList.capacity * sizeof(String));
}

void string_intern_cleanup() {
    for (unsigned int i = 0; i < internsList.size; i++) {
        free((void*) internsList.interns[i]);
    }
    free((void*) internsList.interns);
}

void string_intern_realloc() {
    internsList.capacity = internsList.capacity * 3 / 2;
    internsList.interns = realloc(internsList.interns, internsList.capacity * sizeof(String));
}

String string_intern_new(String string, unsigned long count) {
    if (internsList.size == internsList.capacity)
        string_intern_realloc();

    // Copy till the end of the string if count is greater than string lenght
    char* intern = malloc(count + 1);
    strncpy(intern, string, count);
    intern[count] = '\0';

    internsList.interns[internsList.size++] = intern;
    return intern;
}


String string_intern_n(String string, unsigned long count) {
    if (internsList.size == internsList.capacity)
        string_intern_realloc();
    for (int i = 0; i < internsList.size; i++) {
        String intern = internsList.interns[i];
        if (strlen(intern) == count && strncmp(intern, string, count) == 0)
            return intern;
    }
    return string_intern_new(string, count);
}

String string_intern(String string) {
    return string_intern_n(string, strlen(string));
}