#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "symbol_table.h"
#include "codegen.h"

#define BYTES_PER_TYPE 8
#define SYS_CALL_EXIT 93

#define REG_0(typename) (typename->type == PRIM_DOUBLE ? "fa0" : "a0")
#define REG_1(typename) (typename->type == PRIM_DOUBLE ? "fa1" : "a1")
#define LOAD(typename)  (typename->type == PRIM_DOUBLE ? "flw" : "lw ")
#define STORE(typename) (typename->type == PRIM_DOUBLE ? "fsw" : "sw ")

static int FOR_COUNTER = 0;
static int WHILE_COUNTER = 0;
static int ELSE_COUNTER = 0;
static int ENDIF_COUNTER = 0;
static int FILE_COUNTER = 0;
static int TERNARY_ELSE_COUNTER = 0;
static int TERNARY_END_COUNTER = 0;

static int TARGET = 0;

static char *NEXT_BREAK;
static char *NEXT_CONTINUE;

static AST_Func_List *FUNCTION_LIST = NULL;

AST_Func *func_lookup
(
	AST_Func_List                      *list, 
	char                               *identifier
)
{
	AST_Func_List *current = list;

	do
	{
		if (current->function == NULL) 
		{
			current = current->next;
		}
		else
		{
			if (
				strcmp(
					current->function->func_declarator->declarator.func_declarator.declarator->identifier,
					identifier
				)
				== 0
			)
			{
				return current->function;
			}

			// Go to the next symbol table entry
			current = current->next;
		}
	} 
	while (current != NULL);

	return NULL;
}

int 
write_ast_to_riscv_file
(
	char                               *filename, 
	AST_Root                           *root,
	int                                target
)
{
	// Variable Setup
	FILE *file_pointer;

	// Open File
	file_pointer = fopen(filename, "w");
	if (file_pointer == NULL)
	{
		printf("Could not open .s file!");
		return 1;
	}

	// Set the target
	TARGET = target;

	// Generate RISC-V code and write it to file
	write_root_to_riscv_file(file_pointer, root);

	// Close file and exit
	fclose(file_pointer);
	return 0;
}

void write_root_to_riscv_file
(
	FILE                               *file_pointer, 
	AST_Root                           *node
)
{
	// Set the global, static function list for lookup
	FUNCTION_LIST = node->functions;

	// And the local one for writing each to the file
	AST_Func_List *functions = node->functions;

	// Text section & main as globl
	fprintf(file_pointer, ".text\n");
	fprintf(file_pointer, ".globl main\n\n");

	while (functions != NULL)
	{
		// Variable init
		NEXT_BREAK    = NULL;
		NEXT_CONTINUE = NULL;

		write_func_to_riscv_file(file_pointer, functions->function);
		functions = functions->next;
	}
}

void write_func_to_riscv_file
(
	FILE                               *file_pointer,	
	AST_Func                           *function
)
{
	// SymbolTable
	int variable_area_size = write_symbol_table_to_riscv_file(file_pointer, function->table);

	// Don't forget about the parameters!
	function->table = combine_symbol_table_with_parameter_table(
		function->table, 
		variable_area_size, 
		function->func_declarator->declarator.func_declarator.parameter_table
	);

	// Needed for return statements
	if (function->table != NULL)
	{
		function->table->size_without_parameter_table = variable_area_size;
	}

	// Text section
	fprintf(file_pointer, ".text\n");

	// Function name
	char *identifier = function->func_declarator->declarator.func_declarator.declarator->identifier;
	fprintf(file_pointer, "%s:\n\n", identifier);

	// If this is NOT the main function then we are in a function call
	// In that case, store the current
	// - stack pointer
	// - a0 register (contains return address)
	// - s0 register (important for variable access)
	// on the stack so we can restore that later
	if 
	(
		strcmp(identifier, "main") != 0
	)
	{
		fprintf(file_pointer, "# Store current sp, a0 and s0 on stack\n");
		fprintf(file_pointer, "    add       a1, zero, sp\n");
		fprintf(file_pointer, "    addi      sp, sp, -%d\n", BYTES_PER_TYPE);
		fprintf(file_pointer, "    sw        a1, 0(sp)\n");

		// Store the current a0 register on the stack
		fprintf(file_pointer, "    addi      sp, sp, -%d\n", BYTES_PER_TYPE);
		fprintf(file_pointer, "    sw        a0, 0(sp)\n");

		// Store the current s0 register on the stack
		fprintf(file_pointer, "    addi      sp, sp, -%d\n", BYTES_PER_TYPE);
		fprintf(file_pointer, "    sw        s0, 0(sp)\n\n");
	}

	// Setup sp & s0
	fprintf(file_pointer, "# Setup stack pointer & store start of variable section in s0 reg.\n");
	fprintf(file_pointer, "    addi      sp,sp,-%d\n", variable_area_size);
	fprintf(file_pointer, "    add       s0,sp,zero\n\n");
	fflush(file_pointer);
	
	// Body
	write_stat_to_riscv_file(file_pointer, function->body, function->table);

	// Write nop at end so that function can't end in label without statement
	fprintf(file_pointer, "    nop\n\n\n");

	if 
	(
		strcmp(identifier, "main") != 0
	)
	{
		// Restore old sp, a0, s0 and return to caller
		// First, get the stack pointer to point to where the old s0 is stored
		fprintf(file_pointer, "    # Restore and return to caller\n");
		fprintf(file_pointer, "    addi      sp, s0, %d\n", variable_area_size);

		// Restore s0
		fprintf(file_pointer, "    lw        s0, %d(sp)\n", BYTES_PER_TYPE * 0);

		// Restore a0
		fprintf(file_pointer, "    lw        a0, %d(sp)\n", BYTES_PER_TYPE * 1);

		// Restore sp - first into a2, then into sp
		fprintf(file_pointer, "    lw        a2, %d(sp)\n", BYTES_PER_TYPE * 2);
		fprintf(file_pointer, "    add       sp, zero, a2\n");

		// Finally, jump to the caller
		fprintf(file_pointer, "    jr        a0\n");
	}
}

// Write the symbol table to the assembly file and determines the offset for
// the stack so that the variable area can be reserved
int write_symbol_table_to_riscv_file 
(
	FILE                               *file_pointer, 
	SymbolTable                        *table
)
{
	if (table == NULL) return 0;

	int stack_pointer_offset = 0;

	SymbolTable *current = table;
	do
	{
		if (current->entry == NULL) current = current->next;

		// Determine the stack pointer offset
		// Only supports a single, constant amount of bytes per type
		current->entry->stack_pointer_offset = stack_pointer_offset;
		stack_pointer_offset += BYTES_PER_TYPE;

		// Print a comment regarding this entry to the RISC-V assembly file
		fprintf(
			file_pointer,
			"# name: %s\n",
			current->entry->declarator->declarator.iden_declarator.declarator->identifier
		);
		fflush(file_pointer);

		switch (current->entry->type->type)
		{
			case PRIM_VOID:
				fprintf(file_pointer, "# type: PRIM_VOID\n");
				break;
			case PRIM_CHAR:
				fprintf(file_pointer, "# type: PRIM_CHAR\n");
				break;
			case PRIM_INT:
				fprintf(file_pointer, "# type: PRIM_INT\n");
				break;
			case PRIM_DOUBLE:
				fprintf(file_pointer, "# type: PRIM_DOUBLE\n");
				break;
			default:
				printf("UKNOWN TYPE\n");
				break;
		}
		fflush(file_pointer);

		fprintf(
			file_pointer,
			"# offset: %d\n\n",
			current->entry->stack_pointer_offset
		);
		fflush(file_pointer);

		// Go to the next symbol table entry
		current = current->next;
	}
	while (current != NULL);

	// Return the total offset to be used later on
	return stack_pointer_offset;
}

