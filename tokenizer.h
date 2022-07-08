/*
    Tokens: number, plus, minus, divide, times
*/
enum token_type {
    number, plus, minus, divide, times, left_paren, right_paren, whitespace, eof
};

char* expr;
extern int pos;

struct token {
    enum token_type tt;
    char* lexeme;
};

struct token current_token;

void initialize_tokenizer(char*);
void clean_tokenizer();

void next_token();

void print_token();

int is_number(char);
int is_operator(char);
int is_paren(char);
int is_whitespace(char);
int is_eof(char);

