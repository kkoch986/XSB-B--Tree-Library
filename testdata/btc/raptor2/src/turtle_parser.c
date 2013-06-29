/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse         turtle_parser_parse
#define yylex           turtle_parser_lex
#define yyerror         turtle_parser_error
#define yylval          turtle_parser_lval
#define yychar          turtle_parser_char
#define yydebug         turtle_parser_debug
#define yynerrs         turtle_parser_nerrs


/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 31 "./turtle_parser.y"

#ifdef HAVE_CONFIG_H
#include <raptor_config.h>
#endif

#ifdef WIN32
#include <win32_raptor_config.h>
#endif

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#ifdef HAVE_ERRNO_H
#include <errno.h>
#endif
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include "raptor2.h"
#include "raptor_internal.h"

#include <turtle_parser.h>

#define YY_DECL int turtle_lexer_lex (YYSTYPE *turtle_parser_lval, yyscan_t yyscanner)
#define YY_NO_UNISTD_H 1
#include <turtle_lexer.h>

#include <turtle_common.h>


/* Make verbose error messages for syntax errors */
#ifdef RAPTOR_DEBUG
#define YYERROR_VERBOSE 1
#endif

#ifdef RAPTOR_DEBUG
const char * turtle_token_print(raptor_world* world, int token, YYSTYPE *lval);
#endif



/* Slow down the grammar operation and watch it work */
#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 2
#define YYDEBUG 1
#endif

/* the lexer does not seem to track this */
#undef RAPTOR_TURTLE_USE_ERROR_COLUMNS

/* set api.push_pull to "push" if this is defined */
#undef TURTLE_PUSH_PARSE

/* Prototypes */ 
int turtle_parser_error(void* rdf_parser, const char *msg);

/* Missing turtle_lexer.c/h prototypes */
int turtle_lexer_get_column(yyscan_t yyscanner);
/* Not used here */
/* void turtle_lexer_set_column(int  column_no , yyscan_t yyscanner);*/


/* What the lexer wants */
extern int turtle_lexer_lex (YYSTYPE *turtle_parser_lval, yyscan_t scanner);

/* Make lex/yacc interface as small as possible */
#undef yylex
#define yylex turtle_lexer_lex
#define YYLEX_PARAM ((raptor_turtle_parser*)(((raptor_parser*)rdf_parser)->context))->scanner


/* Prototypes for local functions */
static void raptor_turtle_generate_statement(raptor_parser *parser, raptor_statement *triple);



/* Line 268 of yacc.c  */
#line 157 "turtle_parser.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     A = 258,
     AT = 259,
     HAT = 260,
     DOT = 261,
     COMMA = 262,
     SEMICOLON = 263,
     LEFT_SQUARE = 264,
     RIGHT_SQUARE = 265,
     LEFT_ROUND = 266,
     RIGHT_ROUND = 267,
     LEFT_CURLY = 268,
     RIGHT_CURLY = 269,
     TRUE_TOKEN = 270,
     FALSE_TOKEN = 271,
     PREFIX = 272,
     BASE = 273,
     STRING_LITERAL = 274,
     URI_LITERAL = 275,
     GRAPH_NAME_LEFT_CURLY = 276,
     BLANK_LITERAL = 277,
     QNAME_LITERAL = 278,
     IDENTIFIER = 279,
     INTEGER_LITERAL = 280,
     FLOATING_LITERAL = 281,
     DECIMAL_LITERAL = 282,
     ERROR_TOKEN = 283
   };
#endif
/* Tokens.  */
#define A 258
#define AT 259
#define HAT 260
#define DOT 261
#define COMMA 262
#define SEMICOLON 263
#define LEFT_SQUARE 264
#define RIGHT_SQUARE 265
#define LEFT_ROUND 266
#define RIGHT_ROUND 267
#define LEFT_CURLY 268
#define RIGHT_CURLY 269
#define TRUE_TOKEN 270
#define FALSE_TOKEN 271
#define PREFIX 272
#define BASE 273
#define STRING_LITERAL 274
#define URI_LITERAL 275
#define GRAPH_NAME_LEFT_CURLY 276
#define BLANK_LITERAL 277
#define QNAME_LITERAL 278
#define IDENTIFIER 279
#define INTEGER_LITERAL 280
#define FLOATING_LITERAL 281
#define DECIMAL_LITERAL 282
#define ERROR_TOKEN 283




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 122 "./turtle_parser.y"

  unsigned char *string;
  raptor_term *identifier;
  raptor_sequence *sequence;
  raptor_uri *uri;
  int integer; /* 0+ for a xsd:integer datatyped RDF literal */