void write_stat_to_riscv_file
(
	FILE                               *file_pointer, 
	AST_Stat                           *statement,
	SymbolTable                        *table
)
{
	fprintf(file_pointer, "\n# Start of statement\n");

	AST_Stat_List *statements;

	int else_value   = -1;
	int endif_value  = -1;
	int for_value    = -1;
	int while_value  = -1;

	char *break_backup    = NULL;
	char *continue_backup = NULL;

	int variable_area_size = 0;

	switch (statement->statement_type)
	{
		case STAT_EXPR:
			// Visit the expression
			free(write_expr_to_riscv_file(file_pointer, statement->statement.expression, table, 0));
			break;

		case STAT_COMPOUND:
			statements = statement->statement.compound;
			while (statements != NULL)
			{
				write_stat_to_riscv_file(file_pointer, statements->statement, table);
				statements = statements->next;
			}
			break;
		
		case STAT_IF:
			// Visit child node first - puts result onto stack
			free(write_expr_to_riscv_file(file_pointer, statement->statement.if_statement.condition, table, 0));

			endif_value = ENDIF_COUNTER++;
			write_equals_check_and_branch(file_pointer, "endif", endif_value);

			// Visit body
			write_stat_to_riscv_file(file_pointer, statement->statement.if_statement.statement, table);

			// After visiting the if-body, jump to the endif
			fprintf(file_pointer, "    j         .endif%d\n", endif_value);

			// End the if statement
			fprintf(file_pointer, ".endif%d:\n    nop\n", endif_value);

			break;

		case STAT_IF_ELSE:
			// Visit child node with condition expression first - puts result onto stack
			free(write_expr_to_riscv_file(file_pointer, statement->statement.if_else_statement.condition, table, 0));

			// Write the boolean check and branching jump
			else_value = ELSE_COUNTER++;
			endif_value = ENDIF_COUNTER++;
			write_equals_check_and_branch(file_pointer, "else", else_value);

			// Visit if-body
			write_stat_to_riscv_file(file_pointer, statement->statement.if_else_statement.if_statement, table);

			// After visiting the if-body, jump to the endif
			fprintf(file_pointer, "    j         .endif%d\n", endif_value);

			// Now the else body
			fprintf(file_pointer, ".else%d:\n", else_value);

			// Visit else-body
			write_stat_to_riscv_file(file_pointer, statement->statement.if_else_statement.else_statement, table);

			// After visiting the else-body, jump to the endif
			fprintf(file_pointer, "    j         .endif%d\n", endif_value);

			// End the if statement
			fprintf(file_pointer, ".endif%d:\n    nop\n", endif_value);

			break;

		case STAT_FOR:
			// Visit the initial init expression - Remember that this goes out of scope!
			free(write_expr_to_riscv_file(file_pointer, statement->statement.for_statement.init_expression, table, 0));

			// Write the "header" of the for loop
			// This gets revisited every time to re-check the condition
			for_value = FOR_COUNTER++;
			fprintf(file_pointer, ".for%d:\n", for_value);

			break_backup = NEXT_BREAK;
			continue_backup = NEXT_CONTINUE;
			NEXT_BREAK = construct_string("endfor", for_value);
			NEXT_CONTINUE = construct_string("updatefor", for_value);

			// Write the condition check
			free(write_expr_to_riscv_file(file_pointer, statement->statement.for_statement.condition, table, 0));

			// Write the boolean check and branching jump
			write_equals_check_and_branch(file_pointer, "endfor", for_value);

			// Write for body
			write_stat_to_riscv_file(file_pointer, statement->statement.for_statement.body, table);

			// Write update expression with label to jump to in case of continue
			fprintf(file_pointer, ".updatefor%d:\n", for_value);
			free(write_expr_to_riscv_file(file_pointer, statement->statement.for_statement.update_expression, table, 0));

			// Jump to the start with the condition check
			fprintf(file_pointer, "    j         .for%d\n", for_value);

			// Write the for-end to jump to when we are out of iterations
			// Note that this can use the same counter value
			fprintf(file_pointer, ".endfor%d:\n    nop\n", for_value);

			// Cleanup
			free(NEXT_BREAK);
			free(NEXT_CONTINUE);
			NEXT_BREAK = break_backup;
			NEXT_CONTINUE = continue_backup;

			break;

		case STAT_WHILE:
			// Write the "header" of the while loop
			// This gets revisited every time to re-check the condition
			while_value = WHILE_COUNTER++;
			fprintf(file_pointer, ".while%d:\n", while_value);

			break_backup = NEXT_BREAK;
			continue_backup = NEXT_CONTINUE;
			NEXT_BREAK = construct_string("endwhile", while_value);
			NEXT_CONTINUE = construct_string("while", while_value);

			// Write the condition check
			free(write_expr_to_riscv_file(file_pointer, statement->statement.while_statement.condition, table, 0));

			// Write the boolean check and branching jump
			write_equals_check_and_branch(file_pointer, "endwhile", while_value);

			// Write while body
			write_stat_to_riscv_file(file_pointer, statement->statement.while_statement.body, table);

			// Jump to the start with the condition check
			fprintf(file_pointer, "    j         .while%d\n", while_value);

			// Write the while-end to jump to when the condition fails
			fprintf(file_pointer, ".endwhile%d:\n    nop\n", while_value);

			// Cleanup
			free(NEXT_BREAK);
			free(NEXT_CONTINUE);
			NEXT_BREAK = break_backup;
			NEXT_CONTINUE = continue_backup;

			break;

		case STAT_DO_WHILE:
			while_value = WHILE_COUNTER++;

			// Write the while-start to jump to as long as the condition is true
			fprintf(file_pointer, ".while%d:\n", while_value);

			break_backup = NEXT_BREAK;
			continue_backup = NEXT_CONTINUE;
			NEXT_BREAK = construct_string("endwhile", while_value);
			NEXT_CONTINUE = construct_string("whilecond", while_value);

			// Write while body
			write_stat_to_riscv_file(file_pointer, statement->statement.do_while_statement.body, table);

			// Write the condition check with label for jump in case of continue
			fprintf(file_pointer, ".whilecond%d:\n", while_value);
			free(write_expr_to_riscv_file(file_pointer, statement->statement.do_while_statement.condition, table, 0));

			// Put one into the other register
			fprintf(file_pointer, "    addi      a0, zero, 1\n");

			// Perform branch if its less than 1 (i.e. 0)
			fprintf(file_pointer, "    bge       a1, a0, .while%d\n", while_value);

			// Write the while-end
			fprintf(file_pointer, ".endwhile%d:\n    nop\n", while_value);

			// Cleanup
			free(NEXT_BREAK);
			free(NEXT_CONTINUE);
			NEXT_BREAK = break_backup;
			NEXT_CONTINUE = continue_backup;

			break;

		case STAT_SWITCH:
			printf("NOT SUPPORTED: STATEMENT TYPE 'SWITCH'\n");
			break;

		case STAT_GOTO:
			printf("NOT SUPPORTED: STATEMENT TYPE 'GOTO'\n");			
			break;

		case STAT_CONTINUE:
			fprintf(file_pointer, "    j         .%s\n", NEXT_CONTINUE);
			break;

		case STAT_BREAK:
			fprintf(file_pointer, "    j         .%s\n", NEXT_BREAK);
			break;

		case STAT_RETURN_EXPR:
			// Writes the expression / its result into (f)a1
			free(write_expr_to_riscv_file(file_pointer, statement->statement.expression, table, 0));

			// no break here intentional 

		case STAT_RETURN:
			variable_area_size = (table != NULL) ? table->size_without_parameter_table : 0;

			// Restore old sp, a0, s0 and return to caller
			// First, get the stack pointer to point to where the old s0 is stored
			fprintf(file_pointer, "    # Restore and return to caller\n");
			fprintf(file_pointer, "    addi      sp, s0, %d\n", variable_area_size);

			// Restore s0
			fprintf(file_pointer, "    lw        s0, %d(sp)\n", BYTES_PER_TYPE * 0);

			// Restore a0
			fprintf(file_pointer, "    lw        a0, %d(sp)\n", BYTES_PER_TYPE * 1);

			// Restore sp - first into a2, then into sp
			fprintf(file_pointer, "    lw        a2, %d(sp)\n", BYTES_PER_TYPE * 2);
			fprintf(file_pointer, "    add       sp, zero, a2\n");

			// Finally, jump to the caller
			fprintf(file_pointer, "    jr        a0\n");

			break;
		
		case STAT_LABELED:
			printf("NOT SUPPORTED: STATEMENT TYPE 'STAT_LABELED'\n");
			break;

		default:
			printf("ERROR: RISC-V_CODE_GENERATOR: STATEMENT TYPE NOT SUPPORTED!\n");
	};
	
	fprintf(file_pointer, "# End of statement\n\n");
}

