D           [0-9]
L           [a-zA-Z_]
H           [a-fA-F0-9]
E           [Ee][+-]?{D}+
FS          (f|F|l|L)
IS          (u|U|l|L)*

%{
#include <stdio.h>

#include "ast.h"
#include "util.h"

#include "parser.tab.h"

// Function declarations
void count();
void comment();
int check_type();
int fileno(FILE *stream);

%}

%option nounput

%%
"/*"                    { comment(); }

"auto"                  { count(); return(AUTO); }
"break"                 { count(); return(BREAK); }
"case"                  { count(); return(CASE); }
"char"                  { count(); return(CHAR); }
"const"                 { count(); return(CONST); }
"continue"              { count(); return(CONTINUE); }
"default"               { count(); return(DEFAULT); }
"do"                    { count(); return(DO); }
"double"                { count(); return(DOUBLE); }
"else"                  { count(); return(ELSE); }
"enum"                  { count(); return(ENUM); }
"extern"                { count(); return(EXTERN); }
"float"                 { count(); return(FLOAT); }
"for"                   { count(); return(FOR); }
"goto"                  { count(); return(GOTO); }
"if"                    { count(); return(IF); }
"int"                   { count(); return(INT); }
"long"                  { count(); return(LONG); }
"register"              { count(); return(REGISTER); }
"return"                { count(); return(RETURN); }
"short"                 { count(); return(SHORT); }
"signed"                { count(); return(SIGNED); }
"sizeof"                { count(); return(SIZEOF); }
"static"                { count(); return(STATIC); }
"struct"                { count(); return(STRUCT); }
"switch"                { count(); return(SWITCH); }
"typedef"               { count(); return(TYPEDEF); }
"union"                 { count(); return(UNION); }
"unsigned"              { count(); return(UNSIGNED); }
"void"                  { count(); return(VOID); }
"volatile"              { count(); return(VOLATILE); }
"while"                 { count(); return(WHILE); }

{L}({L}|{D})*           { count(); yylval.iden = new_identifier(to_string(yytext));   return(check_type()); }

0[xX]{H}+{IS}?          { count(); yylval.int_value = to_int(yytext, 16);             return(INT_CONSTANT); /* e.g. 0xFful = 255 */ }
0{D}+{IS}?              { count(); yylval.int_value = to_int(yytext,  8);             return(INT_CONSTANT); /* e.g. 022ul = 18   */ }
{D}+{IS}?               { count(); yylval.int_value = to_int(yytext, 10);             return(INT_CONSTANT); /* e.g. 12ul       */ }

L?'(\\.|[^\\'])+'       { count(); yylval.char_value = to_char(yytext);               return(CHAR_CONSTANT); }

{D}+{E}{FS}?            { count(); yylval.double_value = to_double(yytext);           return(DOUBLE_CONSTANT); /* e.g. 2e+3 */ }
{D}*"."{D}+({E})?{FS}?  { count(); yylval.double_value = to_double(yytext);           return(DOUBLE_CONSTANT); /* e.g. .1 */ }
{D}+"."{D}*({E})?{FS}?  { count(); yylval.double_value = to_double(yytext);           return(DOUBLE_CONSTANT); /* e.g. 1. */ }

L?\"(\\.|[^\\"])*\"     { count(); yylval.string_value = to_string(yytext); return(STRING_LITERAL); }

"..."                   { count(); return(ELLIPSIS); }
">>="                   { count(); return(RIGHT_ASSIGN); }
"<<="                   { count(); return(LEFT_ASSIGN); }
"+="                    { count(); return(ADD_ASSIGN); }
"-="                    { count(); return(SUB_ASSIGN); }
"*="                    { count(); return(MUL_ASSIGN); }
"/="                    { count(); return(DIV_ASSIGN); }
"%="                    { count(); return(MOD_ASSIGN); }
"&="                    { count(); return(AND_ASSIGN); }
"^="                    { count(); return(XOR_ASSIGN); }
"|="                    { count(); return(OR_ASSIGN); }
">>"                    { count(); return(RIGHT_OP); }
"<<"                    { count(); return(LEFT_OP); }
"++"                    { count(); return(INC_OP); }
"--"                    { count(); return(DEC_OP); }
"->"                    { count(); return(PTR_OP); }
"&&"                    { count(); return(AND_OP); }
"||"                    { count(); return(OR_OP); }
"<="                    { count(); return(LE_OP); }
">="                    { count(); return(GE_OP); }
"=="                    { count(); return(EQ_OP); }
"!="                    { count(); return(NE_OP); }
";"                     { count(); return(';'); }
("{"|"<%")              { count(); return('{'); }
("}"|"%>")              { count(); return('}'); }
","                     { count(); return(','); }
":"                     { count(); return(':'); }
"="                     { count(); return('='); }
"("                     { count(); return('('); }
")"                     { count(); return(')'); }
("["|"<:")              { count(); return('['); }
("]"|":>")              { count(); return(']'); }
"."                     { count(); return('.'); }
"&"                     { count(); return('&'); }
"!"                     { count(); return('!'); }
"~"                     { count(); return('~'); }
"-"                     { count(); return('-'); }
"+"                     { count(); return('+'); }
"*"                     { count(); return('*'); }
"/"                     { count(); return('/'); }
"%"                     { count(); return('%'); }
"<"                     { count(); return('<'); }
">"                     { count(); return('>'); }
"^"                     { count(); return('^'); }
"|"                     { count(); return('|'); }
"?"                     { count(); return('?'); }

[ \t\v\n\f]             { count(); }
.                       { /* ignore bad characters */ }

%%

int yywrap()
{
	return(1);
}


void comment()
{
	char c, c1;

loop:
	while ((c = input()) != '*' && c != 0) {}
	if ((c1 = input()) != '/' && c != 0) { goto loop; }
}


int column = 0;

void count()
{
	int i;

	for (i = 0; yytext[i] != '\0'; i++)
	{
		if (yytext[i] == '\n')
		{
			column = 0;
		}
		else if (yytext[i] == '\t')
		{
			column += 8 - (column % 8);
		}
		else
		{
			column++;
		}
	}
}


int check_type()
{
	/*
	 * pseudo code --- this is what it should check
	 *
	 *	if (yytext == type_name)
	 *		return(TYPE_NAME);
	 *
	 *	return(IDENTIFIER);
	 */

	/*
	 *	it actually will only return IDENTIFIER
	 */

	return(IDENTIFIER);
}