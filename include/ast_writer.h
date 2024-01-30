#ifndef AST_WRITER_H
#define AST_WRITER_H

#include <stdio.h>

#include "ast.h"

int write_ast_to_dot_file(char* filename, AST_Root* root);
void write_root_to_dot_file(FILE *file_pointer, AST_Root *node, int this_node_counter, int* node_counter);
void write_parent_child_to_dot_file(FILE *file_pointer, int parent, int child, char* label, int counter);

void write_type_to_dot_file(FILE *file_pointer, AST_Type *type,       int this_node_counter, int* node_counter);
void write_func_to_dot_file(FILE *file_pointer,	AST_Func *function,   int this_node_counter, int* node_counter);

void write_iden_to_dot_file(FILE *file_pointer,	AST_Iden *identifier, int this_node_counter, int* node_counter);
void write_expr_to_dot_file(FILE *file_pointer,	AST_Expr *expression, int this_node_counter, int* node_counter);
void write_stat_to_dot_file(FILE *file_pointer,	AST_Stat *statement,  int this_node_counter, int* node_counter);

int write_node_to_dot_file (FILE *file_pointer, void *node, EASTNodeType type, int* node_counter);

void write_char_to_dot_file(FILE *file_pointer, char character);

#endif
