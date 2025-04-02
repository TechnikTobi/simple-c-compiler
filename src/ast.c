#include <stdio.h>
#include <stdlib.h>

#include "ast.h"

///////////////////////////////////////////////////////////////////////////////
// ROOT
///////////////////////////////////////////////////////////////////////////////

AST_Root *new_ast(AST_Func_List *functions)
{
	AST_Root *new = (AST_Root*) malloc(sizeof(AST_Root));
	new->functions = functions;
	return new;
}

///////////////////////////////////////////////////////////////////////////////
// FUNCTION
///////////////////////////////////////////////////////////////////////////////

AST_Decl_Func *new_decl_func(SymbolTable *table, AST_Stat *body)
{
	AST_Decl_Func *new = (AST_Decl_Func*) malloc(sizeof(AST_Decl_Func));
	new->table = table;
	new->body = body;
	return new;
}

AST_Func* new_func(AST_Type *return_type, AST_Decl *func_decl, AST_Decl_Func *decl_func)
{
	AST_Func *new = (AST_Func*) malloc(sizeof(AST_Func));
	new->return_type = return_type;
	new->func_declarator = func_decl;
	new->table = decl_func->table;
	new->body = decl_func->body;
	free(decl_func);
	return new;
}

AST_Func_List *new_func_list(void)
{
	AST_Func_List *new = (AST_Func_List*) malloc(sizeof(AST_Func_List));
	new->function = NULL;
	new->next = NULL;
	return new;
}

AST_Func_List *func_list_append(AST_Func_List *current, AST_Func *value)
{
	if (current           == NULL)     current = new_func_list();
	if (current->function == NULL)     { current->function = value; return current; }
	if (current->next     == NULL)     current->next = new_func_list();
	
	func_list_append(current->next, value);

	return current;
}

///////////////////////////////////////////////////////////////////////////////
// TYPE
///////////////////////////////////////////////////////////////////////////////

AST_Type *new_empty_type(void)
{
	AST_Type *new = (AST_Type*) malloc(sizeof(AST_Type));
	new->qualifier_and_specifier = 0;
	new->modifier = 0;
	new->pointer_level = 0;
	return new;
}

AST_Type *new_type(ETypeNames type)
{
	AST_Type *new = new_empty_type();
	new->type = type;
	return new;
}

AST_Type *clone_type(AST_Type *type)
{
	AST_Type *new = new_empty_type();
	
	new->qualifier_and_specifier = type->qualifier_and_specifier;
	new->modifier                = type->modifier;
	new->pointer_level           = type->pointer_level;
	new->type                    = type->type;

	return new;
}

AST_Type *add_qualifier_or_specifier(AST_Type *type, unsigned int qualifier_specifier)
{
	type->qualifier_and_specifier = type->qualifier_and_specifier | qualifier_specifier;
	return type;
}

AST_Type *add_modifier(AST_Type *type, unsigned int modifier)
{
	type->modifier = type->modifier | modifier;
	return type;
}

AST_Type *copy_to_type_from_type(AST_Type *type, AST_Type *specifiers)
{
	type->qualifier_and_specifier = type->qualifier_and_specifier | specifiers->qualifier_and_specifier;
	type->modifier = type->modifier | specifiers->modifier;
	// What about type->pointer_level?
	return type;
}

AST_Type *set_pointer_level(AST_Type *type, unsigned int pointer_level)
{
	type->pointer_level = pointer_level;
	return type;
}

///////////////////////////////////////////////////////////////////////////////
// IDENTIFIER
///////////////////////////////////////////////////////////////////////////////

AST_Iden *new_identifier(char* identifier)
{
	AST_Iden *new = (AST_Iden*) malloc(sizeof(AST_Iden));
	new->identifier = identifier;
	return new;
}

AST_Iden_List* new_identifier_list(void)
{
	AST_Iden_List *new = (AST_Iden_List*) malloc(sizeof(AST_Iden_List));
	new->identifier = NULL;
	new->next = NULL;
	return new;
}

AST_Iden_List* identifier_list_append(AST_Iden_List *current, AST_Iden *value)
{
	if (current             == NULL)   current = new_identifier_list();
	if (current->identifier == NULL)   { current->identifier = value; return current; }
	if (current->next       == NULL)   current->next = new_identifier_list();
	
	identifier_list_append(current->next, value);

	return current;
}

