#include <stdio.h>

#include "util/string_intern.h"
#include "parser/lexer.h"


void tokenfree(Token* token) {
    if (token->type == STRING)
        free((void*) token->string);
}


int main(int argc, const char** argv) {

    if (argc != 2) {
        fprintf(stderr, "Only argument must be a file.");
        exit(-1);
    }

    string_intern_init();

    StringIntern path = string_intern(argv[1]);

    TokenList list = tokenize_file(path);
    for (int i = 0; i < list.size; i++) {
        Token* token = list.elements + i;
        switch (token->type) {
            case LPAREN:
                printf("LPAREN( %s:%d:%d )\n", token->location.path, token->location.line, token->location.column);
                break;
            case RPAREN:
                printf("RPAREN( %s:%d:%d )\n", token->location.path, token->location.line, token->location.column);
                break;
            case LBRACK:
                printf("LBRACK( %s:%d:%d )\n", token->location.path, token->location.line, token->location.column);
                break;
            case RBRACK:
                printf("RBRACK( %s:%d:%d )\n", token->location.path, token->location.line, token->location.column);
                break;
            case LCURL:
                printf("LCURL( %s:%d:%d )\n", token->location.path, token->location.line, token->location.column);
                break;
            case RCURL:
                printf("RCURL( %s:%d:%d )\n", token->location.path, token->location.line, token->location.column);
                break;
            case SYMBOL:
                printf("SYMBOL( %s, [%#010x]), %s:%d:%d )\n", token->symbol, token->symbol, token->location.path, token->location.line, token->location.column);
                break;
            case KEYWORD:
                printf("KEYWORD( %s, [%#010x], %s:%d:%d )\n", token->keyword, token->keyword, token->location.path, token->location.line, token->location.column);
                break;
            case INTEGER:
                printf("INTEGER( %ld, %s:%d:%d )\n", token->integer, token->location.path, token->location.line, token->location.column);
                break;
            case STRING:
                printf("STRING( \"%s\", %s:%d:%d )\n", token->string, token->location.path, token->location.line, token->location.column);
                break;
            default:
                printf("¯\\_(ツ)_/¯ ( %d - %s:%d:%d )\n", token->type, token->location.path, token->location.line, token->location.column);
                break;
        }
    }

    tokenlist_foreach(&list, &tokenfree);
    tokenlist_free(&list);

    string_intern_cleanup();

}
