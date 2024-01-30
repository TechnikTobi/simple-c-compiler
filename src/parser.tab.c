/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "typedefs.h"
#include "symbol_table.h"

int yylex();
void yyerror(char*);
AST_Root *tree;


#line 87 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SIZEOF = 3,                     /* SIZEOF  */
  YYSYMBOL_PTR_OP = 4,                     /* PTR_OP  */
  YYSYMBOL_INC_OP = 5,                     /* INC_OP  */
  YYSYMBOL_DEC_OP = 6,                     /* DEC_OP  */
  YYSYMBOL_LEFT_OP = 7,                    /* LEFT_OP  */
  YYSYMBOL_RIGHT_OP = 8,                   /* RIGHT_OP  */
  YYSYMBOL_LE_OP = 9,                      /* LE_OP  */
  YYSYMBOL_GE_OP = 10,                     /* GE_OP  */
  YYSYMBOL_EQ_OP = 11,                     /* EQ_OP  */
  YYSYMBOL_NE_OP = 12,                     /* NE_OP  */
  YYSYMBOL_AND_OP = 13,                    /* AND_OP  */
  YYSYMBOL_OR_OP = 14,                     /* OR_OP  */
  YYSYMBOL_MUL_ASSIGN = 15,                /* MUL_ASSIGN  */
  YYSYMBOL_DIV_ASSIGN = 16,                /* DIV_ASSIGN  */
  YYSYMBOL_MOD_ASSIGN = 17,                /* MOD_ASSIGN  */
  YYSYMBOL_ADD_ASSIGN = 18,                /* ADD_ASSIGN  */
  YYSYMBOL_SUB_ASSIGN = 19,                /* SUB_ASSIGN  */
  YYSYMBOL_LEFT_ASSIGN = 20,               /* LEFT_ASSIGN  */
  YYSYMBOL_RIGHT_ASSIGN = 21,              /* RIGHT_ASSIGN  */
  YYSYMBOL_AND_ASSIGN = 22,                /* AND_ASSIGN  */
  YYSYMBOL_XOR_ASSIGN = 23,                /* XOR_ASSIGN  */
  YYSYMBOL_OR_ASSIGN = 24,                 /* OR_ASSIGN  */
  YYSYMBOL_TYPEDEF = 25,                   /* TYPEDEF  */
  YYSYMBOL_EXTERN = 26,                    /* EXTERN  */
  YYSYMBOL_STATIC = 27,                    /* STATIC  */
  YYSYMBOL_AUTO = 28,                      /* AUTO  */
  YYSYMBOL_REGISTER = 29,                  /* REGISTER  */
  YYSYMBOL_CHAR = 30,                      /* CHAR  */
  YYSYMBOL_SHORT = 31,                     /* SHORT  */
  YYSYMBOL_INT = 32,                       /* INT  */
  YYSYMBOL_LONG = 33,                      /* LONG  */
  YYSYMBOL_SIGNED = 34,                    /* SIGNED  */
  YYSYMBOL_UNSIGNED = 35,                  /* UNSIGNED  */
  YYSYMBOL_FLOAT = 36,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 37,                    /* DOUBLE  */
  YYSYMBOL_CONST = 38,                     /* CONST  */
  YYSYMBOL_VOLATILE = 39,                  /* VOLATILE  */
  YYSYMBOL_VOID = 40,                      /* VOID  */
  YYSYMBOL_STRUCT = 41,                    /* STRUCT  */
  YYSYMBOL_UNION = 42,                     /* UNION  */
  YYSYMBOL_ENUM = 43,                      /* ENUM  */
  YYSYMBOL_ELLIPSIS = 44,                  /* ELLIPSIS  */
  YYSYMBOL_CASE = 45,                      /* CASE  */
  YYSYMBOL_DEFAULT = 46,                   /* DEFAULT  */
  YYSYMBOL_IF = 47,                        /* IF  */
  YYSYMBOL_ELSE = 48,                      /* ELSE  */
  YYSYMBOL_SWITCH = 49,                    /* SWITCH  */
  YYSYMBOL_WHILE = 50,                     /* WHILE  */
  YYSYMBOL_DO = 51,                        /* DO  */
  YYSYMBOL_FOR = 52,                       /* FOR  */
  YYSYMBOL_GOTO = 53,                      /* GOTO  */
  YYSYMBOL_CONTINUE = 54,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 55,                     /* BREAK  */
  YYSYMBOL_RETURN = 56,                    /* RETURN  */
  YYSYMBOL_NO_ELSE = 57,                   /* NO_ELSE  */
  YYSYMBOL_INT_CONSTANT = 58,              /* INT_CONSTANT  */
  YYSYMBOL_DOUBLE_CONSTANT = 59,           /* DOUBLE_CONSTANT  */
  YYSYMBOL_CHAR_CONSTANT = 60,             /* CHAR_CONSTANT  */
  YYSYMBOL_STRING_LITERAL = 61,            /* STRING_LITERAL  */
  YYSYMBOL_IDENTIFIER = 62,                /* IDENTIFIER  */
  YYSYMBOL_63_ = 63,                       /* '('  */
  YYSYMBOL_64_ = 64,                       /* ')'  */
  YYSYMBOL_65_ = 65,                       /* '['  */
  YYSYMBOL_66_ = 66,                       /* ']'  */
  YYSYMBOL_67_ = 67,                       /* ','  */
  YYSYMBOL_68_ = 68,                       /* '&'  */
  YYSYMBOL_69_ = 69,                       /* '*'  */
  YYSYMBOL_70_ = 70,                       /* '+'  */
  YYSYMBOL_71_ = 71,                       /* '-'  */
  YYSYMBOL_72_ = 72,                       /* '~'  */
  YYSYMBOL_73_ = 73,                       /* '!'  */
  YYSYMBOL_74_ = 74,                       /* '/'  */
  YYSYMBOL_75_ = 75,                       /* '%'  */
  YYSYMBOL_76_ = 76,                       /* '<'  */
  YYSYMBOL_77_ = 77,                       /* '>'  */
  YYSYMBOL_78_ = 78,                       /* '^'  */
  YYSYMBOL_79_ = 79,                       /* '|'  */
  YYSYMBOL_80_ = 80,                       /* '?'  */
  YYSYMBOL_81_ = 81,                       /* ':'  */
  YYSYMBOL_82_ = 82,                       /* '='  */
  YYSYMBOL_83_ = 83,                       /* ';'  */
  YYSYMBOL_84_ = 84,                       /* '{'  */
  YYSYMBOL_85_ = 85,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 86,                  /* $accept  */
  YYSYMBOL_primary_expression = 87,        /* primary_expression  */
  YYSYMBOL_postfix_expression = 88,        /* postfix_expression  */
  YYSYMBOL_argument_expression_list = 89,  /* argument_expression_list  */
  YYSYMBOL_unary_expression = 90,          /* unary_expression  */
  YYSYMBOL_unary_operator = 91,            /* unary_operator  */
  YYSYMBOL_cast_expression = 92,           /* cast_expression  */
  YYSYMBOL_multiplicative_expression = 93, /* multiplicative_expression  */
  YYSYMBOL_additive_expression = 94,       /* additive_expression  */
  YYSYMBOL_shift_expression = 95,          /* shift_expression  */
  YYSYMBOL_relational_expression = 96,     /* relational_expression  */
  YYSYMBOL_equality_expression = 97,       /* equality_expression  */
  YYSYMBOL_and_expression = 98,            /* and_expression  */
  YYSYMBOL_exclusive_or_expression = 99,   /* exclusive_or_expression  */
  YYSYMBOL_inclusive_or_expression = 100,  /* inclusive_or_expression  */
  YYSYMBOL_logical_and_expression = 101,   /* logical_and_expression  */
  YYSYMBOL_logical_or_expression = 102,    /* logical_or_expression  */
  YYSYMBOL_conditional_expression = 103,   /* conditional_expression  */
  YYSYMBOL_assignment_expression = 104,    /* assignment_expression  */
  YYSYMBOL_assignment_operator = 105,      /* assignment_operator  */
  YYSYMBOL_expression = 106,               /* expression  */
  YYSYMBOL_constant_expression = 107,      /* constant_expression  */
  YYSYMBOL_declaration = 108,              /* declaration  */
  YYSYMBOL_declaration_specifiers = 109,   /* declaration_specifiers  */
  YYSYMBOL_declarator_list = 110,          /* declarator_list  */
  YYSYMBOL_type_qualifier = 111,           /* type_qualifier  */
  YYSYMBOL_storage_class_specifier = 112,  /* storage_class_specifier  */
  YYSYMBOL_modified_type_specifier = 113,  /* modified_type_specifier  */
  YYSYMBOL_type_specifier = 114,           /* type_specifier  */
  YYSYMBOL_type_modifier_list = 115,       /* type_modifier_list  */
  YYSYMBOL_type_modifier = 116,            /* type_modifier  */
  YYSYMBOL_specifier_qualifier_list = 117, /* specifier_qualifier_list  */
  YYSYMBOL_declarator = 118,               /* declarator  */
  YYSYMBOL_direct_declarator = 119,        /* direct_declarator  */
  YYSYMBOL_type_name = 120,                /* type_name  */
  YYSYMBOL_function_declarator = 121,      /* function_declarator  */
  YYSYMBOL_statement = 122,                /* statement  */
  YYSYMBOL_labeled_statement = 123,        /* labeled_statement  */
  YYSYMBOL_compound_statement = 124,       /* compound_statement  */
  YYSYMBOL_function_compound_statement = 125, /* function_compound_statement  */
  YYSYMBOL_declaration_list = 126,         /* declaration_list  */
  YYSYMBOL_statement_list = 127,           /* statement_list  */
  YYSYMBOL_expr_statement = 128,           /* expr_statement  */
  YYSYMBOL_selection_statement = 129,      /* selection_statement  */
  YYSYMBOL_iteration_statement = 130,      /* iteration_statement  */
  YYSYMBOL_jump_statement = 131,           /* jump_statement  */
  YYSYMBOL_translation_unit = 132,         /* translation_unit  */
  YYSYMBOL_function_definition_list = 133, /* function_definition_list  */
  YYSYMBOL_function_definition = 134       /* function_definition  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  38
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   780

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  86
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  150
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  247

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   317


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    73,     2,     2,     2,    75,    68,     2,
      63,    64,    69,    70,    67,    71,     2,    74,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    81,    83,
      76,    82,    77,    80,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    65,     2,    66,    78,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    84,    79,    85,    72,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   130,   130,   131,   132,   133,   134,   135,   139,   140,
     141,   142,   143,   144,   148,   149,   153,   154,   155,   156,
     157,   158,   162,   163,   164,   165,   166,   167,   171,   172,
     176,   177,   178,   179,   183,   184,   185,   189,   190,   191,
     195,   196,   197,   198,   199,   203,   204,   205,   209,   210,
     214,   215,   219,   220,   224,   225,   229,   230,   234,   235,
     239,   240,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   258,   259,   263,   267,   271,   272,   273,
     274,   275,   276,   280,   281,   285,   286,   290,   291,   292,
     293,   294,   298,   299,   303,   304,   305,   306,   307,   311,
     312,   316,   317,   318,   319,   323,   324,   325,   326,   330,
     334,   338,   342,   346,   347,   348,   349,   350,   351,   355,
     356,   357,   361,   362,   366,   367,   368,   369,   373,   374,
     378,   379,   383,   384,   388,   389,   390,   394,   395,   396,
     397,   401,   402,   403,   404,   405,   409,   413,   414,   418,
     419
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SIZEOF", "PTR_OP",
  "INC_OP", "DEC_OP", "LEFT_OP", "RIGHT_OP", "LE_OP", "GE_OP", "EQ_OP",
  "NE_OP", "AND_OP", "OR_OP", "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN",
  "ADD_ASSIGN", "SUB_ASSIGN", "LEFT_ASSIGN", "RIGHT_ASSIGN", "AND_ASSIGN",
  "XOR_ASSIGN", "OR_ASSIGN", "TYPEDEF", "EXTERN", "STATIC", "AUTO",
  "REGISTER", "CHAR", "SHORT", "INT", "LONG", "SIGNED", "UNSIGNED",
  "FLOAT", "DOUBLE", "CONST", "VOLATILE", "VOID", "STRUCT", "UNION",
  "ENUM", "ELLIPSIS", "CASE", "DEFAULT", "IF", "ELSE", "SWITCH", "WHILE",
  "DO", "FOR", "GOTO", "CONTINUE", "BREAK", "RETURN", "NO_ELSE",
  "INT_CONSTANT", "DOUBLE_CONSTANT", "CHAR_CONSTANT", "STRING_LITERAL",
  "IDENTIFIER", "'('", "')'", "'['", "']'", "','", "'&'", "'*'", "'+'",
  "'-'", "'~'", "'!'", "'/'", "'%'", "'<'", "'>'", "'^'", "'|'", "'?'",
  "':'", "'='", "';'", "'{'", "'}'", "$accept", "primary_expression",
  "postfix_expression", "argument_expression_list", "unary_expression",
  "unary_operator", "cast_expression", "multiplicative_expression",
  "additive_expression", "shift_expression", "relational_expression",
  "equality_expression", "and_expression", "exclusive_or_expression",
  "inclusive_or_expression", "logical_and_expression",
  "logical_or_expression", "conditional_expression",
  "assignment_expression", "assignment_operator", "expression",
  "constant_expression", "declaration", "declaration_specifiers",
  "declarator_list", "type_qualifier", "storage_class_specifier",
  "modified_type_specifier", "type_specifier", "type_modifier_list",
  "type_modifier", "specifier_qualifier_list", "declarator",
  "direct_declarator", "type_name", "function_declarator", "statement",
  "labeled_statement", "compound_statement", "function_compound_statement",
  "declaration_list", "statement_list", "expr_statement",
  "selection_statement", "iteration_statement", "jump_statement",
  "translation_unit", "function_definition_list", "function_definition", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-126)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     718,  -126,  -126,  -126,  -126,  -126,  -126,  -126,  -126,  -126,
    -126,  -126,  -126,  -126,  -126,  -126,  -126,   -37,   -42,   734,
     734,   734,  -126,   541,  -126,   -40,    63,   718,  -126,     4,
     -40,  -126,  -126,  -126,  -126,  -126,   171,  -126,  -126,  -126,
    -126,  -126,   608,   643,   643,   669,   -16,    13,    24,    84,
     537,    94,    10,    51,    80,    83,  -126,  -126,  -126,  -126,
      86,   625,  -126,  -126,  -126,  -126,  -126,  -126,  -126,   293,
    -126,  -126,   246,    76,   669,  -126,   -46,   -33,   123,    -2,
     124,    96,    87,    89,   156,    -1,  -126,  -126,   -56,  -126,
     108,  -126,  -126,  -126,   232,   354,  -126,  -126,  -126,  -126,
    -126,   625,  -126,   669,  -126,  -126,  -126,  -126,    97,   537,
     669,   669,   669,   125,   564,    98,  -126,  -126,  -126,   -53,
     537,   -43,    16,    16,  -126,   115,  -126,   415,  -126,  -126,
     321,   669,  -126,  -126,  -126,  -126,  -126,  -126,  -126,  -126,
    -126,  -126,  -126,   669,  -126,   669,   669,   669,   669,   669,
     669,   669,   669,   669,   669,   669,   669,   669,   669,   669,
     669,   669,   669,   669,   669,  -126,  -126,   -48,  -126,  -126,
    -126,  -126,   476,  -126,  -126,   116,   537,  -126,    -7,    -6,
       0,   119,   564,  -126,  -126,  -126,  -126,  -126,  -126,   669,
    -126,  -126,     2,  -126,    71,  -126,  -126,  -126,  -126,   -46,
     -46,   -33,   -33,   123,   123,   123,   123,    -2,    -2,   124,
      96,    87,    89,   156,   -45,  -126,   108,  -126,  -126,  -126,
    -126,   537,   537,   537,   669,   443,  -126,  -126,   669,  -126,
     669,  -126,   135,  -126,  -126,    61,   537,    65,  -126,  -126,
     537,   101,  -126,   537,  -126,  -126,  -126
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    87,    88,    89,    90,    91,    95,   101,    96,   102,
     103,   104,    97,    98,    85,    86,    94,     0,     0,    81,
      77,    79,    93,     0,    99,     0,     0,   146,   147,     0,
       0,    82,    78,    80,    92,   100,     0,   150,     1,   148,
     112,   149,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     3,     4,     5,     6,
       2,     0,    22,    23,    24,    25,    26,    27,   132,     0,
     124,     8,    16,    28,     0,    30,    34,    37,    40,    45,
      48,    50,    52,    54,    56,    58,    60,    73,     0,   128,
       0,   130,   113,   114,     0,     0,   115,   116,   117,   118,
       2,     0,    20,     0,    17,    18,    28,    75,     0,     0,
       0,     0,     0,     0,     0,     0,   142,   143,   144,     0,
       0,     0,   108,   106,   111,     0,   122,     0,    12,    13,
       0,     0,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    62,     0,    19,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   133,   110,     0,    83,   109,
     126,   129,     0,   125,   131,     0,     0,   121,     0,     0,
       0,     0,     0,   141,   145,   119,     7,   107,   105,     0,
     123,    10,     0,    14,     0,    61,    31,    32,    33,    35,
      36,    38,    39,    43,    44,    41,    42,    46,    47,    49,
      51,    53,    55,    57,     0,    74,     0,    76,   127,    21,
     120,     0,     0,     0,     0,     0,    29,    11,     0,     9,
       0,    84,   134,   136,   137,     0,     0,     0,    15,    59,
       0,     0,   139,     0,   135,   138,   140
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -126,  -126,  -126,  -126,   -41,  -126,   -62,    -9,     9,  -112,
       5,    29,    26,    32,    52,    50,  -126,   -39,  -125,  -126,
     -30,  -126,   120,    -4,  -126,     1,  -126,   127,   192,  -126,
     196,    27,    20,  -126,   144,   228,   -50,  -126,  -126,   217,
    -126,   -60,  -104,  -126,  -126,  -126,  -126,  -126,   221
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    71,    72,   192,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,   143,
      88,   108,    89,    18,   167,    19,    20,    21,    22,    23,
      24,   124,   168,   169,   125,    25,    91,    92,    93,    37,
      94,    95,    96,    97,    98,    99,    26,    27,    28
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
     113,   102,   104,   105,   106,   193,   107,   152,   153,   127,
     182,   164,   144,   162,   164,    31,    32,    33,   195,   216,
      17,   186,   164,   145,   164,   119,    29,   165,   146,   147,
     184,   121,    90,   106,   172,   217,   230,   148,   149,   215,
     203,   204,   205,   206,    36,   174,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,   221,   222,   177,
     164,   164,   122,    38,   223,   109,   227,   164,    40,   228,
     185,   121,   115,   121,   154,   155,   110,   174,   225,   163,
     178,   179,   180,   196,   197,   198,    42,   111,    43,    44,
      90,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   194,   122,   238,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   174,   122,   122,   241,   220,   226,   164,   243,
     150,   151,   164,   214,   116,   156,   157,   229,   164,   199,
     200,    56,    57,    58,    59,   100,    61,   112,   106,   187,
     188,    62,    63,    64,    65,    66,    67,   114,   142,   201,
     202,   207,   208,   117,   158,   159,   118,   120,   160,   161,
     166,   232,   233,   234,    42,   181,    43,    44,   176,   189,
     219,   183,   224,   240,   245,   210,   242,   209,   123,   106,
     244,   239,   211,   246,   235,   237,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,   213,   212,   171,    34,    45,    46,    47,    35,
      48,    49,    50,    51,    52,    53,    54,    55,   123,    56,
      57,    58,    59,    60,    61,    42,   231,    43,    44,    62,
      63,    64,    65,    66,    67,   175,    30,    41,    39,   123,
     123,   128,   129,     0,    68,    69,    70,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,     0,     0,     0,     0,    45,    46,    47,
       0,    48,    49,    50,    51,    52,    53,    54,    55,     0,
      56,    57,    58,    59,    60,    61,    42,     0,    43,    44,
      62,    63,    64,    65,    66,    67,     0,     0,     0,   130,
       0,   131,     0,     0,     0,    68,    69,   170,     0,     0,
       0,     0,     0,     0,    42,     0,    43,    44,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    45,    46,
      47,     0,    48,    49,    50,    51,    52,    53,    54,    55,
       0,    56,    57,    58,    59,    60,    61,    42,     0,    43,
      44,    62,    63,    64,    65,    66,    67,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    68,    69,   126,    56,
      57,    58,    59,   100,    61,   191,     0,     0,     0,    62,
      63,    64,    65,    66,    67,     0,     0,     0,     0,    45,
      46,    47,     0,    48,    49,    50,    51,    52,    53,    54,
      55,     0,    56,    57,    58,    59,    60,    61,    42,     0,
      43,    44,    62,    63,    64,    65,    66,    67,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    68,    69,   173,
       0,     0,     0,     0,     0,     0,    42,     0,    43,    44,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      45,    46,    47,     0,    48,    49,    50,    51,    52,    53,
      54,    55,     0,    56,    57,    58,    59,    60,    61,    42,
       0,    43,    44,    62,    63,    64,    65,    66,    67,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    68,    69,
     190,    56,    57,    58,    59,   100,    61,   236,     0,     0,
       0,    62,    63,    64,    65,    66,    67,     0,     0,     0,
       0,    45,    46,    47,     0,    48,    49,    50,    51,    52,
      53,    54,    55,     0,    56,    57,    58,    59,    60,    61,
      42,     0,    43,    44,    62,    63,    64,    65,    66,    67,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    68,
      69,   218,     0,     0,     0,     0,     0,    42,     0,    43,
      44,     6,     7,     8,     9,    10,    11,    12,    13,     0,
       0,    16,    45,    46,    47,     0,    48,    49,    50,    51,
      52,    53,    54,    55,     0,    56,    57,    58,    59,    60,
      61,     0,     0,     0,     0,    62,    63,    64,    65,    66,
      67,    42,     0,    43,    44,     0,     0,     0,     0,     0,
      68,    69,    56,    57,    58,    59,   100,    61,    42,     0,
      43,    44,    62,    63,    64,    65,    66,    67,     0,     0,
       0,     0,     0,     0,     0,     0,    42,    68,    43,    44,
       0,     0,     0,     0,     0,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    56,    57,    58,    59,
     100,   101,    42,     0,    43,    44,    62,    63,    64,    65,
      66,    67,     0,    56,    57,    58,    59,   100,    61,     0,
       0,     0,     0,    62,    63,    64,    65,    66,    67,     0,
       0,    56,    57,    58,    59,   100,   103,     0,     0,     0,
       0,    62,    63,    64,    65,    66,    67,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    56,    57,    58,
      59,   100,    61,     0,     0,     0,     0,    62,    63,    64,
      65,    66,    67,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,     0,     0,     0,     0,     0,
      17
};

static const yytype_int16 yycheck[] =
{
      50,    42,    43,    44,    45,   130,    45,     9,    10,    69,
     114,    67,    74,    14,    67,    19,    20,    21,   143,    67,
      62,    64,    67,    69,    67,    55,    63,    83,    74,    75,
      83,    61,    36,    74,    94,    83,    81,    70,    71,   164,
     152,   153,   154,   155,    84,    95,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    64,    64,   109,
      67,    67,    61,     0,    64,    81,    64,    67,    64,    67,
     120,   101,    62,   103,    76,    77,    63,   127,   182,    80,
     110,   111,   112,   145,   146,   147,     3,    63,     5,     6,
      94,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,   131,   101,   228,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   172,   122,   123,    64,   176,   189,    67,    64,
       7,     8,    67,   163,    83,    11,    12,    66,    67,   148,
     149,    58,    59,    60,    61,    62,    63,    63,   189,   122,
     123,    68,    69,    70,    71,    72,    73,    63,    82,   150,
     151,   156,   157,    83,    68,    78,    83,    81,    79,    13,
      62,   221,   222,   223,     3,    50,     5,     6,    81,    64,
      64,    83,    63,    48,    83,   159,   236,   158,    61,   230,
     240,   230,   160,   243,   224,   225,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,   162,   161,    94,    23,    45,    46,    47,    23,
      49,    50,    51,    52,    53,    54,    55,    56,   101,    58,
      59,    60,    61,    62,    63,     3,   216,     5,     6,    68,
      69,    70,    71,    72,    73,   101,    18,    30,    27,   122,
     123,     5,     6,    -1,    83,    84,    85,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    -1,    -1,    -1,    -1,    45,    46,    47,
      -1,    49,    50,    51,    52,    53,    54,    55,    56,    -1,
      58,    59,    60,    61,    62,    63,     3,    -1,     5,     6,
      68,    69,    70,    71,    72,    73,    -1,    -1,    -1,    63,
      -1,    65,    -1,    -1,    -1,    83,    84,    85,    -1,    -1,
      -1,    -1,    -1,    -1,     3,    -1,     5,     6,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    46,
      47,    -1,    49,    50,    51,    52,    53,    54,    55,    56,
      -1,    58,    59,    60,    61,    62,    63,     3,    -1,     5,
       6,    68,    69,    70,    71,    72,    73,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    83,    84,    85,    58,
      59,    60,    61,    62,    63,    64,    -1,    -1,    -1,    68,
      69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,    45,
      46,    47,    -1,    49,    50,    51,    52,    53,    54,    55,
      56,    -1,    58,    59,    60,    61,    62,    63,     3,    -1,
       5,     6,    68,    69,    70,    71,    72,    73,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    84,    85,
      -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,     5,     6,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    46,    47,    -1,    49,    50,    51,    52,    53,    54,
      55,    56,    -1,    58,    59,    60,    61,    62,    63,     3,
      -1,     5,     6,    68,    69,    70,    71,    72,    73,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    84,
      85,    58,    59,    60,    61,    62,    63,    64,    -1,    -1,
      -1,    68,    69,    70,    71,    72,    73,    -1,    -1,    -1,
      -1,    45,    46,    47,    -1,    49,    50,    51,    52,    53,
      54,    55,    56,    -1,    58,    59,    60,    61,    62,    63,
       3,    -1,     5,     6,    68,    69,    70,    71,    72,    73,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,
      84,    85,    -1,    -1,    -1,    -1,    -1,     3,    -1,     5,
       6,    30,    31,    32,    33,    34,    35,    36,    37,    -1,
      -1,    40,    45,    46,    47,    -1,    49,    50,    51,    52,
      53,    54,    55,    56,    -1,    58,    59,    60,    61,    62,
      63,    -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,
      73,     3,    -1,     5,     6,    -1,    -1,    -1,    -1,    -1,
      83,    84,    58,    59,    60,    61,    62,    63,     3,    -1,
       5,     6,    68,    69,    70,    71,    72,    73,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,    83,     5,     6,
      -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    58,    59,    60,    61,
      62,    63,     3,    -1,     5,     6,    68,    69,    70,    71,
      72,    73,    -1,    58,    59,    60,    61,    62,    63,    -1,
      -1,    -1,    -1,    68,    69,    70,    71,    72,    73,    -1,
      -1,    58,    59,    60,    61,    62,    63,    -1,    -1,    -1,
      -1,    68,    69,    70,    71,    72,    73,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,    59,    60,
      61,    62,    63,    -1,    -1,    -1,    -1,    68,    69,    70,
      71,    72,    73,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    -1,    -1,    -1,    -1,    -1,
      62
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    62,   109,   111,
     112,   113,   114,   115,   116,   121,   132,   133,   134,    63,
     121,   109,   109,   109,   114,   116,    84,   125,     0,   134,
      64,   125,     3,     5,     6,    45,    46,    47,    49,    50,
      51,    52,    53,    54,    55,    56,    58,    59,    60,    61,
      62,    63,    68,    69,    70,    71,    72,    73,    83,    84,
      85,    87,    88,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   106,   108,
     109,   122,   123,   124,   126,   127,   128,   129,   130,   131,
      62,    63,    90,    63,    90,    90,    90,   103,   107,    81,
      63,    63,    63,   122,    63,    62,    83,    83,    83,   106,
      81,   106,   111,   113,   117,   120,    85,   127,     5,     6,
      63,    65,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    82,   105,    92,    69,    74,    75,    70,    71,
       7,     8,     9,    10,    76,    77,    11,    12,    68,    78,
      79,    13,    14,    80,    67,    83,    62,   110,   118,   119,
      85,   108,   127,    85,   122,   120,    81,   122,   106,   106,
     106,    50,   128,    83,    83,   122,    64,   117,   117,    64,
      85,    64,    89,   104,   106,   104,    92,    92,    92,    93,
      93,    94,    94,    95,    95,    95,    95,    96,    96,    97,
      98,    99,   100,   101,   106,   104,    67,    83,    85,    64,
     122,    64,    64,    64,    63,   128,    92,    64,    67,    66,
      81,   118,   122,   122,   122,   106,    64,   106,   104,   103,
      48,    64,   122,    64,   122,    83,   122
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    86,    87,    87,    87,    87,    87,    87,    88,    88,
      88,    88,    88,    88,    89,    89,    90,    90,    90,    90,
      90,    90,    91,    91,    91,    91,    91,    91,    92,    92,
      93,    93,    93,    93,    94,    94,    94,    95,    95,    95,
      96,    96,    96,    96,    96,    97,    97,    97,    98,    98,
      99,    99,   100,   100,   101,   101,   102,   102,   103,   103,
     104,   104,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   106,   106,   107,   108,   109,   109,   109,
     109,   109,   109,   110,   110,   111,   111,   112,   112,   112,
     112,   112,   113,   113,   114,   114,   114,   114,   114,   115,
     115,   116,   116,   116,   116,   117,   117,   117,   117,   118,
     119,   120,   121,   122,   122,   122,   122,   122,   122,   123,
     123,   123,   124,   124,   125,   125,   125,   125,   126,   126,
     127,   127,   128,   128,   129,   129,   129,   130,   130,   130,
     130,   131,   131,   131,   131,   131,   132,   133,   133,   134,
     134
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     3,     1,     4,
       3,     4,     2,     2,     1,     3,     1,     2,     2,     2,
       2,     4,     1,     1,     1,     1,     1,     1,     1,     4,
       1,     3,     3,     3,     1,     3,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     5,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     3,     1,     2,     1,
       2,     1,     2,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     2,     1,     2,     1,     1,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     3,
       4,     3,     2,     3,     2,     3,     3,     4,     1,     2,
       1,     2,     1,     2,     5,     7,     5,     5,     7,     6,
       7,     3,     2,     2,     2,     3,     1,     1,     2,     3,
       2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* primary_expression: IDENTIFIER  */
