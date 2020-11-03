#include <stdio.h>

#include "util/string.h"
#include "parser/lexer.h"


int main() {

    string_intern_init();

    String path = string_intern("./test.clj");

    TokenList list = tokenize_file(path);
    for (int i = 0; i < list.size; i++) {
        Token* token = list.elements + i;
        switch (token->type) {
            case SYMBOL:
                printf("SYMBOL(%s, [%#010x]), %s:%d:%d)\n", token->symbol, token->symbol, token->location.path, token->location.line, token->location.column);
                break;
            case KEYWORD:
                printf("KEYWORD(%s, [%#010x], %s:%d:%d)\n", token->keyword, token->keyword, token->location.path, token->location.line, token->location.column);
                break;
            case INTEGER:
                printf("INTEGER(%ld), %s:%d:%d)\n", token->integer, token->location.path, token->location.line, token->location.column);
                break;
            default:
                printf("¯\\_(ツ)_/¯\n");
                break;
        }
    }

    tokenlist_free(&list);

    string_intern_cleanup();

}
