%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "typedefs.h"
#include "symbol_table.h"

int yylex(void);
void yyerror(char*);
AST_Root *tree;

%}


%token SIZEOF
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN

%token TYPEDEF EXTERN STATIC AUTO REGISTER
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token STRUCT UNION ENUM ELLIPSIS

%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%nonassoc NO_ELSE
%nonassoc ELSE

%start translation_unit

%union {
	int                                int_value;
	unsigned int                       uint_value;
	double                             double_value;
	char                               char_value;
	char                               *string_value;
	
	EUnaryOperation                    unary_op;
	EBinaryOperation                   binary_op;
	
	AST_Iden                           *iden;
	AST_Type                           *type;
	AST_Decl                           *decl;
	AST_Expr                           *expr;
	AST_Stat                           *stat;
	AST_Func                           *func;

	AST_Decl_Func                      *decl_func;

	AST_Iden_List                      *iden_list;
	AST_Decl_List                      *decl_list;
	AST_Expr_List                      *expr_list;
	AST_Stat_List                      *stat_list;
	AST_Func_List                      *func_list;

	SymbolTable                        *table;
	SymbolTableEntry                   *table_entry;
}

%token <int_value>                     INT_CONSTANT;
%token <double_value>                  DOUBLE_CONSTANT;
%token <char_value>                    CHAR_CONSTANT;
%token <string_value>                  STRING_LITERAL;

%token <iden>                          IDENTIFIER;

%type <uint_value>                     type_qualifier;
%type <uint_value>                     storage_class_specifier;
%type <uint_value>                     type_modifier;
%type <uint_value>                     type_modifier_list;

%type <type>                           type_name;
%type <type>                           type_specifier;
%type <type>                           modified_type_specifier;
%type <type>                           declaration_specifiers;
%type <type>                           specifier_qualifier_list;

%type <uint_value>                     abstract_declarator;
%type <uint_value>                     pointer;

%type <decl>                           declarator;
%type <decl>                           direct_declarator;
%type <decl>                           function_declarator;

%type <expr>                           primary_expression;
%type <expr>                           postfix_expression;
%type <expr>                           unary_expression;
%type <expr>                           cast_expression;
%type <expr>                           multiplicative_expression;
%type <expr>                           additive_expression;
%type <expr>                           shift_expression;
%type <expr>                           relational_expression;
%type <expr>                           equality_expression;
%type <expr>                           and_expression;
%type <expr>                           exclusive_or_expression;
%type <expr>                           inclusive_or_expression;
%type <expr>                           logical_and_expression;
%type <expr>                           logical_or_expression;
%type <expr>                           conditional_expression;
%type <expr>                           assignment_expression;
%type <expr>                           expression;
%type <expr>                           constant_expression;

%type <unary_op>                       unary_operator;
%type <binary_op>                      assignment_operator;

%type <stat>                           statement;
%type <stat>                           labeled_statement;
%type <stat>                           compound_statement;
%type <stat>                           expr_statement;
%type <stat>                           selection_statement;
%type <stat>                           iteration_statement;
%type <stat>                           jump_statement;

%type <func>                           function_definition;
%type <decl_func>                      function_compound_statement;

%type <decl_list>                      declarator_list;
%type <expr_list>                      argument_expression_list;
%type <stat_list>                      statement_list;
%type <func_list>                      function_definition_list;

%type <table>                          declaration_list;
%type <table>                          declaration;

%type <table>                          parameter_list;
%type <table>                          parameter;

%%

primary_expression
	: IDENTIFIER                                                                { $$ = new_identifier_expr($1); }
	| INT_CONSTANT                                                              { $$ = new_const_int_expr($1); }
	| DOUBLE_CONSTANT                                                           { $$ = new_const_double_expr($1); }
	| CHAR_CONSTANT                                                             { $$ = new_const_char_expr($1); }
	| STRING_LITERAL                                                            { $$ = new_const_string_expr($1); }
	| '(' expression ')'                                                        { $$ = $2; }
	;

postfix_expression
	: primary_expression                                                        { $$ = $1; }
	| postfix_expression '[' expression ']'                                     { $$ = new_array_access_expression($1, $3); }
	| postfix_expression '(' ')'                                                { $$ = new_call_expression($1, NULL); }
	| postfix_expression '(' argument_expression_list ')'                       { $$ = new_call_expression($1, $3); }
	| postfix_expression INC_OP                                                 { $$ = new_unary_expression(POSTFIX_INC, $1); }
	| postfix_expression DEC_OP                                                 { $$ = new_unary_expression(POSTFIX_DEC, $1); }
	;

