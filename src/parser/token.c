#include "token.h"


#define TOKEN_GENERATOR_C(fname, ttype)                                     \
Token token_##fname(unsigned int line, unsigned int column, String path) {  \
    Token token;                                                            \
    token.type = ttype;                                                     \
    token.string = NULL;                                                    \
    token.location.line = line;                                             \
    token.location.column = column;                                         \
    token.location.path = path;                                             \
    return token;                                                           \
}

#define TOKEN_GENERATOR_DATA_C(fname, ttype, argt)                                      \
Token token_##fname(argt fname, unsigned int line, unsigned int column, String path) {  \
    Token token;                                                                        \
    token.type = ttype;                                                                 \
    token.fname = fname;                                                                \
    token.location.line = line;                                                         \
    token.location.column = column;                                                     \
    token.location.path = path;                                                         \
    return token;                                                                       \
}

TOKEN_GENERATOR_C(lparen, LPAREN)
TOKEN_GENERATOR_C(rparen, RPAREN)
TOKEN_GENERATOR_C(lbrack, LBRACK)
TOKEN_GENERATOR_C(rbrack, RBRACK)
TOKEN_GENERATOR_C(lcurl, LCURL)
TOKEN_GENERATOR_C(rcurl, RCURL)
TOKEN_GENERATOR_C(hash, HASH)
TOKEN_GENERATOR_C(nil, NIL)

TOKEN_GENERATOR_DATA_C(symbol, SYMBOL, String)
TOKEN_GENERATOR_DATA_C(keyword, KEYWORD, String)
TOKEN_GENERATOR_DATA_C(integer, INTEGER, long)
TOKEN_GENERATOR_DATA_C(string, STRING, const char*)