char*
construct_string
(
	char* string,
	int value
)
{
	char *return_value = calloc(128, sizeof(char));
	snprintf(return_value, 128, "%s%d", string, value);
	return return_value;
}

void
write_equals_check_and_branch
(
	FILE *file_pointer,	
	char *base_jump_type,
	int  jump_counter
)
{
	// Put one into the other register
	fprintf(file_pointer, "    addi      a0, zero, 1\n");

	// Perform branch if its less than 1 (i.e. 0)
	fprintf(file_pointer, "    blt       a1, a0, .%s%d\n", base_jump_type, jump_counter);
}

AST_Type *write_expr_to_riscv_file 
(
	FILE *file_pointer,	
	AST_Expr *expression, 
	SymbolTable *table,
	int write_to_stack
)
{
	SymbolTableEntry *entry;

	float value;
	int hex_value;
	char *identifier = NULL;

	int ternary_else_value = -1;
	int ternary_end_value = -1;

	int store_reg1_on_stack = 0;
	AST_Type *type_name = new_empty_type();

	switch (expression->expression_type)
	{
		case EXPR_CONST_INT:
			fprintf(file_pointer, "    li        a1,%d\n", expression->expression.const_int_expression);

			store_reg1_on_stack = 1;
			type_name = new_type(PRIM_INT);
			break;

		case EXPR_CONST_DOUBLE:
			// Convert float value to hex representation
			value = expression->expression.const_double_expression;
			hex_value = *(int*)&value;

			// Write to fa1
			fprintf(file_pointer, "    li        a1, 0x%08X\n", hex_value);
			fprintf(file_pointer, "    sw        a1, -%d(sp)\n", BYTES_PER_TYPE);
			fprintf(file_pointer, "    flw       fa1, -%d(sp)\n", BYTES_PER_TYPE);

			store_reg1_on_stack = 1;
			type_name = new_type(PRIM_DOUBLE);
			break;

		case EXPR_CONST_CHAR:
			fprintf(file_pointer, "    addi      a1,zero,%d\n", (int) expression->expression.const_char_expression);
			
			store_reg1_on_stack = 1;
			type_name = new_type(PRIM_CHAR);;
			break;

		case EXPR_CONST_STRING:
			printf("NOT SUPPORTED: EXPR_CONST_STRING\n");
			store_reg1_on_stack = 0;
			break;
			
		case EXPR_IDENTIFIER:

			// Special cases to access certain registers for debugging
			if 
			(
				strcmp(expression->expression.identifier_expression->identifier, "_SP") == 0
			)
			{
				fprintf(file_pointer, "    add       a1, zero, sp\n");
				type_name = new_type(PRIM_INT);
				break;
			}
			else if
			(
				strcmp(expression->expression.identifier_expression->identifier, "_S0") == 0
			)
			{
				fprintf(file_pointer, "    add       a1, zero, s0\n");
				type_name = new_type(PRIM_INT);
				break;
			}
			else if
			(
				strcmp(expression->expression.identifier_expression->identifier, "_A0") == 0
			)
			{
				fprintf(file_pointer, "    add       a1, zero, a0\n");
				type_name = new_type(PRIM_INT);
				break;
			}

			entry = lookup(table, expression->expression.identifier_expression->identifier);

			if (entry == NULL)
			{
				printf("PANIC! CAN'T FIND IDENTIFIER: %s\n", expression->expression.identifier_expression->identifier);
				exit(1);
			}

			type_name = clone_type(entry->type);

			fprintf(file_pointer, "# Reading '%s'\n", expression->expression.identifier_expression->identifier);
			fprintf(file_pointer, "    %s       %s, %d(s0)\n", LOAD(type_name), REG_1(type_name), entry->stack_pointer_offset);

			store_reg1_on_stack = 1;
			break;

		case EXPR_UNARY:
			// Visit binary expression
			type_name = write_unary_expr_to_riscv_file(file_pointer, expression, table, 0);
			store_reg1_on_stack = 1;
			break;

		case EXPR_BINARY:
			// Visit binary expression
			type_name = write_binary_expr_to_riscv_file(file_pointer, expression, table, 0);
			store_reg1_on_stack = 1;
			break;

		case EXPR_TERNARY:
			// Visit child node with condition expression first - puts result onto stack
			free(write_expr_to_riscv_file(file_pointer, expression->expression.ternary_expression.condition, table, 0));

			// Put one into the other register
			fprintf(file_pointer, "    addi      a0, zero, 1\n");

			// Perform branch if its less than 1 (i.e. 0)
			ternary_else_value = TERNARY_ELSE_COUNTER++;
			ternary_end_value = TERNARY_END_COUNTER++;
			fprintf(file_pointer, "    blt       a1, a0, .ternaryelse%d\n", ternary_else_value);

			// Visit if-body
			type_name = write_expr_to_riscv_file(file_pointer, expression->expression.ternary_expression.if_expression, table, 0);

			// After visiting the if-body, jump to the endif
			fprintf(file_pointer, "    j         .ternaryend%d\n", ternary_end_value);

			// Now the else body
			fprintf(file_pointer, ".ternaryelse%d:\n", ternary_else_value);

			// Visit else-body
			free(write_expr_to_riscv_file(file_pointer, expression->expression.ternary_expression.else_expression, table, 0));

			// After visiting the else-body, jump to the endif
			fprintf(file_pointer, "    j         .ternaryend%d\n", ternary_end_value);

			// End the if statement
			fprintf(file_pointer, ".ternaryend%d:\n", ternary_end_value);
			
			// Don't perform store on stack as this was done by one of the child expressions
			store_reg1_on_stack = 1;
			break;

		case EXPR_CAST:
			printf("IN DEVELOPMENT: EXPR_CAST\n");

			// TODO: ACTUALLY A LOT MORE THAN JUST CHANGING THE TYPE!

			free(write_expr_to_riscv_file(file_pointer, expression->expression.cast_expression.expression, table, 0));
			type_name = clone_type(expression->expression.cast_expression.type);

			store_reg1_on_stack = 0;
			break;

		case EXPR_ARRAY_ACCESS:
			printf("NOT SUPPORTED: EXPR_ARRAY_ACCESS\n");
			store_reg1_on_stack = 0;
			break;

		case EXPR_STRUCT_MEMBER_ACCESS:
			printf("NOT SUPPORTED: EXPR_STRUCT_MEMBER_ACCESS\n");
			store_reg1_on_stack = 0;
			break;

		case EXPR_STRUCT_POINTER_MEMBER_ACCESS:
			printf("NOT SUPPORTED: EXPR_STRUCT_POINTER_MEMBER_ACCESS\n");
			store_reg1_on_stack = 0;
			break;

		case EXPR_CALL:
			identifier = expression->expression.call_expression.expression->expression.identifier_expression->identifier;

			if 
			(
				strcmp(identifier, "print") == 0 || strcmp(identifier, "printf") == 0
			)
			{
				write_print_expression(file_pointer, expression, table);
			}
			else if
			(
				strcmp(identifier, "file_open") == 0
			)
			{
				write_file_open_expression(file_pointer, expression, table);
				type_name = new_type(PRIM_INT);
			}
			else if
			(
				strcmp(identifier, "file_write") == 0
			)
			{
				write_file_write_expression(file_pointer, expression, table);
			}
			else if
			(
				strcmp(identifier, "file_close") == 0
			)
			{
				write_file_close_expression(file_pointer, expression, table);
			}
			else if
			(
				strcmp(identifier, "exit") == 0
			)
			{
				write_exit_expression(file_pointer, expression, table);
			}
			else
			{
				// Find the name of the function to call
				AST_Func *func = func_lookup(FUNCTION_LIST, identifier);

				if (func == NULL)
				{
					printf("ERROR: COULD NOT FIND FUNCTION TO CALL: %s\n", identifier);
					exit(1);
				}

				AST_Expr_List *expression_list = expression->expression.call_expression.args;

				int argument_counter = 0;

				while (expression_list != NULL)
				{
					if (expression_list->expression != NULL)
					{
						// Visit the expression & store it on stack
						write_expr_to_riscv_file(file_pointer, expression_list->expression, table, 1);
						++argument_counter;
					}

					// Get ready for the next argument
					expression_list = expression_list->next;
				}

				// Write the number of bytes the arguments consume on the stack
				// Also account for the fact that this value itself takes up
				// a further BYTES_PER_TYPE amount of bytes
				// This is why we add +1 prior to the multiplication
				fprintf(file_pointer, "    addi      sp, sp, -%d\n", BYTES_PER_TYPE);
				fprintf(file_pointer, "    addi      a0, zero, %d\n", BYTES_PER_TYPE * (argument_counter + 1));
				fprintf(file_pointer, "    sw        a0, 0(sp)\n");

				// Call the function
				fprintf(file_pointer, "    jal       a0, %s\n", identifier);

				// Afterwards, update the stack pointer *again* to get rid 
				// of the function parameters that were previously stored on
				// the stack
				fprintf(file_pointer, "    lw        a0, 0(sp)\n");
				fprintf(file_pointer, "    add       sp, sp, a0\n\n");

				type_name = func->return_type;

				printf("IN DEVELOPMENT: EXPR_CALL other than 'print' and 'printf'\n");
			}

			store_reg1_on_stack = 0;
			break;

		case EXPR_SIZEOF_EXPR:
			printf("NOT SUPPORTED: EXPR_SIZEOF_EXPR\n");
			store_reg1_on_stack = 0;
			break;

		case EXPR_SIZEOF_TYPE:
			printf("NOT SUPPORTED: EXPR_SIZEOF_EXPR\n");
			store_reg1_on_stack = 0;
			break;
		
		default:
			break;
	}

	// In the end, store a1 on the stack if we are at a expression "end" node
	// and the parent node tells us to do so
	if (store_reg1_on_stack && write_to_stack)
	{
		fprintf(file_pointer, "    addi      sp, sp, -%d\n", BYTES_PER_TYPE);
		fprintf(file_pointer, "    %s       %s, 0(sp)\n", STORE(type_name), REG_1(type_name));
	}

	return type_name;
}



