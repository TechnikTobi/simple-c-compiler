#include <stdio.h>
#include <string.h>

#include "ast.h"
#include "ast_writer.h"

#define FONTNAME "Arial"

int 
write_ast_to_dot_file
(
	char* filename, 
	AST_Root* root
)
{

	// Variable Setup
	FILE *file_pointer;
	int node_counter = 1;

	// Open File
	file_pointer = fopen(filename, "w");
	if (file_pointer == NULL)
	{
		printf("Could not open .dot file!");
		return 1;
	}

	// Start .dot file
	fprintf(file_pointer, "digraph D {\nsplines=polyline\noverlap=false\nnodesep=0.1\n");

	// Write actual AST to .dot file
	write_node_to_dot_file(file_pointer, root, AST_ROOT, &node_counter);

	// End .dot file
	fprintf(file_pointer, "}");

	// Close file and exit
	fclose(file_pointer);
	return 0;
}

int
write_node_to_dot_file
(
	FILE *file_pointer,
	void *node,
	EASTNodeType type,
	int* node_counter
)
{
	int this_node_counter = (*node_counter)++;

	switch (type)
	{
		case AST_ROOT:
			write_root_to_dot_file(file_pointer, (AST_Root*)node, this_node_counter, node_counter);
			break;
		case AST_FUNC:
			write_func_to_dot_file(file_pointer, (AST_Func*)node, this_node_counter, node_counter);
			break;
		case AST_STAT:
			write_stat_to_dot_file(file_pointer, (AST_Stat*)node, this_node_counter, node_counter);
			break;
		case AST_EXPR:
			write_expr_to_dot_file(file_pointer, (AST_Expr*)node, this_node_counter, node_counter);
			break;
		case AST_IDEN:
			write_iden_to_dot_file(file_pointer, (AST_Iden*)node, this_node_counter, node_counter);
			break;
		case AST_TYPE:
			write_type_to_dot_file(file_pointer, (AST_Type*)node, this_node_counter, node_counter);
			break;
		default:
			break;
	}

	// Return the node_counter of the node processed for the callee to draw relations
	return this_node_counter;
}

void write_root_to_dot_file(FILE *file_pointer, AST_Root *node, int this_node_counter, int* node_counter)
{
	fprintf(file_pointer, "%i [label=\"ROOT\", fontname=\"%s\" ];\n", this_node_counter, FONTNAME);

	AST_Func_List *functions = node->functions;
	int counter = 1;
	while (functions != NULL)
	{
		int child_node_counter = write_node_to_dot_file(file_pointer, functions->function, AST_FUNC, node_counter);
		write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, NULL, counter++);
		functions = functions->next;
	}
}

void write_parent_child_to_dot_file(FILE *file_pointer, int parent, int child, char* label, int counter)
{ 
	fprintf(file_pointer, "%i -> %i", parent, child); 	

	if (label == NULL && counter < 0)
	{
		fprintf(file_pointer, ";\n"); 	
		return;
	}

	fprintf(file_pointer, " [minlen=4, label=\"");
	if (label != NULL) fprintf(file_pointer, "%s ", label);
	if (counter >= 0) fprintf(file_pointer, "%i", counter);
	fprintf(file_pointer, "\", labeldistance=0, fontname=\"%s\" ];\n", FONTNAME);
}

