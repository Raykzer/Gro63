/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "../ccl-master/parser.y" /* yacc.c:339  */


////////////////////////////////////////////////////////////////////////////
//
//   ccli : The Computation and Control Language Tools
//   -------------------------------------------------
//
//   Copyright (c) 2003 Eric Klavins, California Institute of Technology
//   For more information, email klavins@caltech.edu
//
//   This program is free software; you can redistribute it and/or
//   modify it under the terms of the GNU General Public License
//   as published by the Free Software Foundation; either version 2
//   of the License, or (at your option) any later version.
// 
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program; if not, write to the Free Software
//   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
//

#include <unistd.h>
//#include <dlfcn.h>
#include <stdio.h>
#include <sstream>
//#include "/usr/include/c++/4.2.1/sstream"
#include <string.h>
#include <list>
#include <string>
#include "Expr.h"
#include "Program.h"
#include "parser.h"
#include "Type.h"

#define NL printf ( "\n" )

// for g++ compatibility 
extern int yyparse ( void );
extern int yylex ( void );
extern int yyerror ( char * s );
extern void yyrestart ( FILE * new_file );

extern int lineNum[MAX_INCLUDE_DEPTH+1];
extern int include_stack_ptr;
extern char * current_file_name[MAX_INCLUDE_DEPTH+1];

// for lists
Value int_list_el = Value ( 0 );
Value empty ( &int_list_el );

#define EMPTY new Expr ( new Value ( new std::list<Value *> ) )
#define UC { printf ( "under construction\n" ); $$ = NULL; }

// for lambdas and recursions
Environment * main_env = NULL;

#define PUSH(__str__) {                                               \
    main_env = new Environment ( __str__, new TypeExpr(), main_env );  \
} 

#define PUSH_WITH_TYPE(__str__,__type__) {                            \
  main_env = new Environment ( __str__, __type__, main_env );         \
} 

#define POP {                                                         \
  if ( !main_env->is_freed() ) {                                      \
    delete main_env->get_type();                                      \
    main_env->set_freed ( true );				      \
  } \
  Environment * temp = main_env;                                      \
  main_env = main_env->get_tail();                                    \
  delete temp;                                                        \
}

#define POP_SIMP {                                                    \
  Environment * temp = main_env;                                      \
  main_env = main_env->get_tail();                                    \
  delete temp;                                                        \
}

#define ERROR(__msg__...) {                                             \
                                                                        \
    std::stringstream strm;                                             \
                                                                        \
     strm << "gro encountered an error in "                             \
       << current_file_name[include_stack_ptr]                          \
       << " on line " << lineNum[include_stack_ptr]                     \
       << ".<blockquote>" << __msg__ << "</blockquote>";                \
                                                                        \
     throw strm.str();                                                  \
                                                                        \
}

#define TYPE_ERROR(__msg__...) {                                        \
                                                                        \
    std::stringstream strm;                                             \
                                                                        \
     strm << "Type error in "                                           \
       << current_file_name[include_stack_ptr]                          \
       << " on line " << lineNum[include_stack_ptr]                     \
       << ".<blockquote>" << __msg__ << "</blockquote>";                \
                                                                        \
     throw strm.str();                                                  \
                                                                        \
}

#define TYPE_ERROR1(__e__,__t__,__msg__...) {                                         \
                                                                                      \
    std::stringstream strm;                                                           \
                                                                                      \
    strm << "Type error in "                                                          \
         << current_file_name[include_stack_ptr]              \
         << " on line " << lineNum[include_stack_ptr]                                                \
         << "<br><blockquote>" << __msg__ << " Here, "                                \
         << "<i>" << __e__->tostring() << "</i> has type <i>" << __t__->tostring()    \
         << ".</i></blockquote>";                                                     \
                                                                                      \
         throw strm.str();                                                            \
                                                                                      \
}

#define TYPE_ERROR2(__e1__,__t1__,__e2__,__t2__,__msg__...) {                         \
                                                                                      \
    std::stringstream strm;                                                           \
                                                                                      \
    strm << "Type error in "                                                          \
         <<  current_file_name[include_stack_ptr]              \
         << " on line " << lineNum[include_stack_ptr]                                                \
         << "<br><blockquote>" << __msg__ << " In particular, "                       \
         << "<i>" << __e1__->tostring() << "</i> has type <i>" << __t1__->tostring() << "</i>, while " \
         << "<i>" << __e2__->tostring() << "</i> has type <i>" << __t2__->tostring() << ".</i>"        \
         << "</blockquote>";                                                          \
                                                                                      \
         throw strm.str();                                                            \
                                                                                      \
}

#define SET_INFO(__e__) { __e__->set_line_info ( lineNum[include_stack_ptr], current_file_name[include_stack_ptr] ); }

#define DBG {                                             \
    printf ( "Debug statement: reached %s, line %d\n",    \
                    __FILE__, __LINE__);                  \
    fflush ( stdout );                                    \
}

#define VERBOOSE printf ( ">> line %d of %s\n", lineNum[include_stack_ptr], current_file_name[include_stack_ptr] );
#define VERBOSE

// main scope 
Scope * top_scope;

// for computing types of locals in programs
std::list<TypeExpr *> program_garbage;

TypeExpr * fun_temp;

// auxilliary flags for external fuction type construction
bool rec_extensible_flag, rec_ret_ex_flag;

// list of internally defined ccl functions
std::list<InternalFunction *> ccl_function_list;

 int foreach_index = 0;


#line 237 "../ccl-master/parser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.hpp".  */
#ifndef YY_YY_CCL_MASTER_PARSER_HPP_INCLUDED
# define YY_YY_CCL_MASTER_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    t_SEMICOLON = 258,
    t_INTEGER = 259,
    t_REAL = 260,
    t_EQUALS = 261,
    t_LCURLY = 262,
    t_RCURLY = 263,
    t_COMMA = 264,
    t_TRUE = 265,
    t_FALSE = 266,
    t_NOT = 267,
    t_LBBRACKET = 268,
    t_RBBRACKET = 269,
    t_LBRACKET = 270,
    t_RBRACKET = 271,
    t_HEAD = 272,
    t_TAIL = 273,
    t_CONCAT = 274,
    t_CONS = 275,
    t_DOT = 276,
    t_ASSIGN = 277,
    t_LAMBDA = 278,
    t_COLON = 279,
    t_STRCAT = 280,
    t_COMPOSE = 281,
    t_NEEDS = 282,
    t_VAR = 283,
    t_STRING = 284,
    t_OR = 285,
    t_AND = 286,
    t_LESS_THAN = 287,
    t_LESS_THAN_OR_EQUAL = 288,
    t_GREATER_THAN = 289,
    t_GREATER_THAN_OR_EQUAL = 290,
    t_EQUAL = 291,
    t_NOT_EQUAL = 292,
    t_MINUS = 293,
    t_MOD = 294,
    t_DIV = 295,
    t_POWER = 296,
    t_RECORD_ADD = 297,
    t_PLUS = 298,
    t_MULT = 299,
    t_LPAREN = 300,
    t_RPAREN = 301,
    t_APP = 302,
    t_LET = 303,
    t_IN = 304,
    t_FOREACH = 305,
    t_DO = 306,
    t_END = 307,
    t_IF = 308,
    t_THEN = 309,
    t_ELSE = 310,
    t_FUN = 311,
    t_EXTERNAL = 312,
    t_INTERNAL = 313,
    t_PROGRAM = 314,
    t_SHARING = 315,
    t_EXEC = 316,
    t_BACKQUOTE = 317,
    t_UNIT = 318,
    t_BOOL = 319,
    t_INT = 320,
    t_LIST = 321,
    t_VARARGS = 322,
    t_INTO = 323,
    t_MAP_TO_CELLS = 324,
    UMINUS = 325,
    UNOT = 326
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 172 "../ccl-master/parser.y" /* yacc.c:355  */


  Expr * exp;
  char * str;        /* for variable names */
  int i;
  double real;
  std::list<Expr *> * elist;
  std::list<Expr::FIELD *> * field_list;
  std::list<char *> * vlist;
  Command * command;
  std::list<Command *> * command_list;
  Clause * cls;
  Statement * st;
  std::list<Statement *> * st_list;
  Program * prog;  
  TypeExpr * type;
  std::list<TypeExpr *> * type_list;
  Environment * env;


