#ifndef _TOKEN_FUNC_H
#define _TOKEN_FUNC_H

/* ENUM WHICH SPECIFIES THE TOKEN TYPES */
typedef enum
{
    Keyword,
    Identifier,
    Integer_constant,
    Float_constant,
    Char_constant,
    String_literal,
    Operator,
    Left_parenthesis,
    Right_parenthesis,
    Special_character,
    Not_recognised
} Token_type;

/* functions to check and print tokens */
Status check_token(char *token_str);
void print_token(char *token, Token_type tok_type);

/* Tokenizer functions --> check for valid tokens */
Status is_keyword(char *token);
Status is_identifier(char token);
Status is_operator(char token);
Status is_numerical(char *token);
Status is_char_literal(char token);
Status is_str_literal(char token);
Status is_left_parenthesis(char token);
Status is_right_parenthesis(char token);

/* Functions which stores the tokens in char array */
Token_type store_identifier(char *token_str, char *token);
Token_type store_operator(char *token_str, char *token);
Token_type store_numerical(char *token_str, char *token);
Token_type store_char(char *token_str, char *token);
Token_type store_string(char *token_str, char *token);


#endif
