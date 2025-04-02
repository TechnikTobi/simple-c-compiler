#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "typedefs.h"
#include "symbol_table.h"


SymbolTableEntry *new_symbol_table_entry(AST_Type *type, AST_Decl *declarator)
{
	SymbolTableEntry *new = (SymbolTableEntry*) malloc(sizeof(SymbolTableEntry));
	new->type = type;
	new->declarator = declarator;
	new->stack_pointer_offset = 0;
	return new;
}

SymbolTable *new_symbol_table(SymbolTableEntry *entry)
{
	SymbolTable *new = (SymbolTable*) malloc(sizeof(SymbolTable));
	new->entry = entry;
	new->previous = NULL;
	new->next = NULL;
	return new;
}

SymbolTable *new_symbol_table_from_decl_list(AST_Type *type, AST_Decl_List *decl_list)
{
	SymbolTable *table = NULL;

	AST_Decl_List *declarator_entry = decl_list;

	while (declarator_entry != NULL)
	{
		SymbolTableEntry *entry = new_symbol_table_entry(type, declarator_entry->declarator);
		table = symbol_table_insert_end(table, entry);

		declarator_entry = declarator_entry->next;
	}

	return table;
}

SymbolTable *symbol_table_append_end(SymbolTable *table, SymbolTable *other)
{
	if (table           == NULL)       { return other; }
	if (table->next     != NULL)       { symbol_table_append_end(table->next, other); return table; }
	if (other->previous != NULL)       { symbol_table_append_end(table, other->previous); return table; }

	table->next = other;
	other->previous = table;
	
	return table;
}

SymbolTable *symbol_table_insert_end(SymbolTable *table, SymbolTableEntry *entry)
{
	SymbolTable *new = new_symbol_table(entry);
	return symbol_table_append_end(table, new);
}

SymbolTable *combine_symbol_table_with_parameter_table(SymbolTable *table, int table_len, SymbolTable *parameter_table)
{
	// Note that the parameter table needs a different offset scheme than the
	// actual symbol table.
	// In the "normal" symbol table, the offset increases the later the 
	// variable is declared.
	// With the parameters, the first parameter is the first one being
	// pushed on the stack, thus needing the largest offset, the latest the 
	// smallest offset.
	// Furthermore, this smallest offset is larger than the size of the symbol 
	// table as we need to account for the following values being on the stack
	// between these two areas:
	// - the number of parameters (1x BYTES_PER_TYPE)
	// - the old sp, a0 and s0 registers (3x BYTES_PER_TYPE)

	if (parameter_table == NULL) 
	{
		return table;
	}

	// The table len is the number of symbols that we acquired upon writing
	// the local symbol table to the output file and can be used to compute the
	// smallest offset
	int offset = table_len + (1 + 3) * 8;

	// Get the last entry in the parameter table
	SymbolTable *last = parameter_table;
	while (last->next != NULL) last = last->next;

	while (last->previous != NULL)
	{
		if (last->entry != NULL)
		{
			last->entry->stack_pointer_offset = offset;
			offset += 8;
		}

		last = last->previous;
	}

	// Don't forget the first item in the parameter table!
	if (last->entry != NULL)
	{
		last->entry->stack_pointer_offset = offset;
	}

	// Finally, append the parameter table to the symbol table
	return symbol_table_append_end(table, parameter_table);
}

SymbolTableEntry *lookup(SymbolTable *table, char *identifier)
{
	SymbolTable *current = table;

	if (table == NULL) return NULL;

	do
	{
		if (current->entry == NULL) 
		{
			current = current->next;
		}
		else
		{
			if (
				strcmp(
					current->entry->declarator->declarator.iden_declarator.declarator->identifier,
					identifier
				)
				== 0
			)
			{
				return current->entry;
			}

			// Go to the next symbol table entry
			current = current->next;
		}
	} 
	while (current != NULL);

	return NULL;
}

void print_symbol_table(SymbolTable *table, char* func_name)
{
	printf("\nStart of Symbol table for function \'%s\':\n", func_name);

	if (table == NULL)
	{
		printf("EMPTY SYMBOL TABLE!\n");
		return;
	}

	SymbolTable *current = table;
	do
	{
		if (current->entry == NULL) current = current->next;;

		printf("\n");
		printf("Entry:\n");
		printf("Symbol: %s\n", current->entry->declarator->declarator.iden_declarator.declarator->identifier);
		printf("Function: %s\n", current->entry->declarator->type == DECL_FUNC ? "YES" : "NO");

		// Type Qualifier & Specifier
		printf("Qualifier & Specifier: ");

		if ((current->entry->type->qualifier_and_specifier & 64) == 64)
			printf("const ");

		if ((current->entry->type->qualifier_and_specifier & 32) == 32)
			printf("volatile ");

		if ((current->entry->type->qualifier_and_specifier & 16) == 16)
			printf("typedef ");

		if ((current->entry->type->qualifier_and_specifier & 8) == 8)
			printf("extern ");

		if ((current->entry->type->qualifier_and_specifier & 4) == 4)
			printf("static ");

		if ((current->entry->type->qualifier_and_specifier & 2) == 2)
			printf("auto ");

		if ((current->entry->type->qualifier_and_specifier & 1) == 1)
			printf("register ");

		if (current->entry->type->qualifier_and_specifier == 0)
			printf("NONE");

		printf("\n");


		// Type Modifiers
		printf("Type Modifiers: ");

		if ((current->entry->type->modifier & 8) == 8)
			printf("short ");

		if ((current->entry->type->modifier & 4) == 4)
			printf("long ");

		if ((current->entry->type->modifier & 2) == 2)
			printf("signed ");

		if ((current->entry->type->modifier & 1) == 1)
			printf("unsigned ");

		if (current->entry->type->modifier == 0)
			printf("NONE");

		printf("\n");


		// Primitive Type
		printf("Primitive: ");

		switch (current->entry->type->type)
		{
			case PRIM_VOID:
				printf("void");
				break;
			case PRIM_CHAR:
				printf("char");
				break;
			case PRIM_INT:
				printf("int");
				break;
			case PRIM_DOUBLE:
				printf("double");
				break;
			default: 
				printf("UNKNOWN");
		}

		printf("\n");


		// Go to the next symbol table entry
		current = current->next;
	} 
	while (current != NULL);

	printf("\nEnd of Symbol table for function \'%s\'\n", func_name);
}
