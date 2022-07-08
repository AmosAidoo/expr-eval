#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
    char *input;
    size_t len = 0;

    getline(&input, &len, stdin);

    // Pass expression to the tokenizer
    initialize_tokenizer(input);
    // Parse expression
    // while (current_token.tt != eof) {
    //     next_token();
    //     print_token();
    // }
    // recognizer();
    parser();

    free(input);
    return 0;
}