#line 130 "parser.y"
                                                                                    { (yyval.expr) = new_identifier_expr((yyvsp[0].iden)); }
#line 1508 "parser.tab.c"
    break;

  case 3: /* primary_expression: INT_CONSTANT  */
#line 131 "parser.y"
                                                                                    { (yyval.expr) = new_const_int_expr((yyvsp[0].int_value)); }
#line 1514 "parser.tab.c"
    break;

  case 4: /* primary_expression: DOUBLE_CONSTANT  */
#line 132 "parser.y"
                                                                                    { (yyval.expr) = new_const_double_expr((yyvsp[0].double_value)); }
#line 1520 "parser.tab.c"
    break;

  case 5: /* primary_expression: CHAR_CONSTANT  */
#line 133 "parser.y"
                                                                                    { (yyval.expr) = new_const_char_expr((yyvsp[0].char_value)); }
#line 1526 "parser.tab.c"
    break;

  case 6: /* primary_expression: STRING_LITERAL  */
#line 134 "parser.y"
                                                                                    { (yyval.expr) = new_const_string_expr((yyvsp[0].string_value)); }
#line 1532 "parser.tab.c"
    break;

  case 7: /* primary_expression: '(' expression ')'  */
#line 135 "parser.y"
                                                                                    { (yyval.expr) = (yyvsp[-1].expr); }