///////////////////////////////////////////////////////////////////////////////
// DECLARATOR
///////////////////////////////////////////////////////////////////////////////

AST_Decl *new_identifier_declarator(AST_Iden *identifier)
{
	AST_Decl *new = (AST_Decl*) malloc(sizeof(AST_Decl));
	new->type = DECL_IDEN;
	new->declarator.iden_declarator.declarator = identifier;
	return new;
}

AST_Decl *new_function_declarator(AST_Iden *identifier, SymbolTable *parameter_table)
{
	AST_Decl *new = (AST_Decl*) malloc(sizeof(AST_Decl));
	new->type = DECL_FUNC;
	new->declarator.func_declarator.declarator = identifier;
	new->declarator.func_declarator.parameter_table = parameter_table;
	return new;
}

AST_Decl_List* new_decl_list(void)
{
	AST_Decl_List *new = (AST_Decl_List*) malloc(sizeof(AST_Decl_List));
	new->declarator = NULL;
	new->next = NULL;
	return new;
}

AST_Decl_List* decl_list_append(AST_Decl_List *current, AST_Decl *value)
{
	if (current             == NULL)   current = new_decl_list();
	if (current->declarator == NULL)   { current->declarator = value; return current; }
	if (current->next       == NULL)   current->next = new_decl_list();
	
	decl_list_append(current->next, value);

	return current;
}

///////////////////////////////////////////////////////////////////////////////
// EXPRESSIONS
///////////////////////////////////////////////////////////////////////////////

AST_Expr *new_const_int_expr(int value)
{
	AST_Expr *new = (AST_Expr*) malloc(sizeof(AST_Expr));
	new->expression_type = EXPR_CONST_INT;
	new->expression.const_int_expression = value;
	return new;
}

AST_Expr *new_const_double_expr(double value)
{
	AST_Expr *new = (AST_Expr*) malloc(sizeof(AST_Expr));
	new->expression_type = EXPR_CONST_DOUBLE;
	new->expression.const_double_expression = value;
	return new;
}

AST_Expr *new_const_char_expr(char value)
{
	AST_Expr *new = (AST_Expr*) malloc(sizeof(AST_Expr));
	new->expression_type = EXPR_CONST_CHAR;
	new->expression.const_char_expression = value;
	return new;
}

AST_Expr *new_const_string_expr(char *value)
{
	AST_Expr *new = (AST_Expr*) malloc(sizeof(AST_Expr));
	new->expression_type = EXPR_CONST_STRING;
	new->expression.const_string_expression = value;
	return new;
}

AST_Expr *new_identifier_expr(AST_Iden *value)
{
	AST_Expr *new = (AST_Expr*) malloc(sizeof(AST_Expr));
	new->expression_type = EXPR_IDENTIFIER;
	new->expression.identifier_expression = value;
	return new;
}

AST_Expr *new_unary_expression(EUnaryOperation op, AST_Expr *expression)
{
	AST_Expr *new = (AST_Expr*) malloc(sizeof(AST_Expr));
	new->expression_type = EXPR_UNARY;
	new->expression.unary_expression.operation = op;
	new->expression.unary_expression.operand = expression;
	return new;
}

AST_Expr* new_sizeof_expr_expression(AST_Expr *expression)
{
	AST_Expr *new = (AST_Expr*) malloc(sizeof(AST_Expr));
	new->expression_type = EXPR_SIZEOF_EXPR;
	new->expression.sizeof_unary_expression.expression = expression;
	return new;
}

AST_Expr* new_sizeof_type_expression(AST_Type *type)
{
	AST_Expr *new = (AST_Expr*) malloc(sizeof(AST_Expr));
	new->expression_type = EXPR_SIZEOF_TYPE;
	new->expression.sizeof_type_expression.type = type;
	return new;
}

AST_Expr *new_binary_expression(EBinaryOperation op, AST_Expr *left, AST_Expr *right)
{
	AST_Expr *new = (AST_Expr*) malloc(sizeof(AST_Expr));
	new->expression_type = EXPR_BINARY;
	new->expression.binary_expression.operation = op;
	new->expression.binary_expression.left = left;
	new->expression.binary_expression.right = right;
	return new;
}