AST_Type *write_unary_expr_to_riscv_file 
(
	FILE *file_pointer,	
	AST_Expr *expression, 
	SymbolTable *table,
	int write_to_stack
)
{
	SymbolTableEntry *entry;
	AST_Type *type_name = new_type(-2);

	// Visit the expression
	type_name = write_expr_to_riscv_file(file_pointer, expression->expression.unary_expression.operand, table, 0);

	// The "result" of the previous call is located in REG_1 (either a1 or fa1)
	// The value stored in (f)a0 is not important at this point and may be 
	// overwritten in the upcoming switch statement.

	// Now what?
	switch (expression->expression.unary_expression.operation)
	{
		case UNARY_PLUS:
			// Do nothing
			break;

		case UNARY_MINUS:
			switch (type_name->type)
			{
				case PRIM_DOUBLE: fprintf(file_pointer, "    li        a1, 0x00000000\n"); 
				                  fprintf(file_pointer, "    sw        a1, -%d(sp)\n", BYTES_PER_TYPE);
				                  fprintf(file_pointer, "    flw       fa0, -%d(sp)\n", BYTES_PER_TYPE);
				                  fprintf(file_pointer, "    fsub.s    fa1, fa0, fa1\n"); break;
				case PRIM_INT:    fprintf(file_pointer, "    sub       a1, zero, a1\n"); break;
				default:          printf("UNARY EXPRESSION WARNING: Unsupported type for UNARY_MINUS!\n");
			}
			break;

		case B_ONE_COMPLEMENT:
			switch (type_name->type)
			{
				case PRIM_INT:    fprintf(file_pointer, "    not       a1, a1\n"); break;
				default:          printf("UNARY EXPRESSION WARNING: Unsupported type for B_ONE_COMPLEMENT!\n");
			}
			break;

		case L_NOT:
			switch (type_name->type)
			{
				case PRIM_DOUBLE: fprintf(file_pointer, "    flt.s     a1, zero, fa1\n"); break;
				case PRIM_INT:    fprintf(file_pointer, "    slt       a1, zero, a1\n"); break;
				default:          printf("UNARY EXPRESSION WARNING: Unsupported type for L_NOT!\n");
			}
			fprintf(file_pointer, "    xori      a1, a1, 1\n");
			fprintf(file_pointer, "!");
			break;

		case REF:
			printf("IN DEVELOPMENT: UNARY OPERATION 'REF'.\n");
			printf("    AS C REQUIRES THIS TO BE A LOCALIZABLE VALUE (=lvalue) WE ASSUME THIS TO BE AN IDENTIFIER\n");

			entry = lookup(table, expression->expression.unary_expression.operand->expression.identifier_expression->identifier);
			fprintf(file_pointer, "    addi      a1, s0, %d\n", entry->stack_pointer_offset);

			type_name = clone_type(entry->type);
			set_pointer_level(type_name, entry->type->pointer_level);

			break;

		case DEREF:
			printf("IN DEVELOPMENT: UNARY OPERATION 'DEREF'\n");

			int pointer_level = type_name->pointer_level;
			if (pointer_level < 1)
			{
				printf("WARNING: TRYING TO DEREF NON-POINTER!\n");
			}

			fprintf(file_pointer, "# Dereferencing (needs temp register to add stack pointer with offset from a1)\n");
			fprintf(file_pointer, "    add       t0, zero, a1\n"); 
			fprintf(file_pointer, "    %s       %s, 0(t0)\n", LOAD(type_name), REG_1(type_name));

			break;

		case POSTFIX_INC:
			if (expression->expression.unary_expression.operand->expression_type != EXPR_IDENTIFIER)
			{
				printf("UNARY EXPRESSION WARNING: Operator POSTFIX_INC can only be applied to EXPR_IDENTIFIER!\n");
				break;
			}
			entry = lookup(table, expression->expression.unary_expression.operand->expression.identifier_expression->identifier);

			// Increment value, put result into REG_0
			// REG_1 stays untouched at this point, as the next read should
			// still be with the old, non-incremented value
			// REG_0 gets used to store the result of the increment at the 
			// variables location on the stack
			switch (type_name->type)
			{
				case PRIM_INT:    fprintf(file_pointer, "    addi      a0, a1, 1\n"); break;
				case PRIM_DOUBLE: fprintf(file_pointer, "    addi      a0, zero, 1\n");
				                  fprintf(file_pointer, "    fcvt.s.w   fa0, a0\n");
				                  fprintf(file_pointer, "    fadd.s    fa0, fa0, fa1\n"); break;
				default:          printf("UNARY EXPRESSION WARNING: Unsupported type for POSTFIX_INC!\n");
			}

			// Store contents of REG_0
			fprintf(file_pointer, "    %s       %s, %d(s0)\n", STORE(type_name), REG_0(type_name), entry->stack_pointer_offset);
			break;

		case POSTFIX_DEC:
			if (expression->expression.unary_expression.operand->expression_type != EXPR_IDENTIFIER)
			{
				printf("UNARY EXPRESSION WARNING: Operator POSTFIX_INC can only be applied to EXPR_IDENTIFIER!\n");
				break;
			}
			entry = lookup(table, expression->expression.unary_expression.operand->expression.identifier_expression->identifier);

			// Decrement value, put result into REG_0
			switch (type_name->type)
			{
				case PRIM_INT:    fprintf(file_pointer, "    addi      a0, zero, 1\n");
				                  fprintf(file_pointer, "    sub       a0, a1, a0\n"); break;
				case PRIM_DOUBLE: fprintf(file_pointer, "    addi      a0, zero, 1\n");
				                  fprintf(file_pointer, "    fsub.s    fa0, fa1, fa0\n"); break;
				default:          printf("UNARY EXPRESSION WARNING: Unsupported type for POSTFIX_DEC!\n");
			}

			// Store contents of REG_0
			fprintf(file_pointer, "    %s       %s, %d(s0)\n", STORE(type_name), REG_0(type_name), entry->stack_pointer_offset);
			break;

		case PREFIX_INC:
			if (expression->expression.unary_expression.operand->expression_type != EXPR_IDENTIFIER)
			{
				printf("UNARY EXPRESSION WARNING: Operator POSTFIX_INC can only be applied to EXPR_IDENTIFIER!\n");
				break;
			}
			entry = lookup(table, expression->expression.unary_expression.operand->expression.identifier_expression->identifier);

			// Increment value, put result into REG_1
			switch (type_name->type)
			{
				case PRIM_INT:    fprintf(file_pointer, "    addi      a1, a1, 1\n"); break;
				case PRIM_DOUBLE: fprintf(file_pointer, "    addi      a0, zero, 1\n");
				                  fprintf(file_pointer, "    fcvt.s.w   fa0, a0\n");
				                  fprintf(file_pointer, "    fadd.s    fa1, fa0, fa1\n"); break;
				break;
				default:          printf("UNARY EXPRESSION WARNING: Unsupported type for PREFIX_INC!\n");
			}

			// Store contents of REG_1
			fprintf(file_pointer, "    %s       %s, %d(s0)\n", STORE(type_name), REG_1(type_name), entry->stack_pointer_offset);
			break;

		case PREFIX_DEC:
			if (expression->expression.unary_expression.operand->expression_type != EXPR_IDENTIFIER)
			{
				printf("UNARY EXPRESSION WARNING: Operator POSTFIX_INC can only be applied to EXPR_IDENTIFIER!\n");
				break;
			}
			entry = lookup(table, expression->expression.unary_expression.operand->expression.identifier_expression->identifier);

			// Decrement value, put result into REG_1
			switch (type_name->type)
			{
				case PRIM_INT:    fprintf(file_pointer, "    addi      a0, zero, 1\n");
				                  fprintf(file_pointer, "    sub       a1, a1, a0\n"); break;
				case PRIM_DOUBLE: fprintf(file_pointer, "    addi      a0, zero, 1\n");
				                  fprintf(file_pointer, "    fsub.s    fa1, fa1, fa0\n"); break;
				break;
				default:          printf("UNARY EXPRESSION WARNING: Unsupported type for PREFIX_DEC!\n");
			}

			// Store contents of REG_1
			fprintf(file_pointer, "    %s       %s, %d(s0)\n", STORE(type_name), REG_1(type_name), entry->stack_pointer_offset);
			break;

		default:
			printf("ERROR: UNKOWN UNARY OPERATOR TYPE!\n");
	}

	// In the end, store REG_1 on the stack
	if (write_to_stack)
	{
		fprintf(file_pointer, "# Store result of unary expression on stack\n");
		fprintf(file_pointer, "    addi      sp, sp, -%d\n", BYTES_PER_TYPE);
		fprintf(file_pointer, "    %s       %s, 0(sp)\n\n", STORE(type_name), REG_1(type_name));
	}

	return type_name;
}