/* Line 293 of yacc.c  */
#line 259 "turtle_parser.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 271 "turtle_parser.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   132

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  29
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  59
/* YYNRULES -- Number of states.  */
#define YYNSTATES  79

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   283

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
      25,    26,    27,    28
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     6,    11,    12,    17,    19,    20,
      22,    25,    27,    31,    34,    38,    39,    41,    43,    45,
      48,    51,    55,    57,    60,    62,    64,    66,    71,    74,
      77,    79,    81,    86,    90,    92,    94,    96,    98,   100,
     102,   106,   112,   118,   122,   126,   128,   130,   132,   134,
     136,   138,   140,   142,   144,   145,   147,   151,   153,   157
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      30,     0,    -1,    37,    -1,    -1,    21,    32,    34,    14,
      -1,    -1,    13,    33,    34,    14,    -1,    35,    -1,    -1,
      36,    -1,    36,     6,    -1,    39,    -1,    36,     6,    39,
      -1,    37,    38,    -1,    37,    38,     6,    -1,    -1,    44,
      -1,    31,    -1,    39,    -1,    47,    43,    -1,     1,     6,
      -1,    40,     7,    49,    -1,    49,    -1,    41,    49,    -1,
      49,    -1,    48,    -1,     3,    -1,    43,     8,    42,    40,
      -1,    42,    40,    -1,    43,     8,    -1,    45,    -1,    46,
      -1,    17,    24,    20,     6,    -1,    18,    20,     6,    -1,
      51,    -1,    53,    -1,    51,    -1,    51,    -1,    53,    -1,
      50,    -1,    19,     4,    24,    -1,    19,     4,    24,     5,
      20,    -1,    19,     4,    24,     5,    23,    -1,    19,     5,
      20,    -1,    19,     5,    23,    -1,    19,    -1,    25,    -1,
      26,    -1,    27,    -1,    15,    -1,    16,    -1,    20,    -1,
      23,    -1,    43,    -1,    -1,    22,    -1,     9,    52,    10,
      -1,    54,    -1,    11,    41,    12,    -1,    11,    12,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   193,   193,   198,   197,   230,   229,   257,   258,   262,
     263,   266,   267,   270,   271,   272,   275,   276,   277,   280,
     321,   325,   365,   409,   449,   493,   503,   516,   577,   609,
     620,   620,   623,   660,   671,   675,   682,   689,   693,   697,
     710,   723,   747,   771,   788,   804,   816,   834,   852,   870,
     885,   903,   917,   934,   939,   944,   961,  1012,  1019,  1121
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "\"a\"", "\"@\"", "\"^\"", "\".\"",
  "\",\"", "\";\"", "\"[\"", "\"]\"", "\"(\"", "\")\"", "\"{\"", "\"}\"",
  "\"true\"", "\"false\"", "\"@prefix\"", "\"@base\"",
  "\"string literal\"", "\"URI literal\"", "\"Graph URI literal {\"",
  "\"blank node\"", "\"QName\"", "\"identifier\"", "\"integer literal\"",
  "\"floating point literal\"", "\"decimal literal\"", "ERROR_TOKEN",
  "$accept", "Document", "graph", "$@1", "$@2", "graphBody", "triplesList",
  "dotTriplesList", "statementList", "statement", "triples", "objectList",
  "itemList", "verb", "propertyList", "directive", "prefix", "base",
  "subject", "predicate", "object", "literal", "resource",
  "propertyListOpt", "blank", "collection", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    29,    30,    32,    31,    33,    31,    34,    34,    35,
      35,    36,    36,    37,    37,    37,    38,    38,    38,    39,
      39,    40,    40,    41,    41,    42,    42,    43,    43,    43,
      44,    44,    45,    46,    47,    47,    48,    49,    49,    49,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    51,    51,    52,    52,    53,    53,    53,    54,    54
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     4,     0,     4,     1,     0,     1,
       2,     1,     3,     2,     3,     0,     1,     1,     1,     2,
       2,     3,     1,     2,     1,     1,     1,     4,     2,     2,
       1,     1,     4,     3,     1,     1,     1,     1,     1,     1,
       3,     5,     5,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     1,     3,     1,     3,     2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      15,     0,     0,     1,     0,    54,     0,     5,     0,     0,
      51,     3,    55,    52,    17,    13,    18,    16,    30,    31,
       0,    34,    35,    57,    20,    26,     0,    53,    25,    36,
       0,    59,    49,    50,    45,    46,    47,    48,     0,    24,
      39,    37,    38,     0,     0,     0,     0,    14,    19,    28,
      22,    29,    56,     0,     0,    58,    23,     0,     7,     9,
      11,     0,    33,     0,     0,     0,    40,    43,    44,     6,
       0,    32,     4,    21,    27,     0,    12,    41,    42
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,    14,    46,    43,    57,    58,    59,     2,    15,
      60,    49,    38,    26,    27,    17,    18,    19,    20,    28,
      50,    40,    41,    30,    42,    23
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -15
static const yytype_int8 yypact[] =
{
     -15,    10,     4,   -15,     2,     8,    67,   -15,   -12,    -6,
     -15,   -15,   -15,   -15,   -15,    14,   -15,   -15,   -15,   -15,
       8,   -15,   -15,   -15,   -15,   -15,   105,    15,   -15,   -15,
      22,   -15,   -15,   -15,    25,   -15,   -15,   -15,    86,   -15,
     -15,   -15,   -15,    37,    13,    28,    37,   -15,    15,    29,
     -15,     8,   -15,    11,   -14,   -15,   -15,    23,   -15,    34,
     -15,    41,   -15,    36,   105,   105,    38,   -15,   -15,   -15,
      52,   -15,   -15,   -15,    29,    -4,   -15,   -15,   -15
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -15,   -15,   -15,   -15,   -15,     6,   -15,   -15,   -15,   -15,
       0,   -11,   -15,     5,    35,   -15,   -15,   -15,   -15,   -15,
       1,   -15,    -2,   -15,    -1,   -15
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -11
static const yytype_int8 yytable[] =
{
      21,    22,    16,    29,    -2,     4,    67,    39,    24,    68,
       3,    25,    44,     5,    45,     6,    77,     7,    29,    78,
      47,     8,     9,    51,    10,    11,    12,    13,    10,    53,
      54,    13,    52,    61,    62,    66,    64,    69,     4,    56,
      70,    21,    22,    75,    21,    22,     5,    71,     6,    29,
      72,    -8,    63,     4,    74,    48,    65,    10,     0,    12,
      13,     5,     0,     6,     0,    73,   -10,     0,    21,    22,
      76,     0,    10,     0,    12,    13,     5,     0,     6,    31,
       0,     0,    32,    33,     0,     0,    34,    10,     0,    12,
      13,     0,    35,    36,    37,     5,     0,     6,    55,     0,
       0,    32,    33,     0,     0,    34,    10,     0,    12,    13,
       0,    35,    36,    37,     5,     0,     6,     0,     0,     0,
      32,    33,     0,     0,    34,    10,     0,    12,    13,     0,
      35,    36,    37
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-15))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
       2,     2,     2,     5,     0,     1,    20,     6,     6,    23,
       0,     3,    24,     9,    20,    11,    20,    13,    20,    23,
       6,    17,    18,     8,    20,    21,    22,    23,    20,     4,
       5,    23,    10,    20,     6,    24,     7,    14,     1,    38,
       6,    43,    43,     5,    46,    46,     9,     6,    11,    51,
      14,    14,    46,     1,    65,    20,    51,    20,    -1,    22,
      23,     9,    -1,    11,    -1,    64,    14,    -1,    70,    70,
      70,    -1,    20,    -1,    22,    23,     9,    -1,    11,    12,
      -1,    -1,    15,    16,    -1,    -1,    19,    20,    -1,    22,
      23,    -1,    25,    26,    27,     9,    -1,    11,    12,    -1,
      -1,    15,    16,    -1,    -1,    19,    20,    -1,    22,    23,
      -1,    25,    26,    27,     9,    -1,    11,    -1,    -1,    -1,
      15,    16,    -1,    -1,    19,    20,    -1,    22,    23,    -1,
      25,    26,    27
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    30,    37,     0,     1,     9,    11,    13,    17,    18,
      20,    21,    22,    23,    31,    38,    39,    44,    45,    46,
      47,    51,    53,    54,     6,     3,    42,    43,    48,    51,
      52,    12,    15,    16,    19,    25,    26,    27,    41,    49,
      50,    51,    53,    33,    24,    20,    32,     6,    43,    40,
      49,     8,    10,     4,     5,    12,    49,    34,    35,    36,
      39,    20,     6,    34,     7,    42,    24,    20,    23,    14,
       6,     6,    14,    49,    40,     5,    39,    20,    23
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (rdf_parser, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, rdf_parser); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, raptor_parser* rdf_parser)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, rdf_parser)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    raptor_parser* rdf_parser;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (rdf_parser);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, raptor_parser* rdf_parser)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, rdf_parser)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    raptor_parser* rdf_parser;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, rdf_parser);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, raptor_parser* rdf_parser)
#else
static void
yy_reduce_print (yyvsp, yyrule, rdf_parser)
    YYSTYPE *yyvsp;
    int yyrule;
    raptor_parser* rdf_parser;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       , rdf_parser);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, rdf_parser); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
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

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, raptor_parser* rdf_parser)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, rdf_parser)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    raptor_parser* rdf_parser;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (rdf_parser);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {
      case 19: /* "\"string literal\"" */

/* Line 1391 of yacc.c  */
#line 171 "./turtle_parser.y"
	{
  if((yyvaluep->string))
    RAPTOR_FREE(char*, (yyvaluep->string));
};

/* Line 1391 of yacc.c  */
#line 1293 "turtle_parser.c"
	break;
      case 20: /* "\"URI literal\"" */

/* Line 1391 of yacc.c  */
#line 176 "./turtle_parser.y"
	{
  if((yyvaluep->uri))
    raptor_free_uri((yyvaluep->uri));
};

/* Line 1391 of yacc.c  */
#line 1305 "turtle_parser.c"
	break;
      case 22: /* "\"blank node\"" */

/* Line 1391 of yacc.c  */
#line 171 "./turtle_parser.y"
	{
  if((yyvaluep->string))
    RAPTOR_FREE(char*, (yyvaluep->string));
};

/* Line 1391 of yacc.c  */
#line 1317 "turtle_parser.c"
	break;
      case 23: /* "\"QName\"" */

/* Line 1391 of yacc.c  */
#line 176 "./turtle_parser.y"
	{
  if((yyvaluep->uri))
    raptor_free_uri((yyvaluep->uri));
};

/* Line 1391 of yacc.c  */
#line 1329 "turtle_parser.c"
	break;
      case 24: /* "\"identifier\"" */

/* Line 1391 of yacc.c  */
#line 171 "./turtle_parser.y"
	{
  if((yyvaluep->string))
    RAPTOR_FREE(char*, (yyvaluep->string));
};

/* Line 1391 of yacc.c  */
#line 1341 "turtle_parser.c"
	break;
      case 25: /* "\"integer literal\"" */

/* Line 1391 of yacc.c  */
#line 171 "./turtle_parser.y"
	{
  if((yyvaluep->string))
    RAPTOR_FREE(char*, (yyvaluep->string));
};

/* Line 1391 of yacc.c  */
#line 1353 "turtle_parser.c"
	break;
      case 26: /* "\"floating point literal\"" */

/* Line 1391 of yacc.c  */
#line 171 "./turtle_parser.y"
	{
  if((yyvaluep->string))
    RAPTOR_FREE(char*, (yyvaluep->string));
};

/* Line 1391 of yacc.c  */
#line 1365 "turtle_parser.c"
	break;
      case 27: /* "\"decimal literal\"" */

/* Line 1391 of yacc.c  */
#line 171 "./turtle_parser.y"
	{
  if((yyvaluep->string))
    RAPTOR_FREE(char*, (yyvaluep->string));
};

/* Line 1391 of yacc.c  */
#line 1377 "turtle_parser.c"
	break;
      case 40: /* "objectList" */

/* Line 1391 of yacc.c  */
#line 186 "./turtle_parser.y"
	{
  if((yyvaluep->sequence))
    raptor_free_sequence((yyvaluep->sequence));
};

/* Line 1391 of yacc.c  */
#line 1389 "turtle_parser.c"
	break;
      case 41: /* "itemList" */

/* Line 1391 of yacc.c  */
#line 186 "./turtle_parser.y"
	{
  if((yyvaluep->sequence))
    raptor_free_sequence((yyvaluep->sequence));
};

/* Line 1391 of yacc.c  */
#line 1401 "turtle_parser.c"
	break;
      case 42: /* "verb" */

/* Line 1391 of yacc.c  */
#line 181 "./turtle_parser.y"
	{
  if((yyvaluep->identifier))
    raptor_free_term((yyvaluep->identifier));
};

/* Line 1391 of yacc.c  */
#line 1413 "turtle_parser.c"
	break;
      case 43: /* "propertyList" */

/* Line 1391 of yacc.c  */
#line 186 "./turtle_parser.y"
	{
  if((yyvaluep->sequence))
    raptor_free_sequence((yyvaluep->sequence));
};

/* Line 1391 of yacc.c  */
#line 1425 "turtle_parser.c"
	break;
      case 47: /* "subject" */

/* Line 1391 of yacc.c  */
#line 181 "./turtle_parser.y"
	{
  if((yyvaluep->identifier))
    raptor_free_term((yyvaluep->identifier));
};

/* Line 1391 of yacc.c  */
#line 1437 "turtle_parser.c"
	break;
      case 48: /* "predicate" */

/* Line 1391 of yacc.c  */
#line 181 "./turtle_parser.y"
	{
  if((yyvaluep->identifier))
    raptor_free_term((yyvaluep->identifier));
};

/* Line 1391 of yacc.c  */
#line 1449 "turtle_parser.c"
	break;
      case 49: /* "object" */

/* Line 1391 of yacc.c  */
#line 181 "./turtle_parser.y"
	{
  if((yyvaluep->identifier))
    raptor_free_term((yyvaluep->identifier));
};

/* Line 1391 of yacc.c  */
#line 1461 "turtle_parser.c"
	break;
      case 50: /* "literal" */

/* Line 1391 of yacc.c  */
#line 181 "./turtle_parser.y"
	{
  if((yyvaluep->identifier))
    raptor_free_term((yyvaluep->identifier));
};

/* Line 1391 of yacc.c  */
#line 1473 "turtle_parser.c"
	break;
      case 51: /* "resource" */

/* Line 1391 of yacc.c  */
#line 181 "./turtle_parser.y"
	{
  if((yyvaluep->identifier))
    raptor_free_term((yyvaluep->identifier));
};

/* Line 1391 of yacc.c  */
#line 1485 "turtle_parser.c"
	break;
      case 52: /* "propertyListOpt" */

/* Line 1391 of yacc.c  */
#line 186 "./turtle_parser.y"
	{
  if((yyvaluep->sequence))
    raptor_free_sequence((yyvaluep->sequence));
};

/* Line 1391 of yacc.c  */
#line 1497 "turtle_parser.c"
	break;
      case 53: /* "blank" */

/* Line 1391 of yacc.c  */
#line 181 "./turtle_parser.y"
	{
  if((yyvaluep->identifier))
    raptor_free_term((yyvaluep->identifier));
};

/* Line 1391 of yacc.c  */
#line 1509 "turtle_parser.c"
	break;
      case 54: /* "collection" */

/* Line 1391 of yacc.c  */
#line 181 "./turtle_parser.y"
	{
  if((yyvaluep->identifier))
    raptor_free_term((yyvaluep->identifier));
};

/* Line 1391 of yacc.c  */
#line 1521 "turtle_parser.c"
	break;

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (raptor_parser* rdf_parser);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (raptor_parser* rdf_parser)
#else
int
yyparse (rdf_parser)
    raptor_parser* rdf_parser;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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
      yychar = YYLEX;
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
  *++yyvsp = yylval;

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
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:

/* Line 1806 of yacc.c  */
#line 198 "./turtle_parser.y"
    {
    /* action in mid-rule so this is run BEFORE the triples in graphBody */
    raptor_parser* parser = (raptor_parser *)rdf_parser;
    raptor_turtle_parser* turtle_parser;

    turtle_parser = (raptor_turtle_parser*)parser->context;
    if(!turtle_parser->trig)
      turtle_parser_error(rdf_parser, "{ ... } is not allowed in Turtle");
    else {
      if(turtle_parser->graph_name)
        raptor_free_term(turtle_parser->graph_name);
      turtle_parser->graph_name = raptor_new_term_from_uri(((raptor_parser*)rdf_parser)->world, (yyvsp[(1) - (1)].uri));
      raptor_free_uri((yyvsp[(1) - (1)].uri));
      raptor_parser_start_graph(parser, turtle_parser->graph_name->value.uri, 1);
    }
  }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 215 "./turtle_parser.y"
    {
  raptor_parser* parser = (raptor_parser *)rdf_parser;
  raptor_turtle_parser* turtle_parser;

  turtle_parser = (raptor_turtle_parser*)parser->context;

  if(turtle_parser->trig) {
    raptor_parser_end_graph(parser, turtle_parser->graph_name->value.uri, 1);
    raptor_free_term(turtle_parser->graph_name);
    turtle_parser->graph_name = NULL;
    parser->emitted_default_graph = 0;
  }
}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 230 "./turtle_parser.y"
    {
    /* action in mid-rule so this is run BEFORE the triples in graphBody */
    raptor_parser* parser = (raptor_parser *)rdf_parser;
    raptor_turtle_parser* turtle_parser;

    turtle_parser = (raptor_turtle_parser*)parser->context;
    if(!turtle_parser->trig)
      turtle_parser_error(rdf_parser, "{ ... } is not allowed in Turtle");
    else {
      raptor_parser_start_graph(parser, NULL, 1);
      parser->emitted_default_graph++;
    }
  }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 244 "./turtle_parser.y"
    {
  raptor_parser* parser = (raptor_parser *)rdf_parser;
  raptor_turtle_parser* turtle_parser;

  turtle_parser = (raptor_turtle_parser*)parser->context;
  if(turtle_parser->trig) {
    raptor_parser_end_graph(parser, NULL, 1);
    parser->emitted_default_graph = 0;
  }
}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 281 "./turtle_parser.y"
    {
  int i;

#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
  printf("statement 2\n subject=");
  if((yyvsp[(1) - (2)].identifier))
    raptor_term_print_as_ntriples((yyvsp[(1) - (2)].identifier), stdout);
  else
    fputs("NULL", stdout);
  if((yyvsp[(2) - (2)].sequence)) {
    printf("\n propertyList (reverse order to syntax)=");
    raptor_sequence_print((yyvsp[(2) - (2)].sequence), stdout);
    printf("\n");
  } else     
    printf("\n and empty propertyList\n");
#endif

  if((yyvsp[(1) - (2)].identifier) && (yyvsp[(2) - (2)].sequence)) {
    /* have subject and non-empty property list, handle it  */
    for(i = 0; i < raptor_sequence_size((yyvsp[(2) - (2)].sequence)); i++) {
      raptor_statement* t2 = (raptor_statement*)raptor_sequence_get_at((yyvsp[(2) - (2)].sequence), i);
      t2->subject = raptor_term_copy((yyvsp[(1) - (2)].identifier));
    }
#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
    printf(" after substitution propertyList=");
    raptor_sequence_print((yyvsp[(2) - (2)].sequence), stdout);
    printf("\n\n");
#endif
    for(i = 0; i < raptor_sequence_size((yyvsp[(2) - (2)].sequence)); i++) {
      raptor_statement* t2 = (raptor_statement*)raptor_sequence_get_at((yyvsp[(2) - (2)].sequence), i);
      raptor_turtle_generate_statement((raptor_parser*)rdf_parser, t2);
    }
  }

  if((yyvsp[(2) - (2)].sequence))
    raptor_free_sequence((yyvsp[(2) - (2)].sequence));

  if((yyvsp[(1) - (2)].identifier))
    raptor_free_term((yyvsp[(1) - (2)].identifier));
}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 326 "./turtle_parser.y"
    {
  raptor_statement *triple;

#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
  printf("objectList 1\n");
  if((yyvsp[(3) - (3)].identifier)) {
    printf(" object=\n");
    raptor_term_print_as_ntriples((yyvsp[(3) - (3)].identifier), stdout);
    printf("\n");
  } else  
    printf(" and empty object\n");
  if((yyvsp[(1) - (3)].sequence)) {
    printf(" objectList=");
    raptor_sequence_print((yyvsp[(1) - (3)].sequence), stdout);
    printf("\n");
  } else
    printf(" and empty objectList\n");
#endif

  if(!(yyvsp[(3) - (3)].identifier))
    (yyval.sequence) = NULL;
  else {
    triple = raptor_new_statement_from_nodes(((raptor_parser*)rdf_parser)->world, NULL, NULL, (yyvsp[(3) - (3)].identifier), NULL);
    if(!triple) {
      raptor_free_sequence((yyvsp[(1) - (3)].sequence));
      YYERROR;
    }
    if(raptor_sequence_push((yyvsp[(1) - (3)].sequence), triple)) {
      raptor_free_sequence((yyvsp[(1) - (3)].sequence));
      YYERROR;
    }
    (yyval.sequence) = (yyvsp[(1) - (3)].sequence);
#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
    printf(" objectList is now ");
    raptor_sequence_print((yyval.sequence), stdout);
    printf("\n\n");
#endif
  }
}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 366 "./turtle_parser.y"
    {
  raptor_statement *triple;

#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
  printf("objectList 2\n");
  if((yyvsp[(1) - (1)].identifier)) {
    printf(" object=\n");
    raptor_term_print_as_ntriples((yyvsp[(1) - (1)].identifier), stdout);
    printf("\n");
  } else  
    printf(" and empty object\n");
#endif

  if(!(yyvsp[(1) - (1)].identifier))
    (yyval.sequence) = NULL;
  else {
    triple = raptor_new_statement_from_nodes(((raptor_parser*)rdf_parser)->world, NULL, NULL, (yyvsp[(1) - (1)].identifier), NULL);
    if(!triple)
      YYERROR;
#ifdef RAPTOR_DEBUG
    (yyval.sequence) = raptor_new_sequence((raptor_data_free_handler)raptor_free_statement,
                             (raptor_data_print_handler)raptor_statement_print);
#else
    (yyval.sequence) = raptor_new_sequence((raptor_data_free_handler)raptor_free_statement, NULL);
#endif
    if(!(yyval.sequence)) {
      raptor_free_statement(triple);
      YYERROR;
    }
    if(raptor_sequence_push((yyval.sequence), triple)) {
      raptor_free_sequence((yyval.sequence));
      (yyval.sequence) = NULL;
      YYERROR;
    }
#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
    printf(" objectList is now ");
    raptor_sequence_print((yyval.sequence), stdout);
    printf("\n\n");
#endif
  }
}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 410 "./turtle_parser.y"
    {
  raptor_statement *triple;

#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
  printf("objectList 1\n");
  if((yyvsp[(2) - (2)].identifier)) {
    printf(" object=\n");
    raptor_term_print_as_ntriples((yyvsp[(2) - (2)].identifier), stdout);
    printf("\n");
  } else  
    printf(" and empty object\n");
  if((yyvsp[(1) - (2)].sequence)) {
    printf(" objectList=");
    raptor_sequence_print((yyvsp[(1) - (2)].sequence), stdout);
    printf("\n");
  } else
    printf(" and empty objectList\n");
#endif

  if(!(yyvsp[(2) - (2)].identifier))
    (yyval.sequence) = NULL;
  else {
    triple = raptor_new_statement_from_nodes(((raptor_parser*)rdf_parser)->world, NULL, NULL, (yyvsp[(2) - (2)].identifier), NULL);
    if(!triple) {
      raptor_free_sequence((yyvsp[(1) - (2)].sequence));
      YYERROR;
    }
    if(raptor_sequence_push((yyvsp[(1) - (2)].sequence), triple)) {
      raptor_free_sequence((yyvsp[(1) - (2)].sequence));
      YYERROR;
    }
    (yyval.sequence) = (yyvsp[(1) - (2)].sequence);
#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
    printf(" objectList is now ");
    raptor_sequence_print((yyval.sequence), stdout);
    printf("\n\n");
#endif
  }
}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 450 "./turtle_parser.y"
    {
  raptor_statement *triple;

#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
  printf("objectList 2\n");
  if((yyvsp[(1) - (1)].identifier)) {
    printf(" object=\n");
    raptor_term_print_as_ntriples((yyvsp[(1) - (1)].identifier), stdout);
    printf("\n");
  } else  
    printf(" and empty object\n");
#endif

  if(!(yyvsp[(1) - (1)].identifier))
    (yyval.sequence) = NULL;
  else {
    triple = raptor_new_statement_from_nodes(((raptor_parser*)rdf_parser)->world, NULL, NULL, (yyvsp[(1) - (1)].identifier), NULL);
    if(!triple)
      YYERROR;
#ifdef RAPTOR_DEBUG
    (yyval.sequence) = raptor_new_sequence((raptor_data_free_handler)raptor_free_statement,
                             (raptor_data_print_handler)raptor_statement_print);
#else
    (yyval.sequence) = raptor_new_sequence((raptor_data_free_handler)raptor_free_statement, NULL);
#endif
    if(!(yyval.sequence)) {
      raptor_free_statement(triple);
      YYERROR;
    }
    if(raptor_sequence_push((yyval.sequence), triple)) {
      raptor_free_sequence((yyval.sequence));
      (yyval.sequence) = NULL;
      YYERROR;
    }
#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
    printf(" objectList is now ");
    raptor_sequence_print((yyval.sequence), stdout);
    printf("\n\n");
#endif
  }
}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 494 "./turtle_parser.y"
    {
#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
  printf("verb predicate=");
  raptor_term_print_as_ntriples((yyvsp[(1) - (1)].identifier), stdout);
  printf("\n");
#endif

  (yyval.identifier) = (yyvsp[(1) - (1)].identifier);
}
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 504 "./turtle_parser.y"
    {
#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
  printf("verb predicate = rdf:type (a)\n");
#endif

  (yyval.identifier) = raptor_term_copy(RAPTOR_RDF_type_term(((raptor_parser*)rdf_parser)->world));
  if(!(yyval.identifier))
    YYERROR;
}
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 517 "./turtle_parser.y"
    {
  int i;
  
#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
  printf("propertyList 1\n verb=");
  raptor_term_print_as_ntriples((yyvsp[(3) - (4)].identifier), stdout);
  printf("\n objectList=");
  raptor_sequence_print((yyvsp[(4) - (4)].sequence), stdout);
  printf("\n propertyList=");
  raptor_sequence_print((yyvsp[(1) - (4)].sequence), stdout);
  printf("\n\n");
#endif
  
  if((yyvsp[(4) - (4)].sequence) == NULL) {
#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
    printf(" empty objectList not processed\n");
#endif
  } else if((yyvsp[(3) - (4)].identifier) && (yyvsp[(4) - (4)].sequence)) {
    /* non-empty property list, handle it  */
    for(i = 0; i < raptor_sequence_size((yyvsp[(4) - (4)].sequence)); i++) {
      raptor_statement* t2 = (raptor_statement*)raptor_sequence_get_at((yyvsp[(4) - (4)].sequence), i);
      t2->predicate = raptor_term_copy((yyvsp[(3) - (4)].identifier));
    }
  
#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
    printf(" after substitution objectList=");
    raptor_sequence_print((yyvsp[(4) - (4)].sequence), stdout);
    printf("\n");
#endif
  }

  if((yyvsp[(1) - (4)].sequence) == NULL) {
#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
    printf(" empty propertyList not copied\n\n");
#endif
  } else if((yyvsp[(3) - (4)].identifier) && (yyvsp[(4) - (4)].sequence) && (yyvsp[(1) - (4)].sequence)) {
    while(raptor_sequence_size((yyvsp[(4) - (4)].sequence))) {
      raptor_statement* t2 = (raptor_statement*)raptor_sequence_unshift((yyvsp[(4) - (4)].sequence));
      if(raptor_sequence_push((yyvsp[(1) - (4)].sequence), t2)) {
        raptor_free_sequence((yyvsp[(1) - (4)].sequence));
        raptor_free_term((yyvsp[(3) - (4)].identifier));
        raptor_free_sequence((yyvsp[(4) - (4)].sequence));
        YYERROR;
      }
    }

#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
    printf(" after appending objectList (reverse order)=");
    raptor_sequence_print((yyvsp[(1) - (4)].sequence), stdout);
    printf("\n\n");
#endif

    raptor_free_sequence((yyvsp[(4) - (4)].sequence));
  }

  if((yyvsp[(3) - (4)].identifier))
    raptor_free_term((yyvsp[(3) - (4)].identifier));

  (yyval.sequence) = (yyvsp[(1) - (4)].sequence);
}
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 578 "./turtle_parser.y"
    {
  int i;
#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
  printf("propertyList 2\n verb=");
  raptor_term_print_as_ntriples((yyvsp[(1) - (2)].identifier), stdout);
  if((yyvsp[(2) - (2)].sequence)) {
    printf("\n objectList=");
    raptor_sequence_print((yyvsp[(2) - (2)].sequence), stdout);
    printf("\n");
  } else
    printf("\n and empty objectList\n");
#endif

  if((yyvsp[(1) - (2)].identifier) && (yyvsp[(2) - (2)].sequence)) {
    for(i = 0; i < raptor_sequence_size((yyvsp[(2) - (2)].sequence)); i++) {
      raptor_statement* t2 = (raptor_statement*)raptor_sequence_get_at((yyvsp[(2) - (2)].sequence), i);
      t2->predicate = raptor_term_copy((yyvsp[(1) - (2)].identifier));
    }

#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
    printf(" after substitution objectList=");
    raptor_sequence_print((yyvsp[(2) - (2)].sequence), stdout);
    printf("\n\n");
#endif
  }

  if((yyvsp[(1) - (2)].identifier))
    raptor_free_term((yyvsp[(1) - (2)].identifier));

  (yyval.sequence) = (yyvsp[(2) - (2)].sequence);
}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 610 "./turtle_parser.y"
    {
  (yyval.sequence) = (yyvsp[(1) - (2)].sequence);
#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
  printf("propertyList 5\n trailing semicolon returning existing list ");
  raptor_sequence_print((yyval.sequence), stdout);
  printf("\n\n");
#endif
}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 624 "./turtle_parser.y"
    {
  unsigned char *prefix = (yyvsp[(2) - (4)].string);
  raptor_turtle_parser* turtle_parser = (raptor_turtle_parser*)(((raptor_parser*)rdf_parser)->context);
  raptor_namespace *ns;

#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
  printf("directive @prefix %s %s\n",((yyvsp[(2) - (4)].string) ? (char*)(yyvsp[(2) - (4)].string) : "(default)"), raptor_uri_as_string((yyvsp[(3) - (4)].uri)));
#endif

  if(prefix) {
    size_t len = strlen((const char*)prefix);
    if(prefix[len-1] == ':') {
      if(len == 1)
         /* declaring default namespace prefix @prefix : ... */
        prefix = NULL;
      else
        prefix[len-1]='\0';
    }
  }

  ns = raptor_new_namespace_from_uri(&turtle_parser->namespaces, prefix, (yyvsp[(3) - (4)].uri), 0);
  if(ns) {
    raptor_namespaces_start_namespace(&turtle_parser->namespaces, ns);
    raptor_parser_start_namespace((raptor_parser*)rdf_parser, ns);
  }

  if((yyvsp[(2) - (4)].string))
    RAPTOR_FREE(char*, (yyvsp[(2) - (4)].string));
  raptor_free_uri((yyvsp[(3) - (4)].uri));

  if(!ns)
    YYERROR;
}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 661 "./turtle_parser.y"
    {
  raptor_uri *uri=(yyvsp[(2) - (3)].uri);
  /*raptor_turtle_parser* turtle_parser = (raptor_turtle_parser*)(((raptor_parser*)rdf_parser)->context);*/
  raptor_parser* parser = (raptor_parser*)rdf_parser;
  if(parser->base_uri)
    raptor_free_uri(parser->base_uri);
  parser->base_uri = uri;
}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 672 "./turtle_parser.y"
    {
  (yyval.identifier) = (yyvsp[(1) - (1)].identifier);
}
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 676 "./turtle_parser.y"
    {
  (yyval.identifier) = (yyvsp[(1) - (1)].identifier);
}
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 683 "./turtle_parser.y"
    {
  (yyval.identifier) = (yyvsp[(1) - (1)].identifier);
}
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 690 "./turtle_parser.y"
    {
  (yyval.identifier) = (yyvsp[(1) - (1)].identifier);
}
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 694 "./turtle_parser.y"
    {
  (yyval.identifier) = (yyvsp[(1) - (1)].identifier);
}
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 698 "./turtle_parser.y"
    {
#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
  printf("object literal=");
  raptor_term_print_as_ntriples((yyvsp[(1) - (1)].identifier), stdout);
  printf("\n");
#endif

  (yyval.identifier) = (yyvsp[(1) - (1)].identifier);
}
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 711 "./turtle_parser.y"
    {
#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
  printf("literal + language string=\"%s\"\n", (yyvsp[(1) - (3)].string));
#endif

  (yyval.identifier) = raptor_new_term_from_literal(((raptor_parser*)rdf_parser)->world,
                                    (yyvsp[(1) - (3)].string), NULL, (yyvsp[(3) - (3)].string));
  RAPTOR_FREE(char*, (yyvsp[(1) - (3)].string));
  RAPTOR_FREE(char*, (yyvsp[(3) - (3)].string));
  if(!(yyval.identifier))
    YYERROR;
}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 724 "./turtle_parser.y"
    {
#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
  printf("literal + language=\"%s\" datatype string=\"%s\" uri=\"%s\"\n", (yyvsp[(1) - (5)].string), (yyvsp[(3) - (5)].string), raptor_uri_as_string((yyvsp[(5) - (5)].uri)));
#endif

  if((yyvsp[(5) - (5)].uri)) {
    if((yyvsp[(3) - (5)].string)) {
      raptor_parser_warning((raptor_parser*)rdf_parser, 
                            "Ignoring language used with datatyped literal");
      RAPTOR_FREE(char*, (yyvsp[(3) - (5)].string));
      (yyvsp[(3) - (5)].string) = NULL;
    }
  
    (yyval.identifier) = raptor_new_term_from_literal(((raptor_parser*)rdf_parser)->world,
                                      (yyvsp[(1) - (5)].string), (yyvsp[(5) - (5)].uri), NULL);
    RAPTOR_FREE(char*, (yyvsp[(1) - (5)].string));
    raptor_free_uri((yyvsp[(5) - (5)].uri));
    if(!(yyval.identifier))
      YYERROR;
  } else
    (yyval.identifier) = NULL;
    
}
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 748 "./turtle_parser.y"
    {
#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
  printf("literal + language=\"%s\" datatype string=\"%s\" qname URI=<%s>\n", (yyvsp[(1) - (5)].string), (yyvsp[(3) - (5)].string), raptor_uri_as_string((yyvsp[(5) - (5)].uri)));
#endif

  if((yyvsp[(5) - (5)].uri)) {
    if((yyvsp[(3) - (5)].string)) {
      raptor_parser_warning((raptor_parser*)rdf_parser, 
                            "Ignoring language used with datatyped literal");
      RAPTOR_FREE(char*, (yyvsp[(3) - (5)].string));
      (yyvsp[(3) - (5)].string) = NULL;
    }
  
    (yyval.identifier) = raptor_new_term_from_literal(((raptor_parser*)rdf_parser)->world,
                                      (yyvsp[(1) - (5)].string), (yyvsp[(5) - (5)].uri), NULL);
    RAPTOR_FREE(char*, (yyvsp[(1) - (5)].string));
    raptor_free_uri((yyvsp[(5) - (5)].uri));
    if(!(yyval.identifier))
      YYERROR;
  } else
    (yyval.identifier) = NULL;

}
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 772 "./turtle_parser.y"
    {
#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
  printf("literal + datatype string=\"%s\" uri=\"%s\"\n", (yyvsp[(1) - (3)].string), raptor_uri_as_string((yyvsp[(3) - (3)].uri)));
#endif

  if((yyvsp[(3) - (3)].uri)) {
    (yyval.identifier) = raptor_new_term_from_literal(((raptor_parser*)rdf_parser)->world,
                                      (yyvsp[(1) - (3)].string), (yyvsp[(3) - (3)].uri), NULL);
    RAPTOR_FREE(char*, (yyvsp[(1) - (3)].string));
    raptor_free_uri((yyvsp[(3) - (3)].uri));
    if(!(yyval.identifier))
      YYERROR;
  } else
    (yyval.identifier) = NULL;
    
}
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 789 "./turtle_parser.y"
    {
#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
  printf("literal + datatype string=\"%s\" qname URI=<%s>\n", (yyvsp[(1) - (3)].string), raptor_uri_as_string((yyvsp[(3) - (3)].uri)));
#endif

  if((yyvsp[(3) - (3)].uri)) {
    (yyval.identifier) = raptor_new_term_from_literal(((raptor_parser*)rdf_parser)->world,
                                      (yyvsp[(1) - (3)].string), (yyvsp[(3) - (3)].uri), NULL);
    RAPTOR_FREE(char*, (yyvsp[(1) - (3)].string));
    raptor_free_uri((yyvsp[(3) - (3)].uri));
    if(!(yyval.identifier))
      YYERROR;
  } else
    (yyval.identifier) = NULL;
}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 805 "./turtle_parser.y"
    {
#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
  printf("literal string=\"%s\"\n", (yyvsp[(1) - (1)].string));
#endif

  (yyval.identifier) = raptor_new_term_from_literal(((raptor_parser*)rdf_parser)->world,
                                    (yyvsp[(1) - (1)].string), NULL, NULL);
  RAPTOR_FREE(char*, (yyvsp[(1) - (1)].string));
  if(!(yyval.identifier))
    YYERROR;
}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 817 "./turtle_parser.y"
    {
  raptor_uri *uri;
#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
  printf("resource integer=%s\n", (yyvsp[(1) - (1)].string));
#endif
  uri = raptor_new_uri(((raptor_parser*)rdf_parser)->world, (const unsigned char*)"http://www.w3.org/2001/XMLSchema#integer");
  if(!uri) {
    RAPTOR_FREE(char*, (yyvsp[(1) - (1)].string));
    YYERROR;
  }
  (yyval.identifier) = raptor_new_term_from_literal(((raptor_parser*)rdf_parser)->world,
                                    (yyvsp[(1) - (1)].string), uri, NULL);
  RAPTOR_FREE(char*, (yyvsp[(1) - (1)].string));
  raptor_free_uri(uri);
  if(!(yyval.identifier))
    YYERROR;
}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 835 "./turtle_parser.y"
    {
  raptor_uri *uri;
#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
  printf("resource double=%s\n", (yyvsp[(1) - (1)].string));
#endif
  uri = raptor_new_uri(((raptor_parser*)rdf_parser)->world, (const unsigned char*)"http://www.w3.org/2001/XMLSchema#double");
  if(!uri) {
    RAPTOR_FREE(char*, (yyvsp[(1) - (1)].string));
    YYERROR;
  }
  (yyval.identifier) = raptor_new_term_from_literal(((raptor_parser*)rdf_parser)->world,
                                    (yyvsp[(1) - (1)].string), uri, NULL);
  RAPTOR_FREE(char*, (yyvsp[(1) - (1)].string));
  raptor_free_uri(uri);
  if(!(yyval.identifier))
    YYERROR;
}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 853 "./turtle_parser.y"
    {
  raptor_uri *uri;
#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
  printf("resource decimal=%s\n", (yyvsp[(1) - (1)].string));
#endif
  uri = raptor_new_uri(((raptor_parser*)rdf_parser)->world, (const unsigned char*)"http://www.w3.org/2001/XMLSchema#decimal");
  if(!uri) {
    RAPTOR_FREE(char*, (yyvsp[(1) - (1)].string));
    YYERROR;
  }
  (yyval.identifier) = raptor_new_term_from_literal(((raptor_parser*)rdf_parser)->world,
                                    (yyvsp[(1) - (1)].string), uri, NULL);
  RAPTOR_FREE(char*, (yyvsp[(1) - (1)].string));
  raptor_free_uri(uri);
  if(!(yyval.identifier))
    YYERROR;
}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 871 "./turtle_parser.y"
    {
  raptor_uri *uri;
#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
  fputs("resource boolean true\n", stderr);
#endif
  uri = raptor_new_uri(((raptor_parser*)rdf_parser)->world, (const unsigned char*)"http://www.w3.org/2001/XMLSchema#boolean");
  if(!uri)
    YYERROR;
  (yyval.identifier) = raptor_new_term_from_literal(((raptor_parser*)rdf_parser)->world,
                                    (const unsigned char*)"true", uri, NULL);
  raptor_free_uri(uri);
  if(!(yyval.identifier))
    YYERROR;
}
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 886 "./turtle_parser.y"
    {
  raptor_uri *uri;
#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
  fputs("resource boolean false\n", stderr);
#endif
  uri = raptor_new_uri(((raptor_parser*)rdf_parser)->world, (const unsigned char*)"http://www.w3.org/2001/XMLSchema#boolean");
  if(!uri)
    YYERROR;
  (yyval.identifier) = raptor_new_term_from_literal(((raptor_parser*)rdf_parser)->world,
                                    (const unsigned char*)"false", uri, NULL);
  raptor_free_uri(uri);
  if(!(yyval.identifier))
    YYERROR;
}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 904 "./turtle_parser.y"
    {
#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
  printf("resource URI=<%s>\n", raptor_uri_as_string((yyvsp[(1) - (1)].uri)));
#endif

  if((yyvsp[(1) - (1)].uri)) {
    (yyval.identifier) = raptor_new_term_from_uri(((raptor_parser*)rdf_parser)->world, (yyvsp[(1) - (1)].uri));
    raptor_free_uri((yyvsp[(1) - (1)].uri));
    if(!(yyval.identifier))
      YYERROR;
  } else
    (yyval.identifier) = NULL;
}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 918 "./turtle_parser.y"
    {
#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
  printf("resource qname URI=<%s>\n", raptor_uri_as_string((yyvsp[(1) - (1)].uri)));
#endif

  if((yyvsp[(1) - (1)].uri)) {
    (yyval.identifier) = raptor_new_term_from_uri(((raptor_parser*)rdf_parser)->world, (yyvsp[(1) - (1)].uri));
    raptor_free_uri((yyvsp[(1) - (1)].uri));
    if(!(yyval.identifier))
      YYERROR;
  } else
    (yyval.identifier) = NULL;
}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 935 "./turtle_parser.y"
    {
  (yyval.sequence) = (yyvsp[(1) - (1)].sequence);
}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 939 "./turtle_parser.y"
    {
  (yyval.sequence) = NULL;
}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 945 "./turtle_parser.y"
    {
  const unsigned char *id;
#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
  printf("subject blank=\"%s\"\n", (yyvsp[(1) - (1)].string));
#endif
  id = raptor_world_internal_generate_id(((raptor_parser*)rdf_parser)->world,
                                         (yyvsp[(1) - (1)].string));
  if(!id)
    YYERROR;

  (yyval.identifier) = raptor_new_term_from_blank(((raptor_parser*)rdf_parser)->world, id);
  RAPTOR_FREE(char*, id);

  if(!(yyval.identifier))
    YYERROR;
}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 962 "./turtle_parser.y"
    {
  int i;
  const unsigned char *id;

  id = raptor_world_generate_bnodeid(((raptor_parser*)rdf_parser)->world);
  if(!id) {
    if((yyvsp[(2) - (3)].sequence))
      raptor_free_sequence((yyvsp[(2) - (3)].sequence));
    YYERROR;
  }

  (yyval.identifier) = raptor_new_term_from_blank(((raptor_parser*)rdf_parser)->world, id);
  RAPTOR_FREE(char*, id);
  if(!(yyval.identifier)) {
    if((yyvsp[(2) - (3)].sequence))
      raptor_free_sequence((yyvsp[(2) - (3)].sequence));
    YYERROR;
  }

  if((yyvsp[(2) - (3)].sequence) == NULL) {
#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
    printf("resource\n propertyList=");
    raptor_term_print_as_ntriples((yyval.identifier), stdout);
    printf("\n");
#endif
  } else {
    /* non-empty property list, handle it  */
#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
    printf("resource\n propertyList=");
    raptor_sequence_print((yyvsp[(2) - (3)].sequence), stdout);
    printf("\n");
#endif

    for(i = 0; i < raptor_sequence_size((yyvsp[(2) - (3)].sequence)); i++) {
      raptor_statement* t2 = (raptor_statement*)raptor_sequence_get_at((yyvsp[(2) - (3)].sequence), i);
      t2->subject = raptor_term_copy((yyval.identifier));
      raptor_turtle_generate_statement((raptor_parser*)rdf_parser, t2);
    }

#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1
    printf(" after substitution objectList=");
    raptor_sequence_print((yyvsp[(2) - (3)].sequence), stdout);
    printf("\n\n");
#endif

    raptor_free_sequence((yyvsp[(2) - (3)].sequence));

  }
  
}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 1013 "./turtle_parser.y"
    {
  (yyval.identifier) = (yyvsp[(1) - (1)].identifier);
}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 1020 "./turtle_parser.y"
    {
  int i;
  raptor_world* world = ((raptor_parser*)rdf_parser)->world;
  raptor_term* first_identifier = NULL;
  raptor_term* rest_identifier = NULL;
  raptor_term* object = NULL;
  raptor_term* blank = NULL;

#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
  printf("collection\n objectList=");
  raptor_sequence_print((yyvsp[(2) - (3)].sequence), stdout);
  printf("\n");
#endif

  first_identifier = raptor_new_term_from_uri(world, RAPTOR_RDF_first_URI(world));
  if(!first_identifier)
    goto err_collection;
  rest_identifier = raptor_new_term_from_uri(world, RAPTOR_RDF_rest_URI(world));
  if(!rest_identifier)
    goto err_collection;
  
  /* non-empty property list, handle it  */
#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
  printf("resource\n propertyList=");
  raptor_sequence_print((yyvsp[(2) - (3)].sequence), stdout);
  printf("\n");
#endif

  object = raptor_new_term_from_uri(world, RAPTOR_RDF_nil_URI(world));
  if(!object)
    goto err_collection;

  for(i = raptor_sequence_size((yyvsp[(2) - (3)].sequence))-1; i>=0; i--) {
    raptor_term* temp;
    raptor_statement* t2 = (raptor_statement*)raptor_sequence_get_at((yyvsp[(2) - (3)].sequence), i);
    const unsigned char *blank_id;

    blank_id = raptor_world_generate_bnodeid(((raptor_parser*)rdf_parser)->world);
    if(!blank_id)
      goto err_collection;

    blank = raptor_new_term_from_blank(((raptor_parser*)rdf_parser)->world,
                                       blank_id);
    RAPTOR_FREE(char*, blank_id);
    if(!blank)
      goto err_collection;
    
    t2->subject = blank;
    t2->predicate = first_identifier;
    /* t2->object already set to the value we want */
    raptor_turtle_generate_statement((raptor_parser*)rdf_parser, t2);
    
    temp = t2->object;
    
    t2->subject = blank;
    t2->predicate = rest_identifier;
    t2->object = object;
    raptor_turtle_generate_statement((raptor_parser*)rdf_parser, t2);

    t2->subject = NULL;
    t2->predicate = NULL;
    t2->object = temp;

    raptor_free_term(object);
    object = blank;
    blank = NULL;
  }
  
#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1
  printf(" after substitution objectList=");
  raptor_sequence_print((yyvsp[(2) - (3)].sequence), stdout);
  printf("\n\n");
#endif

  raptor_free_sequence((yyvsp[(2) - (3)].sequence));

  raptor_free_term(first_identifier);
  raptor_free_term(rest_identifier);

  (yyval.identifier)=object;

  break; /* success */

  err_collection:

  if(blank)
    raptor_free_term(blank);

  if(object)
    raptor_free_term(object);

  if(rest_identifier)
    raptor_free_term(rest_identifier);

  if(first_identifier)
    raptor_free_term(first_identifier);

  raptor_free_sequence((yyvsp[(2) - (3)].sequence));

  YYERROR;
}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 1122 "./turtle_parser.y"
    {
  raptor_world* world = ((raptor_parser*)rdf_parser)->world;

#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1  
  printf("collection\n empty\n");
#endif

  (yyval.identifier) = raptor_new_term_from_uri(world, RAPTOR_RDF_nil_URI(world));
  if(!(yyval.identifier))
    YYERROR;
}
    break;



/* Line 1806 of yacc.c  */
#line 2901 "turtle_parser.c"
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

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (rdf_parser, YY_("syntax error"));
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
        yyerror (rdf_parser, yymsgp);
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
		      yytoken, &yylval, rdf_parser);
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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
		  yystos[yystate], yyvsp, rdf_parser);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (rdf_parser, YY_("memory exhausted"));
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
                  yytoken, &yylval, rdf_parser);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, rdf_parser);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 1136 "./turtle_parser.y"