argument_expression_list
	: assignment_expression                                                     { $$ = expression_list_append(NULL, $1); }
	| argument_expression_list ',' assignment_expression                        { $$ = expression_list_append($1, $3); }
	;

unary_expression
	: postfix_expression                                                        { $$ = $1; }
	| INC_OP unary_expression                                                   { $$ = new_unary_expression(PREFIX_INC, $2); }
	| DEC_OP unary_expression                                                   { $$ = new_unary_expression(PREFIX_DEC, $2); }
	| unary_operator cast_expression                                            { $$ = new_unary_expression($1, $2); }
	| SIZEOF unary_expression                                                   { $$ = new_sizeof_expr_expression($2); }
	| SIZEOF '(' type_name ')'                                                  { $$ = new_sizeof_type_expression($3); }
	;

unary_operator
	: '&'                                                                       { $$ = REF; }
	| '*'                                                                       { $$ = DEREF; }
	| '+'                                                                       { $$ = UNARY_PLUS; }
	| '-'                                                                       { $$ = UNARY_MINUS; }
	| '~'                                                                       { $$ = B_ONE_COMPLEMENT; }
	| '!'                                                                       { $$ = L_NOT; }
	;

cast_expression
	: unary_expression                                                          { $$ = $1; }
	| '(' type_name ')' cast_expression                                         { $$ = new_cast_expression($2, $4); }
	;

multiplicative_expression
	: cast_expression                                                           { $$ = $1; }
	| multiplicative_expression '*' cast_expression                             { $$ = new_binary_expression(MULT, $1, $3); }
	| multiplicative_expression '/' cast_expression                             { $$ = new_binary_expression(DIV, $1, $3); }
	| multiplicative_expression '%' cast_expression                             { $$ = new_binary_expression(MOD, $1, $3); }
	;

additive_expression
	: multiplicative_expression                                                 { $$ = $1; }
	| additive_expression '+' multiplicative_expression                         { $$ = new_binary_expression(PLUS, $1, $3); }
	| additive_expression '-' multiplicative_expression                         { $$ = new_binary_expression(MINUS, $1, $3); }
	;

shift_expression
	: additive_expression                                                       { $$ = $1; }
	| shift_expression LEFT_OP additive_expression                              { $$ = new_binary_expression(SHIFT_L, $1, $3); }
	| shift_expression RIGHT_OP additive_expression                             { $$ = new_binary_expression(SHIFT_R, $1, $3); }
	;

relational_expression
	: shift_expression                                                          { $$ = $1; }
	| relational_expression '<' shift_expression                                { $$ = new_binary_expression(LESS, $1, $3); }
	| relational_expression '>' shift_expression                                { $$ = new_binary_expression(GREATER, $1, $3); }
	| relational_expression LE_OP shift_expression                              { $$ = new_binary_expression(LESS_EQUAL, $1, $3); }
	| relational_expression GE_OP shift_expression                              { $$ = new_binary_expression(GREATER_EQUAL, $1, $3); }
	;

equality_expression
	: relational_expression                                                     { $$ = $1; }
	| equality_expression EQ_OP relational_expression                           { $$ = new_binary_expression(EQUAL, $1, $3); }
	| equality_expression NE_OP relational_expression                           { $$ = new_binary_expression(NOT_EQUAL, $1, $3); }
	;

and_expression
	: equality_expression                                                       { $$ = $1; }
	| and_expression '&' equality_expression                                    { $$ = new_binary_expression(B_AND, $1, $3); }
	;

exclusive_or_expression
	: and_expression                                                            { $$ = $1; }
	| exclusive_or_expression '^' and_expression                                { $$ = new_binary_expression(B_XOR, $1, $3); }
	;

inclusive_or_expression
	: exclusive_or_expression                                                   { $$ = $1; }
	| inclusive_or_expression '|' exclusive_or_expression                       { $$ = new_binary_expression(B_OR, $1, $3); }
	;

logical_and_expression
	: inclusive_or_expression                                                   { $$ = $1; }
	| logical_and_expression AND_OP inclusive_or_expression                     { $$ = new_binary_expression(L_AND, $1, $3); }
	;

logical_or_expression
	: logical_and_expression                                                    { $$ = $1; }
	| logical_or_expression OR_OP logical_and_expression                        { $$ = new_binary_expression(L_OR, $1, $3); }
	;

conditional_expression
	: logical_or_expression                                                     { $$ = $1; }
	| logical_or_expression '?' expression ':' conditional_expression           { $$ = new_ternary_expression($1, $3, $5); }
	;

assignment_expression
	: conditional_expression                                                    { $$ = $1; }
	| unary_expression assignment_operator assignment_expression                { $$ = new_assignment_expression($2, $1, $3); }
	;