#line 1538 "parser.tab.c"
    break;

  case 8: /* postfix_expression: primary_expression  */
#line 139 "parser.y"
                                                                                    { (yyval.expr) = (yyvsp[0].expr); }
#line 1544 "parser.tab.c"
    break;

  case 9: /* postfix_expression: postfix_expression '[' expression ']'  */
#line 140 "parser.y"
                                                                                    { (yyval.expr) = new_array_access_expression((yyvsp[-3].expr), (yyvsp[-1].expr)); }
#line 1550 "parser.tab.c"
    break;

  case 10: /* postfix_expression: postfix_expression '(' ')'  */
#line 141 "parser.y"
                                                                                    { (yyval.expr) = new_call_expression((yyvsp[-2].expr), NULL); }
#line 1556 "parser.tab.c"
    break;

  case 11: /* postfix_expression: postfix_expression '(' argument_expression_list ')'  */
#line 142 "parser.y"
                                                                                    { (yyval.expr) = new_call_expression((yyvsp[-3].expr), (yyvsp[-1].expr_list)); }
#line 1562 "parser.tab.c"
    break;

  case 12: /* postfix_expression: postfix_expression INC_OP  */
#line 143 "parser.y"
                                                                                    { (yyval.expr) = new_unary_expression(POSTFIX_INC, (yyvsp[-1].expr)); }
