#include "tokenizer.h"

enum op_type { unary, binary, sentinel };
enum node_type { leaf, inner };

struct _operator {
    enum op_type ot;
    char* op;
};

#define STACK_SIZE 1000
int OPERATOR_STACK_TOP, OPERAND_STACK_TOP;


void push_operand(char**, char*);
void push_operator(struct _operator**, enum op_type, char*);
void pop_operand(char**);
void pop_operator(struct _operator**);
char* top_operand(char**);
void pushOperator(struct _operator*);
void popOperator();
int precedence(struct _operator*);
struct _operator* top_operator(struct _operator**);

char **operands;
struct _operator **operators;

void expect();
void error(char*);
void recognizer();
void parser();

void E();
void P();

void EParse();
void PParse();

int is_binop(enum token_type);
int is_value(enum token_type);
int is_unary_operator(enum token_type);