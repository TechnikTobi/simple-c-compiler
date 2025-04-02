#ifndef AST_H
#define AST_H

#include "typedefs.h"
#include "symbol_table.h"

///////////////////////////////////////////////////////////////////////////////
// ROOT
///////////////////////////////////////////////////////////////////////////////

struct 
S_AST_Root
{
	AST_Func_List            *functions;
};

AST_Root* new_ast(AST_Func_List *functions);

///////////////////////////////////////////////////////////////////////////////
// TYPE
///////////////////////////////////////////////////////////////////////////////

struct 
S_AST_Type
{
	unsigned int             qualifier_and_specifier;
	unsigned int             modifier;
	unsigned int             pointer_level;
	ETypeNames               type;
};

AST_Type *new_empty_type(void);
AST_Type *new_type(ETypeNames type);
AST_Type *clone_type(AST_Type *type);
AST_Type *add_qualifier_or_specifier(AST_Type *type, unsigned int qualifier_specifier);
AST_Type *add_modifier(AST_Type *type, unsigned int modifier);
AST_Type *copy_to_type_from_type(AST_Type *type, AST_Type *specifiers);
AST_Type *set_pointer_level(AST_Type *type, unsigned int pointer_level);

///////////////////////////////////////////////////////////////////////////////
// DECLARATOR
///////////////////////////////////////////////////////////////////////////////

struct
S_AST_Decl
{
	EDeclaratorTypes         type;
	union
	{
		struct
		{
			AST_Iden         *declarator;
		} iden_declarator;
		struct
		{
			AST_Iden         *declarator;
			SymbolTable      *parameter_table;
		} func_declarator;
	} declarator;
};

AST_Decl *new_identifier_declarator(AST_Iden *identifier);
AST_Decl *new_function_declarator(AST_Iden *identifier, SymbolTable *parameter_table);

struct 
S_AST_Decl_List
{
	AST_Decl                 *declarator;
	AST_Decl_List            *next;
};

AST_Decl_List* new_decl_list(void);
AST_Decl_List* decl_list_append(AST_Decl_List *current, AST_Decl *value);

///////////////////////////////////////////////////////////////////////////////
// FUNCTION
///////////////////////////////////////////////////////////////////////////////

struct
S_AST_Decl_Func
{
	SymbolTable              *table;
	AST_Stat                 *body;
};

AST_Decl_Func *new_decl_func(SymbolTable *table, AST_Stat *body);

struct 
S_AST_Func
{
	AST_Type                 *return_type;
	AST_Decl                 *func_declarator;
	SymbolTable              *table;
	AST_Stat                 *body;
};

AST_Func* new_func(AST_Type *return_type, AST_Decl *func_decl, AST_Decl_Func *decl_func);

struct 
S_AST_Func_List
{
	AST_Func *function;
	AST_Func_List *next;
};

AST_Func_List* new_func_list(void);
AST_Func_List* func_list_append(AST_Func_List *current, AST_Func *value);

///////////////////////////////////////////////////////////////////////////////
// IDENTIFIER
///////////////////////////////////////////////////////////////////////////////

struct
S_AST_Iden
{
	char                     *identifier;
};

AST_Iden* new_identifier(char* identifier);

struct
S_AST_Iden_List
{
	AST_Iden *identifier;
	AST_Iden_List *next;
};

AST_Iden_List* new_identifier_list(void);
AST_Iden_List* identifier_list_append(AST_Iden_List *current, AST_Iden *value);

///////////////////////////////////////////////////////////////////////////////
// EXPRESSION
///////////////////////////////////////////////////////////////////////////////

struct 
S_AST_Expr
{
	EExpressionType expression_type;
	union
	{
		int                  const_int_expression;
		double               const_double_expression;
		char                 const_char_expression;
		char                 *const_string_expression;
		AST_Iden             *identifier_expression;

		struct
		{
			EUnaryOperation  operation;
			AST_Expr         *operand;
		} unary_expression;
		struct
		{
			AST_Expr         *expression;
		} sizeof_unary_expression;
		struct
		{
			AST_Type         *type;
		} sizeof_type_expression;

		struct
		{
			EBinaryOperation operation;
			AST_Expr         *left;
			AST_Expr         *right;
		} binary_expression;
		struct
		{
			AST_Type         *type;
			AST_Expr         *expression;
		} cast_expression;
		struct
		{
			AST_Expr         *array;
			AST_Expr         *index;
		} array_access_expression;
		struct
		{
			AST_Expr         *structure;
			AST_Iden         *member;
		} struct_member_access_expression;
		struct
		{
			AST_Expr         *pointer_structure;
			AST_Iden         *member;
		} struct_pointer_member_access_expression;
		struct
		{
			AST_Expr         *expression;
			AST_Expr_List    *args;
		} call_expression;

		struct
		{
			AST_Expr         *condition;
			AST_Expr         *if_expression;
			AST_Expr         *else_expression;
		} ternary_expression;
	} expression;
};