AST_Expr *new_assignment_expression(EBinaryOperation op, AST_Expr* left, AST_Expr* right)
{

	AST_Expr *new = (AST_Expr*) malloc(sizeof(AST_Expr));
	new->expression_type = EXPR_BINARY;
	new->expression.binary_expression.operation = ASSIGNMENT;
	new->expression.binary_expression.left = left;

	switch(op)
	{
		case MULT:
		case DIV:
		case MOD:
		case PLUS:
		case MINUS:
		case SHIFT_L:
		case SHIFT_R:
		case B_AND:
		case B_XOR:
		case B_OR:
			new->expression.binary_expression.right = new_binary_expression(op, left, right);
			break;
		default:
			if (op != ASSIGNMENT) printf("WARNING: new_assignment_expression HAS ILLEGAL SECONDARY OPERATION!");
			new->expression.binary_expression.right = right;
			break;
			
	}
	
	return new;
}

AST_Expr *new_ternary_expression(AST_Expr *condition, AST_Expr *if_expression, AST_Expr *else_expression)
{
	AST_Expr *new = (AST_Expr*) malloc(sizeof(AST_Expr));
	new->expression_type = EXPR_TERNARY;
	new->expression.ternary_expression.condition = condition;
	new->expression.ternary_expression.if_expression = if_expression;
	new->expression.ternary_expression.else_expression = else_expression;
	return new;
}

AST_Expr *new_cast_expression(AST_Type *type, AST_Expr *expression)
{
	AST_Expr *new = (AST_Expr*) malloc(sizeof(AST_Expr));
	new->expression_type = EXPR_CAST;
	new->expression.cast_expression.type = type;
	new->expression.cast_expression.expression = expression;
	return new;
}

AST_Expr *new_call_expression(AST_Expr *expression, AST_Expr_List *args)
{
	AST_Expr *new = (AST_Expr*) malloc(sizeof(AST_Expr));
	new->expression_type = EXPR_CALL;
	new->expression.call_expression.expression = expression;
	new->expression.call_expression.args = args;
	return new;
}

AST_Expr* new_array_access_expression(AST_Expr *array, AST_Expr *index)
{
	AST_Expr *new = (AST_Expr*) malloc(sizeof(AST_Expr));
	new->expression_type = EXPR_ARRAY_ACCESS;
	new->expression.array_access_expression.array = array;
	new->expression.array_access_expression.index = index;
	return new;
}

AST_Expr* new_struct_member_access_expression(AST_Expr *structure, AST_Iden *member)
{
	AST_Expr *new = (AST_Expr*) malloc(sizeof(AST_Expr));
	new->expression_type = EXPR_STRUCT_MEMBER_ACCESS;
	new->expression.struct_member_access_expression.structure = structure;
	new->expression.struct_member_access_expression.member = member;
	return new;
}

AST_Expr* new_struct_pointer_member_access_expression(AST_Expr *pointer_structure, AST_Iden *member)
{
	AST_Expr *new = (AST_Expr*) malloc(sizeof(AST_Expr));
	new->expression_type = EXPR_STRUCT_POINTER_MEMBER_ACCESS;
	new->expression.struct_pointer_member_access_expression.pointer_structure = pointer_structure;
	new->expression.struct_pointer_member_access_expression.member = member;
	return new;
}

AST_Expr_List *new_expression_list(void)
{
	AST_Expr_List *new = (AST_Expr_List*) malloc(sizeof(AST_Expr_List));
	new->expression = NULL;
	new->next = NULL;
	return new;
}

AST_Expr_List *expression_list_append(AST_Expr_List *current, AST_Expr *value)
{
	if (current             == NULL)   current = new_expression_list();
	if (current->expression == NULL)   { current->expression = value; return current; }
	if (current->next       == NULL)   current->next = new_expression_list();
	
	expression_list_append(current->next, value);

	return current;
}

///////////////////////////////////////////////////////////////////////////////
// STATEMENTS
///////////////////////////////////////////////////////////////////////////////

AST_Stat *new_expression_statement(AST_Expr *expression)
{
	AST_Stat *new = (AST_Stat*) malloc(sizeof(AST_Stat));
	new->statement_type = STAT_EXPR;
	new->statement.expression = expression;
	return new;
}

AST_Stat *new_statement(void)
{
	AST_Stat *new = (AST_Stat*) malloc(sizeof(AST_Stat));
	return new;
}

AST_Stat_List *new_statement_list(void)
{
	AST_Stat_List *new = (AST_Stat_List*) malloc(sizeof(AST_Stat_List));
	new->statement = NULL;
	new->next = NULL;
	return new;
}

