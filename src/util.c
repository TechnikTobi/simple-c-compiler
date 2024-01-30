#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

int
to_int(
	char *yytext, 
	int base
)
{
	char *end_pointer = NULL;
	long long long_long_value = strtol(yytext, &end_pointer, base);

	if (*end_pointer != '\0')
	{
		printf("ERROR: to_int FAILED DURING strtol!");
	}

	int int_value = (int) long_long_value;
	if ((long long) int_value != long_long_value)
	{
		printf("WARNING: CONST INT TOO LARGE FOR INT");
	}
	return int_value;
}

double 
to_double
(
	char *yytext
)
{
	char *end_pointer = NULL;
	double double_value = strtod(yytext, &end_pointer);

	if (*end_pointer != '\0')
	{
		printf("ERROR: to_double FAILED DURING strtod!");
	}

	return double_value;
}

char
handle_escape_sequence
(
	char escape_char
)
{
	switch (escape_char)
	{
		case 'a':
			return 0x07;

		case 'b':
			return 0x08;

		case 'e':
			return 0x1b;

		case 'f':
			return 0x0c;

		case 'n':
			return 0x0a;

		case 'r':
			return 0x0d;

		case 't':
			return 0x09;

		case 'v':
			return 0x0b;

		case '\\':
			return 0x5c;

		case '\'':
			return 0x27;

		case '"':
			return 0x22;

		case '?':
			return 0x3f;
			
		default:
			return 0x00;
	}
}

char 
to_char
(
	char *yytext
)
{
	// This function is a bit problematic as it fails with escape sequences
	// that are longer than one character
	// See: https://en.wikipedia.org/wiki/Escape_sequences_in_C
	if (strlen(yytext) > 3)
	{
		if (strlen(yytext) == 4 && yytext[1] == '\\')
		{
			return handle_escape_sequence(yytext[2]);
		}

		printf("ERROR: to_char FAILED!");
	}

	return yytext[1];
}

char* 
to_string
(
	char *yytext
)
{
	// Allocate space
	size_t string_length = strlen(yytext);
	char *string_value = (char*) malloc(sizeof(char) * string_length + 1);

	// Copy with escape sequence handling and set last char to END
	size_t string_value_i = 0;
	for (size_t i = 0; i < string_length; i++)
	{
		char next_char = yytext[i];
		if (next_char == '\\')
		{
			next_char = handle_escape_sequence(yytext[++i]);
		}
		string_value[string_value_i++] = next_char;
	}
	string_value[string_value_i] = '\0';

	// Return finished copy
	return string_value;
}