/* Support functions */

int
turtle_parser_error(void* ctx, const char *msg)
{
  raptor_parser* rdf_parser = (raptor_parser *)ctx;
  raptor_turtle_parser* turtle_parser;

  turtle_parser = (raptor_turtle_parser*)rdf_parser->context;
  
  if(turtle_parser->error_count++)
    return 0;

  rdf_parser->locator.line = turtle_parser->lineno;
#ifdef RAPTOR_TURTLE_USE_ERROR_COLUMNS
  rdf_parser->locator.column = turtle_lexer_get_column(yyscanner);
#endif

  raptor_log_error(rdf_parser->world, RAPTOR_LOG_LEVEL_ERROR,
                   &rdf_parser->locator, msg);

  return 0;
}


int
turtle_syntax_error(raptor_parser *rdf_parser, const char *message, ...)
{
  raptor_turtle_parser* turtle_parser = (raptor_turtle_parser*)rdf_parser->context;
  va_list arguments;

  if(turtle_parser->error_count++)
    return 0;

  rdf_parser->locator.line = turtle_parser->lineno;
#ifdef RAPTOR_TURTLE_USE_ERROR_COLUMNS
  rdf_parser->locator.column = turtle_lexer_get_column(yyscanner);
#endif

  va_start(arguments, message);
  
  raptor_parser_log_error_varargs(((raptor_parser*)rdf_parser),
                                  RAPTOR_LOG_LEVEL_ERROR, message, arguments);

  va_end(arguments);

  return 0;
}