#line 370 "../ccl-master/parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_CCL_MASTER_PARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 387 "../ccl-master/parser.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  65
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   658

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  72
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  123
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  246

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   326

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   287,   287,   288,   293,   310,   353,   389,   414,   414,
     443,   448,   449,   450,   455,   462,   509,   514,   515,   520,
     690,   715,   721,   726,   735,   736,   737,   738,   743,   744,
     749,   754,   763,   763,   768,   769,   774,   779,   788,   793,
     802,   804,   804,   817,   818,   819,   820,   826,   827,   828,
     829,   830,   831,   832,   833,   838,   839,   840,   841,   846,
     847,   848,   849,   850,   851,   852,   854,   863,   864,   865,
     866,   871,   872,   873,   874,   876,   919,   947,   949,   951,
     995,  1004,  1031,  1059,  1068,  1075,  1086,  1094,  1101,  1106,
    1108,  1109,  1110,  1111,  1112,  1113,  1115,  1138,  1145,  1152,
    1157,  1166,  1175,  1180,  1199,  1200,  1201,  1202,  1203,  1204,
    1205,  1206,  1207,  1207,  1212,  1218,  1227,  1236,  1243,  1250,
    1256,  1262,  1271,  1280
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "t_SEMICOLON", "t_INTEGER", "t_REAL",
  "t_EQUALS", "t_LCURLY", "t_RCURLY", "t_COMMA", "t_TRUE", "t_FALSE",
  "t_NOT", "t_LBBRACKET", "t_RBBRACKET", "t_LBRACKET", "t_RBRACKET",
  "t_HEAD", "t_TAIL", "t_CONCAT", "t_CONS", "t_DOT", "t_ASSIGN",
  "t_LAMBDA", "t_COLON", "t_STRCAT", "t_COMPOSE", "t_NEEDS", "t_VAR",
  "t_STRING", "t_OR", "t_AND", "t_LESS_THAN", "t_LESS_THAN_OR_EQUAL",
  "t_GREATER_THAN", "t_GREATER_THAN_OR_EQUAL", "t_EQUAL", "t_NOT_EQUAL",
  "t_MINUS", "t_MOD", "t_DIV", "t_POWER", "t_RECORD_ADD", "t_PLUS",
  "t_MULT", "t_LPAREN", "t_RPAREN", "t_APP", "t_LET", "t_IN", "t_FOREACH",
  "t_DO", "t_END", "t_IF", "t_THEN", "t_ELSE", "t_FUN", "t_EXTERNAL",
  "t_INTERNAL", "t_PROGRAM", "t_SHARING", "t_EXEC", "t_BACKQUOTE",
  "t_UNIT", "t_BOOL", "t_INT", "t_LIST", "t_VARARGS", "t_INTO",
  "t_MAP_TO_CELLS", "UMINUS", "UNOT", "$accept", "stmts", "stmt", "$@1",
  "arglist", "progexpr", "share", "atomic", "stat_list", "stat", "clause",
  "alist", "separator", "assignment", "varlist", "varlist_comma", "expr",
  "$@2", "expr1", "expr12", "expr2", "expr3", "expr4", "expr5", "expr6",
  "let_sub", "let_list", "exprlist", "term", "list_body", "rec_el_list",
  "type_expr", "$@3", "type_assign_list", "type_expr2", "type_expr_list", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326
};
# endif

#define YYPACT_NINF -198

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-198)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     181,  -198,  -198,   348,  -198,  -198,   480,    53,   506,   506,
      63,   -17,  -198,   480,   348,    82,    88,   348,   105,    20,
     110,   480,   348,   120,  -198,   121,    44,   145,    21,    69,
       1,   553,  -198,  -198,   133,   140,    21,   128,    18,     1,
       1,  -198,   348,    69,   108,   129,   348,   104,   112,   102,
     131,  -198,  -198,  -198,    20,   134,  -198,  -198,  -198,  -198,
     -15,  -198,   123,    69,   111,  -198,   181,   348,   430,   430,
     430,   480,   480,   480,   480,   480,   480,   480,   480,   480,
     506,   506,   506,   506,   506,   562,   401,   589,  -198,  -198,
     348,  -198,   348,   138,  -198,   146,  -198,    10,  -198,  -198,
     161,   348,   348,   348,  -198,    34,   -20,   -36,  -198,   126,
    -198,    20,   144,  -198,  -198,  -198,   145,   145,   145,    21,
      21,    21,    21,    21,    21,    69,    69,    69,     1,     1,
       1,     1,     1,   553,    -1,   157,  -198,  -198,  -198,   152,
     348,   237,  -198,    82,   132,   136,   139,   348,  -198,   167,
     174,   179,  -198,    20,    71,  -198,    11,  -198,   348,  -198,
       5,  -198,  -198,  -198,   348,   348,  -198,    20,   -20,  -198,
       2,   151,   172,  -198,  -198,   266,   173,   158,     5,    85,
    -198,   150,   153,    39,  -198,    20,   177,  -198,   185,   180,
     107,  -198,   208,   210,   122,   166,   348,    86,     9,  -198,
    -198,  -198,   -20,  -198,  -198,     5,  -198,    97,  -198,  -198,
    -198,  -198,   348,   209,   348,    14,  -198,   160,  -198,   175,
    -198,   189,  -198,   348,   197,   348,  -198,   144,  -198,  -198,
     118,  -198,   200,   196,   218,  -198,  -198,  -198,   319,   183,
    -198,  -198,   348,    15,   160,  -198
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      10,    89,    91,    99,    93,    94,     0,   102,     0,     0,
       0,    90,    92,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     3,     4,    40,    43,    47,    55,
      59,    67,    71,    77,    98,     0,    54,     0,     0,    69,
      70,    41,    88,    63,     0,     0,     0,     0,     0,     0,
       0,   106,   112,   108,     0,     0,   104,   105,   107,   111,
       0,   114,     0,    66,     0,     1,    10,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   102,     0,    90,    72,
      99,    95,     0,     0,    96,     0,    87,     0,    78,    83,
      85,     0,     0,     0,    37,     0,   119,     0,   103,     0,
     109,     0,    13,    82,     2,     5,    46,    45,    44,    48,
      49,    50,    51,    52,    53,    57,    58,    56,    64,    65,
      61,    62,    60,    68,    90,     0,    73,    97,   101,     0,
       0,     0,    75,     0,     0,     0,     0,     0,    36,     0,
     118,     0,   110,   123,   120,    12,     0,    74,     0,    42,
       0,    86,    84,    79,     0,     0,     6,     0,   119,   113,
     122,     0,     0,     8,   100,     0,     0,     0,     0,     0,
      16,     0,     0,   116,   117,   123,     0,    11,     0,     0,
       0,    23,    27,     0,    35,     0,    88,     0,     0,    76,
      81,    80,   119,   121,     7,     0,    39,     0,    19,    22,
      26,    24,     0,     0,     0,     0,    21,    18,   115,     9,
      25,     0,    34,     0,     0,     0,    20,    13,    14,    38,
       0,    31,    35,     0,    17,    32,    28,    33,     0,     0,
      29,    30,    88,     0,    18,    15
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -198,  -198,   164,  -198,     6,  -160,   -12,    37,  -198,    46,
    -198,  -198,  -198,  -197,  -198,  -198,     0,  -198,  -198,   -30,
      23,    -6,    -4,   168,   -29,  -198,   103,  -190,  -198,   155,
    -198,   -18,  -198,  -159,  -198,    66
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    23,    24,   188,   156,   179,   228,   180,   190,   191,
     192,   230,   238,   193,   105,   207,    96,    95,    26,    27,
      28,    29,    30,    31,    32,    46,    47,    97,    33,    35,
      38,   170,   106,   151,    61,   171
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      25,    60,    89,    34,    39,    40,   215,    43,   149,   184,
     152,   185,   175,   109,    44,    63,   175,    49,   197,   141,
     172,    92,    64,   225,   225,    51,   231,    93,    42,    36,
     110,   176,   111,   177,    94,    52,   107,   177,   116,   117,
     118,   241,    85,   218,    42,   219,   100,   150,   202,    53,
     178,   110,   243,   111,   178,   147,   142,   173,   136,    77,
     226,   244,   148,    78,    79,    54,    25,   115,   110,    68,
     111,   125,   126,   127,    69,    70,   128,   129,   130,   131,
     132,    37,    55,    56,    57,    58,   135,    59,    80,    81,
      34,    41,   138,   154,   119,   120,   121,   122,   123,   124,
     220,   144,   145,   146,    89,   110,   221,   111,    82,    83,
      45,     1,     2,    84,     3,   208,    48,     4,     5,     6,
      65,   235,     7,    66,     8,     9,   236,   237,   198,   198,
      10,   199,   216,    50,   189,    11,    12,   110,    62,   111,
     159,   161,    90,    67,   212,    13,   213,   166,    91,   183,
      92,    99,    14,   101,    98,    15,   103,    16,   174,   104,
      17,   102,   108,   113,   181,   182,   139,   140,   112,    21,
     143,   153,   155,   157,   158,   194,    22,    71,    72,    73,
      74,    75,    76,   168,   163,     1,     2,   164,     3,   167,
     194,     4,     5,     6,   165,   169,     7,   186,     8,     9,
     187,   195,   200,   196,    10,   201,   204,   205,   206,    11,
      12,   210,   222,   211,   224,   214,   223,   229,   198,    13,
     227,   233,   212,   232,   239,   161,    14,   172,   242,    15,
     114,    16,   245,   234,    17,   217,   209,    18,   232,    19,
      20,     1,     2,    21,     3,   137,   162,     4,     5,     6,
      22,   203,     7,   133,     8,     9,     0,     0,     0,     0,
      10,     0,     0,     0,     0,    11,    12,     0,     0,     0,
       1,     2,     0,     3,     0,    13,     4,     5,     6,     0,
       0,     7,    14,     8,     9,    15,     0,    16,     0,    10,
      17,     0,     0,   189,    11,    12,   160,     0,     0,    21,
       0,     0,     0,     0,    13,     0,    22,     0,     0,     0,
       0,    14,     0,     0,    15,     0,    16,     0,     0,    17,
       0,     0,     0,     1,     2,     0,     3,   240,    21,     4,
       5,     6,     0,     0,     7,    22,     8,     9,     0,     0,
       0,     0,    10,     0,     0,     0,     0,    11,    12,     0,
       0,     0,     1,     2,     0,     3,     0,    13,     4,     5,
       6,     0,     0,     7,    14,     8,     9,    15,     0,    16,
       0,    10,    17,     0,     0,     0,    11,    12,     0,     0,
       0,    21,     0,     0,     0,     0,    13,     0,    22,     0,
       0,     0,     0,    14,     0,     0,    15,     0,    16,     0,
       0,    17,     0,     0,     0,     1,     2,     0,     3,     0,
      21,     4,     5,     6,     0,     0,     7,    22,     8,     9,
       0,     0,     0,     0,    10,     0,     0,     0,     0,   134,
      12,     0,     0,     0,     1,     2,     0,     3,     0,    13,
       4,     5,     6,     0,     0,     7,    14,     8,     9,    15,
       0,    16,     0,     0,    17,     0,     0,     0,    11,    12,
       0,     0,     0,    21,     0,     0,     0,     0,    13,     0,
      22,     0,     0,     0,     0,    14,     0,     0,    15,     0,
      16,     0,     0,    17,     1,     2,     0,     3,     0,     0,
       4,     5,    21,     0,     0,     7,     0,     8,     9,    22,
       0,     0,     0,     0,     0,     0,     0,     0,    11,    12,
       1,     2,     0,     3,     0,     0,     4,     5,    13,     0,
       0,     7,     0,     8,     9,    14,     0,     0,    15,     0,
      16,     0,     0,    17,    11,    12,     0,     0,     0,     0,
       0,     0,    21,     0,     0,     0,     0,     0,     0,    22,
       0,    14,     0,     0,    15,     0,    16,     1,     2,    17,
       3,     0,     0,     4,     5,     0,     1,     2,    86,     3,
       0,     0,     4,     5,    87,    22,     0,     7,     0,     0,
       0,    88,    12,     0,     0,     0,     0,     0,     0,     0,
      11,    12,     0,     1,     2,     0,     3,     0,    14,     4,
       5,    15,     0,    16,     7,     0,    17,    14,     0,     0,
      15,     0,    16,     0,     0,    17,     0,    88,    12,     0,
       0,     0,    22,     0,     0,     0,     0,     0,     0,     0,
       0,    22,     0,     0,    14,     0,     0,    15,     0,    16,
       0,     0,    17,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    22
};