void write_type_to_dot_file(FILE *file_pointer, AST_Type *type,       int this_node_counter, int* node_counter)
{
	fprintf(file_pointer, "%i [label=\"type:\n", this_node_counter);
	
	// Type Qualifier & Specifier
	if ((type->qualifier_and_specifier & 64) == 64)
		fprintf(file_pointer, "const ");

	if ((type->qualifier_and_specifier & 32) == 32)
		fprintf(file_pointer, "volatile ");

	if ((type->qualifier_and_specifier & 16) == 16)
		fprintf(file_pointer, "typedef ");

	if ((type->qualifier_and_specifier & 8) == 8)
		fprintf(file_pointer, "extern ");

	if ((type->qualifier_and_specifier & 4) == 4)
		fprintf(file_pointer, "static ");

	if ((type->qualifier_and_specifier & 2) == 2)
		fprintf(file_pointer, "auto ");

	if ((type->qualifier_and_specifier & 1) == 1)
		fprintf(file_pointer, "register ");

	// Type Modifiers
	if ((type->modifier & 8) == 8)
		fprintf(file_pointer, "short ");

	if ((type->modifier & 4) == 4)
		fprintf(file_pointer, "long ");

	if ((type->modifier & 2) == 2)
		fprintf(file_pointer, "signed ");

	if ((type->modifier & 1) == 1)
		fprintf(file_pointer, "unsigned ");

	// Primitive Type
	switch (type->type)
	{
		case PRIM_VOID:
			fprintf(file_pointer, "void");
			break;
		case PRIM_CHAR:
			fprintf(file_pointer, "char");
			break;
		case PRIM_INT:
			fprintf(file_pointer, "int");
			break;
		case PRIM_DOUBLE:
			fprintf(file_pointer, "double");
			break;
		default: 
			fprintf(file_pointer, "UNKNOWN");
	}

	fprintf(file_pointer, "\", fontname=\"%s\" ];\n", FONTNAME);
}

void write_func_to_dot_file(FILE *file_pointer,	AST_Func *function, int this_node_counter, int* node_counter)
{
	fprintf(
		file_pointer, 
		"%i [label=\"Function: \n\'%s\'\", fontname=\"%s\" ];\n", 
		this_node_counter, 
		function->func_declarator->declarator->identifier, 
		FONTNAME
	);

	// Return type
	int child_node_counter = write_node_to_dot_file(file_pointer, function->return_type, AST_TYPE, node_counter);
	write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, NULL, -1);

	// SymbolTable
	fprintf(file_pointer, "%i [label=\"SymbolTable\n(not shown)\", fontname=\"%s\" ];\n", (*node_counter), FONTNAME);
	write_parent_child_to_dot_file(file_pointer, this_node_counter, (*node_counter)++, NULL, -1);

	if (function->table != NULL)
	{
		print_symbol_table(function->table, function->func_declarator->declarator->identifier);
	}

	// Body
	int child_body_node_counter = write_node_to_dot_file(file_pointer, function->body, AST_STAT, node_counter);
	write_parent_child_to_dot_file(file_pointer, this_node_counter, child_body_node_counter, "function body", -1);
}


void write_iden_to_dot_file(FILE *file_pointer, AST_Iden *identifier, int this_node_counter, int* node_counter)
{
	fprintf(
		file_pointer, 
		"%i [label=\"identifier:\n%s\", fontname=\"%s\" ];\n", 
		this_node_counter, 
		identifier->identifier, 
		FONTNAME
	);
}

void print_unary_operator_to_file(FILE *file_pointer, EUnaryOperation op)
{
	switch (op)
	{
		case UNARY_PLUS:
			fprintf(file_pointer, "+");
			break;
		case UNARY_MINUS:
			fprintf(file_pointer, "-");
			break;
		case B_ONE_COMPLEMENT:
			fprintf(file_pointer, "~");
			break;
		case L_NOT:
			fprintf(file_pointer, "!");
			break;
		case REF:
			fprintf(file_pointer, "&");
			break;
		case DEREF:
			fprintf(file_pointer, "*");	
			break;
		case POSTFIX_INC:
			fprintf(file_pointer, "++ (post)");
			break;
		case POSTFIX_DEC:
			fprintf(file_pointer, "-- (post)");
			break;
		case PREFIX_INC:
			fprintf(file_pointer, "++ (pre)");
			break;
		case PREFIX_DEC:
			fprintf(file_pointer, "-- (pre)");
			break;
		default:
			printf("ERROR: AST_WRITER: UNKOWN UNARY OPERATOR TYPE!\n");
	};
}

