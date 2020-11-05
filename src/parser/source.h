#ifndef LISPURE_SOURCE_H
#define LISPURE_SOURCE_H

#include "../util/string_intern.h"

typedef struct SourceCode {

    const char* text;
    StringIntern path;

    unsigned long position;
    unsigned long length;

    unsigned int line;
    unsigned int column;

} SourceCode;

SourceCode source_new(const char* text);
SourceCode source_from_file(const char* path);
void source_free(SourceCode* code);

char source_peek(SourceCode* code);
char source_consume(SourceCode* code);
unsigned long source_remaining(SourceCode* code);

#endif //LISPURE_SOURCE_H
