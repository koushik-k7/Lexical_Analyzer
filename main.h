#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 100

/* enum to return the status of the functions */
typedef enum
{
    e_success,
    e_failure,
} Status;

/* Functions to validate and analyze the files */
Status validate_arguments(int argc, char **argv);
Status lexical_analyze(FILE *fp);


#endif
