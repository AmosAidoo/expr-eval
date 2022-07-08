# expr-eval
A simple and crude infix expression parser and evaluator in C (implements the shunting yard algorithm). Evaluates expression during parsing, doesn't produce any intermediate representation but can be easily modified to do so. Contains a number of `prinf`s to show what is happening.

Valid Operators: `+, -, *, /`. Can contain parentheses too.

Valid Operands: numbers

Takes single line input from `stdin`. 

Reference material: [https://www.engr.mun.ca/~theo/Misc/exp_parsing.htm](https://www.engr.mun.ca/~theo/Misc/exp_parsing.htm)