raptor_uri*
turtle_qname_to_uri(raptor_parser *rdf_parser, unsigned char *name, size_t name_len) 
{
  raptor_turtle_parser* turtle_parser = (raptor_turtle_parser*)rdf_parser->context;

  rdf_parser->locator.line = turtle_parser->lineno;
#ifdef RAPTOR_TURTLE_USE_ERROR_COLUMNS
  rdf_parser->locator.column = turtle_lexer_get_column(yyscanner);
#endif

  return raptor_qname_string_to_uri(&turtle_parser->namespaces, name, name_len);
}



#ifndef TURTLE_PUSH_PARSE
static int
turtle_parse(raptor_parser *rdf_parser, const char *string, size_t length)
{
  raptor_turtle_parser* turtle_parser = (raptor_turtle_parser*)rdf_parser->context;
  int rc;
  
  if(!string || !*string)
    return 0;
  
  if(turtle_lexer_lex_init(&turtle_parser->scanner))
    return 1;
  turtle_parser->scanner_set = 1;

#if defined(YYDEBUG) && YYDEBUG > 0
  turtle_parser_debug = 1;
#endif

  turtle_lexer_set_extra(rdf_parser, turtle_parser->scanner);
  (void)turtle_lexer__scan_bytes((char *)string, (int)length, turtle_parser->scanner);

  rc = turtle_parser_parse(rdf_parser);

  turtle_lexer_lex_destroy(turtle_parser->scanner);
  turtle_parser->scanner_set = 0;

  return rc;
}
#endif