AST_Type *write_binary_expr_to_riscv_file 
(
	FILE *file_pointer,	
	AST_Expr *expression, 
	SymbolTable *table,
	int write_to_stack
)
{
	SymbolTableEntry *entry;
	AST_Type *type_name = new_empty_type();

	AST_Type *l_type = new_type(-1);
	AST_Type *r_type = new_type(-1);

	// Visit left expression, except for the case where we have an assignment
	if (expression->expression.binary_expression.operation != ASSIGNMENT)
	{
		fprintf(file_pointer, "# VISIT LEFT\n");
		l_type = write_expr_to_riscv_file(file_pointer, expression->expression.binary_expression.left, table, 1);
	}

	// Visit right expression
	fprintf(file_pointer, "# VISIT RIGHT\n");
	r_type = write_expr_to_riscv_file(file_pointer, expression->expression.binary_expression.right, table, 0);

	fprintf(file_pointer, "# Load left into (f)a0 (except for assignments) - right already is in (f)a1 due to call with 'write_to_stack' set to 0\n");

	// Again, we don't need to do this for assignments
	if (expression->expression.binary_expression.operation != ASSIGNMENT)
	{
		fprintf(file_pointer, "    %s       %s, 0(sp)\n", LOAD(l_type), REG_0(l_type)); // Left
		fprintf(file_pointer, "    addi      sp, sp, %d\n\n", BYTES_PER_TYPE);
	}

	if (((int)l_type->type >= 0) && (l_type->type != r_type->type))
	{
		printf("BINARY EXPRESSION WARNING: LEFT (%d) AND RIGHT (%d) TYPES DON'T MATCH! TRYING TO CONVERT!\n", l_type->type, r_type->type);

		int conversion_rule_found = 1;

		if (l_type->type == PRIM_DOUBLE && r_type->type == PRIM_INT)
		{
			// Convert right to double
			fprintf(file_pointer, "    fcvt.s.w   fa1, a1\n");
			r_type = new_type(PRIM_DOUBLE);
		}
		else if (l_type->type == PRIM_INT && r_type->type == PRIM_DOUBLE)
		{
			// Convert left to double
			fprintf(file_pointer, "    fcvt.s.w   fa0, a0\n");
			l_type = new_type(PRIM_DOUBLE);
		}
		else
		{
			conversion_rule_found = 0;
		}

		if (conversion_rule_found)
		{
			printf("CONVERSION RULE FOUND!\n");
		}
		else
		{
			printf("BINARY EXPRESSION WARNING: NO CONVERSION RULE FOUND!\n");
			return type_name;
		}
	}

	// Now what?
	switch (expression->expression.binary_expression.operation)
	{
		case ASSIGNMENT:
			// Check that left side is a symbol
			if (expression->expression.binary_expression.left->expression_type != EXPR_IDENTIFIER)
			{
				printf("ERROR: Expected an identifier on the left hand side of an assignment!");
				return type_name;
			}

			// Find the left symbol in the symbol table
			entry = lookup(table, expression->expression.binary_expression.left->expression.identifier_expression->identifier);

			if (entry == NULL)
			{
				printf("ERROR: Could not find symbol table entry!\n"); fflush(stdin);
			}

			l_type = clone_type(entry->type);

			// Check that types are compatible
			if (l_type->type != r_type->type)
			{
				// If not, try to make a conversion
				printf("ASSIGNMENT WARNING: Different types: Left %d and Right %d\n", l_type->type, r_type->type);

				if (l_type->type == PRIM_DOUBLE && r_type->type == PRIM_INT)  // int->double
				{
					fprintf(file_pointer, "    fcvt.s.w   fa1, a1\n");
				}
				else if (l_type->type == PRIM_INT && r_type->type == PRIM_DOUBLE)  // double->int
				{
					fprintf(file_pointer, "    fcvt.w.s   a1, fa1\n");
				}
				else if 
				(
					(l_type->type == PRIM_CHAR && r_type->type == PRIM_INT)
					||
					(l_type->type == PRIM_INT  && r_type->type == PRIM_CHAR)
				)
				{
					// No code needed for conversion	
				}
				else
				{
					printf("ASSIGNMENT ERROR: Can't write Assignment due non-existant conversion rule!\n");
					return type_name;
				}
			}

			// Store reg_1 into the variable
			fprintf(file_pointer, "# Assignment\n");
			fprintf(file_pointer, "    %s       %s, %d(s0)\n", STORE(l_type), REG_1(l_type), entry->stack_pointer_offset);
			fflush(file_pointer);
			type_name = clone_type(r_type);
			break;

		case PLUS:
			switch (r_type->type)
			{
				case PRIM_DOUBLE: fprintf(file_pointer, "    fadd.s    fa1, fa0, fa1\n"); break;
				case PRIM_INT:    fprintf(file_pointer, "    add       a1, a0, a1\n"); break;
				default:          printf("BINARY EXPRESSION WARNING: Unsupported RIGHT TYPE for PLUS!\n");
			}
			type_name = clone_type(r_type);
			break;

		case MINUS:
			switch (r_type->type)
			{
				case PRIM_DOUBLE: fprintf(file_pointer, "    fsub.s    fa1, fa0, fa1\n"); break;
				case PRIM_INT:    fprintf(file_pointer, "    sub       a1, a0, a1\n"); break;
				default:          printf("BINARY EXPRESSION WARNING: Unsupported RIGHT TYPE for MINUS!\n");
			}
			type_name = clone_type(r_type);
			break;

		case MULT:
			switch (r_type->type)
			{
				case PRIM_DOUBLE: fprintf(file_pointer, "    fmul.s    fa1, fa0, fa1\n"); break;
				case PRIM_INT:    fprintf(file_pointer, "    mul       a1, a0, a1\n"); break;
				default:          printf("BINARY EXPRESSION WARNING: Unsupported RIGHT TYPE for MULT! (%d)\n", r_type->type);
			}
			type_name = clone_type(r_type);
			break;

		case DIV:
			switch (r_type->type)
			{
				case PRIM_DOUBLE: fprintf(file_pointer, "    fdiv.s    fa1, fa0, fa1\n"); break;
				case PRIM_INT:    fprintf(file_pointer, "    div       a1, a0, a1\n"); break;
				default:          printf("BINARY EXPRESSION WARNING: Unsupported RIGHT TYPE for DIV!\n");
			}
			type_name = clone_type(r_type);
			break;

		case MOD:
			switch (r_type->type)
			{
				case PRIM_INT:    fprintf(file_pointer, "    rem       a1, a0, a1\n"); break;
				default:          printf("BINARY EXPRESSION WARNING: Unsupported RIGHT TYPE for MOD!\n");
			}
			type_name = clone_type(r_type);
			break;

		case EQUAL:
			switch (r_type->type)
			{
				case PRIM_DOUBLE: fprintf(file_pointer, "    feq.s     a1, fa0, fa1\n"); break;
				case PRIM_INT:    fprintf(file_pointer, "    slt       a2, a0, a1\n"); // For equality, this needs to be false
				                  fprintf(file_pointer, "    slt       a3, a1, a0\n"); // For equality, this needs to be false
				                  fprintf(file_pointer, "    or        a1, a2, a3\n"); 
				                  fprintf(file_pointer, "    xori      a1, a1, 1\n"); break;
				default:          printf("BINARY EXPRESSION WARNING: Unsupported RIGHT TYPE for EQUAL!\n");
			}
			type_name = new_type(PRIM_INT);
			break;

		case NOT_EQUAL:
			switch (r_type->type)
			{
				case PRIM_DOUBLE: fprintf(file_pointer, "    feq.s     a1, fa0, fa1\n");
				                  fprintf(file_pointer, "    xori      a1, a1, 1\n"); break;
				case PRIM_INT:    fprintf(file_pointer, "    slt       a2, a0, a1\n");
				                  fprintf(file_pointer, "    slt       a3, a1, a0\n");
				                  fprintf(file_pointer, "    or        a1, a2, a3\n"); break;
				default:          printf("BINARY EXPRESSION WARNING: Unsupported RIGHT TYPE for NOT_EQUAL!\n");
			}
			type_name = new_type(PRIM_INT);
			break;

		case LESS:
			switch (r_type->type)
			{
				case PRIM_DOUBLE: fprintf(file_pointer, "    flt.s     a1, fa0, fa1\n"); break;
				case PRIM_INT:    fprintf(file_pointer, "    slt       a1, a0, a1\n"); break;
				default:          printf("BINARY EXPRESSION WARNING: Unsupported RIGHT TYPE for LESS!\n");
			}
			type_name = new_type(PRIM_INT);
			break;

		case LESS_EQUAL:
			switch (r_type->type)
			{
				case PRIM_DOUBLE: fprintf(file_pointer, "    fle.s     a1, fa0, fa1\n"); break;
				case PRIM_INT:    fprintf(file_pointer, "    slt       a1, a1, a0\n");
				                  fprintf(file_pointer, "    xori      a1, a1, 1\n"); break;
				default:          printf("BINARY EXPRESSION WARNING: Unsupported RIGHT TYPE for LESS_EQUAL!\n");
			}
			type_name = new_type(PRIM_INT);
			break;

		case GREATER:
			switch (r_type->type)
			{
				case PRIM_DOUBLE: fprintf(file_pointer, "    flt.s     a1, fa1, fa0\n"); break;
				case PRIM_INT:    fprintf(file_pointer, "    slt       a1, a1, a0\n"); break;
				default:          printf("BINARY EXPRESSION WARNING: Unsupported RIGHT TYPE for GREATER!\n");
			}
			type_name = new_type(PRIM_INT);
			break;

		case GREATER_EQUAL:
			switch (r_type->type)
			{
				case PRIM_DOUBLE: fprintf(file_pointer, "    fle.s     a1, fa1, fa0\n"); break;
				case PRIM_INT:    fprintf(file_pointer, "    slt       a1, a0, a1\n");
				                  fprintf(file_pointer, "    xori      a1, a1, 1\n"); break;
				default:          printf("BINARY EXPRESSION WARNING: Unsupported RIGHT TYPE for GREATER_EQUAL!\n");
			}
			type_name = new_type(PRIM_INT);
			break;

		case L_AND:
			if (l_type->type == PRIM_DOUBLE || r_type->type == PRIM_DOUBLE) printf("BINARY EXPRESSION WARNING: Unsupported Type for L_AND!\n");
			fprintf(file_pointer, "    and       a1, a0, a1\n");
			type_name = new_type(PRIM_INT);
			break;

		case L_OR:
			if (l_type->type == PRIM_DOUBLE || r_type->type == PRIM_DOUBLE) printf("BINARY EXPRESSION WARNING: Unsupported Type for L_OR!\n");
			fprintf(file_pointer, "    or        a1, a0, a1\n");
			type_name = new_type(PRIM_INT);
			break;

		case B_AND:
			if (l_type->type == PRIM_DOUBLE || r_type->type == PRIM_DOUBLE) printf("BINARY EXPRESSION WARNING: Unsupported Type for B_AND!\n");
			fprintf(file_pointer, "    and       a1, a0, a1\n");
			type_name = new_type(PRIM_INT);
			break;

		case B_OR:
			if (l_type->type == PRIM_DOUBLE || r_type->type == PRIM_DOUBLE) printf("BINARY EXPRESSION WARNING: Unsupported Type for B_OR!\n");
			fprintf(file_pointer, "    or        a1, a0, a1\n");
			type_name = new_type(PRIM_INT);
			break;

		case B_XOR:
			if (l_type->type == PRIM_DOUBLE || r_type->type == PRIM_DOUBLE) printf("BINARY EXPRESSION WARNING: Unsupported Type for B_XOR!\n");
			fprintf(file_pointer, "    xor       a1, a0, a1\n");
			type_name = new_type(PRIM_INT);
			break;

		case SHIFT_L:
			if (l_type->type == PRIM_DOUBLE || r_type->type == PRIM_DOUBLE) printf("BINARY EXPRESSION WARNING: Unsupported Type for SHIFT_L!\n");
			fprintf(file_pointer, "    sll       a1, a0, a1\n");
			type_name = new_type(PRIM_INT);
			break;

		case SHIFT_R:
			if (l_type->type == PRIM_DOUBLE || r_type->type == PRIM_DOUBLE) printf("BINARY EXPRESSION WARNING: Unsupported Type for SHIFT_R!\n");
			fprintf(file_pointer, "    srl       a1, a0, a1\n");
			type_name = new_type(PRIM_INT);
			break;

		case CONCAT:
			printf("NOT SUPPORTED: BINARY OPERATION 'CONCAT'\n");
			break;
			
		default:
			printf("ERROR: AST_WRITER: UNKOWN BINARY OPERATOR TYPE!\n");
	}

	// In the end, store REG_1 on the stack
	if (write_to_stack)
	{
		fprintf(file_pointer, "# Store result of binary expression on stack\n");
		fprintf(file_pointer, "    addi      sp, sp, -%d\n", BYTES_PER_TYPE);
		fprintf(file_pointer, "    %s       %s, 0(sp)\n\n", STORE(type_name), REG_1(type_name));
	}

	free(l_type);
	free(r_type);

	return type_name;
}

