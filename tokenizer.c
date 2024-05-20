#include "main.h"
#include "tokenizer_func.h"

char *token_str;
char *token;
int pos = 0;
int line = 1;
int str_flag = 0;

/*
 * DESCRIPTION: This function performs the lexical analyze operatiom
 * INPUT: FILE pointer to .c file
 * OUTPUT: success or failure
 */
Status lexical_analyze(FILE *fp)
{
    /* Allocate memory to store tokens */
    token_str = malloc(BUFFER_SIZE * sizeof(char));
    if (token_str == NULL)
    {
	puts("INFO: Memory allocation failed");
	return e_failure;
    }

    token = malloc(BUFFER_SIZE * sizeof(char));
    if (token == NULL)
    {
	puts("INFO: Memory allocation failed");
	return e_failure;
    }
    int ch;

    /* Scan one word --> input buffering */
    while (fscanf(fp, "%[^\n]", token_str) != EOF)
    {
	/* Check the valid token type */
	Status ret_sts = check_token(token_str);
	if (ret_sts == e_failure)
	{
	    /* error message */
	    fprintf(stderr, "INFO: \33[91merror\33[39m at line %d\n", line);
	    return e_failure;
	}

	/* Update line number to display line number in case of error */
	while ((ch = getc(fp)) == '\n')
	{
	    ++line;
	}
	ungetc(ch, fp);
	puts("");
    }

    return e_success;
}


/*
 * DESCRIPTION: This function checks token type and store the tokens and print it on the stdout 
 * INPUT: token string
 * OUTPUT: success or failure
 */
Status check_token(char *token_str)
{
    pos = 0;

    Token_type temp_token;

    while (token_str[pos] != '\0')
    {
	/* Check for string continuation */
	if (str_flag == 1)
	{
	    temp_token = store_string(token_str, token);
	}
	else if ( is_identifier(token_str[pos]) == e_success )
	{
	    temp_token = store_identifier(token_str, token);
	}
	else if ( is_numerical(token_str) == e_success)
	{
	    temp_token = store_numerical(token_str, token);
	}
	else if ( is_operator(token_str[pos]) == e_success )
	{
	    temp_token = store_operator(token_str, token);
	}
	else if ( is_char_literal(token_str[pos]) == e_success)
	{
	    temp_token = store_char(token_str, token);
	}
	else if ( is_str_literal(token_str[pos]) == e_success )
	{
	    temp_token = store_string(token_str, token);
	}
	else if ( is_left_parenthesis(token_str[pos]) == e_success)
	{
	    temp_token = Left_parenthesis;
	}
	else if ( is_right_parenthesis(token_str[pos]) == e_success)
	{
	    temp_token = Right_parenthesis;
	}
	else if ( token_str[pos] == ' ')
	{
	    pos++;
	    continue;
	}
	else 
	{
	    temp_token = Special_character;
	}


	/* Token validation */
	if (temp_token == Not_recognised)
	{
	    return e_failure;
	}
	else
	{
	    print_token(token, temp_token);
	}

	pos++;
    }

    return e_success;


}


/*
 * DESCRIPTION: This function prints the token type and token
 * INPUT: token string, token type
 * OUTPUT: void
 */
void print_token(char *token, Token_type tok_type)
{
    if (tok_type == Keyword)
    {
	printf("%-15s : %s\n", "KEYWORD", token);
    }
    else if ( tok_type == Identifier)
    {
	printf("%-15s : %s\n", "IDENTIFIER", token);
    }
    else if ( tok_type == Integer_constant)
    {
	printf("%-15s : %s\n", "INT_LITERAL", token);
    }
    else if ( tok_type == Float_constant)
    {
	printf("%-15s : %s\n", "FLT_LITERAL", token);
    }
    else if ( tok_type == Char_constant)
    {
	printf("%-15s : %s\n", "CHR_LITERAL", token);
    }
    else if ( tok_type == String_literal)
    {
	printf("%-15s : %s\n", "STR_LITERAL", token);
    }
    else if ( tok_type == Operator)
    {
	printf("%-15s : %s\n", "OPERATOR", token);
    }
    else if ( tok_type == Left_parenthesis)
    {
	printf("%-15s : %c\n", "LPAREN", token_str[pos]);
    }
    else if ( tok_type == Right_parenthesis)
    {
	printf("%-15s : %c\n", "RPAREN", token_str[pos]);
    }
    else if ( tok_type == Special_character)
    {
	printf("%-15s : %c\n", "SPL_CHAR", token_str[pos]);
    }
    else
    {
	puts("Not matched with any tokens");
    }

}