assignment_operator
	: '='                                                                       { $$ = ASSIGNMENT; }
	| MUL_ASSIGN                                                                { $$ = MULT; }
	| DIV_ASSIGN                                                                { $$ = DIV; }
	| MOD_ASSIGN                                                                { $$ = MOD; }
	| ADD_ASSIGN                                                                { $$ = PLUS; }
	| SUB_ASSIGN                                                                { $$ = MINUS; }
	| LEFT_ASSIGN                                                               { $$ = SHIFT_L; }
	| RIGHT_ASSIGN                                                              { $$ = SHIFT_R; }
	| AND_ASSIGN                                                                { $$ = B_AND; }
	| XOR_ASSIGN                                                                { $$ = B_XOR; }
	| OR_ASSIGN                                                                 { $$ = B_OR; }
	;

expression
	: assignment_expression                                                     { $$ = $1; }
	| expression ',' assignment_expression                                      { $$ = new_binary_expression(CONCAT, $1, $3); }
	;

constant_expression
	: conditional_expression                                                    { $$ = $1; }
	;

declaration
	: declaration_specifiers declarator_list ';'                                { $$ = new_symbol_table_from_decl_list($1, $2); }
	;

declaration_specifiers
	: storage_class_specifier                                                   { $$ = add_qualifier_or_specifier(new_empty_type(), $1); }
	| storage_class_specifier declaration_specifiers                            { $$ = add_qualifier_or_specifier($2, $1); }
	| modified_type_specifier                                                   { $$ = $1; }
	| modified_type_specifier declaration_specifiers                            { $$ = copy_to_type_from_type($1, $2); }
	| type_qualifier                                                            { $$ = add_qualifier_or_specifier(new_empty_type(), $1); }
	| type_qualifier declaration_specifiers                                     { $$ = add_qualifier_or_specifier($2, $1); }
	;

declarator_list
	: declarator                                                                { $$ = decl_list_append(NULL, $1); }
	| declarator_list ',' declarator                                            { $$ = decl_list_append($1, $3); }
	;

type_qualifier
	: CONST                                                                     { $$ = 64; }
	| VOLATILE                                                                  { $$ = 32; }
	;

storage_class_specifier
	: TYPEDEF                                                                   { $$ = 16; }
	| EXTERN                                                                    { $$ = 8; }
	| STATIC                                                                    { $$ = 4; }
	| AUTO                                                                      { $$ = 2; }
	| REGISTER                                                                  { $$ = 1; }
	;

modified_type_specifier
	: type_modifier_list type_specifier                                         { $$ = add_modifier($2, $1); }
	| type_specifier                                                            { $$ = $1; }
	;

type_specifier
	: VOID                                                                      { $$ = new_type(PRIM_VOID); }
	| CHAR                                                                      { $$ = new_type(PRIM_CHAR); }
	| INT                                                                       { $$ = new_type(PRIM_INT); }
	| FLOAT                                                                     { $$ = new_type(PRIM_DOUBLE); }
	| DOUBLE                                                                    { $$ = new_type(PRIM_DOUBLE); }
	;

type_modifier_list
	: type_modifier                                                             { $$ = $1; }
	| type_modifier_list type_modifier                                          { $$ = $1 | $2; }
	;

type_modifier
	: SHORT                                                                     { $$ = 8; }
	| LONG                                                                      { $$ = 4; }
	| SIGNED                                                                    { $$ = 2; }
	| UNSIGNED                                                                  { $$ = 1; }
	;

specifier_qualifier_list
	: modified_type_specifier specifier_qualifier_list                          { $$ = copy_to_type_from_type($1, $2); }
	| modified_type_specifier                                                   { $$ = $1; }
	| type_qualifier specifier_qualifier_list                                   { $$ = add_qualifier_or_specifier($2, $1); }
	| type_qualifier                                                            { $$ = add_qualifier_or_specifier(new_empty_type(), $1); }
	;

declarator
	: direct_declarator                                                         { $$ = $1; }
	;

direct_declarator
	: IDENTIFIER                                                                { $$ = new_identifier_declarator($1); }
	;

type_name
	: specifier_qualifier_list                                                  { $$ = $1; }
	| specifier_qualifier_list abstract_declarator                              { $$ = set_pointer_level($1, $2); }
	;

abstract_declarator
	: pointer                                                                   { $$ = $1; }
	;

pointer
	: '*'                                                                       { $$ = 1; }
	| '*' pointer                                                               { $$ = $2 + 1; }
	;