#line 1568 "parser.tab.c"
    break;

  case 13: /* postfix_expression: postfix_expression DEC_OP  */
#line 144 "parser.y"
                                                                                    { (yyval.expr) = new_unary_expression(POSTFIX_DEC, (yyvsp[-1].expr)); }
#line 1574 "parser.tab.c"
    break;

  case 14: /* argument_expression_list: assignment_expression  */
#line 148 "parser.y"
                                                                                    { (yyval.expr_list) = expression_list_append(NULL, (yyvsp[0].expr)); }
#line 1580 "parser.tab.c"
    break;

  case 15: /* argument_expression_list: argument_expression_list ',' assignment_expression  */
#line 149 "parser.y"
                                                                                    { (yyval.expr_list) = expression_list_append((yyvsp[-2].expr_list), (yyvsp[0].expr)); }
#line 1586 "parser.tab.c"
    break;

  case 16: /* unary_expression: postfix_expression  */
#line 153 "parser.y"
                                                                                    { (yyval.expr) = (yyvsp[0].expr); }
#line 1592 "parser.tab.c"
    break;

  case 17: /* unary_expression: INC_OP unary_expression  */
#line 154 "parser.y"
                                                                                    { (yyval.expr) = new_unary_expression(PREFIX_INC, (yyvsp[0].expr)); }