#ifdef TURTLE_PUSH_PARSE
static int
turtle_push_parse(raptor_parser *rdf_parser, 
                  const char *string, size_t length)
{
#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1
  raptor_world* world = rdf_parser->world;
#endif
  raptor_turtle_parser* turtle_parser;
  void *buffer;
  int status;
  yypstate *ps;

  turtle_parser = (raptor_turtle_parser*)rdf_parser->context;

  if(!string || !*string)
    return 0;
  
  if(turtle_lexer_lex_init(&turtle_parser->scanner))
    return 1;
  turtle_parser->scanner_set = 1;

#if defined(YYDEBUG) && YYDEBUG > 0
  turtle_parser_debug = 1;
#endif

  turtle_lexer_set_extra(rdf_parser, turtle_parser->scanner);
  buffer = turtle_lexer__scan_bytes(string, length, turtle_parser->scanner);

  /* returns a parser instance or 0 on out of memory */
  ps = yypstate_new();
  if(!ps)
    return 1;

  do {
    YYSTYPE lval;
    int token;

    memset(&lval, 0, sizeof(YYSTYPE));
    
    token = turtle_lexer_lex(&lval, turtle_parser->scanner);

#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1
    printf("token %s\n", turtle_token_print(world, token, &lval));
#endif

    status = yypush_parse(ps, token, &lval, rdf_parser);

    /* turtle_token_free(world, token, &lval); */

    if(!token || token == EOF || token == ERROR_TOKEN)
      break;
  } while (status == YYPUSH_MORE);
  yypstate_delete(ps);

  turtle_lexer_lex_destroy(turtle_parser->scanner);
  turtle_parser->scanner_set = 0;

  return 0;
}
#endif


