#include "main.h"
#include "tokenizer_func.h"

/* Total keywords in C */
const char *keywords[34] = { "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto",
    "if", "inline", "int", "long", "register", "restrict", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while" };


extern int pos;
extern int str_flag;


/*
 * DESCRIPTION: This function checks the token is keyword or not
 * INPUT: token string
 * OUTPUT: success or failure
 */
Status is_keyword(char *token)
{
    /* Max length of any keyword is 8 */
    if (strlen(token) > 8)
    {
	return e_failure;
    }

    for (int i = 0; i < 34; i++)
    {
	if (strcmp(keywords[i], token) == 0)
	{
	    return e_success;
	}
    }
    return e_failure;
}

/*
 * DESCRIPTION: This function checks the token is identifier or not
 * INPUT: token string
 * OUTPUT: success or failure
 */
Status is_identifier(char token)
{
    if ( (token >= 'a' && token <= 'z') || (token >= 'A' && token <= 'Z') || token == '_' )
    {
	return e_success;
    }
    
    return e_failure;
}

/*
 * DESCRIPTION: This function checks the token is operator or not
 * INPUT: token string
 * OUTPUT: success or failure
 */
Status is_operator(char token)
{
    switch(token)
    {
	case '.': case '+': case '-': case '*': case '/': case '%': case '&': case '~': case '!': case '<': case '>':
	case '=': case '^': case '|': case '?': case ':': case ',':
	    return e_success;
    }
    return e_failure;
}

/*
 * DESCRIPTION: This function checks the token is numerical or not
 * INPUT: token string
 * OUTPUT: success or failure
 */
Status is_numerical(char *token)
{
    if ( (token[pos] >= '0' && token[pos] <= '9') )
    {
	return e_success;
    }
    /* For floating values starting with .(ex: float a = .254;) */
    else if (token[pos] == '.' && token[pos+1] >= '0' && token[pos+1] <= '9')
    {
	return e_success;
    }
    return e_failure;

}

/*
 * DESCRIPTION: This function checks the token is char literal or not
 * INPUT: token string
 * OUTPUT: success or failure
 */
Status is_char_literal(char token)
{
     if (token == '\'')
     {
	 return e_success;
     }
     return e_failure;
}

/*
 * DESCRIPTION: This function checks the token is string literal or not
 * INPUT: token string
 * OUTPUT: success or failure
 */
Status is_str_literal(char token)
{
     if (token == '\"')
     {
	 return e_success;
     }
     return e_failure;
}

/*
 * DESCRIPTION: This function checks the token is left parenthesis or not
 * INPUT: token string
 * OUTPUT: success or failure
 */
Status is_left_parenthesis(char token)
{
     if (token == '(' || token == '{' || token == '[')
     {
	 return e_success;
     }
     return e_failure;
}

/*
 * DESCRIPTION: This function checks the token is right parenthesis or not
 * INPUT: token string
 * OUTPUT: success or failure
 */
Status is_right_parenthesis(char token)
{
     if (token == ')' || token == '}' || token == ']')
     {
	 return e_success;
     }
     return e_failure;
}


/*
 * DESCRIPTION: This function stores the identifier token in char array
 * INPUT: token string
 * OUTPUT: Token type
 */
Token_type store_identifier(char *token_str, char *token)
{
    int loc_pos = 0;

    /* Store identifier as long as it is valid */
    while (token_str[pos] && ((token_str[pos] >= 'A' && token_str[pos] <= 'Z') || (token_str[pos] >= 'a' && token_str[pos] <= 'z') || 
     (token_str[pos] >= '0' && token_str[pos] <= '9') || token_str[pos] == '_'))
    {
	token[loc_pos++] = token_str[pos++];
    }
    --pos;
    token[loc_pos] = '\0';

    /* Check for keyword */
    if (is_keyword(token) == e_success)
    {
	return Keyword;
    }
    return Identifier;
}

/*
 * DESCRIPTION: This function stores the operator token in char array
 * INPUT: token string
 * OUTPUT: Token type
 */
Token_type store_operator(char *token_str, char *token)
{
    int loc_pos = 0;


    switch(token_str[pos])
    {
	/* standalone operators */
	case '.': case '~': case '?': case ':': case ',':
	    {
		token[loc_pos++] = token_str[pos];
		token[loc_pos] = '\0';
		return Operator;
	    }

	    /* Operators which can come with another operator (ex: +=, !=)*/
	case '+': 
	    {
		token[loc_pos++] = token_str[pos++];
		switch(token_str[pos])
		{
		    case '+': case '=':
			token[loc_pos++] = token_str[pos];
			token[loc_pos] = '\0';
			return Operator;
		    default:
			pos--;
		}
		token[loc_pos] = '\0';
		return Operator;
	    }
	case '-':
	    {
		token[loc_pos++] = token_str[pos++];
		switch(token_str[pos])
		{
		    case '-': case '=': case '>':
			token[loc_pos++] = token_str[pos];
			token[loc_pos] = '\0';
			return Operator;
		    default:
			pos--;
		}
		token[loc_pos] = '\0';
		return Operator;

	    }
	case '*': case '/': case '%': case '^': case '=': case '!':
	    {
		token[loc_pos++] = token_str[pos++];
		switch(token_str[pos])
		{
		    case '=':
			token[loc_pos++] = token_str[pos];
			token[loc_pos] = '\0';
			return Operator;
		    default:
			pos--;
		}
		token[loc_pos] = '\0';
		return Operator;
	    }
	case '&':
	    {
		token[loc_pos++] = token_str[pos++];
		switch(token_str[pos])
		{
		    case '=': case '&':
			token[loc_pos++] = token_str[pos];
			token[loc_pos] = '\0';
			return Operator;
		    default:
			pos--;
		}
		token[loc_pos] = '\0';
		return Operator;
	    }
	case '|':
	    {
		token[loc_pos++] = token_str[pos++];
		switch(token_str[pos])
		{
		    case '=': case '|':
			token[loc_pos++] = token_str[pos];
			token[loc_pos] = '\0';
			return Operator;
		    default:
			pos--;
		}
		token[loc_pos] = '\0';
		return Operator;
	    }
	    /* Operators can come with 2 operators (ex: <<=, >>=)*/
	case '<':
	    {
		token[loc_pos++] = token_str[pos++];
		switch(token_str[pos])
		{
		    case '<':
			{
			    token[loc_pos++] = token_str[pos++];
			    switch(token_str[pos])
			    {
				case '=':
				    token[loc_pos++] = token_str[pos];
				    token[loc_pos] = '\0';
				    return Operator;
				default:
				    pos--;
			    }
			    token[loc_pos] = '\0';
			    return Operator;
			}
		    case '=':
			token[loc_pos++] = token_str[pos];
			token[loc_pos] = '\0';
			return Operator;
		    default:
			pos--;
		}
		token[loc_pos] = '\0';
		return Operator;
	    }
	case '>':
	    {
		token[loc_pos++] = token_str[pos++];
		switch(token_str[pos])
		{
		    case '>':
			{
			    token[loc_pos++] = token_str[pos++];
			    switch(token_str[pos])
			    {
				case '=':
				    token[loc_pos++] = token_str[pos];
				    token[loc_pos] = '\0';
				    return Operator;
				default:
				    pos--;
			    }
			    token[loc_pos] = '\0';
			    return Operator;
			}
		    case '=':
			token[loc_pos++] = token_str[pos];
			token[loc_pos] = '\0';
			return Operator;
		    default:
			pos--;
		}
		token[loc_pos] = '\0';
		return Operator;
	    }
	default:
	    return Not_recognised;
    }

}

/*
 * DESCRIPTION: This function stores the numerical token in char array
 * INPUT: token string
 * OUTPUT: Token type
 */
Token_type store_numerical(char *token_str, char *token)
{
    int loc_pos = 0;

    /* Check for hexa and octal numericals */
    if ( token_str[pos] == '0' )
    {
	token[loc_pos++] = token_str[pos++];
    }

    if (token_str[pos] == 'x' || token_str[pos] == 'X')
    {
	token[loc_pos++] = token_str[pos++];

	while ((token_str[pos] >= '0' && token_str[pos] <= '9') || (token_str[pos] >= 'a' && token_str[pos] <= 'f') || 
		(token_str[pos] >= 'A' && token_str[pos] <= 'F'))
	{
	    token[loc_pos++] = token_str[pos++];
	}
    }

    while (token_str[pos] >= '0' && token_str[pos] <= '9')
    {
	token[loc_pos++] = token_str[pos++];
    }

    /* check for . e u l l f \0  (delimitters ok) (chars specified only)*/

    if (token_str[pos] == '.')
    {
	token[loc_pos++] = token_str[pos++];

	while (token_str[pos] >= '0' && token_str[pos] <= '9')
	{
	    token[loc_pos++] = token_str[pos++];
	}
	/* Check for scientific notation */
	if (token_str[pos] == 'e')
	{
	    token[loc_pos++] = token_str[pos++];
	    if (token_str[pos] == '+' || token_str[pos] == '-')
	    {
		token[loc_pos++] = token_str[pos++];
	    }
	    while (token_str[pos] >= '0' && token_str[pos] <= '9')
	    {
		token[loc_pos++] = token_str[pos++];
	    }
	}
	
	if ( (token_str[pos] >= 'a' && token_str[pos] <= 'z') || (token_str[pos] >= 'A' && token_str[pos] <= 'Z'))
	{
	    if (token_str[pos] == 'f' || token_str[pos] == 'F' || token_str[pos] == 'l' || token_str[pos] == 'L')
	    {
		token[loc_pos++] = token_str[pos];
		token[loc_pos] = '\0';
		return Float_constant;
	    }
	    else
	    {
		return Not_recognised;
	    }
	}
	else
	{
	    pos--;
	    token[loc_pos] = '\0';
	    return Float_constant;
	}
    }
    else
    {
	if (token_str[pos] == 'u' || token_str[pos] == 'U')
	{
	    token[loc_pos++] = token_str[pos++];
	}
	if (token_str[pos] == 'l' || token_str[pos] == 'L')
	{
	    token[loc_pos++] = token_str[pos++];
	}
	if (token_str[pos] == 'l' || token_str[pos] == 'L')
	{
	    token[loc_pos++] = token_str[pos++];
	}

	if ((token_str[pos] >= 'a' && token_str[pos] <= 'z') || (token_str[pos] >= 'A' && token_str[pos] <= 'Z'))
	{
	    return Not_recognised;
	}
	else
	{
	    pos--;
	    token[loc_pos] = '\0';
	    return Integer_constant;
	}

    }

}

/*
 * DESCRIPTION: This function stores the character token in char array
 * INPUT: token string
 * OUTPUT: Token type
 */
Token_type store_char(char *token_str, char *token)
{
    int loc_pos = 0;

    token[loc_pos++] = token_str[pos++];

    while (token_str[pos] && token_str[pos] != '\'')
    {
	token[loc_pos++] = token_str[pos++];
    }

    if (token_str[pos] == '\'')
    {
	token[loc_pos++] = token_str[pos];
	token[loc_pos] = '\0';
	return Char_constant;
    }
    /* Check until it encounters '. if not found return error */

    return Not_recognised;

}

/*
 * DESCRIPTION: This function stores the string token in char array
 * INPUT: token string
 * OUTPUT: Token type
 */
Token_type store_string(char *token_str, char *token)
{
    int loc_pos = 0;

    if (token_str[pos] == '\"')
    {
	token[loc_pos++] = token_str[pos++];
    }

    while (token_str[pos] && token_str[pos] != '\"')
    {
	token[loc_pos++] = token_str[pos];

	/* Check for escape sequence */
	if (token_str[pos] == '\\')
	{
	    token[loc_pos++] = token_str[++pos];
	}

	if (token_str[pos] == '\0')
	{
	    break;
	}
	++pos;
    }

    /* String may end in single line or can continue to multiple lines */
    if (token_str[pos] == '\"')
    {
	str_flag = 0;
	token[loc_pos++] = token_str[pos];
    }
    /* If string continuing in multiple lines, set string flag */
    else if (token_str[pos-1] == '\\')
    {
	str_flag = 1;
	token[loc_pos++] = token_str[pos];
	pos--;
    }
    else
    {
	return Not_recognised;
    }

    token[loc_pos] = '\0';
    return String_literal;
}



