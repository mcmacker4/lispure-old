#ifndef CLOJURE_NATIVE_LEXER_H
#define CLOJURE_NATIVE_LEXER_H

#include "token.h"
#include "source.h"

#include "../util/list.h"
LIST_GENERIC_H(Token, token)

typedef struct Tokenizer {
    TokenList* list;
    SourceCode* source;
} Tokenizer;

TokenList tokenize_file(const char* path);

#endif //CLOJURE_NATIVE_LEXER_H