/**
 * raptor_turtle_parse_init - Initialise the Raptor Turtle parser
 *
 * Return value: non 0 on failure
 **/

static int
raptor_turtle_parse_init(raptor_parser* rdf_parser, const char *name) {
  raptor_turtle_parser* turtle_parser = (raptor_turtle_parser*)rdf_parser->context;

  if(raptor_namespaces_init(rdf_parser->world, &turtle_parser->namespaces, 0))
    return 1;

  turtle_parser->trig = !strcmp(name, "trig");

  return 0;
}


/* PUBLIC FUNCTIONS */


/*
 * raptor_turtle_parse_terminate - Free the Raptor Turtle parser
 * @rdf_parser: parser object
 * 
 **/
static void
raptor_turtle_parse_terminate(raptor_parser *rdf_parser) {
  raptor_turtle_parser *turtle_parser = (raptor_turtle_parser*)rdf_parser->context;

  raptor_namespaces_clear(&turtle_parser->namespaces);

  if(turtle_parser->scanner_set) {
    turtle_lexer_lex_destroy(turtle_parser->scanner);
    turtle_parser->scanner_set = 0;
  }

  if(turtle_parser->buffer)
    RAPTOR_FREE(cdata, turtle_parser->buffer);

  if(turtle_parser->graph_name) {
    raptor_free_term(turtle_parser->graph_name);
    turtle_parser->graph_name = NULL;
  }
}