AST_Expr* new_const_int_expr(int value);
AST_Expr* new_const_double_expr(double value);
AST_Expr* new_const_char_expr(char value);
AST_Expr* new_const_string_expr(char* value);

AST_Expr* new_identifier_expr(AST_Iden *identifier);

AST_Expr* new_unary_expression(EUnaryOperation op, AST_Expr *expression);
AST_Expr* new_binary_expression(EBinaryOperation op, AST_Expr *left, AST_Expr *right);
AST_Expr* new_assignment_expression(EBinaryOperation op, AST_Expr *left, AST_Expr *right);
AST_Expr* new_ternary_expression(AST_Expr *condition, AST_Expr *if_expression, AST_Expr *else_expression);

AST_Expr* new_sizeof_expr_expression(AST_Expr *expression);
AST_Expr* new_sizeof_type_expression(AST_Type *type);

AST_Expr* new_cast_expression(AST_Type *type, AST_Expr *expression);
AST_Expr* new_call_expression(AST_Expr *expression, AST_Expr_List *args);

AST_Expr* new_array_access_expression(AST_Expr *array, AST_Expr *index);
AST_Expr* new_struct_member_access_expression(AST_Expr *structure, AST_Iden *member);
AST_Expr* new_struct_pointer_member_access_expression(AST_Expr *pointer_structure, AST_Iden *member);

struct
S_AST_Expr_List
{
	AST_Expr *expression;
	AST_Expr_List *next;
};

AST_Expr_List* new_expression_list(void); 
AST_Expr_List* expression_list_append(AST_Expr_List *current, AST_Expr *value);

///////////////////////////////////////////////////////////////////////////////
// STATEMENT
///////////////////////////////////////////////////////////////////////////////

struct 
S_AST_Stat
{
	EStatementType statement_type;
	union
	{
		AST_Expr             *expression;
		AST_Stat_List        *compound;

		struct
		{
			AST_Expr         *condition;
			AST_Stat         *statement;
		} if_statement;
		struct
		{
			AST_Expr         *condition;
			AST_Stat         *if_statement;
			AST_Stat         *else_statement;
		} if_else_statement;
		struct
		{
			AST_Expr         *expression;
			AST_Stat         *body;
		} switch_statement;
		struct
		{
			AST_Expr         *init_expression;
			AST_Expr         *condition;
			AST_Expr         *update_expression;
			AST_Stat         *body;
		} for_statement;

		// Technically, the following two are identical, but I wanted to 
		// emphasize their difference
		struct
		{
			AST_Expr         *condition;
			AST_Stat         *body;
		} while_statement;
		struct
		{
			AST_Stat         *body;
			AST_Expr         *condition;
		} do_while_statement;

		struct
		{
			union
			{
				AST_Iden     *identifier;
				AST_Expr     *expression;
			} value;
		} jump_statement;

		struct
		{
			AST_Iden         *identifier;
			AST_Expr         *const_expression;
			// If both are null -> Label = DEFAULT
			AST_Stat         *statement;
		} labeled_statement;
	} statement;
};

AST_Stat* new_expression_statement(AST_Expr *expression);
AST_Stat* new_if_statement(AST_Expr *condition, AST_Stat* statement);
AST_Stat* new_if_else_statement(AST_Expr *condition, AST_Stat *if_statement, AST_Stat *else_statement);
AST_Stat* new_switch_statement(AST_Expr *expression, AST_Stat* body);
AST_Stat* new_for_statement(AST_Stat *stat1, AST_Stat *stat2, AST_Expr *expression, AST_Stat *body);
AST_Stat* new_while_statement(AST_Expr *condition, AST_Stat *body);
AST_Stat* new_do_while_statement(AST_Stat *body, AST_Expr *condition);
AST_Stat* new_compound_statement(AST_Stat_List *list);
AST_Stat* new_jump_statement(EStatementType type, void *ident_or_expr);
AST_Stat* new_labeled_statement(AST_Iden *identifier, AST_Expr *const_expression, AST_Stat *statement);

struct 
S_AST_Stat_List
{
	AST_Stat* statement;
	AST_Stat_List* next;
};

AST_Stat_List* statement_list_append(AST_Stat_List *current, AST_Stat *value);

#endif