void
write_print_expression
(
	FILE *file_pointer,	
	AST_Expr *expression, 
	SymbolTable *table
)
{
	AST_Expr_List *expression_list = expression->expression.call_expression.args;

	while (expression_list != NULL)
	{
		if (expression_list->expression != NULL)
		{
			// Visit the expression
			fprintf(file_pointer, "# Visit expression to be printed\n");
			AST_Type *type = write_expr_to_riscv_file(file_pointer, expression_list->expression, table, 0);

			switch (type->type)
			{
				case PRIM_VOID:
					printf("PRINT WARNING: Can't print type PRIM_VOID\n");
					break;

				case PRIM_CHAR:
				case PRIM_INT:
					fprintf(file_pointer, "    mv        a0, a1\n");            // Move expression result to a0
					fprintf(file_pointer, "# Print value for ");
					switch (TARGET)
					{
						case 0: fprintf(file_pointer, "Trireme\n    addi      t0, zero, %d\n", type->type == PRIM_INT ? 1 :  2); break;
						case 1: fprintf(file_pointer, "RARS   \n    li        a7, %d\n",       type->type == PRIM_INT ? 1 : 11); break;
						case 2: fprintf(file_pointer, "Spike\n");                                     // Same as printing char
						        fprintf(file_pointer, "    sw        a1, -%d(sp)\n", BYTES_PER_TYPE); // Put character on stack
						        fprintf(file_pointer, "    li        a0, 1\n");                       // STDOUT
						        fprintf(file_pointer, "    addi      a1, sp, -%d\n", BYTES_PER_TYPE); // Address of character
						        fprintf(file_pointer, "    li        a2, 1\n");                       // Length of message (1 char)
						        fprintf(file_pointer, "    li        a7, 64\n"); break;               // Sys call for write
						
							break;
					
						default: printf("PRINT ERROR: UNKNOWN TARGET\n"); break;
					}
					break;

				case PRIM_DOUBLE:
					fprintf(file_pointer, "    fsgnj.s   fa0, fa1, fa1\n");     // Move expression result to fa0
					switch (TARGET)
					{
						case 0: printf("PRINT ERROR: Trireme does not support printing floats!\n"); break; // Trireme
						case 1: fprintf(file_pointer, "    li        a7, 2\n");                     break; // RARS
						case 2: printf("PRINT ERROR: Spike does not support printing floats!\n");   break; // Spike
						default: printf("PRINT ERROR: UNKNOWN TARGET\n"); break;
					}
					break;

				default:
					printf("PRINT WARNING: Data type currently not supported for printing\n");
					break;
			}
		}

		// Perform ecall
		fprintf(file_pointer, "    ecall\n\n");

		// Get ready to print the next argument
		expression_list = expression_list->next;
	}
}