#line 1598 "parser.tab.c"
    break;

  case 18: /* unary_expression: DEC_OP unary_expression  */
#line 155 "parser.y"
                                                                                    { (yyval.expr) = new_unary_expression(PREFIX_DEC, (yyvsp[0].expr)); }
#line 1604 "parser.tab.c"
    break;

  case 19: /* unary_expression: unary_operator cast_expression  */
#line 156 "parser.y"
                                                                                    { (yyval.expr) = new_unary_expression((yyvsp[-1].unary_op), (yyvsp[0].expr)); }
#line 1610 "parser.tab.c"
    break;

  case 20: /* unary_expression: SIZEOF unary_expression  */
#line 157 "parser.y"
                                                                                    { (yyval.expr) = new_sizeof_expr_expression((yyvsp[0].expr)); }
#line 1616 "parser.tab.c"
    break;

  case 21: /* unary_expression: SIZEOF '(' type_name ')'  */
#line 158 "parser.y"
                                                                                    { (yyval.expr) = new_sizeof_type_expression((yyvsp[-1].type)); }
#line 1622 "parser.tab.c"
    break;

  case 22: /* unary_operator: '&'  */
#line 162 "parser.y"
                                                                                    { (yyval.unary_op) = REF; }
#line 1628 "parser.tab.c"
    break;

  case 23: /* unary_operator: '*'  */
#line 163 "parser.y"
                                                                                    { (yyval.unary_op) = DEREF; }
#line 1634 "parser.tab.c"
    break;

  case 24: /* unary_operator: '+'  */
#line 164 "parser.y"
                                                                                    { (yyval.unary_op) = UNARY_PLUS; }
#line 1640 "parser.tab.c"
    break;

  case 25: /* unary_operator: '-'  */
#line 165 "parser.y"
                                                                                    { (yyval.unary_op) = UNARY_MINUS; }
#line 1646 "parser.tab.c"
    break;

  case 26: /* unary_operator: '~'  */
#line 166 "parser.y"
                                                                                    { (yyval.unary_op) = B_ONE_COMPLEMENT; }
#line 1652 "parser.tab.c"
    break;

  case 27: /* unary_operator: '!'  */
#line 167 "parser.y"
                                                                                    { (yyval.unary_op) = L_NOT; }
#line 1658 "parser.tab.c"
    break;

  case 28: /* cast_expression: unary_expression  */
#line 171 "parser.y"
                                                                                    { (yyval.expr) = (yyvsp[0].expr); }
#line 1664 "parser.tab.c"
    break;

  case 29: /* cast_expression: '(' type_name ')' cast_expression  */
#line 172 "parser.y"
                                                                                    { (yyval.expr) = new_cast_expression((yyvsp[-2].type), (yyvsp[0].expr)); }
#line 1670 "parser.tab.c"
    break;

  case 30: /* multiplicative_expression: cast_expression  */
#line 176 "parser.y"
                                                                                    { (yyval.expr) = (yyvsp[0].expr); }
#line 1676 "parser.tab.c"
    break;

  case 31: /* multiplicative_expression: multiplicative_expression '*' cast_expression  */