static const yytype_int16 yycheck[] =
{
       0,    19,    31,     3,     8,     9,   196,    13,    28,   168,
      46,     9,     7,    28,    14,    21,     7,    17,   178,     9,
       9,    22,    22,     9,     9,     5,   223,     9,    45,     6,
      66,    26,    68,    28,    16,    15,    54,    28,    68,    69,
      70,   238,    41,   202,    45,   205,    46,    67,     9,    29,
      45,    66,   242,    68,    45,    21,    46,    46,    87,    38,
      46,    46,    28,    42,    43,    45,    66,    67,    66,    25,
      68,    77,    78,    79,    30,    31,    80,    81,    82,    83,
      84,    28,    62,    63,    64,    65,    86,    67,    19,    20,
      90,    28,    92,   111,    71,    72,    73,    74,    75,    76,
       3,   101,   102,   103,   133,    66,     9,    68,    39,    40,
      28,     4,     5,    44,     7,     8,    28,    10,    11,    12,
       0,     3,    15,     3,    17,    18,     8,     9,    43,    43,
      23,    46,    46,    28,    27,    28,    29,    66,    28,    68,
     140,   141,     9,    22,    22,    38,    24,   147,     8,   167,
      22,    22,    45,    49,    46,    48,    54,    50,   158,    28,
      53,    49,    28,    52,   164,   165,    28,    21,    45,    62,
       9,    45,    28,    16,    22,   175,    69,    32,    33,    34,
      35,    36,    37,     9,    52,     4,     5,    51,     7,    22,
     190,    10,    11,    12,    55,    16,    15,    46,    17,    18,
      28,    28,    52,    45,    23,    52,    29,    22,    28,    28,
      29,     3,   212,     3,   214,    49,     7,    28,    43,    38,
      60,    24,    22,   223,    28,   225,    45,     9,    45,    48,
      66,    50,   244,   227,    53,   198,   190,    56,   238,    58,
      59,     4,     5,    62,     7,    90,   143,    10,    11,    12,
      69,   185,    15,    85,    17,    18,    -1,    -1,    -1,    -1,
      23,    -1,    -1,    -1,    -1,    28,    29,    -1,    -1,    -1,
       4,     5,    -1,     7,    -1,    38,    10,    11,    12,    -1,
      -1,    15,    45,    17,    18,    48,    -1,    50,    -1,    23,
      53,    -1,    -1,    27,    28,    29,    59,    -1,    -1,    62,
      -1,    -1,    -1,    -1,    38,    -1,    69,    -1,    -1,    -1,
      -1,    45,    -1,    -1,    48,    -1,    50,    -1,    -1,    53,
      -1,    -1,    -1,     4,     5,    -1,     7,     8,    62,    10,
      11,    12,    -1,    -1,    15,    69,    17,    18,    -1,    -1,
      -1,    -1,    23,    -1,    -1,    -1,    -1,    28,    29,    -1,
      -1,    -1,     4,     5,    -1,     7,    -1,    38,    10,    11,
      12,    -1,    -1,    15,    45,    17,    18,    48,    -1,    50,
      -1,    23,    53,    -1,    -1,    -1,    28,    29,    -1,    -1,
      -1,    62,    -1,    -1,    -1,    -1,    38,    -1,    69,    -1,
      -1,    -1,    -1,    45,    -1,    -1,    48,    -1,    50,    -1,
      -1,    53,    -1,    -1,    -1,     4,     5,    -1,     7,    -1,
      62,    10,    11,    12,    -1,    -1,    15,    69,    17,    18,
      -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    28,
      29,    -1,    -1,    -1,     4,     5,    -1,     7,    -1,    38,
      10,    11,    12,    -1,    -1,    15,    45,    17,    18,    48,
      -1,    50,    -1,    -1,    53,    -1,    -1,    -1,    28,    29,
      -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,    38,    -1,
      69,    -1,    -1,    -1,    -1,    45,    -1,    -1,    48,    -1,
      50,    -1,    -1,    53,     4,     5,    -1,     7,    -1,    -1,
      10,    11,    62,    -1,    -1,    15,    -1,    17,    18,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,
       4,     5,    -1,     7,    -1,    -1,    10,    11,    38,    -1,
      -1,    15,    -1,    17,    18,    45,    -1,    -1,    48,    -1,
      50,    -1,    -1,    53,    28,    29,    -1,    -1,    -1,    -1,
      -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,    69,
      -1,    45,    -1,    -1,    48,    -1,    50,     4,     5,    53,
       7,    -1,    -1,    10,    11,    -1,     4,     5,    15,     7,
      -1,    -1,    10,    11,    21,    69,    -1,    15,    -1,    -1,
      -1,    28,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      28,    29,    -1,     4,     5,    -1,     7,    -1,    45,    10,
      11,    48,    -1,    50,    15,    -1,    53,    45,    -1,    -1,
      48,    -1,    50,    -1,    -1,    53,    -1,    28,    29,    -1,
      -1,    -1,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    69,    -1,    -1,    45,    -1,    -1,    48,    -1,    50,
      -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,     7,    10,    11,    12,    15,    17,    18,
      23,    28,    29,    38,    45,    48,    50,    53,    56,    58,
      59,    62,    69,    73,    74,    88,    90,    91,    92,    93,
      94,    95,    96,   100,    88,   101,    92,    28,   102,    94,
      94,    28,    45,    93,    88,    28,    97,    98,    28,    88,
      28,     5,    15,    29,    45,    62,    63,    64,    65,    67,
     103,   106,    28,    93,    88,     0,     3,    22,    25,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    42,    43,
      19,    20,    39,    40,    44,    41,    15,    21,    28,    96,
       9,     8,    22,     9,    16,    89,    88,    99,    46,    22,
      88,    49,    49,    54,    28,    86,   104,   103,    28,    28,
      66,    68,    45,    52,    74,    88,    91,    91,    91,    92,
      92,    92,    92,    92,    92,    93,    93,    93,    94,    94,
      94,    94,    94,    95,    28,    88,    96,   101,    88,    28,
      21,     9,    46,     9,    88,    88,    88,    21,    28,    28,
      67,   105,    46,    45,   103,    28,    76,    16,    22,    88,
      59,    88,    98,    52,    51,    55,    88,    22,     9,    16,
     103,   107,     9,    46,    88,     7,    26,    28,    45,    77,
      79,    88,    88,   103,   105,     9,    46,    28,    75,    27,
      80,    81,    82,    85,    88,    28,    45,    77,    43,    46,
      52,    52,     9,   107,    29,    22,    28,    87,     8,    81,
       3,     3,    22,    24,    49,    99,    46,    79,   105,    77,
       3,     9,    88,     7,    88,     9,    46,    60,    78,    28,
      83,    85,    88,    24,    76,     3,     8,     9,    84,    28,
       8,    85,    45,    99,    46,    78
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    72,    73,    73,    74,    74,    74,    74,    75,    74,
      74,    76,    76,    76,    77,    77,    77,    78,    78,    79,
      79,    79,    80,    80,    81,    81,    81,    81,    82,    82,
      83,    83,    84,    84,    85,    85,    86,    86,    87,    87,
      88,    89,    88,    90,    90,    90,    90,    91,    91,    91,
      91,    91,    91,    91,    91,    92,    92,    92,    92,    93,
      93,    93,    93,    93,    93,    93,    93,    94,    94,    94,
      94,    95,    95,    95,    95,    95,    95,    96,    96,    96,
      96,    96,    96,    97,    98,    98,    99,    99,    99,   100,
     100,   100,   100,   100,   100,   100,   100,   101,   101,   101,
     102,   102,   102,   103,   103,   103,   103,   103,   103,   103,
     103,   103,   104,   103,   103,   105,   105,   105,   105,   105,
     106,   107,   107,   107
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     1,     1,     3,     5,     7,     0,     8,
       0,     3,     1,     0,     4,    10,     1,     2,     0,     3,
       4,     3,     2,     1,     2,     3,     2,     1,     5,     6,
       3,     1,     1,     1,     3,     1,     2,     1,     3,     1,
       1,     0,     5,     1,     3,     3,     3,     1,     3,     3,
       3,     3,     3,     3,     2,     1,     3,     3,     3,     1,
       3,     3,     3,     2,     3,     3,     2,     1,     3,     2,
       2,     1,     2,     3,     4,     4,     7,     1,     3,     5,
       7,     7,     3,     2,     4,     2,     3,     1,     0,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     1,     0,
       5,     3,     0,     2,     1,     1,     1,     1,     1,     2,
       3,     1,     0,     4,     1,     5,     3,     3,     1,     0,
       3,     3,     1,     0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 4:
#line 294 "../ccl-master/parser.y" /* yacc.c:1646  */
    {

      VERBOSE; 

      (yyvsp[0].exp)->type_check ( top_scope, main_env ); // will throw an error if there is a problem

      Value * ans = (yyvsp[0].exp)->eval ( top_scope );

      if ( ans->get_type() != Value::UNIT ) { ans->print(); NL; NL;} 

      delete ans;

      //delete $1;

    }
#line 1740 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 311 "../ccl-master/parser.y" /* yacc.c:1646  */
    { 

      VERBOSE;

      Expr * lhs = (yyvsp[-2].exp),
           * rhs = (yyvsp[0].exp);

      !rhs->type_check ( top_scope, main_env );

      if ( lhs->get_type() == Expr::VARIABLE && top_scope->get ( lhs->get_name() ) == NULL) {

        top_scope->add ( lhs->get_name(), rhs->eval ( top_scope ) );

      } else {

	std::list<TypeExpr *> garbage, ng;

	if ( ! TypeExpr::unify ( lhs->compute_type ( top_scope, main_env, &ng, &garbage ),
				 rhs->compute_type ( top_scope, main_env, &ng, &garbage ) ) ) {

          TYPE_ERROR ( "Type Error: The symbol <i>" << lhs->tostring()
                       << "</i> has a different type than does the expression <i>" << rhs->tostring() << ".<i>" );

	} else if ( ! lhs->is_lhs() ) {

          TYPE_ERROR ( "Type Error: illegal expression " << lhs->tostring() << " on left hand side of assignment." );

	} else {

	  top_scope->set ( lhs, rhs->eval ( top_scope ) );

	}

	TypeExpr::take_out ( &garbage );

      }

      delete (yyvsp[-2].exp);
      delete (yyvsp[0].exp);

    }
#line 1786 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 353 "../ccl-master/parser.y" /* yacc.c:1646  */
    {

      VERBOSE;

      fun_temp = new TypeExpr ( new TypeExpr(), new TypeExpr() );

      PUSH_WITH_TYPE ( (yyvsp[-3].str), fun_temp ); 

      std::list<char *>::iterator i;
      Expr * e = (yyvsp[0].exp);
      SET_INFO(e);

      for ( i=(yyvsp[-2].vlist)->begin(); i != (yyvsp[-2].vlist)->end(); i++ ) {
	e = FUNC ( (*i), e );
	free (*i);
	SET_INFO(e);
      }

      delete (yyvsp[-2].vlist);

      e->type_check ( top_scope, main_env );

      fun_temp->reset();
      fun_temp->free_children();

      POP; /* frees fun_temp */

      Value * answer = e->eval ( top_scope );
      top_scope->add ( (yyvsp[-3].str), answer );
      top_scope->set_recursive ( (yyvsp[-3].str) );
      delete e;

      free ( (yyvsp[-3].str) );

    }
#line 1826 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 391 "../ccl-master/parser.y" /* yacc.c:1646  */
    {

      VERBOSE;

      const char * error;

      EXTERNAL_CCLI_FUNCTION f = lookup_ccl_function ( (yyvsp[0].str) );

      if ( f == NULL )  {
        ERROR ( "Could not find symbol <i>" << (yyvsp[0].str) << "</i> in list of internally defined functions." );
      } 

      Value * efunc = new Value ( f, (yyvsp[-5].type), (yyvsp[-2].type_list) );
      top_scope->add ( (yyvsp[-4].str), efunc );
      free ( (yyvsp[-4].str) );

      while ( main_env != NULL )
	POP_SIMP;

      free ( (yyvsp[0].str) );

    }
#line 1853 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 414 "../ccl-master/parser.y" /* yacc.c:1646  */
    {

      VERBOSE;

      std::list<char *>::iterator i;

      for ( i = (yyvsp[-1].vlist)->begin(); i != (yyvsp[-1].vlist)->end(); i++ ) {  // push parameter list onto main_env
	PUSH ( *i );
      }

    }
#line 1869 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 424 "../ccl-master/parser.y" /* yacc.c:1646  */
    {

      std::list<char *>::iterator i;

      (yyvsp[0].prog)->set_args((yyvsp[-4].vlist));
      (yyvsp[0].prog)->compute_arg_types ( main_env ); // doesn't do anything if $8 is atomic
      top_scope->add((yyvsp[-6].str),(yyvsp[0].prog));
      (yyvsp[0].prog)->set_name ( (yyvsp[-6].str) );

      for ( i = (yyvsp[-4].vlist)->begin(); i != (yyvsp[-4].vlist)->end(); i++ ) {  // pop parameter list
	POP;
      }

      TypeExpr::take_out ( &program_garbage );

      free ( (yyvsp[-6].str) );

    }
#line 1892 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 448 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.vlist) = (yyvsp[-2].vlist); (yyval.vlist)->push_back ( (yyvsp[0].str) ); }
#line 1898 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 449 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.vlist) = new std::list<char *>; (yyval.vlist)->push_back ( (yyvsp[0].str) ); }
#line 1904 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 450 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.vlist) = new std::list<char *>; }
#line 1910 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 455 "../ccl-master/parser.y" /* yacc.c:1646  */
    { 

        (yyval.prog) = new CompositeProgram ( (yyvsp[-3].prog), (yyvsp[-1].prog), (yyvsp[0].vlist), current_file_name[include_stack_ptr], lineNum[include_stack_ptr] );
	FREE_STR_LIST ( (yyvsp[0].vlist) );

      }
#line 1921 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 462 "../ccl-master/parser.y" /* yacc.c:1646  */
    {

      // 1) $4 evaluates to a list of constants, and that it isn't empty?

      if ( ! (yyvsp[-6].exp)->type_check ( top_scope, NULL ) ) {  // note: using NULL instead of main_env here because the
                                                     // index set should not depend on parameters of some enclosing
                                                     // program definition
        TYPE_ERROR ( "Something wrong with </i>" << (yyvsp[-6].exp)->tostring() << "<i> in program composition expression." );
      }

      Value * L = (yyvsp[-6].exp)->eval ( top_scope );

      if ( L->get_type() != Value::LIST ) {
        TYPE_ERROR ( "Index set in program composition does not evaluate to a list." );
      }

      if ( L->list_value()->size() < 1 )  {
        ERROR ( "Index set in program composition is empty." );
      }

      // 2) $6 is a program?
      Program * p = top_scope->get_program ( (yyvsp[-4].str) );

      if ( p == NULL ) {
         ERROR ( "The symbol <i>" << (yyvsp[-4].str) << "</i> is undefined, or is not defined as a program." );
      }

      // 3) $6->args and $8 have same length?
      if ( p->get_args()->size() != (yyvsp[-2].elist)->size() ) {
         ERROR ( "The program <i>" << (yyvsp[-4].str) << "</i> is instantiated with the wrong number of arguments "
                << "(should have " << p->get_args()->size() << ")." );
      }

      // 4) Make the composition
      (yyval.prog) = Program::Composition ( p, (yyvsp[-2].elist), (yyvsp[-8].str), L->list_value(), (yyvsp[0].vlist), top_scope, main_env, 
				  current_file_name[include_stack_ptr], lineNum[include_stack_ptr] );

      // 5) Delete old stuff
      free((yyvsp[-8].str));
      free((yyvsp[-4].str));
      FREE_STR_LIST ( (yyvsp[0].vlist) );
      FREE_EXPR_LIST ( (yyvsp[-2].elist) );
      delete (yyvsp[-6].exp);
      delete L;

    }
#line 1972 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 509 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.prog) = (yyvsp[0].prog); }
#line 1978 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 514 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.vlist) = (yyvsp[0].vlist); }
#line 1984 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 515 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.vlist) = new std::list<char *>; }
#line 1990 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 522 "../ccl-master/parser.y" /* yacc.c:1646  */
    {

      AtomicProgram * p = new AtomicProgram ( current_file_name[include_stack_ptr], lineNum[include_stack_ptr] );
      Clause * init = new Clause ( CONST ( true ) );
      std::list<Statement *>::iterator i;
      std::list<TypeExpr *> ng, needs_garbage;
      TypeExpr * T;
      int program_var_counter = 0;

      for ( i=(yyvsp[-1].st_list)->begin(); i!=(yyvsp[-1].st_list)->end(); i++ ) {

	if ( (*i)->com != NULL ) { // initializer //////////////////////////////////////////////////////////////////

	  init->addCommand ( (*i)->com );
	  T = (*i)->com->get_rhs()->compute_type ( top_scope, main_env, &ng, &program_garbage );

          if ( !T->is_consistent() ) TYPE_ERROR ( "Inconsistent type." );

          Expr * lhs = (*i)->com->get_lhs();

          if ( lhs != NULL 
	       && lhs->get_type() == Expr::VARIABLE 
	       && RETRIEVE(main_env,lhs->get_name()) == NULL ) {

	    //	    p->add_symbol ( lhs->get_name(), new Value ( Value::UNIT ) ); 
	    PUSH_WITH_TYPE ( lhs->get_name(), T );
	    program_var_counter++;

	  }

	  if ( lhs != NULL ) { // check types of lhs and rhs

	    TypeExpr * Tlhs = lhs->compute_type ( top_scope, main_env, &ng, &program_garbage );

            if ( !Tlhs->is_consistent() ) TYPE_ERROR ( "Inconsistent type." );

	    if ( ! TypeExpr::unify ( T, Tlhs ) ) {

              TYPE_ERROR ( "Incompatible types in assignment. "
                << "The left hand side has type <i>" << Tlhs->tostring()
                << "</i> while the right hand side has type <i>" << T->tostring() << ".</i>" );
	      
	    }

	  }

	} else if ( (*i)->cl != NULL ) { // clause /////////////////////////////////////////////////////////////////

	  T = (*i)->cl->get_guard()->compute_type ( top_scope, main_env, &ng, &program_garbage );
          if ( !T->is_consistent() ) TYPE_ERROR ( "Inconsistent type." );

          TypeExpr * B = new TypeExpr ( Value::BOOLEAN );
	  program_garbage.push_back ( B );

	  if ( ! TypeExpr::unify ( T, B ) ) {

            TYPE_ERROR ( "Clause does not have Boolean guard. In particular, "
              << "<i>" << (*i)->cl->get_guard()->tostring() << "</i> has type "
              << "<i>" << T->tostring() << ".</i>" );

	  }

	  std::list<Command *>::iterator j;

	  for ( j = (*i)->cl->get_commands()->begin(); j != (*i)->cl->get_commands()->end(); j++ ) {

	    if ( (*j)->get_lhs() != NULL ) {

	      TypeExpr * T1 = (*j)->get_lhs()->compute_type ( top_scope, main_env, &ng, &program_garbage ),
		* T2 = (*j)->get_rhs()->compute_type ( top_scope, main_env, &ng, &program_garbage );
	      
              if ( ! TypeExpr::unify ( T1, T2 ) ) {

                TYPE_ERROR ( "Incompatible types in assignment in command part of guarded command. "
                  << "<i>" << (*j)->get_lhs()->tostring() << "</i> has type <i>" << T1->tostring()
                  << "</i> while <i>" << (*j)->get_rhs()->tostring() << "</i> has type <i>" << T2->tostring() << ".</i>" );

	      }

	    } else {

	      TypeExpr * T = (*j)->get_rhs()->compute_type ( top_scope, main_env, &ng, &program_garbage );
	      if ( !T->is_consistent() )
		return -1;

	    }

	    //TypeExpr::take_out ( &program_garbage );

	  }

	  p->add_clause ( (*i)->cl );

	} else if ( (*i)->vars != NULL ) { // "needs" statement ////////////////////////////////////////////////////

          std::list<char *>::iterator j;

	  for ( j = (*i)->vars->begin(); j != (*i)->vars->end(); j++ ) {
	    PUSH ( *j );
	    needs_garbage.push_back ( main_env->get_type() );
            p->add_needs ( *j ); 
	    program_var_counter++;
	    free ( *j );
	  }

	  delete (*i)->vars;

        }

	delete (*i);

      } // done reading statements

      delete (yyvsp[-1].st_list);
      p->set_init ( init );
      (yyval.prog) = p;

      // save parameter and local variable types
      {

	Environment * env = main_env;
	std::list<TypeExpr *> * vars = new std::list<TypeExpr *>, 
                              * ng_save = new std::list<TypeExpr *>;

	while ( env != NULL ) {
	  env->get_type()->compute_non_generics ( vars );
	  env = env->get_tail();
	}
	
	COPY_TYPEVAR_LIST ( vars, ng_save );

	p->set_non_generics ( ng_save );

	std::list<TypeExpr *>::iterator w;

	Environment * temp = main_env, * locals = NULL;

	for ( int j = 0; j < program_var_counter; j++ ) { // this copies variables in assignments and in needs statements
	  locals = new Environment ( temp->get_name(), temp->get_type()->copy_ex ( vars, ng_save ), locals );
	  temp = temp->get_tail();
	}

	p->set_locals ( locals );
	
	Environment * arg_types = NULL;
	if ( temp != NULL )
	  arg_types = temp->copy_ex ( vars, ng_save );

	p->set_arg_types ( arg_types );

	delete vars;

      } 

      // pop local program vars and add default values 
      for ( int j = 0; j < program_var_counter; j++ ) {
	p->add_symbol ( main_env->get_name(), main_env->get_type()->default_value() );
	POP_SIMP;

      }

      // free needs type exprs
      std::list<TypeExpr *>::iterator q;
      for ( q=needs_garbage.begin(); q != needs_garbage.end(); q++ )
	delete (*q);

    }
#line 2162 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 692 "../ccl-master/parser.y" /* yacc.c:1646  */
    {

      Program * p = top_scope->get_program((yyvsp[-3].str));

      if ( p == NULL ) {
         ERROR ( "Symbol <i>" << (yyvsp[-3].str) << "</i> undefined." );
      }

      std::list<char *> * args = p->get_args();

      if ( args->size() != (yyvsp[-1].elist)->size() ) {
         ERROR ( "The program <i>" << (yyvsp[-3].str) << "</i> is instantiated with the wrong number of arguments "
             << "(should have " << args->size() << ")." );
      }

      p = p->copy();
      p->set_insts ( (yyvsp[-1].elist), top_scope, main_env, (yyvsp[-3].str) );
      (yyval.prog) = new InstProgram ( p, current_file_name[include_stack_ptr], lineNum[include_stack_ptr] ); 

      free ( (yyvsp[-3].str) );

    }
#line 2189 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 715 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.prog) = (yyvsp[-1].prog); }
#line 2195 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 722 "../ccl-master/parser.y" /* yacc.c:1646  */
    {
      (yyval.st_list) = (yyvsp[-1].st_list);
      (yyval.st_list)->push_back ( (yyvsp[0].st) );
    }
#line 2204 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 727 "../ccl-master/parser.y" /* yacc.c:1646  */
    {
      (yyval.st_list) = new std::list<Statement *>;
      (yyval.st_list)->push_back ( (yyvsp[0].st) );
    }
#line 2213 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 735 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.st) = new Statement ( (yyvsp[-1].command) );  }
#line 2219 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 736 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.st) = new Statement ( (yyvsp[-1].vlist) ); }
#line 2225 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 737 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.st) = new Statement ( (yyvsp[-1].cls) ); }
#line 2231 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 738 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.st) = new Statement ( (yyvsp[0].cls) ); }
#line 2237 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 743 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.cls) = new Clause ( (yyvsp[-4].exp), (yyvsp[-1].command_list) ); }
#line 2243 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 744 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.cls) = new Clause ( (yyvsp[-5].exp), (yyvsp[-2].command_list) ); }
#line 2249 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 750 "../ccl-master/parser.y" /* yacc.c:1646  */
    {
      (yyval.command_list) = (yyvsp[-2].command_list);
      (yyval.command_list)->push_back((yyvsp[0].command));
    }
#line 2258 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 755 "../ccl-master/parser.y" /* yacc.c:1646  */
    {
      (yyval.command_list) = new std::list<Command *>;
      (yyval.command_list)->push_back((yyvsp[0].command));
    }
#line 2267 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 768 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.command) = new Command ( (yyvsp[-2].exp), (yyvsp[0].exp) ); }
#line 2273 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 769 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.command) = new Command ( NULL, (yyvsp[0].exp) ); }
#line 2279 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 775 "../ccl-master/parser.y" /* yacc.c:1646  */
    {
      (yyvsp[-1].vlist)->push_front ( (yyvsp[0].str) );
      (yyval.vlist) = (yyvsp[-1].vlist);
    }
#line 2288 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 780 "../ccl-master/parser.y" /* yacc.c:1646  */
    {
      (yyval.vlist) = new std::list<char *>; 
      (yyval.vlist)->push_back ( (yyvsp[0].str) );
    }
#line 2297 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 789 "../ccl-master/parser.y" /* yacc.c:1646  */
    {
      (yyvsp[-2].vlist)->push_front ( (yyvsp[0].str) );
      (yyval.vlist) = (yyvsp[-2].vlist);
    }
#line 2306 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 794 "../ccl-master/parser.y" /* yacc.c:1646  */
    {
      (yyval.vlist) = new std::list<char *>; 
      (yyval.vlist)->push_back ( (yyvsp[0].str) );
    }
#line 2315 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 804 "../ccl-master/parser.y" /* yacc.c:1646  */
    { PUSH((yyvsp[0].str)); }
#line 2321 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 804 "../ccl-master/parser.y" /* yacc.c:1646  */
    { 

      (yyval.exp) = FUNC ( (yyvsp[-3].str), (yyvsp[0].exp) ); 
      SET_INFO((yyval.exp));
      free ( (yyvsp[-3].str) ); 
      POP;

    }
#line 2334 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 817 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2340 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 818 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = BINEXP ( Expr::AND, (yyvsp[-2].exp), (yyvsp[0].exp) ); SET_INFO((yyval.exp)); }
#line 2346 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 819 "../ccl-master/parser.y" /* yacc.c:1646  */
    {  (yyval.exp) = BINEXP ( Expr::OR, (yyvsp[-2].exp), (yyvsp[0].exp) ); SET_INFO((yyval.exp)); }
#line 2352 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 820 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = BINEXP ( Expr::STR_CAT, (yyvsp[-2].exp), (yyvsp[0].exp) ); SET_INFO((yyval.exp)); }
#line 2358 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 826 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2364 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 827 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = BINEXP ( Expr::LT, (yyvsp[-2].exp), (yyvsp[0].exp) ); SET_INFO((yyval.exp)); }
#line 2370 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 828 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = BINEXP ( Expr::LE, (yyvsp[-2].exp), (yyvsp[0].exp) ); SET_INFO((yyval.exp)); }
#line 2376 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 829 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = BINEXP ( Expr::GT, (yyvsp[-2].exp), (yyvsp[0].exp) ); SET_INFO((yyval.exp)); }
#line 2382 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 830 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = BINEXP ( Expr::GE, (yyvsp[-2].exp), (yyvsp[0].exp) ); SET_INFO((yyval.exp)); }
#line 2388 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 831 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = BINEXP ( Expr::EQ, (yyvsp[-2].exp), (yyvsp[0].exp) ); SET_INFO((yyval.exp)); }
#line 2394 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 832 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = BINEXP ( Expr::NE, (yyvsp[-2].exp), (yyvsp[0].exp) ); SET_INFO((yyval.exp)); }
#line 2400 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 833 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = UNEXP ( Expr::NOT, (yyvsp[0].exp) ); SET_INFO((yyval.exp)); }
#line 2406 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 838 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2412 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 839 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = BINEXP ( Expr::PLUS, (yyvsp[-2].exp), (yyvsp[0].exp) ); SET_INFO((yyval.exp)); }
#line 2418 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 840 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = BINEXP ( Expr::MINUS, (yyvsp[-2].exp), (yyvsp[0].exp) ); SET_INFO((yyval.exp)); }
#line 2424 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 841 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = BINEXP ( Expr::RECORD_ADD, (yyvsp[-2].exp), (yyvsp[0].exp) ); SET_INFO((yyval.exp)); }
#line 2430 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 846 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2436 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 847 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = BINEXP ( Expr::MULT, (yyvsp[-2].exp), (yyvsp[0].exp) ); SET_INFO((yyval.exp)); }
#line 2442 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 848 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = BINEXP ( Expr::MOD, (yyvsp[-2].exp), (yyvsp[0].exp) ); SET_INFO((yyval.exp)); }
#line 2448 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 849 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = BINEXP ( Expr::DIV, (yyvsp[-2].exp), (yyvsp[0].exp) ); SET_INFO((yyval.exp)); }
#line 2454 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 850 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = UNEXP ( Expr::UMIN, (yyvsp[0].exp) ); SET_INFO((yyval.exp)); }
#line 2460 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 851 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = BINEXP ( Expr::CONCAT, (yyvsp[-2].exp), (yyvsp[0].exp) ); SET_INFO((yyval.exp)); }
#line 2466 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 852 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = BINEXP ( Expr::CONS, (yyvsp[-2].exp), (yyvsp[0].exp) ); SET_INFO((yyval.exp)); }
#line 2472 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 854 "../ccl-master/parser.y" /* yacc.c:1646  */
    { 
	std::list<char *> locals;
	(yyval.exp) = (yyvsp[0].exp)->prevify ( &locals ); 
	delete (yyvsp[0].exp); 
    }
#line 2482 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 863 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2488 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 864 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = BINEXP ( Expr::POW, (yyvsp[-2].exp), (yyvsp[0].exp) ); SET_INFO((yyval.exp)); }
#line 2494 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 865 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = UNEXP ( Expr::HEAD, (yyvsp[0].exp) ); SET_INFO((yyval.exp)); }
#line 2500 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 866 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = UNEXP ( Expr::TAIL, (yyvsp[0].exp) ); SET_INFO((yyval.exp)); }
#line 2506 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 871 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2512 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 872 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = APP ( (yyvsp[-1].exp), (yyvsp[0].exp) ); SET_INFO((yyval.exp)); }
#line 2518 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 873 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = BINEXP ( Expr::DOT, (yyvsp[-2].exp), (yyvsp[0].exp) ); SET_INFO((yyval.exp)); }
#line 2524 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 874 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = BINEXP ( Expr::LIST_EL, (yyvsp[-3].exp), (yyvsp[-1].exp) ); SET_INFO((yyval.exp)); }
#line 2530 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 876 "../ccl-master/parser.y" /* yacc.c:1646  */
    { // this could be either a function application, an external function application
                                         // or possibly a program

      Value * f = top_scope->get ( (yyvsp[-3].str) );

      if ( f && f->get_type() == Value::EX_FUNCTION ) { // external function 

        if ( !f ) {
          ERROR ( "Seriously odd error. The symbol <i>" << (yyvsp[-3].str) << "</i> is undefined." );
        }

        (yyval.exp) = EAPP ( f->copy(), (yyvsp[-1].elist) ); 
	SET_INFO((yyval.exp));

	free ( (yyvsp[-3].str) );

      } else if ( top_scope->get_program ( (yyvsp[-3].str) ) ) {

          TYPE_ERROR ( "The program <i>" << (yyvsp[-3].str) << "</i> appears mixed with expressions that are not programs." );

      } else {

	if ( (yyvsp[-1].elist)->size() == 1 ) {

          Expr * arg = VAR ( (yyvsp[-3].str) );
	  SET_INFO ( arg );

	  (yyval.exp) = APP ( arg, *((yyvsp[-1].elist)->begin()) );
	  SET_INFO((yyval.exp));

	  free ( (yyvsp[-3].str) );
	  delete (yyvsp[-1].elist);

	} else {

          ERROR ( "Parse error." );

	}

      }

    }
#line 2577 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 919 "../ccl-master/parser.y" /* yacc.c:1646  */
    {

      Value * f = top_scope->get ( (yyvsp[-6].str) );

      if ( f && f->get_type() == Value::EX_FUNCTION ) { // external function 

        if ( !f ) {
          ERROR ( "Seriously odd error. The symbol <i>" << (yyvsp[-6].str) << "</i> is undefined." );
        }

        (yyvsp[-4].elist)->push_back ( new Expr ( (yyvsp[-1].prog) ) );
        (yyval.exp) = EAPP ( f->copy(), (yyvsp[-4].elist) ); 
	SET_INFO((yyval.exp));

      } else {

        ERROR ( "<i>" << (yyvsp[-6].str) << "</i> should refer to an external function since it has a program as an argument." );

      }

      free ( (yyvsp[-6].str) );

    }
#line 2605 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 947 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 2611 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 949 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[-1].exp); SET_INFO((yyval.exp)); }
#line 2617 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 951 "../ccl-master/parser.y" /* yacc.c:1646  */
    { 

      std::list<Statement *>::iterator i;
      Expr * result = NULL;

      for ( i = (yyvsp[-3].st_list)->begin(); i != (yyvsp[-3].st_list)->end(); i++ ) {

        Command * c = (*i)->com;

        if ( c == NULL || c->get_lhs()->get_type() != Expr::VARIABLE ) {
          ERROR ( "Error in let expression (not a variable assignment). " );
	} 

        if ( result == NULL ) {

          result = LETEXP ( c->get_lhs()->get_name(), c->get_rhs()->copy(), (yyvsp[-1].exp) );

        } else {

          result = LETEXP ( c->get_lhs()->get_name(), c->get_rhs()->copy(), result );

	}

      }

      for ( i = (yyvsp[-3].st_list)->begin(); i != (yyvsp[-3].st_list)->end(); i++ ) {

        Command * c = (*i)->com;
	POP;
	delete c;

      }

      if ( result == NULL ) {
        ERROR ( "Empty assignment section in let statement." );
      }

      (yyval.exp) = result;
      SET_INFO((yyval.exp));

      delete (yyvsp[-3].st_list);

    }
#line 2665 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 997 "../ccl-master/parser.y" /* yacc.c:1646  */
    { 

      (yyval.exp) = IFEXP ( (yyvsp[-5].exp), (yyvsp[-3].exp), (yyvsp[-1].exp) ); 
      SET_INFO((yyval.exp));

    }
#line 2676 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 1004 "../ccl-master/parser.y" /* yacc.c:1646  */
    {

      Expr * elambda = FUNC ( (yyvsp[-5].str), (yyvsp[-1].exp) );

      char buf[80];
      sprintf ( buf, "fmanglewahwah%d", foreach_index++ );

      Expr * body = 
        IFEXP ( 
	 BINEXP ( Expr::EQ, VAR("w"), EMPTY ),
	 EMPTY,
	 BINEXP ( 
             Expr::CONS, 
	     APP ( elambda, UNEXP ( Expr::HEAD, VAR("w") ) ),
             APP ( VAR(buf), UNEXP ( Expr::TAIL, VAR("w") ) ) 
           )
        );

      top_scope->add ( buf, new Value ( "w", body ) );
      top_scope->set_recursive ( buf );

      (yyval.exp) = APP ( VAR(buf), (yyvsp[-3].exp) );
      SET_INFO((yyval.exp));
      free ( (yyvsp[-5].str) );

    }
#line 2707 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 1031 "../ccl-master/parser.y" /* yacc.c:1646  */
    {

      EXTERNAL_CCLI_FUNCTION m2c = lookup_ccl_function ( "map_to_cells" );

      Expr * body = (yyvsp[-1].exp);

      std::list<char *> * fv = new std::list<char *>;
      std::list<char *>::iterator i;
      (yyvsp[-1].exp)->freevars ( fv );
      
      for ( i=fv->begin(); i!=fv->end(); i++ ) {
        body = FUNC ( *i, body );
      }

      TypeExpr * R = new TypeExpr();
      std::list<TypeExpr *> * Ta = new std::list<TypeExpr *>;
      Ta->push_back ( new TypeExpr () );

      std::list<Expr *> * args = new std::list<Expr *>;
      args->push_back ( body );

      (yyval.exp) = EAPP ( new Value ( m2c, R, Ta ), args );

    }
#line 2736 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 1060 "../ccl-master/parser.y" /* yacc.c:1646  */
    { 
      PUSH((yyvsp[-1].str)); 
      (yyval.str) = (yyvsp[-1].str);
    }
#line 2745 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 1068 "../ccl-master/parser.y" /* yacc.c:1646  */
    {

      (yyval.st_list) = (yyvsp[0].st_list);
      (yyval.st_list)->push_back ( new Statement ( new Command ( VAR ( (yyvsp[-3].str) ), (yyvsp[-2].exp) ) ) );

    }
#line 2756 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 1075 "../ccl-master/parser.y" /* yacc.c:1646  */
    {
 
      (yyval.st_list) = new std::list<Statement *>;
      (yyval.st_list)->push_front ( new Statement ( new Command ( VAR ( (yyvsp[-1].str) ), (yyvsp[0].exp) ) ) );

    }
#line 2767 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 1087 "../ccl-master/parser.y" /* yacc.c:1646  */
    {

      (yyval.elist) = (yyvsp[-2].elist);
      (yyval.elist)->push_back ( (yyvsp[0].exp) );

    }
#line 2778 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 1094 "../ccl-master/parser.y" /* yacc.c:1646  */
    { 

      (yyval.elist) = new std::list<Expr *>; 
      (yyval.elist)->push_back ( (yyvsp[0].exp) );

    }
#line 2789 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 1101 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.elist) = new std::list<Expr *>; }
#line 2795 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 1106 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = CONST ( (yyvsp[0].i) ); SET_INFO((yyval.exp)); }
#line 2801 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 1108 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = VAR ( (yyvsp[0].str) ); free((yyvsp[0].str)); SET_INFO((yyval.exp)); }
#line 2807 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 1109 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = CONST ( (yyvsp[0].real) ); SET_INFO((yyval.exp)); }
#line 2813 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 1110 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = CONST ( (yyvsp[0].str) ); SET_INFO((yyval.exp)); free ( (yyvsp[0].str) ); }
#line 2819 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 1111 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = CONST ( true ); SET_INFO((yyval.exp)); }
#line 2825 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 1112 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = CONST ( false ); SET_INFO((yyval.exp)); }
#line 2831 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 1113 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) = (yyvsp[-1].exp); SET_INFO((yyval.exp)); }
#line 2837 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 1117 "../ccl-master/parser.y" /* yacc.c:1646  */
    {

	std::list<Expr::FIELD *>::iterator i;

	(yyval.exp) = RECEXP;
	SET_INFO((yyval.exp));

	for ( i = (yyvsp[-1].field_list)->begin(); i != (yyvsp[-1].field_list)->end(); i++ ) {
	  (yyval.exp)->addField ( (*i)->name, (*i)->e );
	  free ( (*i)->name );
          delete *i;
	}

	delete (yyvsp[-1].field_list);

      }
#line 2858 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 1138 "../ccl-master/parser.y" /* yacc.c:1646  */
    {

      (yyval.exp) = BINEXP ( Expr::CONS, (yyvsp[-2].exp), (yyvsp[0].exp) );
      SET_INFO((yyval.exp));

    }
#line 2869 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 1145 "../ccl-master/parser.y" /* yacc.c:1646  */
    { 

       (yyval.exp) = BINEXP ( Expr::CONS, (yyvsp[0].exp), EMPTY ); 
       SET_INFO((yyval.exp));

    }
#line 2880 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 1152 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.exp) =  EMPTY; }
#line 2886 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 1158 "../ccl-master/parser.y" /* yacc.c:1646  */
    {
	(yyval.field_list) = (yyvsp[-4].field_list);
        Expr::FIELD * f = new Expr::FIELD;
	f->name = (yyvsp[-2].str);
	f->e = (yyvsp[0].exp);
	(yyval.field_list)->push_back ( f );
      }
#line 2898 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 1167 "../ccl-master/parser.y" /* yacc.c:1646  */
    {
        (yyval.field_list) = new std::list<Expr::FIELD *>; 
	Expr::FIELD * f = new Expr::FIELD;
	f->name = (yyvsp[-2].str);
	f->e = (yyvsp[0].exp);
        (yyval.field_list)->push_back ( f );
      }
#line 2910 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 1175 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.field_list) = new std::list<Expr::FIELD *>; }
#line 2916 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 1182 "../ccl-master/parser.y" /* yacc.c:1646  */
    {

      TypeExpr * T = RETRIEVE ( main_env, (yyvsp[0].str) );

      if ( T == NULL ) {

	PUSH ( (yyvsp[0].str) );
	(yyval.type) = main_env->get_type();

      } else 

	(yyval.type) = T;

      free ( (yyvsp[0].str) );

    }
#line 2937 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 1199 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.type) = new TypeExpr ( Value::UNIT ); }
#line 2943 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 1200 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.type) = new TypeExpr ( Value::BOOLEAN ); }
#line 2949 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 1201 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.type) = new TypeExpr ( Value::REAL ); }
#line 2955 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 1202 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.type) = new TypeExpr ( Value::INTEGER ); }
#line 2961 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 1203 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.type) = new TypeExpr ( Value::STRING ); }
#line 2967 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 1204 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.type) = new TypeExpr ( (yyvsp[-1].type) ); }
#line 2973 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 1205 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.type) = (yyvsp[-1].type); }
#line 2979 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 1206 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.type) = new TypeExpr ( true ); }
#line 2985 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 1207 "../ccl-master/parser.y" /* yacc.c:1646  */
    { rec_extensible_flag = false; }
#line 2991 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 1207 "../ccl-master/parser.y" /* yacc.c:1646  */
    { 
      (yyval.type) = new TypeExpr ( (yyvsp[-1].env) ); 
      (yyval.type)->set_extensibility ( rec_extensible_flag );
    }
#line 3000 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 1212 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.type) = (yyvsp[0].type); }
#line 3006 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 1220 "../ccl-master/parser.y" /* yacc.c:1646  */
    {

      (yyval.env) = new Environment ( (yyvsp[-4].str), (yyvsp[-2].type), (yyvsp[0].env) );
      free ( (yyvsp[-4].str) );

    }
#line 3017 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 1229 "../ccl-master/parser.y" /* yacc.c:1646  */
    {

      (yyval.env) = new Environment ( (yyvsp[-2].str), (yyvsp[0].type), NULL );
      free ( (yyvsp[-2].str) );

    }
#line 3028 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 1238 "../ccl-master/parser.y" /* yacc.c:1646  */
    {
      (yyval.env) = (yyvsp[0].env);
      rec_extensible_flag = true;
    }
#line 3037 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 1245 "../ccl-master/parser.y" /* yacc.c:1646  */
    {
      (yyval.env) = NULL;
      rec_extensible_flag = true;
    }
#line 3046 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 1250 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.env) = NULL; }
#line 3052 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 1256 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.type) = new TypeExpr ( (yyvsp[-2].type), (yyvsp[0].type) ); }
#line 3058 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 1264 "../ccl-master/parser.y" /* yacc.c:1646  */
    {

      (yyval.type_list) = (yyvsp[0].type_list);
      (yyval.type_list)->push_front ( (yyvsp[-2].type) );

    }
#line 3069 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 1273 "../ccl-master/parser.y" /* yacc.c:1646  */
    {

      (yyval.type_list) = new std::list<TypeExpr *>;
      (yyval.type_list)->push_back ( (yyvsp[0].type) );

    }
#line 3080 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 1280 "../ccl-master/parser.y" /* yacc.c:1646  */
    { (yyval.type_list) =  new std::list<TypeExpr *>; }
#line 3086 "../ccl-master/parser.cpp" /* yacc.c:1646  */
    break;


#line 3090 "../ccl-master/parser.cpp" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1284 "../ccl-master/parser.y" /* yacc.c:1906  */


int yyerror ( char * s ) { 

    std::stringstream strm;
    strm << s << ": near line " << lineNum[include_stack_ptr] << " of " << current_file_name[include_stack_ptr];

    throw ( strm.str() );

    return -1;

}

extern FILE * yyin;

extern void RegisterCCLInternals ( void );

int readOrganismProgram ( Scope * sc, const char * path ) {

  RegisterCCLInternals();

  int i;

  top_scope = sc;

  if ( path == NULL )
    path = strdup ( "(null)" );

  if ( ( yyin = fopen ( path, "r" ) ) == NULL ) {
    ERROR ( "gro is unable to open file named <i>" << path << "</i>" );
  }

  yyrestart ( yyin );

  include_stack_ptr = 0;

  for ( i=0; i<MAX_INCLUDE_DEPTH+1; i++ ) 
    lineNum[i] = 1;  

  current_file_name[0] = strdup ( path );

  try {
    i = yyparse();
  }

  catch ( std::string err ) {
     fclose ( yyin );
     throw err;
  }

  fclose ( yyin );

  while ( !ccl_function_list.empty() ) {
    delete ccl_function_list.front();
    ccl_function_list.pop_front();
  }

  return i;

}

void register_ccl_function ( std::string name, EXTERNAL_CCLI_FUNCTION f ) {

  InternalFunction * inf = new InternalFunction;

  inf->name = name;
  inf->f = f;

  ccl_function_list.push_back ( inf );

}

EXTERNAL_CCLI_FUNCTION lookup_ccl_function ( std::string name ) {

  std::list<InternalFunction *>::iterator i;

  for ( i = ccl_function_list.begin(); i != ccl_function_list.end(); i++ ) {

    if ( (*i)->name == name )
      return (*i)->f;
  }

  return NULL;

}
