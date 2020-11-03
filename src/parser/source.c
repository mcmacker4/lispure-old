//
// Created by mcmacker4 on 11/2/20.
//

#include "source.h"

#include <string.h>
#include <malloc.h>
#include <stdlib.h>

SourceCode source_new(const char* text) {
    SourceCode code;
    code.text = text;
    code.path = NULL;
    code.position = 0;
    code.length = strlen(text);
    code.line = 1;
    code.column = 1;
    return code;
}

const char* read_file(const char* path) {
    FILE* file = fopen(path, "rb");

    if (file == NULL) {
        fprintf(stderr, "Could not open file.\n");
        exit(-1);
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    printf("File size: %ld\n", size);

    char* text = malloc(size + 1);
    fread(text, 1, size, file);
    fclose(file);

    text[size] = 0;

    return text;
}

SourceCode source_from_file(String path) {
    const char* text = read_file(path);
    SourceCode code;
    code.text = text;
    code.path = path;
    code.position = 0;
    code.length = strlen(text);
    code.line = 1;
    code.column = 1;
    return code;
}

void source_free(SourceCode* code) {
    free((void*) code->text);
    memset(code, 0, sizeof(SourceCode));
}

char source_peek(SourceCode* code) {
    if (code->length == code->position)
        return 0;
    return code->text[code->position];
}

char source_consume(SourceCode* code) {
    if (code->length == code->position)
        return 0;
    char c = code->text[code->position++];
    if (c == '\n') {
        code->line++;
        code->column = 1;
    } else {
        code->column++;
    }
    return c;
}

unsigned long source_remaining(SourceCode* code) {
    return code->length - code->position;
}