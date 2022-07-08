#include "parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void expect(enum token_type tt) {
    if (current_token.tt == tt) {
        next_token();
    } else {
        error("unexpected token");
        print_token();
    }
}

void recognizer() {
    next_token();
    E();
    printf("\n");
}

void push_operand(char** stack, char* item) {
    if (OPERAND_STACK_TOP < STACK_SIZE) {
        strcpy(stack[OPERAND_STACK_TOP++], item);
    } else {
        printf("Stack overflow\n");
        exit(1);
    }
}

void pop_operand(char** stack) {
    if (OPERAND_STACK_TOP - 1 < 0) {
        printf("Stack underflow");
        exit(1);
    }
    OPERAND_STACK_TOP--;
}

char* top_operand(char** stack) {
    if (OPERAND_STACK_TOP == 0) {
        printf("Stack is empty\n");
        exit(1);
    }
    return stack[OPERAND_STACK_TOP - 1];
}

void push_operator(struct _operator** stack, enum op_type type, char* item) {
    if (OPERATOR_STACK_TOP < STACK_SIZE) {
        strcpy(stack[OPERATOR_STACK_TOP]->op, item);
        stack[OPERATOR_STACK_TOP]->ot = type;
        OPERATOR_STACK_TOP++;
    } else {
        printf("Stack overflow\n");
        exit(1);
    }
}

void pop_operator(struct _operator** stack) {
    if (OPERATOR_STACK_TOP - 1 < 0) {
        printf("Stack underflow");
        exit(1);
    }
    OPERATOR_STACK_TOP--;
}

struct _operator* top_operator(struct _operator** stack) {
    if (OPERATOR_STACK_TOP == 0) {
        printf("Stack is empty\n");
        exit(1);
    }
    return stack[OPERATOR_STACK_TOP - 1];
}

void parser() {
    OPERATOR_STACK_TOP = 0;
    OPERAND_STACK_TOP = 0;
    operators = (struct _operator**)malloc(STACK_SIZE * sizeof(struct _operator**));
    operands = (char**)malloc(STACK_SIZE * sizeof(char**));
    for (int i = 0; i < STACK_SIZE; i++) {
        operands[i] = (char*)malloc(30 * sizeof(char*));
        operators[i] = (struct _operator*)malloc(sizeof(struct _operator*));
        operators[i]->op = (char*)malloc(5 * sizeof(char));
    }

    next_token();

    // Push sentinel unto the operator stack
    push_operator(operators, sentinel, "sentinel");
    EParse();

    printf("final result is = %s\n", top_operand(operands));
    
    //Free memory
    for (int i = 0; i < STACK_SIZE; i++) {
        free(operands[i]);
        free(operators[i]);
    }
    free(operands);
    free(operators);
}

void EParse() {
    PParse();
    while (is_binop(current_token.tt)) {
        struct _operator* op = (struct _operator*) malloc(sizeof(struct _operator*));
        op->op = current_token.lexeme;
        op->ot = binary;
        pushOperator(op);
        next_token();
        PParse();
    }

    while (top_operator(operators)->ot != sentinel) {
        popOperator();
    }
}

void PParse() {
    if (is_value(current_token.tt)) {
        push_operand(operands, current_token.lexeme);
        next_token();
    } else if (strcmp(current_token.lexeme, "(") == 0) {
        next_token();
        push_operator(operators, sentinel, "sentinel");
        EParse(operators, operands);
        expect(right_paren);
        pop_operator(operators);
    } else if (is_unary_operator(current_token.tt)) {
        struct _operator* op = (struct _operator*) malloc(sizeof(struct _operator*));
        op->op = current_token.lexeme;
        op->ot = unary;
        pushOperator(op);
        next_token();
        PParse();
    } else {
        error("\nexpression doesn't follow grammar");
        print_token();
    }
}

void E() {
    P();
    while (is_binop(current_token.tt)) {
        printf("%s ", current_token.lexeme);
        next_token();
        P();
    }
}

void P() {
    printf("%s ", current_token.lexeme);
    if (is_value(current_token.tt)) {
        next_token();
    } else if (strcmp(current_token.lexeme, "(") == 0) {
        next_token();
        E();
        expect(right_paren);
        printf(")");
    } else if (is_unary_operator(current_token.tt)) {
        printf("(unary_op) ");
        next_token();
        P();
    } else {
        error("expression doesn't follow grammar");
        print_token();
    }
}

void error(char* msg) {
    printf("%s\n", msg);
    exit(1);
}

int is_binop(enum token_type tt) {
    return tt==plus || tt==minus || tt==times || tt==divide;
}

int is_unary_operator(enum token_type tt) {
    return tt==plus || tt==minus;
}

int is_value(enum token_type tt) {
    return tt==number;
}

void popOperator() {
    printf("Inside popOperator\n");
    char x[100];
    if (top_operator(operators)->ot == binary) {
        char* t1 = top_operand(operands);
        pop_operand(operands);
        char* t0 = top_operand(operands);
        pop_operand(operands);
        char* lex = top_operator(operators)->op;
        pop_operator(operators);
        printf("%s %s %s = ", t0, lex, t1);
        if (strcmp(lex, "+") == 0) {
            int r = atoi(t0) + atoi(t1);
            sprintf(x, "%d", r);
            push_operand(operands, x);
        } else if (strcmp(lex, "-") == 0) {
            int r = atoi(t0) - atoi(t1);
            sprintf(x, "%d", r);
            push_operand(operands, x);
        } else if (strcmp(lex, "/") == 0) {
            int r = atoi(t0) / atoi(t1);
            sprintf(x, "%d", r);
            push_operand(operands, x);
        } else if (strcmp(lex, "*") == 0) {
            int r = atoi(t0) * atoi(t1);
            sprintf(x, "%d", r);
            push_operand(operands, x);
        } else {
            printf("Unidentified operator type\n");
            exit(1);
        }
        printf("%s\n", x);
    } else {
        printf("we have a unary operator\n");
        char* lex = top_operator(operators)->op;
        pop_operator(operators);
        if (strcmp(lex, "-") == 0) {
            memset(x, 0, sizeof(x));
            x[0] = '-';
            strcat(x, top_operand(operands));
            printf("concatenated string is %s\n", x);
            pop_operand(operands);
            push_operand(operands, x);
        } else {
            strcpy(x, top_operand(operands));
            pop_operand(operands);
            push_operand(operands, top_operand(operands));
        }
    }
}

void pushOperator(struct _operator* op) {
    printf("Inside pushOperator\n");
    while (precedence(top_operator(operators)) > precedence(op)) {
        printf("precedence of %s is greater than precedence of %s\n", top_operator(operators)->op, op->op);
        popOperator();
    }
    push_operator(operators, op->ot, op->op);
}

int precedence(struct _operator* op) {
    if (op->ot == unary) return 4;
    if (op->ot == sentinel) return 0;
    else {
        char* lex = op->op;
        if (strcmp(lex, "+") == 0) return 2;
        else if (strcmp(lex, "-") == 0) return 2;
        else if (strcmp(lex, "/") == 0) return 3; 
        else if (strcmp(lex, "*") == 0) return 3;
    }
}