static void
raptor_turtle_generate_statement(raptor_parser *parser, raptor_statement *t)
{
  raptor_turtle_parser *turtle_parser = (raptor_turtle_parser*)parser->context;
  raptor_statement *statement = &parser->statement;

  if(!t->subject || !t->predicate || !t->object)
    return;

  if(!parser->statement_handler)
    return;

  if(turtle_parser->trig && turtle_parser->graph_name)
    statement->graph = raptor_term_copy(turtle_parser->graph_name);

  if(!parser->emitted_default_graph && !turtle_parser->graph_name) {
    /* for non-TRIG - start default graph at first triple */
    raptor_parser_start_graph(parser, NULL, 0);
    parser->emitted_default_graph++;
  }
  
  /* Two choices for subject for Turtle */
  if(t->subject->type == RAPTOR_TERM_TYPE_BLANK) {
    statement->subject = raptor_new_term_from_blank(parser->world,
                                                    t->subject->value.blank.string);
  } else {
    /* RAPTOR_TERM_TYPE_URI */
    RAPTOR_ASSERT(t->subject->type != RAPTOR_TERM_TYPE_URI,
                  "subject type is not resource");
    statement->subject = raptor_new_term_from_uri(parser->world,
                                                  t->subject->value.uri);
  }

  /* Predicates are URIs but check for bad ordinals */
  if(!strncmp((const char*)raptor_uri_as_string(t->predicate->value.uri),
              "http://www.w3.org/1999/02/22-rdf-syntax-ns#_", 44)) {
    unsigned char* predicate_uri_string = raptor_uri_as_string(t->predicate->value.uri);
    int predicate_ordinal = raptor_check_ordinal(predicate_uri_string+44);
    if(predicate_ordinal <= 0)
      raptor_parser_error(parser, "Illegal ordinal value %d in property '%s'.", predicate_ordinal, predicate_uri_string);
  }
  
  statement->predicate = raptor_new_term_from_uri(parser->world,
                                                  t->predicate->value.uri);
  

  /* Three choices for object for Turtle */
  if(t->object->type == RAPTOR_TERM_TYPE_URI) {
    statement->object = raptor_new_term_from_uri(parser->world,
                                                 t->object->value.uri);
  } else if(t->object->type == RAPTOR_TERM_TYPE_BLANK) {
    statement->object = raptor_new_term_from_blank(parser->world,
                                                   t->object->value.blank.string);
  } else {
    /* RAPTOR_TERM_TYPE_LITERAL */
    RAPTOR_ASSERT(t->object->type != RAPTOR_TERM_TYPE_LITERAL,
                  "object type is not literal");
    statement->object = raptor_new_term_from_literal(parser->world,
                                                     t->object->value.literal.string,
                                                     t->object->value.literal.datatype,
                                                     t->object->value.literal.language);
  }

  /* Generate the statement */
  (*parser->statement_handler)(parser->user_data, statement);

  raptor_free_term(statement->subject); statement->subject = NULL;
  raptor_free_term(statement->predicate); statement->predicate = NULL;
  raptor_free_term(statement->object); statement->object = NULL;
  if(statement->graph) {
    raptor_free_term(statement->graph); statement->graph = NULL;
  }
}



static int
raptor_turtle_parse_chunk(raptor_parser* rdf_parser, 
                          const unsigned char *s, size_t len,
                          int is_end)
{
  char *ptr;
  raptor_turtle_parser *turtle_parser;
  int rc;

  turtle_parser = (raptor_turtle_parser*)rdf_parser->context;
  
#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1
  RAPTOR_DEBUG2("adding %d bytes to line buffer\n", (int)len);
#endif

  if(len) {
    turtle_parser->buffer = RAPTOR_REALLOC(char*, turtle_parser->buffer,
                                           turtle_parser->buffer_length + len + 1);
    if(!turtle_parser->buffer) {
      raptor_parser_fatal_error(rdf_parser, "Out of memory");
      return 1;
    }

    /* move pointer to end of cdata buffer */
    ptr = turtle_parser->buffer+turtle_parser->buffer_length;

    /* adjust stored length */
    turtle_parser->buffer_length += len;

    /* now write new stuff at end of cdata buffer */
    memcpy(ptr, s, len);
    ptr += len;
    *ptr = '\0';

#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 1
    RAPTOR_DEBUG3("buffer buffer now '%s' (%d bytes)\n", 
                  turtle_parser->buffer, turtle_parser->buffer_length);
#endif
  }
  
  /* if not end, wait for rest of input */
  if(!is_end)
    return 0;

  /* Nothing to do */
  if(!turtle_parser->buffer_length)
    return 0;

#ifdef TURTLE_PUSH_PARSE
  rc = turtle_push_parse(rdf_parser, 
			 turtle_parser->buffer, turtle_parser->buffer_length);
#else
  rc = turtle_parse(rdf_parser, turtle_parser->buffer, turtle_parser->buffer_length);
#endif  

  if(rdf_parser->emitted_default_graph) {
    /* for non-TRIG - end default graph after last triple */
    raptor_parser_end_graph(rdf_parser, NULL, 0);
    rdf_parser->emitted_default_graph--;
  }
  return rc;
}


static int
raptor_turtle_parse_start(raptor_parser *rdf_parser) 
{
  raptor_locator *locator=&rdf_parser->locator;
  raptor_turtle_parser *turtle_parser = (raptor_turtle_parser*)rdf_parser->context;

  /* base URI required for Turtle */
  if(!rdf_parser->base_uri)
    return 1;

  locator->line = 1;
  locator->column= -1; /* No column info */
  locator->byte= -1; /* No bytes info */

  if(turtle_parser->buffer_length) {
    RAPTOR_FREE(cdata, turtle_parser->buffer);
    turtle_parser->buffer = NULL;
    turtle_parser->buffer_length = 0;
  }
  
  turtle_parser->lineno = 1;

  return 0;
}