// Sets up the file handling stuff for the simulator
// Puts the file descriptor into a1 afterwards (to be put into a variable)
void
write_file_open_expression
(
	FILE *file_pointer,	
	AST_Expr *expression, 
	SymbolTable *table
)
{
	if (TARGET != 1 && TARGET != 2)
	{
		printf("FILE ERROR: Only supported by RARS and Spike!\n"); return;
	}

	AST_Expr_List *expression_list = expression->expression.call_expression.args;

	if (expression_list == NULL)
	{
		printf("ERROR: Please specifiy file name for output! (1)\n");
	}

	if (expression_list->expression == NULL)
	{
		printf("ERROR: Please specifiy file name for output! (2)\n");
	}

	if (expression_list->expression->expression_type != EXPR_CONST_STRING)
	{
		printf("ERROR: Output filename needs to be a string!\n");
	}

	char *filename = expression_list->expression->expression.const_string_expression;

	// Filename is independent from target
	fprintf(file_pointer, ".data\n");
	fprintf(file_pointer, "    fout%d: .asciz %s\n", ++FILE_COUNTER, filename);
	fprintf(file_pointer, ".text\n");

	switch (TARGET)
	{
		case 0: // TRIREME
			printf("FILE OPEN ERROR: NO FILE SUPPORT FOR TRIREME\n");
			break;

		case 1: // RARS
			// Open (for writing) a file that does not exist
			fprintf(file_pointer, "# Open file (RARS)\n");
			fprintf(file_pointer, "    li        a7, 1024\n");                  // System call for open file
			fprintf(file_pointer, "    la        a0, fout%d\n", FILE_COUNTER);  // Output file name
			fprintf(file_pointer, "    li        a1, 1\n");                     // Output for write
			fprintf(file_pointer, "    ecall\n");                               // Open the file, file descriptor in a0
			fprintf(file_pointer, "    mv        a1, a0\n");                    // Save the file descriptor in a1
			break;
	
		case 2: // Spike
			fprintf(file_pointer, "# Open file (spike)\n");
			fprintf(file_pointer, "    la        a0, fout%d\n", FILE_COUNTER);  // Output file name
			fprintf(file_pointer, "    li        a1, 0\n");                     // File descriptor bits
			fprintf(file_pointer, "    addi      a1, a1,     1 # WRITE   \n"); 
			fprintf(file_pointer, "    addi      a1, a1,  0100 # CREATE  \n"); 
			fprintf(file_pointer, "    addi      a1, a1, 01000 # TRUNC   \n"); 
			fprintf(file_pointer, "    li        a2, 0\n");                     // Permission bits
			fprintf(file_pointer, "    addi      a2, a2,  0200 # IWUSR   \n"); 
			fprintf(file_pointer, "    addi      a2, a2,  0400 # IRUSR  \n"); 
			fprintf(file_pointer, "    li        a7, 1024\n");                  // System call for file open
			fprintf(file_pointer, "    ecall\n");                               // Perform system call
			fprintf(file_pointer, "    mv        a1, a0\n");                    // Save the file descriptor in a1
			break;

		default:
			printf("FILE OPEN ERROR: UNKNOWN TARGET\n");
			break;
	}
}

