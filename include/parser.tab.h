/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SIZEOF = 258,                  /* SIZEOF  */
    PTR_OP = 259,                  /* PTR_OP  */
    INC_OP = 260,                  /* INC_OP  */
    DEC_OP = 261,                  /* DEC_OP  */
    LEFT_OP = 262,                 /* LEFT_OP  */
    RIGHT_OP = 263,                /* RIGHT_OP  */
    LE_OP = 264,                   /* LE_OP  */
    GE_OP = 265,                   /* GE_OP  */
    EQ_OP = 266,                   /* EQ_OP  */
    NE_OP = 267,                   /* NE_OP  */
    AND_OP = 268,                  /* AND_OP  */
    OR_OP = 269,                   /* OR_OP  */
    MUL_ASSIGN = 270,              /* MUL_ASSIGN  */
    DIV_ASSIGN = 271,              /* DIV_ASSIGN  */
    MOD_ASSIGN = 272,              /* MOD_ASSIGN  */
    ADD_ASSIGN = 273,              /* ADD_ASSIGN  */
    SUB_ASSIGN = 274,              /* SUB_ASSIGN  */
    LEFT_ASSIGN = 275,             /* LEFT_ASSIGN  */
    RIGHT_ASSIGN = 276,            /* RIGHT_ASSIGN  */
    AND_ASSIGN = 277,              /* AND_ASSIGN  */
    XOR_ASSIGN = 278,              /* XOR_ASSIGN  */
    OR_ASSIGN = 279,               /* OR_ASSIGN  */
    TYPEDEF = 280,                 /* TYPEDEF  */
    EXTERN = 281,                  /* EXTERN  */
    STATIC = 282,                  /* STATIC  */
    AUTO = 283,                    /* AUTO  */
    REGISTER = 284,                /* REGISTER  */
    CHAR = 285,                    /* CHAR  */
    SHORT = 286,                   /* SHORT  */
    INT = 287,                     /* INT  */
    LONG = 288,                    /* LONG  */
    SIGNED = 289,                  /* SIGNED  */
    UNSIGNED = 290,                /* UNSIGNED  */
    FLOAT = 291,                   /* FLOAT  */
    DOUBLE = 292,                  /* DOUBLE  */
    CONST = 293,                   /* CONST  */
    VOLATILE = 294,                /* VOLATILE  */
    VOID = 295,                    /* VOID  */
    STRUCT = 296,                  /* STRUCT  */
    UNION = 297,                   /* UNION  */
    ENUM = 298,                    /* ENUM  */
    ELLIPSIS = 299,                /* ELLIPSIS  */
    CASE = 300,                    /* CASE  */
    DEFAULT = 301,                 /* DEFAULT  */
    IF = 302,                      /* IF  */
    ELSE = 303,                    /* ELSE  */
    SWITCH = 304,                  /* SWITCH  */
    WHILE = 305,                   /* WHILE  */
    DO = 306,                      /* DO  */
    FOR = 307,                     /* FOR  */
    GOTO = 308,                    /* GOTO  */
    CONTINUE = 309,                /* CONTINUE  */
    BREAK = 310,                   /* BREAK  */
    RETURN = 311,                  /* RETURN  */
    NO_ELSE = 312,                 /* NO_ELSE  */
    INT_CONSTANT = 313,            /* INT_CONSTANT  */
    DOUBLE_CONSTANT = 314,         /* DOUBLE_CONSTANT  */
    CHAR_CONSTANT = 315,           /* CHAR_CONSTANT  */
    STRING_LITERAL = 316,          /* STRING_LITERAL  */
    IDENTIFIER = 317               /* IDENTIFIER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 35 "parser.y"

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

#line 155 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
