#include "lexer.h"

#include <ctype.h>

LIST_GENERIC_C(Token, token)

void tokenizer_skipspaces(Tokenizer* tokenizer) {
    while (source_remaining(tokenizer->source) &&
            isspace(source_peek(tokenizer->source))) {
        source_consume(tokenizer->source);
    }
}

static inline int is_symbol_head(char c) {
    return isalpha(c) || c == '*' || c == '+' || c == '!' ||
                         c == '-' || c == '_' || c == '?' ||
                         c == '>' || c == '<' || c == '=' ||
                         c == '$';
}

static inline int is_symbol_rest(char c) {
    return is_symbol_head(c) || isdigit(c) || c == '.' || c == '#';
}

void tokenizer_readsymbol(Tokenizer* tokenizer) {
    unsigned long start = tokenizer->source->position;
    unsigned int line = tokenizer->source->line;
    unsigned int column = tokenizer->source->column;
    StringIntern path = tokenizer->source->path;

    while (source_remaining(tokenizer->source) &&
            is_symbol_rest(source_peek(tokenizer->source)))
        source_consume(tokenizer->source);

    unsigned long length = tokenizer->source->position - start;
    StringIntern str = string_intern_n(tokenizer->source->text + start, length);

    tokenlist_append(tokenizer->list, token_symbol(str, line, column, path));
}

void tokenizer_readkeyword(Tokenizer* tokenizer) {
    unsigned long start = tokenizer->source->position;
    unsigned int line = tokenizer->source->line;
    unsigned int column = tokenizer->source->column;
    StringIntern path = tokenizer->source->path;

    source_consume(tokenizer->source); // Consume colon character.

    while (source_remaining(tokenizer->source) &&
            isalnum(source_peek(tokenizer->source)))
        source_consume(tokenizer->source);

    unsigned long length = tokenizer->source->position - start;
    StringIntern str = string_intern_n(tokenizer->source->text + start, length);

    tokenlist_append(tokenizer->list, token_keyword(str, line, column, path));
}

void tokenizer_readinteger(Tokenizer* tokenizer) {
    unsigned int line = tokenizer->source->line;
    unsigned int column = tokenizer->source->column;
    StringIntern path = tokenizer->source->path;

    long value = 0;
    while (isdigit(source_peek(tokenizer->source))) {
        long digit = source_consume(tokenizer->source) - '0';
        value = value * 10 + digit;
    }

    tokenlist_append(tokenizer->list, token_integer(value, line, column, path));
}

void tokenizer_readstring(Tokenizer* tokenizer) {
    unsigned int line = tokenizer->source->line;
    unsigned int column = tokenizer->source->column;
    StringIntern path = tokenizer->source->path;

    source_consume(tokenizer->source);

    unsigned int strlen = 0;
    unsigned int strcap = 512;
    char* str = malloc(strcap);

    while (source_remaining(tokenizer->source) &&
            source_peek(tokenizer->source) != '"') {
        if (strlen == strcap - 1) {
            strcap = strcap * 3 / 2;
            str = realloc(str, strcap);
        }
        str[strlen++] = source_consume(tokenizer->source);
    }

    str = realloc(str, strlen + 1);
    str[strlen] = 0;

    if (source_peek(tokenizer->source) != '"') {
        fprintf(stderr, "Invalid token at %s:%d:%d", path, line, column);
        exit(-1);
    }

    str = realloc(str, strlen + 1);
    str[strlen] = 0;

    source_consume(tokenizer->source);

    tokenlist_append(tokenizer->list, token_string(str, line, column, path));
}

void tokenizer_next(Tokenizer* tokenizer) {

    char c = source_peek(tokenizer->source);

    unsigned int line = tokenizer->source->line;
    unsigned int column = tokenizer->source->column;
    StringIntern path = tokenizer->source->path;

    if (is_symbol_head(c)) {
        tokenizer_readsymbol(tokenizer);
    } else if (isdigit(c)) {
        tokenizer_readinteger(tokenizer);
    } else if (c == ':') {
        tokenizer_readkeyword(tokenizer);
    } else if (c == '(') {
        source_consume(tokenizer->source);
        tokenlist_append(tokenizer->list, token_lparen(line, column, path));
    } else if (c == '"') {
        tokenizer_readstring(tokenizer);
    } else if (c == ')') {
        source_consume(tokenizer->source);
        tokenlist_append(tokenizer->list, token_rparen(line, column, path));
    } else if (c == '[') {
        source_consume(tokenizer->source);
        tokenlist_append(tokenizer->list, token_lbrack(line, column, path));
    } else if (c == ']') {
        source_consume(tokenizer->source);
        tokenlist_append(tokenizer->list, token_rbrack(line, column, path));
    } else if (c == '{') {
        source_consume(tokenizer->source);
        tokenlist_append(tokenizer->list, token_lcurl(line, column, path));
    } else if (c == '}') {
        source_consume(tokenizer->source);
        tokenlist_append(tokenizer->list, token_rcurl(line, column, path));
    } else {
        // TODO Print Error with source.
        SourceCode* source = tokenizer->source;
        fprintf(stderr, "Invalid token at %s:%d:%d\n", source->path, source->line, source->column);
        exit(-1);
    }

}

void tokenizer_tokenize(Tokenizer* tokenizer) {
    tokenizer_skipspaces(tokenizer);
    while (source_remaining(tokenizer->source)) {
        tokenizer_next(tokenizer);
        tokenizer_skipspaces(tokenizer);
    }
}

TokenList tokenize_file(StringIntern path) {
    TokenList list = tokenlist_new();
    SourceCode source = source_from_file(path);

    Tokenizer tokenizer;
    tokenizer.list = &list;
    tokenizer.source = &source;

    tokenizer_tokenize(&tokenizer);

    source_free(&source);

    return list;
}