function_declarator
	: IDENTIFIER '(' ')'                                                        { $$ = new_function_declarator($1, NULL); }
	| IDENTIFIER '(' parameter_list ')'                                         { $$ = new_function_declarator($1, $3); }
	;

parameter_list
	: parameter                                                                 { $$ = symbol_table_append_end(NULL, $1); }
	| parameter parameter_list                                                  { $$ = symbol_table_append_end($1, $2); }
	; 

parameter
	: declaration_specifiers declarator_list                                    { $$ = new_symbol_table_from_decl_list($1, $2); }
	;

statement
	: labeled_statement                                                         { $$ = $1; }
	| compound_statement                                                        { $$ = $1; }
	| expr_statement                                                            { $$ = $1; }
	| selection_statement                                                       { $$ = $1; }
	| iteration_statement                                                       { $$ = $1; }
	| jump_statement                                                            { $$ = $1; }
	;

labeled_statement
	: IDENTIFIER ':' statement                                                  { $$ = new_labeled_statement($1, NULL, $3); }
	| CASE constant_expression ':' statement                                    { $$ = new_labeled_statement(NULL, $2, $4); }
	| DEFAULT ':' statement                                                     { $$ = new_labeled_statement(NULL, NULL, $3); }
	;

compound_statement
	: '{' '}'                                                                   { $$ = NULL; }
	| '{' statement_list '}'                                                    { $$ = new_compound_statement($2); }
	;

function_compound_statement
	: '{' '}'                                                                   { $$ = new_decl_func(NULL, NULL); }
	| '{' statement_list '}'                                                    { $$ = new_decl_func(NULL, new_compound_statement($2)); }
	| '{' declaration_list '}'                                                  { $$ = new_decl_func($2, NULL); }
	| '{' declaration_list statement_list '}'                                   { $$ = new_decl_func($2, new_compound_statement($3)); }
	;

declaration_list
	: declaration                                                               { $$ = symbol_table_append_end(NULL, $1); }
	| declaration_list declaration                                              { $$ = symbol_table_append_end($1, $2); }
	;

statement_list
	: statement                                                                 { $$ = statement_list_append(NULL, $1); }
	| statement_list statement                                                  { $$ = statement_list_append($1, $2); }
	;

expr_statement
	: ';'                                                                       { $$ = NULL; }
	| expression ';'                                                            { $$ = new_expression_statement($1); }
	;

selection_statement
	: IF '(' expression ')' statement %prec NO_ELSE                             { $$ = new_if_statement($3, $5); }
	| IF '(' expression ')' statement ELSE statement                            { $$ = new_if_else_statement($3, $5, $7); }
	| SWITCH '(' expression ')' statement                                       { $$ = new_switch_statement($3, $5); }
	;

iteration_statement
	: WHILE '(' expression ')' statement                                        { $$ = new_while_statement($3, $5); }
	| DO statement WHILE '(' expression ')' ';'                                 { $$ = new_do_while_statement($2, $5); }
	| FOR '(' expr_statement expr_statement ')' statement                       { $$ = new_for_statement($3, $4, NULL, $6); }
	| FOR '(' expr_statement expr_statement expression ')' statement            { $$ = new_for_statement($3, $4, $5, $7); }
	;

jump_statement
	: GOTO IDENTIFIER ';'                                                       { $$ = new_jump_statement(STAT_GOTO, $2); }
	| CONTINUE ';'                                                              { $$ = new_jump_statement(STAT_CONTINUE, NULL); }
	| BREAK ';'                                                                 { $$ = new_jump_statement(STAT_BREAK, NULL); }
	| RETURN ';'                                                                { $$ = new_jump_statement(STAT_RETURN, NULL); }
	| RETURN expression ';'                                                     { $$ = new_jump_statement(STAT_RETURN_EXPR, $2); }
	;

translation_unit
	: function_definition_list                                                  { tree = new_ast($1); }
	;

function_definition_list
	: function_definition                                                       { $$ = func_list_append(NULL, $1); }
	| function_definition_list function_definition                              { $$ = func_list_append($1, $2); }
	;

function_definition
	: declaration_specifiers function_declarator function_compound_statement    { $$ = new_func($1, $2, $3); }
	| function_declarator function_compound_statement                           { $$ = new_func(NULL, $1, $2); }
	;


%%

#include <stdio.h>

extern char yytext[];
extern int column;

void yyerror(char *s)
{
	// Deactivating the body of this function as the output for pointing out
	// that an error occured gets handled in main instead, as for A1 we are
	// only interested in whether or not an error occured but not where it is
	// located in the source code.
	
	// fflush(stdout);
	// printf("\n%*s\n%*s\n", column, "^", column, s);
}