#line 177 "parser.y"
                                                                                    { (yyval.expr) = new_binary_expression(MULT, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1682 "parser.tab.c"
    break;

  case 32: /* multiplicative_expression: multiplicative_expression '/' cast_expression  */
#line 178 "parser.y"
                                                                                    { (yyval.expr) = new_binary_expression(DIV, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1688 "parser.tab.c"
    break;

  case 33: /* multiplicative_expression: multiplicative_expression '%' cast_expression  */
#line 179 "parser.y"
                                                                                    { (yyval.expr) = new_binary_expression(MOD, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1694 "parser.tab.c"
    break;

  case 34: /* additive_expression: multiplicative_expression  */
#line 183 "parser.y"
                                                                                    { (yyval.expr) = (yyvsp[0].expr); }
#line 1700 "parser.tab.c"
    break;

  case 35: /* additive_expression: additive_expression '+' multiplicative_expression  */
#line 184 "parser.y"
                                                                                    { (yyval.expr) = new_binary_expression(PLUS, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1706 "parser.tab.c"
    break;

  case 36: /* additive_expression: additive_expression '-' multiplicative_expression  */
#line 185 "parser.y"
                                                                                    { (yyval.expr) = new_binary_expression(MINUS, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1712 "parser.tab.c"
    break;

  case 37: /* shift_expression: additive_expression  */
#line 189 "parser.y"
                                                                                    { (yyval.expr) = (yyvsp[0].expr); }
#line 1718 "parser.tab.c"
    break;

  case 38: /* shift_expression: shift_expression LEFT_OP additive_expression  */
#line 190 "parser.y"
                                                                                    { (yyval.expr) = new_binary_expression(SHIFT_L, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1724 "parser.tab.c"
    break;

  case 39: /* shift_expression: shift_expression RIGHT_OP additive_expression  */
#line 191 "parser.y"
                                                                                    { (yyval.expr) = new_binary_expression(SHIFT_R, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1730 "parser.tab.c"
    break;

  case 40: /* relational_expression: shift_expression  */
#line 195 "parser.y"
                                                                                    { (yyval.expr) = (yyvsp[0].expr); }
#line 1736 "parser.tab.c"
    break;

  case 41: /* relational_expression: relational_expression '<' shift_expression  */
#line 196 "parser.y"
                                                                                    { (yyval.expr) = new_binary_expression(LESS, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1742 "parser.tab.c"
    break;

  case 42: /* relational_expression: relational_expression '>' shift_expression  */
#line 197 "parser.y"
                                                                                    { (yyval.expr) = new_binary_expression(GREATER, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1748 "parser.tab.c"
    break;

  case 43: /* relational_expression: relational_expression LE_OP shift_expression  */
#line 198 "parser.y"
                                                                                    { (yyval.expr) = new_binary_expression(LESS_EQUAL, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1754 "parser.tab.c"
    break;

  case 44: /* relational_expression: relational_expression GE_OP shift_expression  */
#line 199 "parser.y"
                                                                                    { (yyval.expr) = new_binary_expression(GREATER_EQUAL, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1760 "parser.tab.c"
    break;

  case 45: /* equality_expression: relational_expression  */
#line 203 "parser.y"
                                                                                    { (yyval.expr) = (yyvsp[0].expr); }
#line 1766 "parser.tab.c"
    break;

  case 46: /* equality_expression: equality_expression EQ_OP relational_expression  */
#line 204 "parser.y"
                                                                                    { (yyval.expr) = new_binary_expression(EQUAL, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1772 "parser.tab.c"
    break;

  case 47: /* equality_expression: equality_expression NE_OP relational_expression  */
#line 205 "parser.y"
                                                                                    { (yyval.expr) = new_binary_expression(NOT_EQUAL, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1778 "parser.tab.c"
    break;

  case 48: /* and_expression: equality_expression  */
#line 209 "parser.y"
                                                                                    { (yyval.expr) = (yyvsp[0].expr); }
#line 1784 "parser.tab.c"
    break;

  case 49: /* and_expression: and_expression '&' equality_expression  */
#line 210 "parser.y"
                                                                                    { (yyval.expr) = new_binary_expression(B_AND, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1790 "parser.tab.c"
    break;

  case 50: /* exclusive_or_expression: and_expression  */
#line 214 "parser.y"
                                                                                    { (yyval.expr) = (yyvsp[0].expr); }
#line 1796 "parser.tab.c"
    break;

  case 51: /* exclusive_or_expression: exclusive_or_expression '^' and_expression  */
#line 215 "parser.y"
                                                                                    { (yyval.expr) = new_binary_expression(B_XOR, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1802 "parser.tab.c"
    break;

  case 52: /* inclusive_or_expression: exclusive_or_expression  */
#line 219 "parser.y"
                                                                                    { (yyval.expr) = (yyvsp[0].expr); }
#line 1808 "parser.tab.c"
    break;

  case 53: /* inclusive_or_expression: inclusive_or_expression '|' exclusive_or_expression  */
#line 220 "parser.y"
                                                                                    { (yyval.expr) = new_binary_expression(B_OR, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1814 "parser.tab.c"
    break;

  case 54: /* logical_and_expression: inclusive_or_expression  */
#line 224 "parser.y"
                                                                                    { (yyval.expr) = (yyvsp[0].expr); }
#line 1820 "parser.tab.c"
    break;

  case 55: /* logical_and_expression: logical_and_expression AND_OP inclusive_or_expression  */
#line 225 "parser.y"
                                                                                    { (yyval.expr) = new_binary_expression(L_AND, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1826 "parser.tab.c"
    break;

  case 56: /* logical_or_expression: logical_and_expression  */
#line 229 "parser.y"
                                                                                    { (yyval.expr) = (yyvsp[0].expr); }
#line 1832 "parser.tab.c"
    break;

  case 57: /* logical_or_expression: logical_or_expression OR_OP logical_and_expression  */
#line 230 "parser.y"
                                                                                    { (yyval.expr) = new_binary_expression(L_OR, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1838 "parser.tab.c"
    break;

  case 58: /* conditional_expression: logical_or_expression  */
#line 234 "parser.y"
                                                                                    { (yyval.expr) = (yyvsp[0].expr); }
#line 1844 "parser.tab.c"
    break;

  case 59: /* conditional_expression: logical_or_expression '?' expression ':' conditional_expression  */
#line 235 "parser.y"
                                                                                    { (yyval.expr) = new_ternary_expression((yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1850 "parser.tab.c"
    break;

  case 60: /* assignment_expression: conditional_expression  */
#line 239 "parser.y"
                                                                                    { (yyval.expr) = (yyvsp[0].expr); }
#line 1856 "parser.tab.c"
    break;

  case 61: /* assignment_expression: unary_expression assignment_operator assignment_expression  */
#line 240 "parser.y"
                                                                                    { (yyval.expr) = new_assignment_expression((yyvsp[-1].binary_op), (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1862 "parser.tab.c"
    break;

  case 62: /* assignment_operator: '='  */
#line 244 "parser.y"
                                                                                    { (yyval.binary_op) = ASSIGNMENT; }
#line 1868 "parser.tab.c"
    break;

  case 63: /* assignment_operator: MUL_ASSIGN  */
#line 245 "parser.y"
                                                                                    { (yyval.binary_op) = MULT; }
#line 1874 "parser.tab.c"
    break;

  case 64: /* assignment_operator: DIV_ASSIGN  */
#line 246 "parser.y"
                                                                                    { (yyval.binary_op) = DIV; }
#line 1880 "parser.tab.c"
    break;

  case 65: /* assignment_operator: MOD_ASSIGN  */
#line 247 "parser.y"
                                                                                    { (yyval.binary_op) = MOD; }
#line 1886 "parser.tab.c"
    break;

  case 66: /* assignment_operator: ADD_ASSIGN  */
#line 248 "parser.y"
                                                                                    { (yyval.binary_op) = PLUS; }
#line 1892 "parser.tab.c"
    break;

  case 67: /* assignment_operator: SUB_ASSIGN  */
#line 249 "parser.y"
                                                                                    { (yyval.binary_op) = MINUS; }
#line 1898 "parser.tab.c"
    break;

  case 68: /* assignment_operator: LEFT_ASSIGN  */
#line 250 "parser.y"
                                                                                    { (yyval.binary_op) = SHIFT_L; }
#line 1904 "parser.tab.c"
    break;

  case 69: /* assignment_operator: RIGHT_ASSIGN  */
#line 251 "parser.y"
                                                                                    { (yyval.binary_op) = SHIFT_R; }
#line 1910 "parser.tab.c"
    break;

  case 70: /* assignment_operator: AND_ASSIGN  */
#line 252 "parser.y"
                                                                                    { (yyval.binary_op) = B_AND; }
#line 1916 "parser.tab.c"
    break;

  case 71: /* assignment_operator: XOR_ASSIGN  */
#line 253 "parser.y"
                                                                                    { (yyval.binary_op) = B_XOR; }
#line 1922 "parser.tab.c"
    break;

  case 72: /* assignment_operator: OR_ASSIGN  */
#line 254 "parser.y"
                                                                                    { (yyval.binary_op) = B_OR; }
#line 1928 "parser.tab.c"
    break;

  case 73: /* expression: assignment_expression  */
#line 258 "parser.y"
                                                                                    { (yyval.expr) = (yyvsp[0].expr); }
#line 1934 "parser.tab.c"
    break;

  case 74: /* expression: expression ',' assignment_expression  */
#line 259 "parser.y"
                                                                                    { (yyval.expr) = new_binary_expression(CONCAT, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1940 "parser.tab.c"
    break;

  case 75: /* constant_expression: conditional_expression  */
#line 263 "parser.y"
                                                                                    { (yyval.expr) = (yyvsp[0].expr); }
#line 1946 "parser.tab.c"
    break;

  case 76: /* declaration: declaration_specifiers declarator_list ';'  */
#line 267 "parser.y"
                                                                                    { (yyval.table) = new_symbol_table_from_decl_list((yyvsp[-2].type), (yyvsp[-1].decl_list)); }
#line 1952 "parser.tab.c"
    break;

  case 77: /* declaration_specifiers: storage_class_specifier  */
#line 271 "parser.y"
                                                                                    { (yyval.type) = add_qualifier_or_specifier(new_empty_type(), (yyvsp[0].uint_value)); }
#line 1958 "parser.tab.c"
    break;

  case 78: /* declaration_specifiers: storage_class_specifier declaration_specifiers  */
#line 272 "parser.y"
                                                                                    { (yyval.type) = add_qualifier_or_specifier((yyvsp[0].type), (yyvsp[-1].uint_value)); }
#line 1964 "parser.tab.c"
    break;

  case 79: /* declaration_specifiers: modified_type_specifier  */
#line 273 "parser.y"
                                                                                    { (yyval.type) = (yyvsp[0].type); }
#line 1970 "parser.tab.c"
    break;

  case 80: /* declaration_specifiers: modified_type_specifier declaration_specifiers  */
#line 274 "parser.y"
                                                                                    { (yyval.type) = copy_to_type_from_type((yyvsp[-1].type), (yyvsp[0].type)); }
#line 1976 "parser.tab.c"
    break;

  case 81: /* declaration_specifiers: type_qualifier  */
#line 275 "parser.y"
                                                                                    { (yyval.type) = add_qualifier_or_specifier(new_empty_type(), (yyvsp[0].uint_value)); }
#line 1982 "parser.tab.c"
    break;

  case 82: /* declaration_specifiers: type_qualifier declaration_specifiers  */
#line 276 "parser.y"
                                                                                    { (yyval.type) = add_qualifier_or_specifier((yyvsp[0].type), (yyvsp[-1].uint_value)); }
#line 1988 "parser.tab.c"
    break;

  case 83: /* declarator_list: declarator  */
#line 280 "parser.y"
                                                                                    { (yyval.decl_list) = decl_list_append(NULL, (yyvsp[0].decl)); }
#line 1994 "parser.tab.c"
    break;

  case 84: /* declarator_list: declarator_list ',' declarator  */
#line 281 "parser.y"
                                                                                    { (yyval.decl_list) = decl_list_append((yyvsp[-2].decl_list), (yyvsp[0].decl)); }
#line 2000 "parser.tab.c"
    break;

  case 85: /* type_qualifier: CONST  */
#line 285 "parser.y"
                                                                                    { (yyval.uint_value) = 64; }
#line 2006 "parser.tab.c"
    break;

  case 86: /* type_qualifier: VOLATILE  */
#line 286 "parser.y"
                                                                                    { (yyval.uint_value) = 32; }
#line 2012 "parser.tab.c"
    break;

  case 87: /* storage_class_specifier: TYPEDEF  */
#line 290 "parser.y"
                                                                                    { (yyval.uint_value) = 16; }
#line 2018 "parser.tab.c"
    break;

  case 88: /* storage_class_specifier: EXTERN  */
#line 291 "parser.y"
                                                                                    { (yyval.uint_value) = 8; }
#line 2024 "parser.tab.c"
    break;

  case 89: /* storage_class_specifier: STATIC  */
#line 292 "parser.y"
                                                                                    { (yyval.uint_value) = 4; }
#line 2030 "parser.tab.c"
    break;

  case 90: /* storage_class_specifier: AUTO  */
#line 293 "parser.y"
                                                                                    { (yyval.uint_value) = 2; }
#line 2036 "parser.tab.c"
    break;

  case 91: /* storage_class_specifier: REGISTER  */
#line 294 "parser.y"
                                                                                    { (yyval.uint_value) = 1; }
#line 2042 "parser.tab.c"
    break;

  case 92: /* modified_type_specifier: type_modifier_list type_specifier  */
#line 298 "parser.y"
                                                                                    { (yyval.type) = add_modifier((yyvsp[0].type), (yyvsp[-1].uint_value)); }
#line 2048 "parser.tab.c"
    break;

  case 93: /* modified_type_specifier: type_specifier  */
#line 299 "parser.y"
                                                                                    { (yyval.type) = (yyvsp[0].type); }
#line 2054 "parser.tab.c"
    break;

  case 94: /* type_specifier: VOID  */
#line 303 "parser.y"
                                                                                    { (yyval.type) = new_type(PRIM_VOID); }
#line 2060 "parser.tab.c"
    break;

  case 95: /* type_specifier: CHAR  */
#line 304 "parser.y"
                                                                                    { (yyval.type) = new_type(PRIM_CHAR); }
#line 2066 "parser.tab.c"
    break;

  case 96: /* type_specifier: INT  */
#line 305 "parser.y"
                                                                                    { (yyval.type) = new_type(PRIM_INT); }
#line 2072 "parser.tab.c"
    break;

  case 97: /* type_specifier: FLOAT  */
#line 306 "parser.y"
                                                                                    { (yyval.type) = new_type(PRIM_DOUBLE); }
#line 2078 "parser.tab.c"
    break;

  case 98: /* type_specifier: DOUBLE  */
#line 307 "parser.y"
                                                                                    { (yyval.type) = new_type(PRIM_DOUBLE); }
#line 2084 "parser.tab.c"
    break;

  case 99: /* type_modifier_list: type_modifier  */
#line 311 "parser.y"
                                                                                    { (yyval.uint_value) = (yyvsp[0].uint_value); }
#line 2090 "parser.tab.c"
    break;

  case 100: /* type_modifier_list: type_modifier_list type_modifier  */
#line 312 "parser.y"
                                                                                    { (yyval.uint_value) = (yyvsp[-1].uint_value) | (yyvsp[0].uint_value); }
#line 2096 "parser.tab.c"
    break;

  case 101: /* type_modifier: SHORT  */
#line 316 "parser.y"
                                                                                    { (yyval.uint_value) = 8; }
#line 2102 "parser.tab.c"
    break;

  case 102: /* type_modifier: LONG  */
#line 317 "parser.y"
                                                                                    { (yyval.uint_value) = 4; }
#line 2108 "parser.tab.c"
    break;

  case 103: /* type_modifier: SIGNED  */
#line 318 "parser.y"
                                                                                    { (yyval.uint_value) = 2; }
#line 2114 "parser.tab.c"
    break;

  case 104: /* type_modifier: UNSIGNED  */
#line 319 "parser.y"
                                                                                    { (yyval.uint_value) = 1; }
#line 2120 "parser.tab.c"
    break;

  case 105: /* specifier_qualifier_list: modified_type_specifier specifier_qualifier_list  */
#line 323 "parser.y"
                                                                                    { (yyval.type) = copy_to_type_from_type((yyvsp[-1].type), (yyvsp[0].type)); }
#line 2126 "parser.tab.c"
    break;

  case 106: /* specifier_qualifier_list: modified_type_specifier  */
#line 324 "parser.y"
                                                                                    { (yyval.type) = (yyvsp[0].type); }
#line 2132 "parser.tab.c"
    break;

  case 107: /* specifier_qualifier_list: type_qualifier specifier_qualifier_list  */
#line 325 "parser.y"
                                                                                    { (yyval.type) = add_qualifier_or_specifier((yyvsp[0].type), (yyvsp[-1].uint_value)); }
#line 2138 "parser.tab.c"
    break;

  case 108: /* specifier_qualifier_list: type_qualifier  */
#line 326 "parser.y"
                                                                                    { (yyval.type) = add_qualifier_or_specifier(new_empty_type(), (yyvsp[0].uint_value)); }
#line 2144 "parser.tab.c"
    break;

  case 109: /* declarator: direct_declarator  */
#line 330 "parser.y"
                                                                                    { (yyval.decl) = (yyvsp[0].decl); }
#line 2150 "parser.tab.c"
    break;

  case 110: /* direct_declarator: IDENTIFIER  */
#line 334 "parser.y"
                                                                                    { (yyval.decl) = new_identifier_declarator((yyvsp[0].iden)); }
#line 2156 "parser.tab.c"
    break;

  case 111: /* type_name: specifier_qualifier_list  */
#line 338 "parser.y"
                                                                                    { (yyval.type) = (yyvsp[0].type); }
#line 2162 "parser.tab.c"
    break;

  case 112: /* function_declarator: IDENTIFIER '(' ')'  */
#line 342 "parser.y"
                                                                                    { (yyval.decl) = new_function_declarator((yyvsp[-2].iden)); }
#line 2168 "parser.tab.c"
    break;

  case 113: /* statement: labeled_statement  */
#line 346 "parser.y"
                                                                                    { (yyval.stat) = (yyvsp[0].stat); }
#line 2174 "parser.tab.c"
    break;

  case 114: /* statement: compound_statement  */
#line 347 "parser.y"
                                                                                    { (yyval.stat) = (yyvsp[0].stat); }
#line 2180 "parser.tab.c"
    break;

  case 115: /* statement: expr_statement  */
#line 348 "parser.y"
                                                                                    { (yyval.stat) = (yyvsp[0].stat); }
#line 2186 "parser.tab.c"
    break;

  case 116: /* statement: selection_statement  */
#line 349 "parser.y"
                                                                                    { (yyval.stat) = (yyvsp[0].stat); }
#line 2192 "parser.tab.c"
    break;

  case 117: /* statement: iteration_statement  */
#line 350 "parser.y"
                                                                                    { (yyval.stat) = (yyvsp[0].stat); }
#line 2198 "parser.tab.c"
    break;

  case 118: /* statement: jump_statement  */
#line 351 "parser.y"
                                                                                    { (yyval.stat) = (yyvsp[0].stat); }
#line 2204 "parser.tab.c"
    break;

  case 119: /* labeled_statement: IDENTIFIER ':' statement  */
#line 355 "parser.y"
                                                                                    { (yyval.stat) = new_labeled_statement((yyvsp[-2].iden), NULL, (yyvsp[0].stat)); }
#line 2210 "parser.tab.c"
    break;

  case 120: /* labeled_statement: CASE constant_expression ':' statement  */
#line 356 "parser.y"
                                                                                    { (yyval.stat) = new_labeled_statement(NULL, (yyvsp[-2].expr), (yyvsp[0].stat)); }
#line 2216 "parser.tab.c"
    break;

  case 121: /* labeled_statement: DEFAULT ':' statement  */
#line 357 "parser.y"
                                                                                    { (yyval.stat) = new_labeled_statement(NULL, NULL, (yyvsp[0].stat)); }
#line 2222 "parser.tab.c"
    break;

  case 122: /* compound_statement: '{' '}'  */
#line 361 "parser.y"
                                                                                    { (yyval.stat) = NULL; }
#line 2228 "parser.tab.c"
    break;

  case 123: /* compound_statement: '{' statement_list '}'  */
#line 362 "parser.y"
                                                                                    { (yyval.stat) = new_compound_statement((yyvsp[-1].stat_list)); }
#line 2234 "parser.tab.c"
    break;

  case 124: /* function_compound_statement: '{' '}'  */
#line 366 "parser.y"
                                                                                    { (yyval.decl_func) = new_decl_func(NULL, NULL); }
#line 2240 "parser.tab.c"
    break;

  case 125: /* function_compound_statement: '{' statement_list '}'  */
#line 367 "parser.y"
                                                                                    { (yyval.decl_func) = new_decl_func(NULL, new_compound_statement((yyvsp[-1].stat_list))); }
#line 2246 "parser.tab.c"
    break;

  case 126: /* function_compound_statement: '{' declaration_list '}'  */
#line 368 "parser.y"
                                                                                    { (yyval.decl_func) = new_decl_func((yyvsp[-1].table), NULL); }
#line 2252 "parser.tab.c"
    break;

  case 127: /* function_compound_statement: '{' declaration_list statement_list '}'  */
#line 369 "parser.y"
                                                                                    { (yyval.decl_func) = new_decl_func((yyvsp[-2].table), new_compound_statement((yyvsp[-1].stat_list))); }
#line 2258 "parser.tab.c"
    break;

  case 128: /* declaration_list: declaration  */
#line 373 "parser.y"
                                                                                    { (yyval.table) = symbol_table_append_end(NULL, (yyvsp[0].table)); }
#line 2264 "parser.tab.c"
    break;

  case 129: /* declaration_list: declaration_list declaration  */
#line 374 "parser.y"
                                                                                    { (yyval.table) = symbol_table_append_end((yyvsp[-1].table), (yyvsp[0].table)); }
#line 2270 "parser.tab.c"
    break;

  case 130: /* statement_list: statement  */
#line 378 "parser.y"
                                                                                    { (yyval.stat_list) = statement_list_append(NULL, (yyvsp[0].stat)); }
#line 2276 "parser.tab.c"
    break;

  case 131: /* statement_list: statement_list statement  */
#line 379 "parser.y"
                                                                                    { (yyval.stat_list) = statement_list_append((yyvsp[-1].stat_list), (yyvsp[0].stat)); }
#line 2282 "parser.tab.c"
    break;

  case 132: /* expr_statement: ';'  */
#line 383 "parser.y"
                                                                                    { (yyval.stat) = NULL; }
#line 2288 "parser.tab.c"
    break;

  case 133: /* expr_statement: expression ';'  */
#line 384 "parser.y"
                                                                                    { (yyval.stat) = new_expression_statement((yyvsp[-1].expr)); }
#line 2294 "parser.tab.c"
    break;

  case 134: /* selection_statement: IF '(' expression ')' statement  */
#line 388 "parser.y"
                                                                                    { (yyval.stat) = new_if_statement((yyvsp[-2].expr), (yyvsp[0].stat)); }
#line 2300 "parser.tab.c"
    break;

  case 135: /* selection_statement: IF '(' expression ')' statement ELSE statement  */
#line 389 "parser.y"
                                                                                    { (yyval.stat) = new_if_else_statement((yyvsp[-4].expr), (yyvsp[-2].stat), (yyvsp[0].stat)); }
#line 2306 "parser.tab.c"
    break;

  case 136: /* selection_statement: SWITCH '(' expression ')' statement  */
#line 390 "parser.y"
                                                                                    { (yyval.stat) = new_switch_statement((yyvsp[-2].expr), (yyvsp[0].stat)); }
#line 2312 "parser.tab.c"
    break;

  case 137: /* iteration_statement: WHILE '(' expression ')' statement  */
#line 394 "parser.y"
                                                                                    { (yyval.stat) = new_while_statement((yyvsp[-2].expr), (yyvsp[0].stat)); }
#line 2318 "parser.tab.c"
    break;

  case 138: /* iteration_statement: DO statement WHILE '(' expression ')' ';'  */
#line 395 "parser.y"
                                                                                    { (yyval.stat) = new_do_while_statement((yyvsp[-5].stat), (yyvsp[-2].expr)); }
#line 2324 "parser.tab.c"
    break;

  case 139: /* iteration_statement: FOR '(' expr_statement expr_statement ')' statement  */
#line 396 "parser.y"
                                                                                    { (yyval.stat) = new_for_statement((yyvsp[-3].stat), (yyvsp[-2].stat), NULL, (yyvsp[0].stat)); }
#line 2330 "parser.tab.c"
    break;

  case 140: /* iteration_statement: FOR '(' expr_statement expr_statement expression ')' statement  */
#line 397 "parser.y"
                                                                                    { (yyval.stat) = new_for_statement((yyvsp[-4].stat), (yyvsp[-3].stat), (yyvsp[-2].expr), (yyvsp[0].stat)); }
#line 2336 "parser.tab.c"
    break;

  case 141: /* jump_statement: GOTO IDENTIFIER ';'  */
#line 401 "parser.y"
                                                                                    { (yyval.stat) = new_jump_statement(STAT_GOTO, (yyvsp[-1].iden)); }
#line 2342 "parser.tab.c"
    break;

  case 142: /* jump_statement: CONTINUE ';'  */
#line 402 "parser.y"
                                                                                    { (yyval.stat) = new_jump_statement(STAT_CONTINUE, NULL); }
#line 2348 "parser.tab.c"
    break;

  case 143: /* jump_statement: BREAK ';'  */
#line 403 "parser.y"
                                                                                    { (yyval.stat) = new_jump_statement(STAT_BREAK, NULL); }
#line 2354 "parser.tab.c"
    break;

  case 144: /* jump_statement: RETURN ';'  */
#line 404 "parser.y"
                                                                                    { (yyval.stat) = new_jump_statement(STAT_RETURN, NULL); }
#line 2360 "parser.tab.c"
    break;

  case 145: /* jump_statement: RETURN expression ';'  */
#line 405 "parser.y"
                                                                                    { (yyval.stat) = new_jump_statement(STAT_RETURN_EXPR, (yyvsp[-1].expr)); }
#line 2366 "parser.tab.c"
    break;

  case 146: /* translation_unit: function_definition_list  */
#line 409 "parser.y"
                                                                                    { tree = new_ast((yyvsp[0].func_list)); }
#line 2372 "parser.tab.c"
    break;

  case 147: /* function_definition_list: function_definition  */
#line 413 "parser.y"
                                                                                    { (yyval.func_list) = func_list_append(NULL, (yyvsp[0].func)); }
#line 2378 "parser.tab.c"
    break;

  case 148: /* function_definition_list: function_definition_list function_definition  */
#line 414 "parser.y"
                                                                                    { (yyval.func_list) = func_list_append((yyvsp[-1].func_list), (yyvsp[0].func)); }
#line 2384 "parser.tab.c"
    break;

  case 149: /* function_definition: declaration_specifiers function_declarator function_compound_statement  */
#line 418 "parser.y"
                                                                                    { (yyval.func) = new_func((yyvsp[-2].type), (yyvsp[-1].decl), (yyvsp[0].decl_func)); }
#line 2390 "parser.tab.c"
    break;

  case 150: /* function_definition: function_declarator function_compound_statement  */
#line 419 "parser.y"
                                                                                    { (yyval.func) = new_func(NULL, (yyvsp[-1].decl), (yyvsp[0].decl_func)); }
#line 2396 "parser.tab.c"
    break;


#line 2400 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 423 "parser.y"


#include <stdio.h>

extern char yytext[];
extern int column;

void yyerror(char *s)
{
	// Deactivating the body of this function as the output for pointing out
	// that an error occured gets handled in main instead, as for A1 we are
	// only interested in whether or not an error occured but not where it is
	// located in the source code.
	
	// fflush(stdout);
	// printf("\n%*s\n%*s\n", column, "^", column, s);
}