void print_binary_operator_to_file(FILE *file_pointer, EBinaryOperation op)
{
	switch (op)
	{
		case PLUS:
			fprintf(file_pointer, "+");
			break;
		case MINUS:
			fprintf(file_pointer, "-");
			break;
		case MULT:
			fprintf(file_pointer, "*");
			break;
		case DIV:
			fprintf(file_pointer, "/");
			break;
		case MOD:
			fprintf(file_pointer, "%%");
			break;
		case ASSIGNMENT:
			fprintf(file_pointer, "=");
			break;
		case EQUAL:
			fprintf(file_pointer, "==");
			break;
		case NOT_EQUAL:
			fprintf(file_pointer, "!=");
			break;
		case LESS:
			fprintf(file_pointer, "<");
			break;
		case LESS_EQUAL:
			fprintf(file_pointer, "<=");
			break;
		case GREATER:
			fprintf(file_pointer, ">");
			break;
		case GREATER_EQUAL:
			fprintf(file_pointer, ">=");
			break;
		case L_AND:
			fprintf(file_pointer, "&&");
			break;
		case L_OR:
			fprintf(file_pointer, "||");
			break;
		case B_AND:
			fprintf(file_pointer, "&");
			break;
		case B_OR:
			fprintf(file_pointer, "|");
			break;
		case B_XOR:
			fprintf(file_pointer, "^");
			break;
		case SHIFT_L:
			fprintf(file_pointer, "<<");
			break;
		case SHIFT_R:
			fprintf(file_pointer, ">>");
			break;
		case CONCAT:
			fprintf(file_pointer, "CONCAT (.)");
			break;
		default:
			printf("ERROR: AST_WRITER: UNKOWN BINARY OPERATOR TYPE!\n");
	};
}

void write_char_to_dot_file(FILE *file_pointer, char character)
{
	switch (character)
	{
		case 0x07:
			fprintf(file_pointer, "\\\\a"); break;

		case 0x08:
			fprintf(file_pointer, "\\\\b"); break;

		case 0x09:
			fprintf(file_pointer, "\\\\t"); break;

		case 0x0a:
			fprintf(file_pointer, "\\\\n"); break;

		case 0x0b:
			fprintf(file_pointer, "\\\\v"); break;

		case 0x0c:
			fprintf(file_pointer, "\\\\f"); break;

		case 0x0d:
			fprintf(file_pointer, "\\\\r"); break;

		case 0x1b:
			fprintf(file_pointer, "\\\\e"); break;

		case 0x22:
			fprintf(file_pointer, "\\\""); break;

		case 0x27:
			fprintf(file_pointer, "\\\'"); break;

		case 0x3f:
			fprintf(file_pointer, "\\\\?"); break;

		case 0x5c:
			fprintf(file_pointer, "\\\\\\\\"); break;

		default:
			fprintf(file_pointer, "%c", character);
	}
}