static int
raptor_turtle_parse_recognise_syntax(raptor_parser_factory* factory, 
                                     const unsigned char *buffer, size_t len,
                                     const unsigned char *identifier, 
                                     const unsigned char *suffix, 
                                     const char *mime_type)
{
  int score= 0;
  
  if(suffix) {
    if(!strcmp((const char*)suffix, "ttl"))
      score = 8;
    if(!strcmp((const char*)suffix, "n3"))
      score = 3;
  }
  
  if(mime_type) {
    if(strstr((const char*)mime_type, "turtle"))
      score += 6;
    if(strstr((const char*)mime_type, "n3"))
      score += 3;
  }

  /* Do this as long as N3 is not supported since it shares the same syntax */
  if(buffer && len) {
#define  HAS_TURTLE_PREFIX (raptor_memstr((const char*)buffer, len, "@prefix ") != NULL)
/* The following could also be found with N-Triples but not with @prefix */
#define  HAS_TURTLE_RDF_URI (raptor_memstr((const char*)buffer, len, ": <http://www.w3.org/1999/02/22-rdf-syntax-ns#>") != NULL)

    if(HAS_TURTLE_PREFIX) {
      score = 6;
      if(HAS_TURTLE_RDF_URI)
        score += 2;
    }
  }
  
  return score;
}


static raptor_uri*
raptor_turtle_get_graph(raptor_parser* rdf_parser)
{
  raptor_turtle_parser *turtle_parser;

  turtle_parser = (raptor_turtle_parser*)rdf_parser->context;
  if(turtle_parser->graph_name)
    return raptor_uri_copy(turtle_parser->graph_name->value.uri);

  return NULL;
}


#ifdef RAPTOR_PARSER_TRIG
static int
raptor_trig_parse_recognise_syntax(raptor_parser_factory* factory, 
                                   const unsigned char *buffer, size_t len,
                                   const unsigned char *identifier, 
                                   const unsigned char *suffix, 
                                   const char *mime_type)
{
  int score= 0;
  
  if(suffix) {
    if(!strcmp((const char*)suffix, "trig"))
      score = 9;
#ifndef RAPTOR_PARSER_TURTLE
    if(!strcmp((const char*)suffix, "ttl"))
      score = 8;
    if(!strcmp((const char*)suffix, "n3"))
      score = 3;
#endif
  }
  
  if(mime_type) {
    if(strstr((const char*)mime_type, "trig"))
      score = 6;
#ifndef RAPTOR_PARSER_TURTLE
    if(strstr((const char*)mime_type, "turtle"))
      score += 6;
    if(strstr((const char*)mime_type, "n3"))
      score += 3;
#endif
  }

#ifndef RAPTOR_PARSER_TURTLE
  /* Do this as long as N3 is not supported since it shares the same syntax */
  if(buffer && len) {
#define  HAS_TRIG_PREFIX (raptor_memstr((const char*)buffer, len, "@prefix ") != NULL)
/* The following could also be found with N-Triples but not with @prefix */
#define  HAS_TRIG_RDF_URI (raptor_memstr((const char*)buffer, len, ": <http://www.w3.org/1999/02/22-rdf-syntax-ns#>") != NULL)

    if(HAS_TRIG_PREFIX) {
      score = 6;
      if(HAS_TRIG_RDF_URI)
        score += 2;
    }
  }
#endif
  
  return score;
}
#endif


#ifdef RAPTOR_PARSER_TURTLE
static const char* const turtle_names[4] = { "turtle", "ntriples-plus", "n3", NULL };

static const char* const turtle_uri_strings[3] = {
  "http://www.w3.org/ns/formats/Turtle",
  "http://www.dajobe.org/2004/01/turtle/",
  NULL
};
  
#define TURTLE_TYPES_COUNT 6
static const raptor_type_q turtle_types[TURTLE_TYPES_COUNT + 1] = {
  /* first one is the default */
  { "text/turtle", 11, 10},
  { "application/x-turtle", 20, 10},
  { "application/turtle", 18, 10},
  { "text/n3", 7, 3},
  { "text/rdf+n3", 11, 3},
  { "application/rdf+n3", 18, 3},
  { NULL, 0}
};

static int
raptor_turtle_parser_register_factory(raptor_parser_factory *factory) 
{
  int rc = 0;

  factory->desc.names = turtle_names;

  factory->desc.mime_types = turtle_types;

  factory->desc.label = "Turtle Terse RDF Triple Language";
  factory->desc.uri_strings = turtle_uri_strings;

  factory->desc.flags = RAPTOR_SYNTAX_NEED_BASE_URI;
  
  factory->context_length     = sizeof(raptor_turtle_parser);
  
  factory->init      = raptor_turtle_parse_init;
  factory->terminate = raptor_turtle_parse_terminate;
  factory->start     = raptor_turtle_parse_start;
  factory->chunk     = raptor_turtle_parse_chunk;
  factory->recognise_syntax = raptor_turtle_parse_recognise_syntax;
  factory->get_graph = raptor_turtle_get_graph;

  return rc;
}
#endif


#ifdef RAPTOR_PARSER_TRIG
static const char* const trig_names[2] = { "trig", NULL };
  
static const char* const trig_uri_strings[2] = {
  "http://www.wiwiss.fu-berlin.de/suhl/bizer/TriG/Spec/",
  NULL
};
  
#define TRIG_TYPES_COUNT 1
static const raptor_type_q trig_types[TRIG_TYPES_COUNT + 1] = {
  /* first one is the default */
  { "application/x-trig", 18, 10},
  { NULL, 0, 0}
};

static int
raptor_trig_parser_register_factory(raptor_parser_factory *factory) 
{
  int rc = 0;

  factory->desc.names = trig_names;

  factory->desc.mime_types = trig_types;

  factory->desc.label = "TriG - Turtle with Named Graphs";
  factory->desc.uri_strings = trig_uri_strings;

  factory->desc.flags = RAPTOR_SYNTAX_NEED_BASE_URI;
  
  factory->context_length     = sizeof(raptor_turtle_parser);
  
  factory->init      = raptor_turtle_parse_init;
  factory->terminate = raptor_turtle_parse_terminate;
  factory->start     = raptor_turtle_parse_start;
  factory->chunk     = raptor_turtle_parse_chunk;
  factory->recognise_syntax = raptor_trig_parse_recognise_syntax;
  factory->get_graph = raptor_turtle_get_graph;

  return rc;
}
#endif


#ifdef RAPTOR_PARSER_TURTLE
int
raptor_init_parser_turtle(raptor_world* world)
{
  return !raptor_world_register_parser_factory(world,
                                               &raptor_turtle_parser_register_factory);
}
#endif

#ifdef RAPTOR_PARSER_TRIG
int
raptor_init_parser_trig(raptor_world* world)
{
  return !raptor_world_register_parser_factory(world,
                                               &raptor_trig_parser_register_factory);
}
#endif


#ifdef STANDALONE
#include <stdio.h>
#include <locale.h>

#define TURTLE_FILE_BUF_SIZE 2048

static void
turtle_parser_print_statement(void *user,
                              raptor_statement *statement) 
{
  FILE* stream = (FILE*)user;
  raptor_statement_print(statement, stream);
  putc('\n', stream);
}
  


int
main(int argc, char *argv[]) 
{
  char string[TURTLE_FILE_BUF_SIZE];
  raptor_parser rdf_parser; /* static */
  raptor_turtle_parser turtle_parser; /* static */
  raptor_locator *locator = &rdf_parser.locator;
  FILE *fh;
  const char *filename;
  size_t nobj;
  
#if defined(RAPTOR_DEBUG) && RAPTOR_DEBUG > 2
  turtle_parser_debug = 1;
#endif

  if(argc > 1) {
    filename = argv[1];
    fh = fopen(filename, "r");
    if(!fh) {
      fprintf(stderr, "%s: Cannot open file %s - %s\n", argv[0], filename,
              strerror(errno));
      exit(1);
    }
  } else {
    filename="<stdin>";
    fh = stdin;
  }

  memset(string, 0, TURTLE_FILE_BUF_SIZE);
  nobj = fread(string, TURTLE_FILE_BUF_SIZE, 1, fh);
  if(nobj < TURTLE_FILE_BUF_SIZE) {
    if(ferror(fh)) {
      fprintf(stderr, "%s: file '%s' read failed - %s\n",
              argv[0], filename, strerror(errno));
      fclose(fh);
      return(1);
    }
  }
  
  if(argc > 1)
    fclose(fh);

  memset(&rdf_parser, 0, sizeof(rdf_parser));
  memset(&turtle_parser, 0, sizeof(turtle_parser));

  locator->line= locator->column = -1;
  locator->file= filename;

  turtle_parser.lineno= 1;

  rdf_parser.world = raptor_new_world();
  rdf_parser.context = &turtle_parser;
  rdf_parser.base_uri = raptor_new_uri(rdf_parser.world,
                                       (const unsigned char*)"http://example.org/fake-base-uri/");

  raptor_parser_set_statement_handler(&rdf_parser, stdout,
                                      turtle_parser_print_statement);
  raptor_turtle_parse_init(&rdf_parser, "turtle");
  
  turtle_parser.error_count = 0;

#ifdef TURTLE_PUSH_PARSE
  turtle_push_parse(&rdf_parser, string, strlen(string));
#else
  turtle_parse(&rdf_parser, string, strlen(string));
#endif

  raptor_turtle_parse_terminate(&rdf_parser);
  
  raptor_free_uri(rdf_parser.base_uri);

  raptor_free_world(rdf_parser.world);
  
  return (0);
}
#endif