AST_Stat_List *statement_list_append(AST_Stat_List *current, AST_Stat *value)
{
	if (current            == NULL)    current = new_statement_list();
	if (current->statement == NULL)    { current->statement = value; return current; }
	if (current->next      == NULL)    current->next = new_statement_list();
	
	statement_list_append(current->next, value);

	return current;
}

AST_Stat *new_compound_statement(AST_Stat_List *list)
{
	AST_Stat *new = (AST_Stat*) malloc(sizeof(AST_Stat));
	new->statement_type = STAT_COMPOUND;
	new->statement.compound = list;
	return new;
}

AST_Stat *new_if_statement(AST_Expr *condition, AST_Stat *statement)
{
	AST_Stat *new = (AST_Stat*) malloc(sizeof(AST_Stat));
	new->statement_type = STAT_IF;
	new->statement.if_statement.condition = condition;
	new->statement.if_statement.statement = statement;
	return new;
}

AST_Stat* new_switch_statement(AST_Expr *expression, AST_Stat* body)
{
	AST_Stat *new = (AST_Stat*) malloc(sizeof(AST_Stat));
	new->statement_type = STAT_SWITCH;
	new->statement.switch_statement.expression = expression;
	new->statement.switch_statement.body = body;
	return new;
}

AST_Stat *new_if_else_statement(AST_Expr *condition, AST_Stat *if_statement, AST_Stat *else_statement)
{
	AST_Stat *new = (AST_Stat*) malloc(sizeof(AST_Stat));
	new->statement_type = STAT_IF_ELSE;
	new->statement.if_else_statement.condition = condition;
	new->statement.if_else_statement.if_statement = if_statement;
	new->statement.if_else_statement.else_statement = else_statement;
	return new;
}

AST_Stat *new_for_statement(AST_Stat *stat1, AST_Stat *stat2, AST_Expr *expression, AST_Stat *body)
{
	if (stat1->statement_type != STAT_EXPR) printf("WARNING: new_for_statement: stat1 IS OF WRONG STATEMENT TYPE!");
	if (stat2->statement_type != STAT_EXPR) printf("WARNING: new_for_statement: stat2 IS OF WRONG STATEMENT TYPE!");

	AST_Stat *new = (AST_Stat*) malloc(sizeof(AST_Stat));
	new->statement_type = STAT_FOR;
	new->statement.for_statement.init_expression = stat1->statement.expression;
	new->statement.for_statement.condition = stat2->statement.expression;
	new->statement.for_statement.update_expression = expression;
	new->statement.for_statement.body = body;
	return new;
}

AST_Stat* new_while_statement(AST_Expr *condition, AST_Stat *body)
{
	AST_Stat *new = (AST_Stat*) malloc(sizeof(AST_Stat));
	new->statement_type = STAT_WHILE;
	new->statement.while_statement.condition = condition;
	new->statement.while_statement.body = body;
	return new;
}

AST_Stat* new_do_while_statement(AST_Stat *body, AST_Expr *condition)
{
	AST_Stat *new = (AST_Stat*) malloc(sizeof(AST_Stat));
	new->statement_type = STAT_DO_WHILE;
	new->statement.do_while_statement.body = body;
	new->statement.do_while_statement.condition = condition;
	return new;
}


AST_Stat *new_jump_statement(EStatementType type, void *ident_or_expr)
{
	AST_Stat *new = (AST_Stat*) malloc(sizeof(AST_Stat));
	new->statement_type = type;
	switch (type)
	{
		case STAT_GOTO:
			new->statement.jump_statement.value.identifier = (AST_Iden*) ident_or_expr;
			break;
		case STAT_RETURN_EXPR:
			new->statement.jump_statement.value.expression = (AST_Expr*) ident_or_expr;
			break;
		case STAT_BREAK:
		case STAT_CONTINUE:
		case STAT_RETURN:
			break;
		default:
			printf("WARNING: new_jump_statement GOT ILLEGAL STATEMENT TYPE!");
	}
	return new;
}

AST_Stat* new_labeled_statement(AST_Iden *identifier, AST_Expr *const_expression, AST_Stat *statement)
{
	AST_Stat *new = (AST_Stat*) malloc(sizeof(AST_Stat));
	new->statement_type = STAT_LABELED;
	new->statement.labeled_statement.identifier = identifier;
	new->statement.labeled_statement.const_expression = const_expression;
	new->statement.labeled_statement.statement = statement;
	return new;	
}
