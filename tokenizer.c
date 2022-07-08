#include "tokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pos = 0;
void initialize_tokenizer(char* _expr) {
    expr = (char*) malloc(sizeof(char) * 200);
    strcpy(expr, _expr);
    current_token.lexeme = (char*) malloc(sizeof(char) * 30);
}

void clean_tokenizer() {
    free(expr);
    free(current_token.lexeme);
}

void next_token() {
    if (current_token.tt == eof) return;
    char cc = expr[pos++];
    
    while (is_whitespace(cc)) {
        cc = expr[pos++];
    }
    pos--;

    if (is_number(cc)) {
        char num[21];
        int i = 0;
        while (is_number(cc)) {
            num[i++] = cc;
            pos++;
            cc = expr[pos];
        }
        num[i] = 0x0;
        current_token.tt = number;
        strcpy(current_token.lexeme, num);
    } else if (is_operator(cc)) {
        char op[2];
        op[0] = cc;
        op[1] = 0x0;
        strcpy(current_token.lexeme, op);
        switch(cc) {
            case '+': { current_token.tt = plus; break; }

            case '-': { current_token.tt = minus; break; }

            case '*': { current_token.tt = times; break; }

            case '/': { current_token.tt = divide; break; }
        }
        pos++;
    } else if (is_paren(cc)) {
        if (cc == '(') {
            current_token.tt = left_paren;
            strcpy(current_token.lexeme, "(");
        } else {
            current_token.tt = right_paren;
            strcpy(current_token.lexeme, ")");
        }
        pos++;
    } else if (is_eof(cc)) {
        current_token.tt = eof;
        strcpy(current_token.lexeme, "eof");
    } else {
        printf("Lexical error. Unidentified character: %c\n", cc);
        exit(1);
    }
    print_token();
}

void print_token() {
    switch (current_token.tt) {
        case number: { printf("token_number: "); break; }
        case plus: { printf("token_plus: "); break; }
        case minus: { printf("token_minus: "); break; }
        case divide:{ printf("token_divide: "); break; }
        case times: { printf("token_times: "); break; }
        case left_paren: { printf("token_left_paren: "); break; }
        case right_paren: { printf("token_right_paren: "); break; }
        case whitespace: { printf("token_whitespace: "); break; }
        case eof: { printf("token_eof: "); break; }
    }
    printf("%s\n", current_token.lexeme);
}

int is_number(char c) {
    return c >= '0' && c <= '9';
}

int is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int is_paren(char c) {
    return c == '(' || c == ')';
}

int is_whitespace(char c) {
    return c == ' ';
}

int is_eof(char c) {
    return c == '\n';
}
