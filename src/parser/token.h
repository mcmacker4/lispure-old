#ifndef LISPURE_TOKEN_H
#define LISPURE_TOKEN_H

#include "../util/string.h"

#include <stdlib.h>

typedef enum TokenType {
    LPAREN, RPAREN,
    LBRACK, RBRACK,
    LCURL, RCURL,
    HASH,
    NIL,
    SYMBOL,
    KEYWORD, // Starts with :
    INTEGER,
    STRING
} TokenType;

typedef struct Token {
    TokenType type;
    struct TokenLocation {
        unsigned int line, column;
        String path;
    } location;
    union {
        String symbol;
        String keyword;
        long integer;
        const char* string;
    };
} Token;

#define TOKEN_GENERATOR_H(fname, ttype) \
Token token_##fname(unsigned int line, unsigned int column, String path);

#define TOKEN_GENERATOR_DATA_H(fname, ttype, argt) \
Token token_##fname(argt fname, unsigned int line, unsigned int column, String path);

TOKEN_GENERATOR_H(lparen, LPAREN)
TOKEN_GENERATOR_H(rparen, RPAREN)
TOKEN_GENERATOR_H(lbrack, LBRACK)
TOKEN_GENERATOR_H(rbrack, RBRACK)
TOKEN_GENERATOR_H(lcurl, LCURL)
TOKEN_GENERATOR_H(rcurl, RCURL)
TOKEN_GENERATOR_H(hash, HASH)
TOKEN_GENERATOR_H(nil, NIL)

TOKEN_GENERATOR_DATA_H(symbol, SYMBOL, String)
TOKEN_GENERATOR_DATA_H(keyword, KEYWORD, String)
TOKEN_GENERATOR_DATA_H(integer, INTEGER, long)
TOKEN_GENERATOR_DATA_H(string, STRING, const char*)

#undef TOKEN_GENERATOR_H
#undef TOKEN_GENERATOR_DATA_H

#endif //LISPURE_TOKEN_H
