/*
 * AUTHOR : Koushik K
 * DESCRIPTION: This program act as a lexical analyzer which is part of compilation stage.
 * 		Lexiacl analyzer will read .c file and converts the contents to tokens and identify the tokens.
 * 		In stdout it will print the token and respective lexeme.
 * INPUT : ./lexer <file.c>
 * OUTPUT : Tokens and lexemes in stdout
 */
#include "main.h"

int main(int argc, char **argv)
{
    /* Function which validates the input argument */
    if (validate_arguments(argc, argv) == e_failure)
    {
	puts("Usage: ./lexer <file.c> ");
	return 0;
    }

    /* Open file */
    FILE *fp;
    
    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
	puts("INFO: File doesn't exist");
	return 0;
    }

    /* Check for file empty */
    fseek(fp, 0, SEEK_END);

    if (ftell(fp) <= 1)
    {
	puts("INFO: File empty");
	return 0;
    }

    fseek(fp, 0, SEEK_SET);


    /* scanner, tokenizer, analyzer, output */

    puts("INFO: Lexical analyzer presumes that your .c file is preprocessed");
    puts("INFO: Incase of macro or comments, Lexical analyzer won't ignore them\n");

    if (lexical_analyze(fp) == e_failure)
    {
	puts("INFO: Lexical analyzer failed");
	return 1;
    }

    puts("INFO: Lexical analyzer work done");

    return 0;

}


/*
 * DESCRIPTION: This function validates the command line arguments and return the status
 * INPUT: command line arguments
 * OUTPUT: success or failure
 */
Status validate_arguments(int argc, char **argv)
{
    if (argc < 2)
    {
	puts("INFO: Invalid number of arguments");
	return e_failure;
    }

    char *ptr;
    if ((ptr = strrchr(argv[1], '.')) != NULL && strcmp(ptr, ".c") == 0)
    {
	return e_success;
    }

    puts("INFO: Invalid file format");
    return e_failure;
}