// Expects the file descriptor to be given as first argument
void
write_file_write_expression
(
	FILE *file_pointer,	
	AST_Expr *expression, 
	SymbolTable *table
)
{
	if (TARGET != 1 && TARGET != 2)
	{
		printf("FILE ERROR: Only supported by RARS and Spike!\n"); return;
	}

	SymbolTableEntry *entry;
	AST_Expr_List *expression_list = expression->expression.call_expression.args;

	int descriptor_set = 0;

	while (expression_list != NULL)
	{
		// Put the file descriptor into s6
		if (!descriptor_set)
		{
			// Obtain the descriptor from the given argument
			if (expression_list->expression->expression_type == EXPR_IDENTIFIER)
			{
				entry = lookup(table, expression_list->expression->expression.identifier_expression->identifier);

				if (entry == NULL)
				{
					printf("%s\n", expression->expression.identifier_expression->identifier);
					printf("PANIC!\n");
				}
			}
			else
			{
				printf("PANIC! EXPECTED FILE DESCRIPTOR VIA IDENTIFIER!\n");
			}

			fprintf(file_pointer, "    lw        s6, %d(s0)\n", entry->stack_pointer_offset);

			descriptor_set = 1;
		}
		else
		{
			// Visit the expression
			fprintf(file_pointer, "# Visit expression to be written\n");
			AST_Type *type = write_expr_to_riscv_file(file_pointer, expression_list->expression, table, 0);

			// Write to the file previously opened 
			fprintf(file_pointer, "\n# Write to file\n");
			fprintf(file_pointer, "    li        a7, 64\n"); // system call for write to file
			fprintf(file_pointer, "    mv        a0, s6\n"); // move file descriptor to a0

			switch (type->type)
			{
				case PRIM_VOID:
					printf("WRITE WARNING: Can't write type PRIM_VOID\n");
					break;

				case PRIM_INT: // Fall through to next case
				case PRIM_CHAR:
					switch (TARGET)
					{
						case 1: // Fall through to next case
						case 2: 
							fprintf(file_pointer, "    sw        a1, -%d(sp)\n", BYTES_PER_TYPE); // Prepare value by putting it on the stack
							fprintf(file_pointer, "    addi      a1, sp, -%d\n", BYTES_PER_TYPE); // Load the address that points to the value on the stack
							fprintf(file_pointer, "    li        a2, 1\n");                       // Length of buffer (1 char = 1 byte)
							fprintf(file_pointer, "    ecall\n");                                 // Perform ecall
							break;
						default: printf("WRITE ERROR: UNKNOWN/UNSUPPORTED  TARGET\n"); break;
					}
					break;

				case PRIM_DOUBLE:
					printf("WRITE WARNING: Can't write type PRIM_DOUBLE\n");
					break;

				default:
					printf("WRITE WARNING: Data type currently not supported for printing\n");
					break;
			}
		}
		
		// Get ready to write the next argument
		expression_list = expression_list->next;
	}
}

// Closes a file with given file descriptor expected as first argument
// Other arguments are ignored
void
write_file_close_expression
(
	FILE *file_pointer,	
	AST_Expr *expression, 
	SymbolTable *table
)
{
	if (TARGET != 1 && TARGET != 2)
	{
		printf("FILE ERROR: Only supported by RARS and Spike!\n"); return;
	}

	AST_Expr_List *expression_list = expression->expression.call_expression.args;	
	SymbolTableEntry *entry;

	// Obtain the descriptor from the given argument
	if (expression_list->expression->expression_type == EXPR_IDENTIFIER)
	{
		entry = lookup(table, expression_list->expression->expression.identifier_expression->identifier);

		if (entry == NULL)
		{
			printf("%s\n", expression->expression.identifier_expression->identifier);
			printf("PANIC!\n");
		}
	}
	else
	{
		printf("PANIC! EXPECTED FILE DESCRIPTOR VIA IDENTIFIER!\n");
		return;
	}

	fprintf(file_pointer, "    lw        s6, %d(s0)\n", entry->stack_pointer_offset);

	// Close the file
	fprintf(file_pointer, "# Close file\n");
	fprintf(file_pointer, "    mv        a0, s6\n"); // move file descriptor to a0
	fprintf(file_pointer, "    li        a7, 57\n"); // system call for close file
	fprintf(file_pointer, "    ecall\n");
}

void
write_exit_expression
(
	FILE *file_pointer,	
	AST_Expr *expression, 
	SymbolTable *table
)
{
	// Try to obtain a given exit value
	AST_Expr_List *expression_list = expression->expression.call_expression.args;
	if (expression_list != NULL)
	{
		AST_Expr *expression = expression_list->expression;
		if (expression->expression_type == EXPR_CONST_INT)
		{
			// Write the constant exit value to a0
			fprintf(
				file_pointer, 
				"    addi      a0,zero,%d\n", 
				expression->expression.const_int_expression
			);
		}
		else
		{
			// Try to visit the expression and obtain an integer value
			// Should not put result on stack
			// Instead, copy a1 (the register were the expression result is put
			// after visiting the expression) to a0
			write_expr_to_riscv_file(file_pointer, expression, table, 0);
			fprintf(file_pointer, "    add       a0,a1,zero\n");
		}
	}
	else
	{
		// Write the default exit value to a0
		fprintf(file_pointer, "    addi      a0,zero,0\n");
	}

	fprintf(file_pointer, "# Exit program with given code or default (0) that is stored in a0\n");
	fprintf(file_pointer, "    li        a7, %d\n", SYS_CALL_EXIT);
	fprintf(file_pointer, "    ecall\n");
}