void write_expr_to_dot_file(FILE *file_pointer, AST_Expr *expression, int this_node_counter, int* node_counter)
{
	int child_node_counter = -1;

	switch (expression->expression_type)
	{
		case EXPR_CONST_INT:
			fprintf(file_pointer, "%i [label=\"int:\n%i\", fontname=\"%s\" ];\n", this_node_counter, expression->expression.const_int_expression, FONTNAME);
			break;

		case EXPR_CONST_DOUBLE:
			fprintf(file_pointer, "%i [label=\"double:\n%f\", fontname=\"%s\" ];\n", this_node_counter, expression->expression.const_double_expression, FONTNAME);
			break;

		case EXPR_CONST_CHAR:
			fprintf(file_pointer, "%i [label=\"char:\n\'%c\' (%i)\", fontname=\"%s\" ];\n", this_node_counter, expression->expression.const_char_expression, expression->expression.const_char_expression, FONTNAME);
			break;

		case EXPR_CONST_STRING:
			fprintf(file_pointer, "%i [label=\"string:\n", this_node_counter);
			
			size_t len = strlen(expression->expression.const_string_expression);
			
			for (int i = 0; i < len; i++)
				write_char_to_dot_file(file_pointer, expression->expression.const_string_expression[i]);

			fprintf(file_pointer, "\", fontname=\"%s\" ];\n",  FONTNAME);
			break;
			
		case EXPR_IDENTIFIER:
			write_iden_to_dot_file(file_pointer, expression->expression.identifier_expression, this_node_counter, node_counter);
			break;

		case EXPR_UNARY:
			fprintf(file_pointer, "%i [label=\"", this_node_counter);
			print_unary_operator_to_file(file_pointer, expression->expression.unary_expression.operation);
			fprintf(file_pointer, "\", fontname=\"%s\" ];\n", FONTNAME);

			child_node_counter = write_node_to_dot_file(file_pointer, expression->expression.unary_expression.operand, AST_EXPR, node_counter);
			write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, "operand", -1);

			break;

		case EXPR_BINARY:
			fprintf(file_pointer, "%i [label=\"", this_node_counter);
			print_binary_operator_to_file(file_pointer, expression->expression.binary_expression.operation);
			fprintf(file_pointer, "\", fontname=\"%s\" ];\n", FONTNAME);

			child_node_counter = write_node_to_dot_file(file_pointer, expression->expression.binary_expression.left, AST_EXPR, node_counter);
			write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, "left", -1);

			child_node_counter = write_node_to_dot_file(file_pointer, expression->expression.binary_expression.right, AST_EXPR, node_counter);
			write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, "right", -1);
			
			break;

		case EXPR_TERNARY:
			fprintf(file_pointer, "%i [label=\"Ternary\", fontname=\"%s\" ];\n", this_node_counter, FONTNAME);

			child_node_counter = write_node_to_dot_file(file_pointer, expression->expression.ternary_expression.condition, AST_EXPR, node_counter);
			write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, "?", -1);

			child_node_counter = write_node_to_dot_file(file_pointer, expression->expression.ternary_expression.if_expression, AST_EXPR, node_counter);
			write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, "if", -1);

			child_node_counter = write_node_to_dot_file(file_pointer, expression->expression.ternary_expression.else_expression, AST_EXPR, node_counter);
			write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, "else", -1);

			break;

		case EXPR_CAST:
			fprintf(file_pointer, "%i [label=\"Cast\", fontname=\"%s\" ];\n", this_node_counter, FONTNAME);

			child_node_counter = write_node_to_dot_file(file_pointer, expression->expression.cast_expression.type, AST_TYPE, node_counter);
			write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, "to", -1);

			child_node_counter = write_node_to_dot_file(file_pointer, expression->expression.cast_expression.expression, AST_EXPR, node_counter);
			write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, NULL, -1);

			break;

		case EXPR_ARRAY_ACCESS:
			fprintf(file_pointer, "%i [label=\"Array Element\", fontname=\"%s\" ];\n", this_node_counter, FONTNAME);

			child_node_counter = write_node_to_dot_file(file_pointer, expression->expression.array_access_expression.array, AST_EXPR, node_counter);
			write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, "from", -1);

			child_node_counter = write_node_to_dot_file(file_pointer, expression->expression.array_access_expression.index, AST_EXPR, node_counter);
			write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, "with index", -1);

			break;

		case EXPR_STRUCT_MEMBER_ACCESS:
			fprintf(file_pointer, "%i [label=\"Member Access (.)\", fontname=\"%s\" ];\n", this_node_counter, FONTNAME);

			child_node_counter = write_node_to_dot_file(file_pointer, expression->expression.struct_member_access_expression.structure, AST_EXPR, node_counter);
			write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, "struct", -1);

			child_node_counter = write_node_to_dot_file(file_pointer, expression->expression.struct_member_access_expression.member, AST_IDEN, node_counter);
			write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, "member", -1);

			break;

		case EXPR_STRUCT_POINTER_MEMBER_ACCESS:
			fprintf(file_pointer, "%i [label=\"Member Access (->)\", fontname=\"%s\" ];\n", this_node_counter, FONTNAME);

			child_node_counter = write_node_to_dot_file(file_pointer, expression->expression.struct_pointer_member_access_expression.pointer_structure, AST_EXPR, node_counter);
			write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, "struct pointer", -1);

			child_node_counter = write_node_to_dot_file(file_pointer, expression->expression.struct_pointer_member_access_expression.member, AST_IDEN, node_counter);
			write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, "member", -1);

			break;

		case EXPR_CALL:
			fprintf(file_pointer, "%i [label=\"Func Call\", fontname=\"%s\" ];\n", this_node_counter, FONTNAME);

			child_node_counter = write_node_to_dot_file(file_pointer, expression->expression.call_expression.expression, AST_EXPR, node_counter);
			write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, "function", -1);

			AST_Expr_List *arguments = expression->expression.call_expression.args;
			int counter = 1;
			while(arguments != NULL)
			{
				child_node_counter = write_node_to_dot_file(file_pointer, arguments->expression, AST_EXPR, node_counter);
				write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, "arg", counter++);
				arguments = arguments->next;
			}

			break;

		case EXPR_SIZEOF_EXPR:
			fprintf(file_pointer, "%i [label=\"SizeOfType\", fontname=\"%s\" ];\n", this_node_counter, FONTNAME);

			child_node_counter = write_node_to_dot_file(file_pointer, expression->expression.sizeof_type_expression.type, AST_EXPR, node_counter);
			write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, NULL, -1);

			break;

		case EXPR_SIZEOF_TYPE:
			fprintf(file_pointer, "%i [label=\"SizeOf\", fontname=\"%s\" ];\n", this_node_counter, FONTNAME);

			child_node_counter = write_node_to_dot_file(file_pointer, expression->expression.sizeof_unary_expression.expression, AST_EXPR, node_counter);
			write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, NULL, -1);

			break;

		default:
			printf("ERROR: AST_WRITER: UNKOWN EXPRESSION TYPE!\n");
	};
}

