#ifndef UTIL_H
#define UTIL_H

int to_int(char *yytext, int base);
double to_double(char *yytext);
char handle_escape_sequence(char escape_char);
char to_char(char *yytext);
char* to_string(char *yytext);

#endif
