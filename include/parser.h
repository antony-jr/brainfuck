#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED
#include <stdio.h>

#define END_OF_INSTRUCTIONS 0
#define SET_CELL 1
#define SET_POS 2
#define OPEN_LOOP 3
#define CLOSE_LOOP 4
#define PRINT_CELL 5
#define GET_CELL 6
int *parse_str(const char *);
int *parse_file(FILE *fp);
#endif /* PARSER_H_INCLUDED */
