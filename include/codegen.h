#ifndef CODEGEN_H
#define CODEGEN_H

#include <stdio.h>

#include "ast.h"

AST_Func *func_lookup(AST_Func_List *list, char *identifier);

int write_ast_to_riscv_file(char* filename, AST_Root* root, int target);

void write_root_to_riscv_file (FILE *file_pointer, AST_Root *node);

void write_func_to_riscv_file (FILE *file_pointer,	AST_Func *function);
int write_symbol_table_to_riscv_file (FILE *file_pointer, SymbolTable *table);

void write_stat_to_riscv_file (FILE *file_pointer,	AST_Stat *statement, SymbolTable *table);

AST_Type *write_expr_to_riscv_file        (FILE *file_pointer, AST_Expr *expression, SymbolTable *table, int write_to_stack);
AST_Type *write_unary_expr_to_riscv_file  (FILE *file_pointer, AST_Expr *expression, SymbolTable *table, int write_to_stack);
AST_Type *write_binary_expr_to_riscv_file (FILE *file_pointer, AST_Expr *expression, SymbolTable *table, int write_to_stack);

void write_equals_check_and_branch (FILE *file_pointer,	char *base_jump_type, int jump_counter);

void write_print_expression      (FILE *file_pointer,	AST_Expr *expression, SymbolTable *table);
void write_file_write_expression (FILE *file_pointer,	AST_Expr *expression, SymbolTable *table);
void write_file_open_expression  (FILE *file_pointer,	AST_Expr *expression, SymbolTable *table);
void write_file_close_expression (FILE *file_pointer,	AST_Expr *expression, SymbolTable *table);
void write_exit_expression       (FILE *file_pointer,	AST_Expr *expression, SymbolTable *table);

char *construct_string (char* string, int value);

#endif
