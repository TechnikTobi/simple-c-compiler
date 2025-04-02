#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "typedefs.h"

struct 
S_SymbolTableEntry
{
	AST_Type                 *type;
	AST_Decl                 *declarator;
	int                      stack_pointer_offset;
};

struct 
S_SymbolTable
{
	SymbolTableEntry        *entry;
	SymbolTable             *next;
	SymbolTable             *previous;
	int                     size_without_parameter_table;
};

SymbolTableEntry *new_symbol_table_entry(AST_Type *type, AST_Decl *declarator);

SymbolTable *new_symbol_table(SymbolTableEntry *entry);
SymbolTable *new_symbol_table_from_decl_list(AST_Type *type, AST_Decl_List *decl_list);
SymbolTable *symbol_table_insert_end(SymbolTable *table, SymbolTableEntry *entry);
SymbolTable *symbol_table_append_end(SymbolTable *table, SymbolTable *other);

SymbolTable * combine_symbol_table_with_parameter_table(SymbolTable *table, int table_len, SymbolTable *parameter_table);

SymbolTableEntry *lookup(SymbolTable *table, char *identifier);

void print_symbol_table(SymbolTable *table, char* func_name);

#endif
