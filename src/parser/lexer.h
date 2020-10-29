#ifndef CLOJURE_NATIVE_LEXER_H
#define CLOJURE_NATIVE_LEXER_H

enum TokenType {
    LPAREN, RPAREN,
    LBRACK, RBRACK,
    SYMBOL,
    KEYWORD, // Starts with :
    INTEGER,
    STRING
};

#endif //CLOJURE_NATIVE_LEXER_H
