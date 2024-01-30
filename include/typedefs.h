#ifndef TYPEDEFS_H
#define TYPEDEFS_H

///////////////////////////////////////////////////////////////////////////////
// SYMBOL TABLE
///////////////////////////////////////////////////////////////////////////////

typedef struct S_SymbolTableEntry SymbolTableEntry;
typedef struct S_SymbolTable SymbolTable;

///////////////////////////////////////////////////////////////////////////////
// ABSTRACT SYNTAX TREE
///////////////////////////////////////////////////////////////////////////////

typedef struct S_AST_Root AST_Root;

typedef struct S_AST_Type AST_Type;
typedef struct S_AST_Decl AST_Decl;
typedef struct S_AST_Func AST_Func;

typedef struct S_AST_Decl_Func AST_Decl_Func;

typedef struct S_AST_Iden AST_Iden; // Identifier
typedef struct S_AST_Expr AST_Expr; // Expression
typedef struct S_AST_Stat AST_Stat; // Statement

typedef struct S_AST_Type_List AST_Type_List;
typedef struct S_AST_Decl_List AST_Decl_List;
typedef struct S_AST_Func_List AST_Func_List;

typedef struct S_AST_Iden_List AST_Iden_List;
typedef struct S_AST_Expr_List AST_Expr_List;
typedef struct S_AST_Stat_List AST_Stat_List;

typedef struct S_AST_Node_List AST_Node_List;

typedef enum
{
	UNARY_PLUS,
	UNARY_MINUS,
	B_ONE_COMPLEMENT,
	L_NOT,
	REF,
	DEREF,
	POSTFIX_INC,
	POSTFIX_DEC,
	PREFIX_INC,
	PREFIX_DEC,
} EUnaryOperation;

typedef enum
{
	PLUS,
	MINUS,
	MULT,
	DIV,
	MOD,
	ASSIGNMENT,
	EQUAL,
	NOT_EQUAL,
	LESS,
	LESS_EQUAL,
	GREATER,
	GREATER_EQUAL,
	L_AND,
	L_OR,
	B_AND,
	B_OR,
	B_XOR,
	SHIFT_L,
	SHIFT_R,
	CONCAT // For expression ',' assignment_expression. Value of expression is value of assignment_expression.
} EBinaryOperation;

typedef enum
{
	PRIM_VOID,
	PRIM_CHAR,
	PRIM_INT,
	PRIM_DOUBLE,
} ETypeNames;

typedef enum 
{
	AST_ROOT,
	AST_TYPE,
	AST_DECL,

	AST_IDEN,
	AST_EXPR,
	AST_STAT,

	AST_FUNC,
	
	AST_TYPE_LIST,

	AST_IDEN_LIST,
	AST_EXPR_LIST,
	AST_STAT_LIST,

	AST_FUNC_LIST,
} EASTNodeType;

typedef enum
{
	DECL_IDEN,
	DECL_FUNC,
} EDeclaratorTypes; // And NOT Declarations!

typedef enum
{
	EXPR_CONST_INT,
	EXPR_CONST_DOUBLE,
	EXPR_CONST_CHAR,
	EXPR_CONST_STRING,
	EXPR_IDENTIFIER,
	EXPR_UNARY,
	EXPR_BINARY,
	EXPR_TERNARY,
	EXPR_CAST,
	EXPR_ARRAY_ACCESS,
	EXPR_STRUCT_MEMBER_ACCESS,
	EXPR_STRUCT_POINTER_MEMBER_ACCESS,
	EXPR_CALL,
	EXPR_SIZEOF_EXPR,
	EXPR_SIZEOF_TYPE,
} EExpressionType;

typedef enum
{
	STAT_EXPR,
	STAT_COMPOUND,
	STAT_IF,
	STAT_IF_ELSE,
	STAT_SWITCH,
	STAT_FOR,
	STAT_WHILE,
	STAT_DO_WHILE,
	STAT_GOTO,
	STAT_CONTINUE,
	STAT_BREAK,
	STAT_RETURN,
	STAT_RETURN_EXPR,
	STAT_LABELED,
} EStatementType;

#endif