void write_stat_to_dot_file(FILE *file_pointer, AST_Stat *statement,  int this_node_counter, int* node_counter)
{
	int child_node_counter = -1;

	switch (statement->statement_type)
	{
		case STAT_EXPR:
			write_expr_to_dot_file(file_pointer, statement->statement.expression, this_node_counter, node_counter);
			break;

		case STAT_COMPOUND:
			fprintf(file_pointer, "%i [label=\"Statement List\", fontname=\"%s\" ];\n", this_node_counter, FONTNAME);

			AST_Stat_List *statements = statement->statement.compound;
			int counter = 1;
			while (statements != NULL)
			{
				int child_node_counter = write_node_to_dot_file(file_pointer, statements->statement, AST_STAT, node_counter);
				write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, NULL, counter++);
				statements = statements->next;
			}
			break;

		case STAT_IF:
			fprintf(file_pointer, "%i [label=\"If\", fontname=\"%s\" ];\n", this_node_counter, FONTNAME);

			child_node_counter = write_node_to_dot_file(file_pointer, statement->statement.if_statement.condition, AST_EXPR, node_counter);
			write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, "condition", -1);

			child_node_counter = write_node_to_dot_file(file_pointer, statement->statement.if_statement.statement, AST_STAT, node_counter);
			write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, "then", -1);

			break;
		case STAT_IF_ELSE:
			fprintf(file_pointer, "%i [label=\"If-Else\", fontname=\"%s\" ];\n", this_node_counter, FONTNAME);

			child_node_counter = write_node_to_dot_file(file_pointer, statement->statement.if_else_statement.condition, AST_EXPR, node_counter);
			write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, "condition", -1);

			child_node_counter = write_node_to_dot_file(file_pointer, statement->statement.if_else_statement.if_statement, AST_STAT, node_counter);
			write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, "if-then", -1);

			child_node_counter = write_node_to_dot_file(file_pointer, statement->statement.if_else_statement.else_statement, AST_STAT, node_counter);
			write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, "else-then", -1);

			break;
		case STAT_SWITCH:
			fprintf(file_pointer, "%i [label=\"Switch\", fontname=\"%s\" ];\n", this_node_counter, FONTNAME);

			child_node_counter = write_node_to_dot_file(file_pointer, statement->statement.switch_statement.expression, AST_EXPR, node_counter);
			write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, "switched-expression", -1);

			child_node_counter = write_node_to_dot_file(file_pointer, statement->statement.switch_statement.body, AST_STAT, node_counter);
			write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, "body", -1);

			break;
		case STAT_FOR:
			fprintf(file_pointer, "%i [label=\"For\", fontname=\"%s\" ];\n", this_node_counter, FONTNAME);

			child_node_counter = write_node_to_dot_file(file_pointer, statement->statement.for_statement.init_expression, AST_EXPR, node_counter);
			write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, "init", -1);

			child_node_counter = write_node_to_dot_file(file_pointer, statement->statement.for_statement.condition, AST_EXPR, node_counter);
			write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, "condition", -1);

			child_node_counter = write_node_to_dot_file(file_pointer, statement->statement.for_statement.update_expression, AST_EXPR, node_counter);
			write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, "update", -1);

			child_node_counter = write_node_to_dot_file(file_pointer, statement->statement.for_statement.body, AST_STAT, node_counter);
			write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, "body", -1);

			break;
		case STAT_WHILE:
			fprintf(file_pointer, "%i [label=\"While\", fontname=\"%s\" ];\n", this_node_counter, FONTNAME);

			child_node_counter = write_node_to_dot_file(file_pointer, statement->statement.while_statement.condition, AST_EXPR, node_counter);
			write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, "condition", -1);

			child_node_counter = write_node_to_dot_file(file_pointer, statement->statement.while_statement.body, AST_STAT, node_counter);
			write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, "body", -1);

			break;
		case STAT_DO_WHILE:
			fprintf(file_pointer, "%i [label=\"Do-While\", fontname=\"%s\" ];\n", this_node_counter, FONTNAME);

			child_node_counter = write_node_to_dot_file(file_pointer, statement->statement.do_while_statement.body, AST_STAT, node_counter);
			write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, "body", -1);

			child_node_counter = write_node_to_dot_file(file_pointer, statement->statement.do_while_statement.condition, AST_EXPR, node_counter);
			write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, "condition", -1);

			break;
		case STAT_GOTO:
			fprintf(file_pointer, "%i [label=\"GoTo: \n\'%s\'\", fontname=\"%s\" ];\n", this_node_counter, statement->statement.jump_statement.value.identifier->identifier, FONTNAME);
			break;
		case STAT_CONTINUE:
			fprintf(file_pointer, "%i [label=\"Continue.\", fontname=\"%s\" ];\n", this_node_counter, FONTNAME);
			break;
		case STAT_BREAK:
			fprintf(file_pointer, "%i [label=\"Break.\", fontname=\"%s\" ];\n", this_node_counter, FONTNAME);
			break;
		case STAT_RETURN:
			fprintf(file_pointer, "%i [label=\"Return.\", fontname=\"%s\" ];\n", this_node_counter, FONTNAME);
			break;
		case STAT_RETURN_EXPR:
			fprintf(file_pointer, "%i [label=\"Return:\", fontname=\"%s\" ];\n", this_node_counter, FONTNAME);

			child_node_counter = write_node_to_dot_file(file_pointer, statement->statement.jump_statement.value.expression, AST_EXPR, node_counter);
			write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, NULL, -1);
		
			break;
		case STAT_LABELED:

			if (statement->statement.labeled_statement.identifier != NULL)
			{
				fprintf(file_pointer, "%i [label=\"Label: \n\'%s\'\", fontname=\"%s\" ];\n", this_node_counter, statement->statement.labeled_statement.identifier->identifier, FONTNAME);
			}
			else if (statement->statement.labeled_statement.const_expression != NULL)
			{
				fprintf(file_pointer, "%i [label=\"Case\", fontname=\"%s\" ];\n", this_node_counter, FONTNAME);

				child_node_counter = write_node_to_dot_file(file_pointer, statement->statement.labeled_statement.const_expression, AST_EXPR, node_counter);
				write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, "case const expression", -1);
			}
			else
			{
				fprintf(file_pointer, "%i [label=\"Default.\", fontname=\"%s\" ];\n", this_node_counter, FONTNAME);
			}

			child_node_counter = write_node_to_dot_file(file_pointer, statement->statement.labeled_statement.statement, AST_STAT, node_counter);
			write_parent_child_to_dot_file(file_pointer, this_node_counter, child_node_counter, NULL, -1);
		
			break;
		default:
			printf("ERROR: AST_WRITER: UNKOWN STATEMENT TYPE!\n");
	};
}
