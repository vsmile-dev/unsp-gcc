/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 56 "c-parse.y"

#include "config.h"
#include "system.h"
#include <setjmp.h>

#include "tree.h"
#include "input.h"
#include "c-lex.h"
#include "c-tree.h"
#include "flags.h"
#include "output.h"
#include "toplev.h"

#ifdef MULTIBYTE_CHARS
#include <locale.h>
#endif


/* Since parsers are distinct for each language, put the language string
   definition here.  */
char *language_string = "GNU C";

/* Like YYERROR but do call yyerror.  */
#define YYERROR1 { yyerror ("syntax error"); YYERROR; }

/* Cause the `yydebug' variable to be defined.  */
#define YYDEBUG 1
#define YYLEX yylex()

#line 100 "c-parse.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_C_PARSE_H_INCLUDED
# define YY_YY_C_PARSE_H_INCLUDED
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
    IDENTIFIER = 258,
    TYPENAME = 259,
    SCSPEC = 260,
    TYPESPEC = 261,
    TYPE_QUAL = 262,
    CONSTANT = 263,
    STRING = 264,
    ELLIPSIS = 265,
    SIZEOF = 266,
    ENUM = 267,
    STRUCT = 268,
    UNION = 269,
    IF = 270,
    ELSE = 271,
    WHILE = 272,
    DO = 273,
    FOR = 274,
    SWITCH = 275,
    CASE = 276,
    DEFAULT = 277,
    BREAK = 278,
    CONTINUE = 279,
    RETURN = 280,
    GOTO = 281,
    ASM_KEYWORD = 282,
    TYPEOF = 283,
    ALIGNOF = 284,
    ATTRIBUTE = 285,
    EXTENSION = 286,
    LABEL = 287,
    REALPART = 288,
    IMAGPART = 289,
    ASSIGN = 290,
    OROR = 291,
    ANDAND = 292,
    EQCOMPARE = 293,
    ARITHCOMPARE = 294,
    LSHIFT = 295,
    RSHIFT = 296,
    UNARY = 297,
    PLUSPLUS = 298,
    MINUSMINUS = 299,
    HYPERUNARY = 300,
    POINTSAT = 301,
    INTERFACE = 302,
    IMPLEMENTATION = 303,
    END = 304,
    SELECTOR = 305,
    DEFS = 306,
    ENCODE = 307,
    CLASSNAME = 308,
    PUBLIC = 309,
    PRIVATE = 310,
    PROTECTED = 311,
    PROTOCOL = 312,
    OBJECTNAME = 313,
    CLASS = 314,
    ALIAS = 315,
    OBJC_STRING = 316
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 88 "c-parse.y"
long itype; tree ttype; enum tree_code code;
	char *filename; int lineno; int ends_in_label; 

#line 218 "c-parse.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_C_PARSE_H_INCLUDED  */

/* Second part of user prologue.  */
#line 205 "c-parse.y"

/* Number of statements (loosely speaking) and compound statements 
   seen so far.  */
static int stmt_count;
static int compstmt_count;
  
/* Input file and line number of the end of the body of last simple_if;
   used by the stmt-rule immediately after simple_if returns.  */
static char *if_stmt_file;
static int if_stmt_line;

/* List of types and structure classes of the current declaration.  */
static tree current_declspecs = NULL_TREE;
static tree prefix_attributes = NULL_TREE;

/* Stack of saved values of current_declspecs and prefix_attributes.  */
static tree declspec_stack;

/* 1 if we explained undeclared var errors.  */
static int undeclared_variable_notice;


/* Tell yyparse how to print a token's value, if yydebug is set.  */

#define YYPRINT(FILE,YYCHAR,YYLVAL) yyprint(FILE,YYCHAR,YYLVAL)
extern void yyprint			PROTO ((FILE *, int, YYSTYPE));

#line 262 "c-parse.c"


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
typedef yytype_int16 yy_state_t;

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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2465

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  84
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  158
/* YYNRULES -- Number of rules.  */
#define YYNRULES  405
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  696

#define YYUNDEFTOK  2
#define YYMAXUTOK   316


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    80,     2,     2,     2,    52,    43,     2,
      59,    76,    50,    48,    81,    49,    58,    51,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    38,    77,
       2,    36,     2,    37,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    60,     2,    83,    42,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    82,    41,    78,    79,     2,     2,     2,
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
      35,    39,    40,    44,    45,    46,    47,    53,    54,    55,
      56,    57,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   235,   235,   239,   254,   254,   255,   255,   259,   260,
     261,   269,   274,   284,   289,   294,   296,   298,   299,   300,
     307,   312,   306,   319,   325,   330,   324,   337,   343,   348,
     342,   355,   363,   364,   367,   369,   371,   373,   375,   377,
     379,   383,   389,   390,   394,   396,   401,   402,   405,   408,
     412,   440,   446,   449,   452,   455,   457,   462,   466,   470,
     471,   475,   474,   506,   507,   509,   511,   513,   515,   517,
     519,   521,   523,   525,   527,   529,   532,   531,   538,   537,
     544,   547,   543,   553,   552,   562,   570,   582,   680,   681,
     683,   689,   692,   691,   728,   730,   732,   736,   742,   744,
     750,   751,   756,   758,   759,   770,   775,   776,   777,   778,
     786,   791,   796,   799,   808,   813,   814,   815,   816,   824,
     835,   839,   844,   849,   854,   859,   861,   863,   873,   875,
     880,   881,   883,   888,   893,   895,   901,   902,   904,   917,
     919,   921,   923,   928,   931,   933,   936,   950,   952,   957,
     958,   966,   967,   968,   972,   974,   980,   981,   982,   986,
     987,   991,   992,   997,   998,  1006,  1005,  1013,  1022,  1021,
    1030,  1039,  1040,  1045,  1047,  1052,  1057,  1059,  1065,  1066,
    1068,  1070,  1072,  1080,  1081,  1082,  1083,  1089,  1091,  1090,
    1103,  1110,  1112,  1116,  1117,  1123,  1124,  1126,  1125,  1128,
    1133,  1132,  1136,  1138,  1142,  1143,  1147,  1152,  1154,  1160,
    1169,  1159,  1183,  1192,  1182,  1208,  1209,  1215,  1217,  1222,
    1224,  1226,  1233,  1235,  1244,  1249,  1254,  1256,  1258,  1265,
    1267,  1274,  1279,  1281,  1283,  1288,  1290,  1297,  1299,  1303,
    1305,  1310,  1312,  1317,  1319,  1325,  1324,  1330,  1334,  1337,
    1336,  1340,  1344,  1347,  1346,  1353,  1352,  1358,  1362,  1364,
    1367,  1369,  1375,  1377,  1383,  1384,  1386,  1401,  1407,  1421,
    1427,  1432,  1434,  1440,  1441,  1446,  1449,  1453,  1464,  1465,
    1470,  1476,  1478,  1483,  1485,  1491,  1492,  1496,  1498,  1504,
    1505,  1510,  1513,  1515,  1517,  1519,  1521,  1523,  1525,  1527,
    1531,  1540,  1548,  1549,  1551,  1555,  1557,  1560,  1564,  1574,
    1576,  1582,  1583,  1587,  1601,  1603,  1606,  1608,  1610,  1618,
    1626,  1638,  1642,  1646,  1661,  1660,  1673,  1677,  1681,  1686,
    1691,  1696,  1698,  1704,  1706,  1707,  1725,  1724,  1732,  1744,
    1747,  1757,  1746,  1767,  1775,  1780,  1792,  1795,  1778,  1822,
    1821,  1835,  1840,  1845,  1849,  1853,  1864,  1871,  1878,  1885,
    1896,  1902,  1906,  1912,  1911,  1967,  1998,  2029,  2044,  2060,
    2062,  2068,  2069,  2075,  2076,  2080,  2081,  2086,  2091,  2093,
    2100,  2100,  2110,  2112,  2111,  2121,  2128,  2129,  2139,  2141,
    2146,  2148,  2155,  2164,  2173,  2182,  2192,  2207,  2207,  2217,
    2218,  2228,  2230,  2236,  2238,  2243
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "TYPENAME", "SCSPEC",
  "TYPESPEC", "TYPE_QUAL", "CONSTANT", "STRING", "ELLIPSIS", "SIZEOF",
  "ENUM", "STRUCT", "UNION", "IF", "ELSE", "WHILE", "DO", "FOR", "SWITCH",
  "CASE", "DEFAULT", "BREAK", "CONTINUE", "RETURN", "GOTO", "ASM_KEYWORD",
  "TYPEOF", "ALIGNOF", "ATTRIBUTE", "EXTENSION", "LABEL", "REALPART",
  "IMAGPART", "ASSIGN", "'='", "'?'", "':'", "OROR", "ANDAND", "'|'",
  "'^'", "'&'", "EQCOMPARE", "ARITHCOMPARE", "LSHIFT", "RSHIFT", "'+'",
  "'-'", "'*'", "'/'", "'%'", "UNARY", "PLUSPLUS", "MINUSMINUS",
  "HYPERUNARY", "POINTSAT", "'.'", "'('", "'['", "INTERFACE",
  "IMPLEMENTATION", "END", "SELECTOR", "DEFS", "ENCODE", "CLASSNAME",
  "PUBLIC", "PRIVATE", "PROTECTED", "PROTOCOL", "OBJECTNAME", "CLASS",
  "ALIAS", "OBJC_STRING", "')'", "';'", "'}'", "'~'", "'!'", "','", "'{'",
  "']'", "$accept", "program", "extdefs", "@1", "@2", "extdef", "datadef",
  "fndef", "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "identifier", "unop",
  "expr", "exprlist", "nonnull_exprlist", "unary_expr", "sizeof",
  "alignof", "cast_expr", "$@9", "expr_no_commas", "$@10", "$@11", "$@12",
  "$@13", "$@14", "primary", "@15", "string", "old_style_parm_decls",
  "lineno_datadecl", "datadecls", "datadecl", "lineno_decl", "decls",
  "setspecs", "setattrs", "decl", "typed_declspecs", "reserved_declspecs",
  "typed_declspecs_no_prefix_attr", "reserved_declspecs_no_prefix_attr",
  "declmods", "declmods_no_prefix_attr", "typed_typespecs",
  "reserved_typespecquals", "typespec", "typespecqual_reserved",
  "initdecls", "notype_initdecls", "maybeasm", "initdcl", "@16",
  "notype_initdcl", "@17", "maybe_attribute", "attributes", "attribute",
  "attribute_list", "attrib", "any_word", "init", "$@18",
  "initlist_maybe_comma", "initlist1", "initelt", "$@19", "initval",
  "$@20", "designator_list", "designator", "nested_function", "$@21",
  "$@22", "notype_nested_function", "$@23", "$@24", "declarator",
  "after_type_declarator", "parm_declarator", "notype_declarator",
  "struct_head", "union_head", "enum_head", "structsp", "@25", "@26",
  "@27", "@28", "maybecomma", "maybecomma_warn", "component_decl_list",
  "component_decl_list2", "component_decl", "components",
  "component_declarator", "enumlist", "enumerator", "typename", "absdcl",
  "nonempty_type_quals", "type_quals", "absdcl1", "stmts",
  "lineno_stmt_or_labels", "xstmts", "errstmt", "pushlevel",
  "maybe_label_decls", "label_decls", "label_decl", "compstmt_or_error",
  "compstmt_start", "compstmt", "simple_if", "if_prefix", "do_stmt_start",
  "$@29", "save_filename", "save_lineno", "lineno_labeled_stmt",
  "lineno_stmt_or_label", "stmt_or_label", "stmt", "$@30", "$@31", "$@32",
  "$@33", "@34", "$@35", "$@36", "all_iter_stmt", "all_iter_stmt_simple",
  "@37", "label", "maybe_type_qual", "xexpr", "asm_operands",
  "nonnull_asm_operands", "asm_operand", "asm_clobbers", "parmlist",
  "$@38", "parmlist_1", "$@39", "parmlist_2", "parms", "parm",
  "parmlist_or_identifiers", "$@40", "parmlist_or_identifiers_1",
  "identifiers", "identifiers_or_typenames", "extension", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,    61,    63,    58,   291,
     292,   124,    94,    38,   293,   294,   295,   296,    43,    45,
      42,    47,    37,   297,   298,   299,   300,   301,    46,    40,
      91,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,    41,    59,   125,   126,
      33,    44,   123,    93
};
# endif

#define YYPACT_NINF (-523)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-387)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      91,   137,   163,  2246,  -523,  2246,   109,  -523,  -523,  -523,
    -523,   167,   167,   167,   157,   164,   173,  -523,  -523,  -523,
    -523,  -523,    81,   176,  2274,   200,  -523,   167,  -523,    65,
      84,    89,  -523,  2246,  -523,  -523,  -523,   167,   167,   167,
    2108,  2042,   175,  -523,  -523,    81,    25,  -523,   167,  1372,
    -523,   195,  -523,    81,   200,  -523,   167,  -523,  -523,   627,
    -523,  -523,  -523,  -523,   159,  -523,   182,  -523,   184,  -523,
    -523,  -523,  -523,  -523,  -523,  2108,  2108,   424,  -523,  -523,
    -523,  2108,  -523,  -523,  1071,  -523,  -523,  2108,   211,   212,
    -523,  2135,  2162,  -523,  2397,   711,   272,  2108,  -523,   219,
     403,  -523,   232,  1693,   756,   268,   240,  -523,   195,    81,
    -523,   258,  -523,  1470,   698,   167,  -523,  -523,   195,   145,
    -523,   167,  1462,   381,   411,   170,  1434,   627,  -523,  -523,
    -523,  -523,   167,  -523,   255,   785,  -523,   281,  -523,   477,
    -523,  -523,  -523,  -523,  -523,   260,   274,   271,   295,  -523,
     301,  2108,  1071,  -523,  1071,  -523,  2108,  2108,   342,  -523,
    -523,  2108,  2108,  2108,  2108,  2108,  2108,  2108,  2108,  2108,
    2108,  2108,  2108,  -523,  -523,   424,   424,  2108,  2108,  -523,
    -523,  -523,  -523,   403,  1497,   167,  -523,   426,   460,  -523,
    -523,  -523,  -523,  -523,  -523,  -523,  -523,     0,  -523,   326,
    -523,   411,  -523,  -523,   365,   411,   393,  -523,   899,  1552,
    -523,   321,   360,  -523,   406,    60,  -523,  -523,   385,   167,
     344,   308,  -523,   195,   195,  -523,   698,   167,  -523,  1579,
    -523,  -523,   698,   167,  -523,  -523,  -523,   368,   205,   483,
    -523,   167,  -523,  -523,   414,   371,  -523,   477,  -523,  -523,
    -523,   376,   415,  1931,  -523,  2397,   431,   439,  2397,  2397,
    2108,   479,  2108,  2108,  1604,   834,  1684,  1378,   545,   409,
     409,   448,   448,  -523,  -523,  -523,  -523,  -523,   443,   212,
     438,   304,   349,  -523,  1142,  -523,   456,   403,  -523,  1634,
    -523,   460,   464,   756,  2189,    54,   470,  -523,  -523,  -523,
    1319,  -523,   471,   197,  -523,  -523,     1,  -523,  -523,  -523,
      38,  -523,  -523,  -523,   673,  -523,   381,  -523,  -523,   381,
    -523,   512,  -523,  -523,   467,  -523,  -523,  -523,  -523,  -523,
    -523,   474,  -523,   475,  2108,   424,   478,   371,  -523,   525,
    -523,  -523,  -523,  -523,  -523,   523,  2108,   954,  1523,  -523,
    -523,   426,  -523,  -523,  -523,   426,  -523,  -523,   480,  -523,
    -523,   234,   486,  -523,  -523,   210,   143,  -523,  -523,   576,
    -523,   564,   271,  -523,  -523,  -523,   495,  1856,  -523,  1308,
      38,  -523,  -523,    38,   493,  -523,  -523,   493,  -523,   167,
     167,  2397,  -523,   167,   498,   424,   724,   525,  -523,  1128,
    -523,  2413,  -523,  -523,  2108,  -523,  -523,  -523,   143,   167,
     115,   220,   167,  -523,   167,   220,   167,  1142,  -523,  -523,
    -523,  -523,  -523,   195,  -523,    81,  -523,   701,  -523,  -523,
    2397,  -523,  -523,  1308,  -523,  -523,   299,   299,  -523,  -523,
    -523,   167,  -523,   249,   416,   641,   500,   501,   817,  -523,
    -523,  -523,  -523,  -523,   546,   424,  2108,  -523,   547,  2397,
     521,   522,  -523,  -523,    43,  1248,  2108,   247,   282,   210,
    -523,  1661,  -523,  -523,  -523,   254,   143,  -523,  -523,  -523,
     275,   300,   169,   701,  -523,  -523,  1128,  -523,  -523,  2108,
    -523,   103,   154,  -523,  -523,   424,  -523,  -523,  -523,  -523,
     524,  -523,  -523,  -523,  -523,  1797,  -523,  2285,  1128,  -523,
    -523,  1188,  -523,  1363,  -523,  -523,  2413,  -523,   445,   445,
    -523,  1716,  -523,   529,  -523,  -523,   530,  2353,  2108,  -523,
    -523,  -523,  1877,   575,   555,  -523,  -523,   568,   569,  2108,
     591,   553,   558,  2055,    68,   629,  -523,   600,   566,  -523,
     574,  2278,  -523,   657,   930,    63,  -523,  -523,  -523,  -523,
    -523,  1988,  2108,  -523,   598,  1363,  -523,  -523,  -523,  -523,
    -523,  -523,  2353,  2108,   623,  -523,  2108,  2108,  1741,  -523,
    -523,  -523,  -523,   606,  2108,   611,  -523,   633,   167,  -523,
    -523,   195,  -523,    81,  1014,  -523,  -523,  -523,  -523,  2108,
    -523,  2330,  -523,  -523,  -523,   617,  2108,   677,  -523,   469,
     620,   622,  2108,  -523,  -523,   632,  -523,  2108,  -523,   345,
    -523,   158,   358,  -523,   387,  -523,  -523,  1877,   646,  -523,
    -523,   648,  -523,  -523,  -523,  -523,  2379,  -523,    45,  -523,
     698,  -523,   698,  -523,  -523,  -523,   663,  -523,  -523,  2108,
    -523,  -523,   725,   679,  -523,  -523,  -523,  -523,  -523,  -523,
     699,  -523,   716,    56,   696,  -523,  -523,   271,   271,  -523,
    -523,  2108,   725,   704,   725,  -523,  -523,  2108,   706,    76,
    -523,  -523,   708,  -523,   393,   710,  -523,   272,   294,  -523,
    -523,   713,   393,  -523,  -523,   272
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       4,     0,     6,     0,     1,     0,     0,   153,   144,   151,
     143,   243,   239,   241,     0,     0,     0,   405,    19,     5,
       9,     8,     0,   119,   119,   139,   130,   140,   173,     0,
       0,     0,   152,     0,     7,    17,    18,   244,   240,   242,
       0,     0,     0,   238,   289,     0,     0,   161,   120,     0,
      16,     0,    15,     0,   141,   130,   142,   146,   145,   128,
     174,    32,    33,   264,   248,   264,   252,   255,   257,    11,
      87,    88,   100,    57,    58,     0,     0,     0,    34,    36,
      35,     0,    37,    38,     0,    39,    40,     0,     0,    41,
      59,     0,     0,    63,    44,    46,    89,     0,   287,     0,
     285,   149,     0,   285,   178,     0,     0,    12,     0,     0,
      31,     0,   397,     0,     0,   171,   223,   289,     0,     0,
     159,   120,     0,   215,   216,     0,     0,   129,   132,   156,
     157,   131,   133,   158,     0,     0,   245,     0,   249,     0,
     253,    55,    56,    50,    47,     0,     0,     0,     0,    49,
       0,     0,     0,    51,     0,    53,     0,     0,    80,    78,
      76,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    98,    99,     0,     0,    42,     0,   101,
      48,   154,   289,   380,     0,   120,   283,   286,   147,   155,
     288,   149,   284,   184,   185,   186,   183,     0,   176,   179,
     290,   233,   232,   162,   163,   237,     0,   231,     0,     0,
     236,     0,     0,    29,     0,   326,   107,   327,   170,   172,
       0,     0,    14,     0,     0,    23,     0,   171,   397,     0,
      13,    27,     0,   171,   271,   266,   119,   263,   119,     0,
     264,   171,   264,   280,   281,   260,   278,     0,    91,    90,
     316,   308,     0,     0,    10,    45,     0,     0,    86,    85,
       0,     0,     0,     0,    74,    75,    73,    72,    71,    69,
      70,    64,    65,    66,    67,    68,    97,    96,     0,    43,
       0,   293,     0,   297,     0,   299,     0,     0,   380,     0,
     150,   148,     0,   178,    42,     0,     0,   401,   387,   119,
     119,   399,     0,   388,   390,   398,     0,   234,   235,   307,
       0,   109,   104,   108,     0,   168,   221,   217,   160,   222,
      21,   167,   218,   220,     0,    25,   247,   326,   265,   326,
     272,     0,   251,     0,     0,   261,     0,   260,   317,   309,
      93,    61,    60,    52,    54,     0,     0,    79,    77,    94,
      95,   292,   291,   381,   298,   300,   294,   296,     0,   175,
     177,    87,     0,   164,   385,   285,   285,   382,   383,     0,
     400,     0,     0,    30,   314,   105,   119,   119,   136,     0,
       0,   165,   219,     0,   267,   273,   327,   269,   327,   171,
     171,   282,   279,   171,     0,     0,     0,   310,   311,     0,
      81,    84,   295,   180,     0,   182,   230,   289,   380,   120,
     171,   171,   171,   289,   120,   171,   171,     0,   389,   391,
     402,   315,   112,     0,   113,     0,   136,   134,   190,   188,
     187,   169,    22,     0,    26,   326,   171,     0,   246,   250,
     256,   171,   403,     0,     0,     0,   326,     0,     0,   116,
     327,   302,   312,   203,    87,     0,     0,   200,     0,   202,
       0,   258,   193,   199,     0,     0,     0,     0,   293,     0,
     397,     0,   392,   393,   394,   293,     0,   395,   396,   384,
       0,     0,   163,   135,   138,   137,     0,   166,   274,     0,
     268,   120,   171,   254,   313,     0,   319,   118,   117,   306,
       0,   320,   304,   327,   303,     0,   206,     0,     0,   197,
      62,     0,   192,     0,   205,   196,    82,   181,   228,   229,
     224,     0,   227,     0,   110,   111,     0,   171,     0,   275,
     404,   318,     0,   153,     0,   340,   324,     0,     0,     0,
       0,     0,     0,     0,     0,   369,   361,     0,     0,   114,
     119,   119,   333,   338,     0,     0,   330,   331,   334,   362,
     332,     0,     0,   208,     0,     0,   194,   195,   225,   226,
     189,   277,   171,     0,     0,   326,   371,     0,     0,   367,
     351,   352,   353,     0,     0,     0,   370,     0,   171,   335,
     125,     0,   126,     0,     0,   322,   327,   321,   344,     0,
     127,     0,   201,   198,   276,     0,     0,     0,   372,    46,
       0,     0,     0,   365,   354,     0,   359,     0,   368,     0,
     123,   209,     0,   124,   212,   339,   326,     0,     0,   207,
     323,     0,   325,   363,   345,   349,     0,   360,     0,   121,
       0,   122,     0,   337,   328,   326,     0,   341,   326,   371,
     326,   366,   373,     0,   210,   213,   329,   343,   326,   364,
       0,   350,     0,     0,   374,   375,   355,     0,     0,   342,
     346,     0,   373,     0,     0,   211,   214,   371,     0,     0,
     356,   376,     0,   377,     0,     0,   347,   378,     0,   357,
     326,     0,     0,   348,   358,   379
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -523,  -523,  -523,  -523,  -523,    57,  -523,  -523,  -523,  -523,
    -523,  -523,  -523,  -523,   -26,  -523,   -40,   491,  -127,   440,
    -523,  -523,    -1,  -523,   454,  -523,  -523,  -523,  -523,  -523,
     217,  -523,  -182,  -204,   579,  -523,  -523,   350,  -523,    20,
     -16,   241,     3,   740,  -523,   379,     8,    -8,   -81,   616,
      24,  -162,  -385,   -38,  -105,   -53,  -523,  -523,  -523,   -50,
       7,   116,  -523,   515,  -523,   377,  -523,  -218,  -523,   298,
    -523,  -408,  -523,  -523,   347,  -523,  -523,  -523,  -523,  -523,
    -523,   -37,   -59,    66,   -20,  -523,  -523,  -523,   -32,  -523,
    -523,  -523,  -523,  -523,   482,     2,  -523,   573,   485,   380,
     570,   487,   -35,   -69,   -79,   -82,   -86,   378,  -523,  -523,
    -172,  -523,  -523,  -523,   430,  -232,  -523,  -126,  -523,  -523,
    -523,  -523,   -91,  -341,  -522,   375,  -523,   202,  -523,  -523,
    -523,  -523,  -523,  -523,  -523,  -523,  -523,  -523,   203,  -523,
    -467,   177,  -523,   171,  -523,   543,  -523,  -238,  -523,  -523,
    -523,   489,  -198,  -523,  -523,  -523,  -523,     4
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     3,     5,    19,    20,    21,   226,   380,
     232,   383,   114,   310,   458,    87,   146,   278,    89,    90,
      91,    92,    93,   399,    94,   263,   262,   260,   466,   261,
      95,   147,    96,   213,   214,   215,   375,   445,   446,    22,
     224,   549,   299,    59,   376,   427,   300,    25,   100,   188,
      26,   131,   119,    46,   115,   120,   433,    47,   379,   218,
     219,    28,   197,   198,   199,   431,   486,   460,   461,   462,
     565,   463,   508,   464,   465,   620,   640,   667,   623,   642,
     668,   204,   123,   410,   124,    29,    30,    31,    32,   240,
     242,   247,   139,   512,   336,   134,   135,   237,   384,   385,
     245,   246,   102,   186,   103,   105,   187,   447,   448,   500,
     216,   339,   396,   397,   398,   373,   251,   374,   553,   554,
     555,   575,   596,   314,   597,   451,   556,   557,   626,   574,
     658,   649,   677,   690,   650,   558,   559,   648,   560,   587,
     610,   663,   664,   665,   688,   283,   284,   301,   417,   302,
     303,   304,   207,   208,   305,   306,   443,    97
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      88,    99,    49,    64,    66,    68,    23,    33,    23,    33,
      27,    24,    27,    24,   122,   125,    54,   227,    37,    38,
      39,   252,   320,   217,   295,   106,   290,   133,   325,    48,
     322,    56,   109,   126,   192,   220,    23,    33,   480,   372,
      27,    24,   311,    51,    53,   436,   353,   437,    55,   148,
     279,   143,    48,   607,   236,   203,   238,   515,   121,   221,
      48,  -103,    34,   179,   598,   101,   132,   137,    61,    62,
     312,    61,    62,   211,   141,   142,   292,   370,   196,   513,
     144,   293,   371,   652,    43,   201,   149,    61,    62,   205,
      69,    -2,    61,    62,   672,   133,   180,   282,   106,   227,
     281,   455,   107,   456,   643,   567,   108,   185,   101,   505,
     185,    16,    48,   244,   684,   121,    48,   256,   584,   257,
     250,   653,   599,   656,   217,   121,   659,   191,   661,   290,
     363,    44,   673,    16,   132,   217,   669,     4,   280,   239,
      45,   217,  -103,    60,   286,    16,    43,    63,   432,   276,
     277,   434,   685,    60,    60,    60,   133,   603,   236,   101,
     238,   316,   532,    -3,    60,   319,    65,   279,   693,   287,
     318,    67,    60,    16,   470,   471,   101,   321,   101,   479,
    -172,  -172,   660,   326,    16,   111,    35,    36,  -163,   324,
     185,   332,   528,   413,  -163,   351,   111,    16,    43,   116,
     201,   355,   408,   184,   205,    57,   619,    58,   144,     7,
     682,     9,   190,    43,   406,    27,    40,    11,    12,    13,
     345,   244,   222,    41,   449,    16,   223,   121,   112,   113,
     121,   121,    42,    15,   104,  -163,   386,    60,   388,  -163,
      16,   136,   331,   239,   333,   117,   421,   230,    60,   358,
      16,   108,   342,    50,   118,   627,   327,    43,   329,   133,
     407,   200,   191,   101,   138,   485,   140,   196,   526,   408,
     184,    43,   520,   497,   368,   200,   502,   467,   369,   112,
     113,   179,  -270,  -270,    16,    43,   406,   150,   185,   200,
     564,    27,    54,   151,   185,   181,   412,   416,    16,   112,
     113,    60,    43,   116,   413,   450,   377,    56,   189,   244,
     403,   200,    16,   408,   184,   404,   202,   206,    44,   365,
     366,   485,   282,   517,    55,   468,   494,    45,   151,    16,
     495,   475,   407,   233,    16,    60,   248,   489,   378,   438,
     439,   408,   184,   440,   388,   411,   415,    43,   116,   117,
     249,   200,   524,   250,   182,   450,   223,   503,   118,   241,
     472,   473,   474,   183,   184,   477,   478,   228,   229,   442,
     691,   253,   409,   414,    16,   692,    27,   525,   254,   552,
     -83,   108,   351,   355,   317,   294,   490,   481,   106,   351,
     355,   493,   111,   469,   117,   133,   423,   425,   476,   492,
     492,   426,    72,   118,   308,   482,   552,   212,   288,   289,
    -106,  -106,  -106,  -106,   111,   414,  -106,  -163,  -106,  -106,
    -106,   315,   639,  -163,    27,   352,   223,    61,    62,   506,
     121,   523,    48,    16,  -106,   641,   654,   309,   655,   108,
     228,   229,   529,   491,   121,   328,   112,   113,   201,   205,
     334,   133,   335,   182,   338,   201,   205,   168,   169,   170,
     171,   172,   183,   184,  -163,   548,   129,   130,  -163,   530,
     112,   113,    11,    12,    13,   409,   409,   571,   243,   547,
      61,    62,   414,   414,   234,   288,   289,     7,  -106,     9,
      98,   340,   548,   309,   496,    11,    12,    13,   170,   171,
     172,   552,   687,   583,   470,   471,   547,   343,   550,   561,
     695,    15,    27,   551,    17,   344,   227,   346,   585,   349,
     144,   350,   604,   173,   174,    60,   175,   176,   177,   178,
      60,   153,   155,   605,   518,   519,   608,   611,   618,   354,
     359,   675,   676,    54,   615,   633,   364,   367,   381,   217,
     382,   217,   389,   390,   621,   622,   393,   395,    56,   628,
     180,   400,   405,   402,   550,   561,   631,   420,    27,   551,
     591,   593,   422,   624,   435,    55,   441,   638,  -305,   501,
       7,     8,     9,    10,   -32,   509,   418,   548,    11,    12,
      13,   166,   167,   168,   169,   170,   171,   172,   121,   510,
      48,   547,   531,   511,    15,   255,    16,    60,   570,   608,
     258,   259,   569,   -33,   573,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   576,   577,   579,
     580,   678,   128,   129,   130,   581,   586,   608,   588,    11,
      12,    13,   212,   589,  -115,  -115,  -115,  -115,  -115,  -115,
    -115,   590,  -115,  -115,  -115,  -115,  -115,    16,  -115,  -115,
    -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,
    -115,  -115,  -115,   594,  -115,  -115,   602,     7,     8,     9,
      10,  -115,   606,   614,  -115,    11,    12,    13,   616,  -115,
    -115,  -115,   617,   630,   632,  -115,  -115,   634,   635,   212,
    -115,    15,  -326,  -326,  -326,  -326,   484,   129,   130,   637,
    -326,  -326,  -326,    11,    12,    13,   347,   348,  -115,  -115,
    -115,  -115,   646,  -115,   647,   444,  -326,  -326,  -326,  -326,
    -326,  -326,  -326,  -326,   662,  -326,  -326,  -326,  -326,  -326,
     657,  -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,
    -326,  -326,  -326,  -326,  -326,  -326,   666,  -326,  -326,    61,
      62,   193,   194,   195,  -326,   173,   174,  -326,   175,   176,
     177,   178,  -326,  -326,  -326,   671,   670,   674,  -326,  -326,
    -102,   680,   683,  -326,   686,   362,   234,   689,   391,     7,
     694,     9,    98,   609,   313,   127,   498,    11,    12,    13,
     401,  -326,   600,  -326,  -326,   483,  -326,   291,   360,   566,
     487,   514,   330,    15,   387,   488,    17,   337,   212,   394,
    -326,  -326,   392,   504,   499,  -326,  -326,   452,  -326,   644,
     645,   356,  -326,   430,  -326,  -326,  -326,  -326,  -326,  -326,
    -326,  -326,  -326,  -326,  -326,   681,  -326,     0,  -326,   679,
    -326,  -326,     0,   459,     0,     0,     0,  -326,   419,     0,
    -326,     0,   235,  -262,     0,  -326,  -326,  -326,     0,     0,
       0,  -326,  -326,     0,     0,     0,  -326,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   430,     0,     0,
       0,     0,     0,     0,  -326,  -301,  -326,  -326,     0,  -326,
     296,     0,   297,     7,     8,     9,    10,     0,     0,   298,
     507,    11,    12,    13,     0,     0,     0,     0,     0,   459,
     516,     0,     0,     0,     0,     0,     0,    15,     0,    16,
       0,   595,     0,  -326,  -326,     0,     0,     0,  -326,  -326,
     459,  -326,     0,   527,     0,  -326,     0,  -326,  -326,  -326,
    -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,     0,  -326,
       0,  -326,   459,  -326,  -326,   459,     0,   459,     0,     0,
    -326,     0,     0,  -326,     0,  -386,     0,     0,  -326,  -326,
    -326,     0,   572,     0,  -326,  -326,     0,     0,     0,  -326,
       0,     0,     0,   578,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,  -326,     0,  -326,
    -326,     0,  -326,     0,     0,   625,   601,  -336,  -336,   459,
       0,     0,  -336,  -336,     0,  -336,     0,     0,     0,  -336,
       0,  -336,  -336,  -336,  -336,  -336,  -336,  -336,  -336,  -336,
    -336,  -336,     0,  -336,     0,  -336,     0,  -336,  -336,     0,
       0,     0,     0,     0,  -336,     0,     0,  -336,     0,     0,
       0,     0,  -336,  -336,  -336,     0,   636,     0,  -336,  -336,
       0,     0,   145,  -336,    70,     7,     0,     9,    98,    71,
      72,     0,    73,    11,    12,    13,     0,     0,     0,     0,
       0,  -336,     0,  -336,  -336,     0,  -336,     0,     0,    15,
      74,     0,    17,     0,    75,    76,     0,     0,     0,     0,
       0,    77,     0,     0,    78,     0,     0,     0,     0,    79,
      80,    81,     0,     0,     0,    82,    83,     0,     0,   453,
      84,   454,    62,     0,     0,     0,    71,    72,     0,    73,
       0,     0,     0,   296,     0,     0,     7,     8,     9,    10,
      85,    86,   298,   -92,    11,    12,    13,    74,     0,    17,
       0,    75,    76,     0,     0,     0,     0,     0,    77,     0,
      15,    78,    16,     0,     0,     0,    79,    80,    81,     0,
       0,     0,    82,    83,     0,     0,   455,    84,   456,   453,
       0,   454,    62,     0,     0,     0,    71,    72,     0,    73,
       0,     0,     0,     0,     0,     0,  -191,    85,    86,     0,
     457,     0,     0,     0,     0,     0,     0,    74,  -386,    17,
       0,    75,    76,     0,     0,     0,     0,     0,    77,     0,
       0,    78,     0,     0,     0,     0,    79,    80,    81,     0,
       0,     0,    82,    83,     0,     0,   455,    84,   456,   453,
       0,    70,     0,     0,     0,     0,    71,    72,     0,    73,
       0,     0,     0,     0,     0,     0,  -259,    85,    86,     0,
     457,     0,     0,     0,     0,     0,     0,    74,     0,    17,
       0,    75,    76,     0,  -204,     0,     0,     0,    77,     0,
       0,    78,     0,     0,     0,     0,    79,    80,    81,     0,
       0,     0,    82,    83,     0,     0,  -204,    84,  -204,   428,
       0,    70,     0,     0,     0,     0,    71,    72,     0,    73,
       0,     0,     0,     7,     8,     9,    10,    85,    86,     0,
     457,    11,    12,    13,     0,     0,     0,    74,     0,    17,
       0,    75,    76,     0,     0,     0,     0,    15,    77,    16,
       0,    78,     0,     0,     0,     0,    79,    80,    81,     0,
       0,     0,    82,    83,   453,     0,    70,    84,     0,     0,
       0,    71,    72,   110,    73,     0,   -28,   -28,   -28,   -28,
       0,     0,     0,     0,   -28,   -28,   -28,    85,    86,     0,
     429,     0,    74,     0,    17,     0,    75,    76,     0,   111,
     -28,     0,  -163,    77,     0,     0,    78,     0,  -163,     0,
       0,    79,    80,    81,     0,     0,     0,    82,    83,     0,
       0,     0,    84,   165,   166,   167,   168,   169,   170,   171,
     172,   112,   113,     0,     0,   231,     0,     0,   -24,   -24,
     -24,   -24,    85,    86,     0,   457,   -24,   -24,   -24,  -163,
       0,     0,     0,  -163,   -28,     0,     0,     0,     0,     0,
       0,   111,   -24,   225,  -163,     0,   -20,   -20,   -20,   -20,
    -163,     0,     0,    70,   -20,   -20,   -20,     0,    71,    72,
       0,    73,     0,     0,     0,     0,     0,     0,     0,   111,
     -20,     0,  -163,   112,   113,     0,     0,     0,  -163,    74,
      70,    17,     0,    75,    76,    71,    72,     0,    73,     0,
      77,  -163,     0,    78,     0,  -163,   -24,     0,    79,    80,
     209,     0,     0,     0,    82,    83,    74,     0,    17,    84,
      75,    76,     0,     0,     0,     0,     0,    77,     0,  -163,
      78,     0,     0,  -163,   -20,    79,    80,    81,     0,    85,
      86,    82,    83,   210,     0,    70,    84,     0,     0,     0,
      71,    72,     0,    73,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,    85,    86,     0,     0,
     285,    74,    70,    17,     0,    75,    76,    71,    72,     0,
      73,     0,    77,     0,     0,    78,     0,     0,     0,     0,
      79,    80,    81,     0,     0,     0,    82,    83,    74,     0,
      17,    84,    75,    76,     0,     0,     0,     0,     0,    77,
       0,     0,    78,     0,     0,     0,     0,    79,    80,    81,
       0,    85,    86,    82,    83,   307,     0,    70,    84,     0,
       0,     0,    71,    72,     0,    73,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,     0,    85,    86,
       0,     0,   323,    74,    70,    17,     0,    75,    76,    71,
      72,     0,    73,     0,    77,     0,     0,    78,     0,     0,
       0,     0,    79,    80,    81,     0,     0,     0,    82,    83,
      74,     0,    17,    84,    75,    76,     0,     7,     0,     9,
     190,    77,     0,     0,    78,    11,    12,    13,     0,    79,
      80,   521,     0,    85,    86,    82,    83,   357,     0,    70,
      84,    15,     0,    16,    71,    72,     0,    73,   164,   165,
     166,   167,   168,   169,   170,   171,   172,     0,     0,     0,
      85,    86,     0,   182,   522,    74,     0,    17,     0,    75,
      76,   612,   183,   184,     0,     0,    77,     0,     0,    78,
       0,     0,     0,     0,    79,    80,    81,     0,     0,     0,
      82,    83,     0,     0,     0,    84,   156,   157,   158,   613,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,     0,    85,    86,     0,     0,   568,
     454,   533,     8,     9,    10,    71,    72,     0,    73,    11,
      12,    13,   534,     0,   535,   536,   537,   538,   539,   540,
     541,   542,   543,   544,   545,    15,    74,    16,    17,     0,
      75,    76,     0,     0,     0,     0,     0,    77,     0,     0,
      78,     0,     0,     0,     0,    79,    80,    81,     0,     0,
       0,    82,    83,     0,     0,     0,    84,     0,     0,     0,
       7,    57,     9,    58,     0,     0,     0,     0,    11,    12,
      13,     0,     0,     0,   546,     0,    85,    86,     0,   250,
     454,    62,     0,     0,    15,    71,    72,     0,    73,     0,
       0,     0,   534,     0,   535,   536,   537,   538,   539,   540,
     541,   542,   543,   544,   545,     0,    74,     0,    17,     0,
      75,    76,     0,     0,     0,     0,     0,    77,     0,     0,
      78,     0,     0,     0,     0,    79,    80,    81,     0,     0,
       0,    82,    83,   424,    70,     0,    84,     0,     0,    71,
      72,     0,    73,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   546,     0,    85,    86,     0,   250,
      74,     0,    17,     0,    75,    76,     0,     0,     0,     0,
       0,    77,     0,     0,    78,     0,     0,     0,     0,    79,
      80,    81,     0,     0,     0,    82,    83,     0,     0,     0,
      84,    70,     7,     8,     9,    10,    71,    72,     0,    73,
      11,    12,    13,     0,     0,     0,     0,     0,     0,     0,
      85,    86,     0,   341,     0,     0,    15,    74,    16,    17,
       0,    75,    76,     0,     0,     0,     0,     0,    77,     0,
       0,    78,     0,     0,     0,     0,    79,    80,    81,     0,
       0,     0,    82,    83,     0,    70,     7,    84,     9,    98,
      71,    72,     0,    73,    11,    12,    13,     0,    70,     0,
       0,     0,     0,    71,    72,     0,    73,    85,    86,     0,
      15,    74,     0,    17,     0,    75,    76,     0,     0,     0,
       0,     0,    77,     0,    74,    78,    17,     0,    75,    76,
      79,    80,    81,     0,     0,    77,    82,    83,    78,     0,
       0,    84,     0,    79,    80,    81,     0,     0,     0,    82,
      83,    70,     0,     0,    84,     0,    71,    72,     0,    73,
       0,    85,    86,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   582,     0,    85,    86,     0,    74,    70,    17,
       0,    75,    76,    71,    72,     0,    73,     0,    77,     0,
       0,    78,     0,     0,     0,     0,    79,    80,    81,     0,
       0,     0,    82,    83,    74,    70,    17,    84,    75,    76,
      71,    72,     0,    73,     0,    77,     0,     0,    78,     0,
       0,     0,     0,    79,    80,    81,     0,    85,    86,    82,
      83,    74,   361,    17,   152,    75,    76,    71,    72,     0,
      73,     0,    77,     0,     0,    78,     0,     0,     0,     0,
      79,    80,    81,     0,    85,    86,    82,    83,    74,     0,
      17,   154,    75,    76,     0,     0,     0,     0,     0,    77,
       0,     0,    78,     0,     0,     0,     0,    79,    80,    81,
       0,    85,    86,    82,    83,     0,     0,     6,    84,  -119,
       7,     8,     9,    10,     0,     0,     0,     0,    11,    12,
      13,     0,     0,     0,     0,     0,     0,     0,    85,    86,
       0,     0,     0,    14,    15,     0,    16,    17,     7,     8,
       9,    10,     7,     8,     9,    10,    11,    12,    13,     0,
      11,    12,    13,     0,     0,   562,  -119,     0,     0,     0,
       0,     0,    15,     0,    16,  -119,    15,     0,    16,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     156,   157,   158,    18,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    52,     0,     0,     0,   592,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   156,   157,   158,   563,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,    16,     0,     0,     0,     0,   156,   157,
     158,     0,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,     0,     0,     0,     0,
       0,     0,     0,   629,   156,   157,   158,   651,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   156,   157,   158,     0,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     158,     0,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172
};

static const yytype_int16 yycheck[] =
{
      40,    41,    22,    29,    30,    31,     3,     3,     5,     5,
       3,     3,     5,     5,    51,    53,    24,   122,    11,    12,
      13,   147,   226,   114,   206,    45,   188,    59,   232,    22,
     228,    24,    48,    53,   103,   117,    33,    33,   423,     1,
      33,    33,   214,    23,    24,   386,   284,   388,    24,    84,
     177,    77,    45,   575,   135,   108,   135,   465,    51,   118,
      53,     1,     5,     9,     1,    41,    59,    65,     3,     4,
      10,     3,     4,   113,    75,    76,    76,    76,   104,    36,
      81,    81,    81,    38,     3,   105,    87,     3,     4,   109,
      33,     0,     3,     4,    38,   127,    97,   183,   118,   204,
     182,    58,    77,    60,   626,   513,    81,   100,    84,   450,
     103,    30,   105,   139,    38,   108,   109,   152,    50,   154,
      82,    76,    59,   645,   215,   118,   648,   103,   650,   291,
      76,    50,    76,    30,   127,   226,   658,     0,   178,   135,
      59,   232,    82,    27,   184,    30,     3,    82,   380,   175,
     176,   383,    76,    37,    38,    39,   188,   565,   239,   135,
     239,   220,   503,     0,    48,   224,    82,   294,   690,   185,
     223,    82,    56,    30,    59,    60,   152,   227,   154,   417,
      77,    78,   649,   233,    30,    27,    77,    78,    30,   229,
     183,   241,    38,    50,    36,   281,    27,    30,     3,     4,
     220,   287,    59,    60,   224,     5,   591,     7,   209,     4,
     677,     6,     7,     3,     4,   208,    59,    12,    13,    14,
     260,   247,    77,    59,   396,    30,    81,   220,    59,    60,
     223,   224,    59,    28,    59,    77,   327,   121,   329,    81,
      30,    82,   240,   239,   242,    50,   372,    77,   132,   289,
      30,    81,   253,    77,    59,   596,   236,     3,   238,   291,
      50,     7,   238,   239,    82,   427,    82,   293,   486,    59,
      60,     3,   470,   445,    77,     7,   448,   404,    81,    59,
      60,     9,    77,    78,    30,     3,     4,    76,   281,     7,
     508,   284,   300,    81,   287,    76,   365,   366,    30,    59,
      60,   185,     3,     4,    50,   396,   314,   300,    76,   335,
      76,     7,    30,    59,    60,    81,    76,    59,    50,   299,
     300,   483,   408,    76,   300,   407,    77,    59,    81,    30,
      81,   413,    50,    78,    30,   219,    76,    38,   314,   389,
     390,    59,    60,   393,   435,   365,   366,     3,     4,    50,
      76,     7,    77,    82,    50,   446,    81,   448,    59,    78,
     410,   411,   412,    59,    60,   415,   416,    59,    60,   395,
      76,    76,   365,   366,    30,    81,   369,    77,    77,   505,
      38,    81,   468,   469,    76,    59,   436,   425,   408,   475,
     476,   441,    27,   409,    50,   427,   376,   377,   414,   436,
     437,   377,     9,    59,    83,   425,   532,     1,    59,    60,
       4,     5,     6,     7,    27,   408,    10,    30,    12,    13,
      14,    36,    77,    36,   417,    76,    81,     3,     4,   455,
     423,   471,   425,    30,    28,    77,   640,    77,   642,    81,
      59,    60,   492,   436,   437,    77,    59,    60,   468,   469,
      36,   483,    81,    50,    78,   475,   476,    48,    49,    50,
      51,    52,    59,    60,    77,   505,     6,     7,    81,   495,
      59,    60,    12,    13,    14,   468,   469,   527,     1,   505,
       3,     4,   475,   476,     1,    59,    60,     4,    82,     6,
       7,    76,   532,    77,    78,    12,    13,    14,    50,    51,
      52,   627,   684,   543,    59,    60,   532,    76,   505,   505,
     692,    28,   505,   505,    31,    76,   621,    38,   544,    76,
     521,    83,   572,    54,    55,   409,    57,    58,    59,    60,
     414,    91,    92,   573,   468,   469,   576,   577,   588,    83,
      76,   667,   668,   551,   584,    76,    76,    76,    36,   640,
      83,   642,    78,    78,   591,   593,    78,    32,   551,   599,
     561,    38,    76,    83,   561,   561,   606,     3,   561,   561,
     550,   551,    77,   593,    81,   551,    78,   617,    78,    78,
       4,     5,     6,     7,    38,    38,    10,   627,    12,    13,
      14,    46,    47,    48,    49,    50,    51,    52,   591,    78,
     593,   627,    78,    81,    28,   151,    30,   491,    78,   649,
     156,   157,    83,    38,    59,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,    59,    59,    38,
      77,   671,     5,     6,     7,    77,     7,   677,    38,    12,
      13,    14,     1,    77,     3,     4,     5,     6,     7,     8,
       9,    77,    11,    12,    13,    14,    15,    30,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    16,    33,    34,    78,     4,     5,     6,
       7,    40,    59,    77,    43,    12,    13,    14,    77,    48,
      49,    50,    59,    76,    17,    54,    55,    77,    76,     1,
      59,    28,     4,     5,     6,     7,     5,     6,     7,    77,
      12,    13,    14,    12,    13,    14,   262,   263,    77,    78,
      79,    80,    76,    82,    76,     1,    28,     3,     4,     5,
       6,     7,     8,     9,     9,    11,    12,    13,    14,    15,
      77,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    77,    33,    34,     3,
       4,     5,     6,     7,    40,    54,    55,    43,    57,    58,
      59,    60,    48,    49,    50,    59,    77,    81,    54,    55,
      82,    77,    76,    59,    76,   294,     1,    77,   334,     4,
      77,     6,     7,   576,   215,    55,   446,    12,    13,    14,
     346,    77,   561,    79,    80,   426,    82,   191,   293,   511,
     433,   464,   239,    28,   329,   435,    31,   247,     1,   337,
       3,     4,   335,   448,   446,     8,     9,   397,    11,   627,
     627,   288,    15,   379,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,   674,    29,    -1,    31,   672,
      33,    34,    -1,   399,    -1,    -1,    -1,    40,   369,    -1,
      43,    -1,    77,    78,    -1,    48,    49,    50,    -1,    -1,
      -1,    54,    55,    -1,    -1,    -1,    59,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,   433,    -1,    -1,
      -1,    -1,    -1,    -1,    77,    78,    79,    80,    -1,    82,
       1,    -1,     3,     4,     5,     6,     7,    -1,    -1,    10,
     456,    12,    13,    14,    -1,    -1,    -1,    -1,    -1,   465,
     466,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    30,
      -1,     1,    -1,     3,     4,    -1,    -1,    -1,     8,     9,
     486,    11,    -1,   489,    -1,    15,    -1,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    -1,    29,
      -1,    31,   508,    33,    34,   511,    -1,   513,    -1,    -1,
      40,    -1,    -1,    43,    -1,    76,    -1,    -1,    48,    49,
      50,    -1,   528,    -1,    54,    55,    -1,    -1,    -1,    59,
      -1,    -1,    -1,   539,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    77,    -1,    79,
      80,    -1,    82,    -1,    -1,     1,   562,     3,     4,   565,
      -1,    -1,     8,     9,    -1,    11,    -1,    -1,    -1,    15,
      -1,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    -1,    29,    -1,    31,    -1,    33,    34,    -1,
      -1,    -1,    -1,    -1,    40,    -1,    -1,    43,    -1,    -1,
      -1,    -1,    48,    49,    50,    -1,   612,    -1,    54,    55,
      -1,    -1,     1,    59,     3,     4,    -1,     6,     7,     8,
       9,    -1,    11,    12,    13,    14,    -1,    -1,    -1,    -1,
      -1,    77,    -1,    79,    80,    -1,    82,    -1,    -1,    28,
      29,    -1,    31,    -1,    33,    34,    -1,    -1,    -1,    -1,
      -1,    40,    -1,    -1,    43,    -1,    -1,    -1,    -1,    48,
      49,    50,    -1,    -1,    -1,    54,    55,    -1,    -1,     1,
      59,     3,     4,    -1,    -1,    -1,     8,     9,    -1,    11,
      -1,    -1,    -1,     1,    -1,    -1,     4,     5,     6,     7,
      79,    80,    10,    82,    12,    13,    14,    29,    -1,    31,
      -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      28,    43,    30,    -1,    -1,    -1,    48,    49,    50,    -1,
      -1,    -1,    54,    55,    -1,    -1,    58,    59,    60,     1,
      -1,     3,     4,    -1,    -1,    -1,     8,     9,    -1,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    78,    79,    80,    -1,
      82,    -1,    -1,    -1,    -1,    -1,    -1,    29,    76,    31,
      -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    43,    -1,    -1,    -1,    -1,    48,    49,    50,    -1,
      -1,    -1,    54,    55,    -1,    -1,    58,    59,    60,     1,
      -1,     3,    -1,    -1,    -1,    -1,     8,     9,    -1,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    78,    79,    80,    -1,
      82,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    31,
      -1,    33,    34,    -1,    36,    -1,    -1,    -1,    40,    -1,
      -1,    43,    -1,    -1,    -1,    -1,    48,    49,    50,    -1,
      -1,    -1,    54,    55,    -1,    -1,    58,    59,    60,     1,
      -1,     3,    -1,    -1,    -1,    -1,     8,     9,    -1,    11,
      -1,    -1,    -1,     4,     5,     6,     7,    79,    80,    -1,
      82,    12,    13,    14,    -1,    -1,    -1,    29,    -1,    31,
      -1,    33,    34,    -1,    -1,    -1,    -1,    28,    40,    30,
      -1,    43,    -1,    -1,    -1,    -1,    48,    49,    50,    -1,
      -1,    -1,    54,    55,     1,    -1,     3,    59,    -1,    -1,
      -1,     8,     9,     1,    11,    -1,     4,     5,     6,     7,
      -1,    -1,    -1,    -1,    12,    13,    14,    79,    80,    -1,
      82,    -1,    29,    -1,    31,    -1,    33,    34,    -1,    27,
      28,    -1,    30,    40,    -1,    -1,    43,    -1,    36,    -1,
      -1,    48,    49,    50,    -1,    -1,    -1,    54,    55,    -1,
      -1,    -1,    59,    45,    46,    47,    48,    49,    50,    51,
      52,    59,    60,    -1,    -1,     1,    -1,    -1,     4,     5,
       6,     7,    79,    80,    -1,    82,    12,    13,    14,    77,
      -1,    -1,    -1,    81,    82,    -1,    -1,    -1,    -1,    -1,
      -1,    27,    28,     1,    30,    -1,     4,     5,     6,     7,
      36,    -1,    -1,     3,    12,    13,    14,    -1,     8,     9,
      -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,
      28,    -1,    30,    59,    60,    -1,    -1,    -1,    36,    29,
       3,    31,    -1,    33,    34,     8,     9,    -1,    11,    -1,
      40,    77,    -1,    43,    -1,    81,    82,    -1,    48,    49,
      50,    -1,    -1,    -1,    54,    55,    29,    -1,    31,    59,
      33,    34,    -1,    -1,    -1,    -1,    -1,    40,    -1,    77,
      43,    -1,    -1,    81,    82,    48,    49,    50,    -1,    79,
      80,    54,    55,    83,    -1,     3,    59,    -1,    -1,    -1,
       8,     9,    -1,    11,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    79,    80,    -1,    -1,
      83,    29,     3,    31,    -1,    33,    34,     8,     9,    -1,
      11,    -1,    40,    -1,    -1,    43,    -1,    -1,    -1,    -1,
      48,    49,    50,    -1,    -1,    -1,    54,    55,    29,    -1,
      31,    59,    33,    34,    -1,    -1,    -1,    -1,    -1,    40,
      -1,    -1,    43,    -1,    -1,    -1,    -1,    48,    49,    50,
      -1,    79,    80,    54,    55,    83,    -1,     3,    59,    -1,
      -1,    -1,     8,     9,    -1,    11,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    -1,    79,    80,
      -1,    -1,    83,    29,     3,    31,    -1,    33,    34,     8,
       9,    -1,    11,    -1,    40,    -1,    -1,    43,    -1,    -1,
      -1,    -1,    48,    49,    50,    -1,    -1,    -1,    54,    55,
      29,    -1,    31,    59,    33,    34,    -1,     4,    -1,     6,
       7,    40,    -1,    -1,    43,    12,    13,    14,    -1,    48,
      49,    50,    -1,    79,    80,    54,    55,    83,    -1,     3,
      59,    28,    -1,    30,     8,     9,    -1,    11,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    -1,    -1,    -1,
      79,    80,    -1,    50,    83,    29,    -1,    31,    -1,    33,
      34,    10,    59,    60,    -1,    -1,    40,    -1,    -1,    43,
      -1,    -1,    -1,    -1,    48,    49,    50,    -1,    -1,    -1,
      54,    55,    -1,    -1,    -1,    59,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    -1,    79,    80,    -1,    -1,    83,
       3,     4,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    15,    -1,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    -1,
      33,    34,    -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,
      43,    -1,    -1,    -1,    -1,    48,    49,    50,    -1,    -1,
      -1,    54,    55,    -1,    -1,    -1,    59,    -1,    -1,    -1,
       4,     5,     6,     7,    -1,    -1,    -1,    -1,    12,    13,
      14,    -1,    -1,    -1,    77,    -1,    79,    80,    -1,    82,
       3,     4,    -1,    -1,    28,     8,     9,    -1,    11,    -1,
      -1,    -1,    15,    -1,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    -1,    29,    -1,    31,    -1,
      33,    34,    -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,
      43,    -1,    -1,    -1,    -1,    48,    49,    50,    -1,    -1,
      -1,    54,    55,    77,     3,    -1,    59,    -1,    -1,     8,
       9,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    77,    -1,    79,    80,    -1,    82,
      29,    -1,    31,    -1,    33,    34,    -1,    -1,    -1,    -1,
      -1,    40,    -1,    -1,    43,    -1,    -1,    -1,    -1,    48,
      49,    50,    -1,    -1,    -1,    54,    55,    -1,    -1,    -1,
      59,     3,     4,     5,     6,     7,     8,     9,    -1,    11,
      12,    13,    14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      79,    80,    -1,    82,    -1,    -1,    28,    29,    30,    31,
      -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    43,    -1,    -1,    -1,    -1,    48,    49,    50,    -1,
      -1,    -1,    54,    55,    -1,     3,     4,    59,     6,     7,
       8,     9,    -1,    11,    12,    13,    14,    -1,     3,    -1,
      -1,    -1,    -1,     8,     9,    -1,    11,    79,    80,    -1,
      28,    29,    -1,    31,    -1,    33,    34,    -1,    -1,    -1,
      -1,    -1,    40,    -1,    29,    43,    31,    -1,    33,    34,
      48,    49,    50,    -1,    -1,    40,    54,    55,    43,    -1,
      -1,    59,    -1,    48,    49,    50,    -1,    -1,    -1,    54,
      55,     3,    -1,    -1,    59,    -1,     8,     9,    -1,    11,
      -1,    79,    80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    77,    -1,    79,    80,    -1,    29,     3,    31,
      -1,    33,    34,     8,     9,    -1,    11,    -1,    40,    -1,
      -1,    43,    -1,    -1,    -1,    -1,    48,    49,    50,    -1,
      -1,    -1,    54,    55,    29,     3,    31,    59,    33,    34,
       8,     9,    -1,    11,    -1,    40,    -1,    -1,    43,    -1,
      -1,    -1,    -1,    48,    49,    50,    -1,    79,    80,    54,
      55,    29,     3,    31,    59,    33,    34,     8,     9,    -1,
      11,    -1,    40,    -1,    -1,    43,    -1,    -1,    -1,    -1,
      48,    49,    50,    -1,    79,    80,    54,    55,    29,    -1,
      31,    59,    33,    34,    -1,    -1,    -1,    -1,    -1,    40,
      -1,    -1,    43,    -1,    -1,    -1,    -1,    48,    49,    50,
      -1,    79,    80,    54,    55,    -1,    -1,     1,    59,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    -1,    12,    13,
      14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,    80,
      -1,    -1,    -1,    27,    28,    -1,    30,    31,     4,     5,
       6,     7,     4,     5,     6,     7,    12,    13,    14,    -1,
      12,    13,    14,    -1,    -1,    10,    50,    -1,    -1,    -1,
      -1,    -1,    28,    -1,    30,    59,    28,    -1,    30,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    36,    37,    77,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    77,    -1,    -1,    -1,    77,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    36,    37,    83,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    30,    -1,    -1,    -1,    -1,    35,    36,
      37,    -1,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    83,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    35,    36,    37,    -1,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      37,    -1,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    85,    86,    87,     0,    88,     1,     4,     5,     6,
       7,    12,    13,    14,    27,    28,    30,    31,    77,    89,
      90,    91,   123,   126,   130,   131,   134,   144,   145,   169,
     170,   171,   172,   241,    89,    77,    78,   144,   144,   144,
      59,    59,    59,     3,    50,    59,   137,   141,   144,   168,
      77,   123,    77,   123,   131,   134,   144,     5,     7,   127,
     145,     3,     4,    82,    98,    82,    98,    82,    98,    89,
       3,     8,     9,    11,    29,    33,    34,    40,    43,    48,
      49,    50,    54,    55,    59,    79,    80,    99,   100,   102,
     103,   104,   105,   106,   108,   114,   116,   241,     7,   100,
     132,   134,   186,   188,    59,   189,   168,    77,    81,   124,
       1,    27,    59,    60,    96,   138,     4,    50,    59,   136,
     139,   144,   165,   166,   168,   137,   168,   127,     5,     6,
       7,   135,   144,   172,   179,   180,    82,   179,    82,   176,
      82,   106,   106,    98,   106,     1,   100,   115,   186,   106,
      76,    81,    59,   103,    59,   103,    35,    36,    37,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    54,    55,    57,    58,    59,    60,     9,
     106,    76,    50,    59,    60,   144,   187,   190,   133,    76,
       7,   134,   187,     5,     6,     7,    98,   146,   147,   148,
       7,   168,    76,   139,   165,   168,    59,   236,   237,    50,
      83,   100,     1,   117,   118,   119,   194,   206,   143,   144,
     189,   166,    77,    81,   124,     1,    92,   138,    59,    60,
      77,     1,    94,    78,     1,    77,   132,   181,   188,   241,
     173,    78,   174,     1,    98,   184,   185,   175,    76,    76,
      82,   200,   201,    76,    77,   108,   186,   186,   108,   108,
     111,   113,   110,   109,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,    98,    98,   101,   102,
     100,   189,   190,   229,   230,    83,   100,   124,    59,    60,
     135,   133,    76,    81,    59,   116,     1,     3,    10,   126,
     130,   231,   233,   234,   235,   238,   239,    83,    83,    77,
      97,   194,    10,   118,   207,    36,   166,    76,   139,   166,
     117,   143,   236,    83,   100,   117,   143,   123,    77,   123,
     181,   179,   143,   179,    36,    81,   178,   184,    78,   195,
      76,    82,   106,    76,    76,   100,    38,   108,   108,    76,
      83,   190,    76,   231,    83,   190,   229,    83,   100,    76,
     147,     3,   101,    76,    76,   123,   123,    76,    77,    81,
      76,    81,     1,   199,   201,   120,   128,   131,   134,   142,
      93,    36,    83,    95,   182,   183,   206,   182,   206,    78,
      78,   108,   185,    78,   178,    32,   196,   197,   198,   107,
      38,   108,    83,    76,    81,    76,     4,    50,    59,   144,
     167,   168,   187,    50,   144,   168,   187,   232,    10,   235,
       3,   201,    77,   123,    77,   123,   134,   129,     1,    82,
     108,   149,   199,   140,   199,    81,   207,   207,   143,   143,
     143,    78,    98,   240,     1,   121,   122,   191,   192,   194,
     206,   209,   198,     1,     3,    58,    60,    82,    98,   108,
     151,   152,   153,   155,   157,   158,   112,   102,   189,   124,
      59,    60,   143,   143,   143,   189,   124,   143,   143,   231,
     136,   137,   168,   129,     5,   135,   150,   149,   183,    38,
     143,   144,   165,   143,    77,    81,    78,   194,   121,   191,
     193,    78,   194,   206,   209,   207,    98,   108,   156,    38,
      78,    81,   177,    36,   158,   155,   108,    76,   167,   167,
     236,    50,    83,   100,    77,    77,   151,   108,    38,   143,
      98,    78,   207,     4,    15,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    77,    98,   100,   125,
     126,   130,   201,   202,   203,   204,   210,   211,   219,   220,
     222,   241,    10,    83,   151,   154,   153,   155,    83,    83,
      78,   143,   108,    59,   213,   205,    59,    59,   108,    38,
      77,    77,    77,   100,    50,    98,     7,   223,    38,    77,
      77,   123,    77,   123,    16,     1,   206,   208,     1,    59,
     125,   108,    78,   155,   143,   100,    59,   208,   100,   114,
     224,   100,    10,    38,    77,   100,    77,    59,   143,   136,
     159,   165,   137,   162,   168,     1,   212,   207,   100,    83,
      76,   100,    17,    76,    77,    76,   108,    77,   100,    77,
     160,    77,   163,   208,   211,   222,    76,    76,   221,   215,
     218,    38,    38,    76,   117,   117,   208,    77,   214,   208,
     224,   208,     9,   225,   226,   227,    77,   161,   164,   208,
      77,    59,    38,    76,    81,   201,   201,   216,   100,   225,
      77,   227,   224,    76,    38,    76,    76,   116,   228,    77,
     217,    76,    81,   208,    77,   116
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    84,    85,    85,    87,    86,    88,    86,    89,    89,
      89,    89,    90,    90,    90,    90,    90,    90,    90,    90,
      92,    93,    91,    91,    94,    95,    91,    91,    96,    97,
      91,    91,    98,    98,    99,    99,    99,    99,    99,    99,
      99,   100,   101,   101,   102,   102,   103,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   104,   105,   106,
     106,   107,   106,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   109,   108,   110,   108,
     111,   112,   108,   113,   108,   108,   108,   114,   114,   114,
     114,   114,   115,   114,   114,   114,   114,   114,   114,   114,
     116,   116,   117,   117,   117,   118,   119,   119,   119,   119,
     120,   120,   120,   120,   121,   122,   122,   122,   122,   123,
     124,   125,   125,   125,   125,   125,   125,   125,   126,   126,
     127,   127,   127,   127,   128,   128,   129,   129,   129,   130,
     130,   130,   130,   131,   131,   131,   131,   132,   132,   133,
     133,   134,   134,   134,   134,   134,   135,   135,   135,   136,
     136,   137,   137,   138,   138,   140,   139,   139,   142,   141,
     141,   143,   143,   144,   144,   145,   146,   146,   147,   147,
     147,   147,   147,   148,   148,   148,   148,   149,   150,   149,
     149,   151,   151,   152,   152,   153,   153,   154,   153,   153,
     156,   155,   155,   155,   157,   157,   158,   158,   158,   160,
     161,   159,   163,   164,   162,   165,   165,   166,   166,   166,
     166,   166,   166,   166,   167,   167,   167,   167,   167,   167,
     167,   168,   168,   168,   168,   168,   168,   168,   168,   169,
     169,   170,   170,   171,   171,   173,   172,   172,   172,   174,
     172,   172,   172,   175,   172,   176,   172,   172,   177,   177,
     178,   178,   179,   179,   180,   180,   180,   181,   181,   181,
     181,   181,   181,   182,   182,   183,   183,   183,   184,   184,
     184,   185,   185,   186,   186,   187,   187,   188,   188,   189,
     189,   190,   190,   190,   190,   190,   190,   190,   190,   190,
     190,   191,   192,   192,   192,   193,   193,   194,   195,   196,
     196,   197,   197,   198,   199,   199,   200,   201,   201,   201,
     201,   202,   202,   203,   205,   204,   206,   207,   208,   208,
     209,   210,   210,   211,   211,   211,   212,   211,   211,   211,
     213,   214,   211,   211,   211,   215,   216,   217,   211,   218,
     211,   211,   211,   211,   211,   211,   211,   211,   211,   211,
     211,   211,   219,   221,   220,   222,   222,   222,   222,   223,
     223,   224,   224,   225,   225,   226,   226,   227,   228,   228,
     230,   229,   231,   232,   231,   231,   233,   233,   233,   233,
     234,   234,   235,   235,   235,   235,   235,   237,   236,   238,
     238,   239,   239,   240,   240,   241
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     1,     0,     2,     0,     3,     1,     1,
       5,     2,     3,     4,     4,     2,     2,     2,     2,     1,
       0,     0,     7,     4,     0,     0,     7,     4,     0,     0,
       6,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     1,     1,     3,     1,     2,     2,     2,
       2,     2,     4,     2,     4,     2,     2,     1,     1,     1,
       4,     0,     7,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     0,     4,     0,     4,
       0,     0,     7,     0,     5,     3,     3,     1,     1,     1,
       3,     3,     0,     4,     4,     4,     3,     3,     2,     2,
       1,     2,     0,     1,     2,     3,     1,     1,     2,     2,
       4,     4,     2,     2,     3,     1,     1,     2,     2,     0,
       0,     4,     4,     3,     3,     2,     2,     2,     2,     3,
       0,     2,     2,     2,     2,     3,     0,     2,     2,     1,
       1,     2,     2,     1,     1,     2,     2,     2,     3,     0,
       2,     1,     1,     1,     4,     4,     1,     1,     1,     1,
       3,     1,     3,     0,     4,     0,     6,     3,     0,     6,
       3,     0,     1,     1,     2,     6,     1,     3,     0,     1,
       4,     6,     4,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     2,     1,     3,     3,     2,     0,     4,     1,
       0,     4,     1,     1,     1,     2,     2,     5,     3,     0,
       0,     5,     0,     0,     5,     1,     1,     3,     3,     4,
       3,     3,     3,     1,     3,     4,     4,     3,     3,     3,
       1,     3,     3,     3,     4,     4,     3,     3,     1,     1,
       2,     1,     2,     1,     2,     0,     7,     5,     2,     0,
       7,     5,     2,     0,     8,     0,     7,     2,     0,     1,
       0,     1,     1,     2,     0,     3,     2,     3,     5,     3,
       1,     1,     2,     1,     3,     4,     6,     5,     1,     3,
       1,     1,     3,     2,     2,     0,     1,     1,     2,     0,
       2,     3,     3,     2,     3,     4,     3,     2,     3,     2,
       3,     1,     1,     2,     2,     0,     1,     2,     0,     0,
       1,     1,     2,     3,     1,     2,     1,     2,     6,     5,
       5,     2,     2,     4,     0,     4,     0,     0,     3,     4,
       3,     1,     1,     1,     1,     2,     0,     4,     1,     3,
       0,     0,     7,     5,     2,     0,     0,     0,    12,     0,
       6,     2,     2,     2,     3,     6,     8,    10,    12,     3,
       4,     1,     1,     0,     6,     3,     5,     2,     3,     0,
       1,     0,     1,     0,     1,     1,     3,     4,     1,     3,
       0,     2,     2,     0,     4,     2,     0,     1,     1,     3,
       1,     3,     4,     4,     4,     4,     4,     0,     2,     1,
       2,     1,     3,     1,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
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
  case 2:
#line 235 "c-parse.y"
                { if (pedantic)
		    pedwarn ("ANSI C forbids an empty source file");
		  finish_file ();
		}
#line 2319 "c-parse.c"
    break;

  case 3:
#line 240 "c-parse.y"
                {
		  /* In case there were missing closebraces,
		     get us back to the global binding level.  */
		  while (! global_bindings_p ())
		    poplevel (0, 0, 0);
		  finish_file ();
		}
#line 2331 "c-parse.c"
    break;

  case 4:
#line 254 "c-parse.y"
        {(yyval.ttype) = NULL_TREE; }
#line 2337 "c-parse.c"
    break;

  case 6:
#line 255 "c-parse.y"
                  {(yyval.ttype) = NULL_TREE; }
#line 2343 "c-parse.c"
    break;

  case 10:
#line 262 "c-parse.y"
                { STRIP_NOPS ((yyvsp[-2].ttype));
		  if ((TREE_CODE ((yyvsp[-2].ttype)) == ADDR_EXPR
		       && TREE_CODE (TREE_OPERAND ((yyvsp[-2].ttype), 0)) == STRING_CST)
		      || TREE_CODE ((yyvsp[-2].ttype)) == STRING_CST)
		    assemble_asm ((yyvsp[-2].ttype));
		  else
		    error ("argument of `asm' is not a constant string"); }
#line 2355 "c-parse.c"
    break;

  case 11:
#line 270 "c-parse.y"
                { pedantic = (yyvsp[-1].itype); }
#line 2361 "c-parse.c"
    break;

  case 12:
#line 275 "c-parse.y"
                { if (pedantic)
		    error ("ANSI C forbids data definition with no type or storage class");
		  else if (!flag_traditional)
		    warning ("data definition has no type or storage class"); 

		  current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[-2].itype)); }
#line 2375 "c-parse.c"
    break;

  case 13:
#line 285 "c-parse.y"
                { current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[-2].itype)); }
#line 2384 "c-parse.c"
    break;

  case 14:
#line 290 "c-parse.y"
                { current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[-2].itype));  }
#line 2393 "c-parse.c"
    break;

  case 15:
#line 295 "c-parse.y"
          { pedwarn ("empty declaration"); }
#line 2399 "c-parse.c"
    break;

  case 16:
#line 297 "c-parse.y"
          { shadow_tag ((yyvsp[-1].ttype)); }
#line 2405 "c-parse.c"
    break;

  case 19:
#line 301 "c-parse.y"
                { if (pedantic)
		    pedwarn ("ANSI C does not allow extra `;' outside of a function"); }
#line 2412 "c-parse.c"
    break;

  case 20:
#line 307 "c-parse.y"
                { if (! start_function (current_declspecs, (yyvsp[0].ttype),
					prefix_attributes, NULL_TREE, 0))
		    YYERROR1;
		  reinit_parse_for_function (); }
#line 2421 "c-parse.c"
    break;

  case 21:
#line 312 "c-parse.y"
                { store_parm_decls (); }
#line 2427 "c-parse.c"
    break;

  case 22:
#line 314 "c-parse.y"
                { finish_function (0); 
		  current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[-5].itype)); }
#line 2437 "c-parse.c"
    break;

  case 23:
#line 320 "c-parse.y"
                { current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[-2].itype)); }
#line 2446 "c-parse.c"
    break;

  case 24:
#line 325 "c-parse.y"
                { if (! start_function (current_declspecs, (yyvsp[0].ttype),
					prefix_attributes, NULL_TREE, 0))
		    YYERROR1;
		  reinit_parse_for_function (); }
#line 2455 "c-parse.c"
    break;

  case 25:
#line 330 "c-parse.y"
                { store_parm_decls (); }
#line 2461 "c-parse.c"
    break;

  case 26:
#line 332 "c-parse.y"
                { finish_function (0); 
		  current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[-5].itype)); }
#line 2471 "c-parse.c"
    break;

  case 27:
#line 338 "c-parse.y"
                { current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[-2].itype)); }
#line 2480 "c-parse.c"
    break;

  case 28:
#line 343 "c-parse.y"
                { if (! start_function (NULL_TREE, (yyvsp[0].ttype),
					prefix_attributes, NULL_TREE, 0))
		    YYERROR1;
		  reinit_parse_for_function (); }
#line 2489 "c-parse.c"
    break;

  case 29:
#line 348 "c-parse.y"
                { store_parm_decls (); }
#line 2495 "c-parse.c"
    break;

  case 30:
#line 350 "c-parse.y"
                { finish_function (0); 
		  current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[-5].itype)); }
#line 2505 "c-parse.c"
    break;

  case 31:
#line 356 "c-parse.y"
                { current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[-2].itype)); }
#line 2514 "c-parse.c"
    break;

  case 34:
#line 368 "c-parse.y"
                { (yyval.code) = ADDR_EXPR; }
#line 2520 "c-parse.c"
    break;

  case 35:
#line 370 "c-parse.y"
                { (yyval.code) = NEGATE_EXPR; }
#line 2526 "c-parse.c"
    break;

  case 36:
#line 372 "c-parse.y"
                { (yyval.code) = CONVERT_EXPR; }
#line 2532 "c-parse.c"
    break;

  case 37:
#line 374 "c-parse.y"
                { (yyval.code) = PREINCREMENT_EXPR; }
#line 2538 "c-parse.c"
    break;

  case 38:
#line 376 "c-parse.y"
                { (yyval.code) = PREDECREMENT_EXPR; }
#line 2544 "c-parse.c"
    break;

  case 39:
#line 378 "c-parse.y"
                { (yyval.code) = BIT_NOT_EXPR; }
#line 2550 "c-parse.c"
    break;

  case 40:
#line 380 "c-parse.y"
                { (yyval.code) = TRUTH_NOT_EXPR; }
#line 2556 "c-parse.c"
    break;

  case 41:
#line 384 "c-parse.y"
                { (yyval.ttype) = build_compound_expr ((yyvsp[0].ttype)); }
#line 2562 "c-parse.c"
    break;

  case 42:
#line 389 "c-parse.y"
                { (yyval.ttype) = NULL_TREE; }
#line 2568 "c-parse.c"
    break;

  case 44:
#line 395 "c-parse.y"
                { (yyval.ttype) = build_tree_list (NULL_TREE, (yyvsp[0].ttype)); }
#line 2574 "c-parse.c"
    break;

  case 45:
#line 397 "c-parse.y"
                { chainon ((yyvsp[-2].ttype), build_tree_list (NULL_TREE, (yyvsp[0].ttype))); }
#line 2580 "c-parse.c"
    break;

  case 47:
#line 403 "c-parse.y"
                { (yyval.ttype) = build_indirect_ref ((yyvsp[0].ttype), "unary *"); }
#line 2586 "c-parse.c"
    break;

  case 48:
#line 406 "c-parse.y"
                { (yyval.ttype) = (yyvsp[0].ttype);
		  pedantic = (yyvsp[-1].itype); }
#line 2593 "c-parse.c"
    break;

  case 49:
#line 409 "c-parse.y"
                { (yyval.ttype) = build_unary_op ((yyvsp[-1].code), (yyvsp[0].ttype), 0);
		  overflow_warning ((yyval.ttype)); }
#line 2600 "c-parse.c"
    break;

  case 50:
#line 413 "c-parse.y"
                { tree label = lookup_label ((yyvsp[0].ttype));
		  if (pedantic)
		    pedwarn ("ANSI C forbids `&&'");
		  if (label == 0)
		    (yyval.ttype) = null_pointer_node;
		  else
		    {
		      TREE_USED (label) = 1;
		      (yyval.ttype) = build1 (ADDR_EXPR, ptr_type_node, label);
		      TREE_CONSTANT ((yyval.ttype)) = 1;
		    }
		}
#line 2617 "c-parse.c"
    break;

  case 51:
#line 441 "c-parse.y"
                { skip_evaluation--;
		  if (TREE_CODE ((yyvsp[0].ttype)) == COMPONENT_REF
		      && DECL_C_BIT_FIELD (TREE_OPERAND ((yyvsp[0].ttype), 1)))
		    error ("`sizeof' applied to a bit-field");
		  (yyval.ttype) = c_sizeof (TREE_TYPE ((yyvsp[0].ttype))); }
#line 2627 "c-parse.c"
    break;

  case 52:
#line 447 "c-parse.y"
                { skip_evaluation--;
		  (yyval.ttype) = c_sizeof (groktypename ((yyvsp[-1].ttype))); }
#line 2634 "c-parse.c"
    break;

  case 53:
#line 450 "c-parse.y"
                { skip_evaluation--;
		  (yyval.ttype) = c_alignof_expr ((yyvsp[0].ttype)); }
#line 2641 "c-parse.c"
    break;

  case 54:
#line 453 "c-parse.y"
                { skip_evaluation--;
		  (yyval.ttype) = c_alignof (groktypename ((yyvsp[-1].ttype))); }
#line 2648 "c-parse.c"
    break;

  case 55:
#line 456 "c-parse.y"
                { (yyval.ttype) = build_unary_op (REALPART_EXPR, (yyvsp[0].ttype), 0); }
#line 2654 "c-parse.c"
    break;

  case 56:
#line 458 "c-parse.y"
                { (yyval.ttype) = build_unary_op (IMAGPART_EXPR, (yyvsp[0].ttype), 0); }
#line 2660 "c-parse.c"
    break;

  case 57:
#line 462 "c-parse.y"
               { skip_evaluation++; }
#line 2666 "c-parse.c"
    break;

  case 58:
#line 466 "c-parse.y"
                { skip_evaluation++; }
#line 2672 "c-parse.c"
    break;

  case 60:
#line 472 "c-parse.y"
                { tree type = groktypename ((yyvsp[-2].ttype));
		  (yyval.ttype) = build_c_cast (type, (yyvsp[0].ttype)); }
#line 2679 "c-parse.c"
    break;

  case 61:
#line 475 "c-parse.y"
                { start_init (NULL_TREE, NULL, 0);
		  (yyvsp[-2].ttype) = groktypename ((yyvsp[-2].ttype));
		  really_start_incremental_init ((yyvsp[-2].ttype)); }
#line 2687 "c-parse.c"
    break;

  case 62:
#line 479 "c-parse.y"
                { char *name;
		  tree result = pop_init_level (0);
		  tree type = (yyvsp[-5].ttype);
		  finish_init ();

		  if (pedantic && ! flag_isoc9x)
		    pedwarn ("ANSI C forbids constructor expressions");
		  if (TYPE_NAME (type) != 0)
		    {
		      if (TREE_CODE (TYPE_NAME (type)) == IDENTIFIER_NODE)
			name = IDENTIFIER_POINTER (TYPE_NAME (type));
		      else
			name = IDENTIFIER_POINTER (DECL_NAME (TYPE_NAME (type)));
		    }
		  else
		    name = "";
		  (yyval.ttype) = result;
		  if (TREE_CODE (type) == ARRAY_TYPE && TYPE_SIZE (type) == 0)
		    {
		      int failure = complete_array_type (type, (yyval.ttype), 1);
		      if (failure)
			abort ();
		    }
		}
#line 2716 "c-parse.c"
    break;

  case 64:
#line 508 "c-parse.y"
                { (yyval.ttype) = parser_build_binary_op ((yyvsp[-1].code), (yyvsp[-2].ttype), (yyvsp[0].ttype)); }
#line 2722 "c-parse.c"
    break;

  case 65:
#line 510 "c-parse.y"
                { (yyval.ttype) = parser_build_binary_op ((yyvsp[-1].code), (yyvsp[-2].ttype), (yyvsp[0].ttype)); }
#line 2728 "c-parse.c"
    break;

  case 66:
#line 512 "c-parse.y"
                { (yyval.ttype) = parser_build_binary_op ((yyvsp[-1].code), (yyvsp[-2].ttype), (yyvsp[0].ttype)); }
#line 2734 "c-parse.c"
    break;

  case 67:
#line 514 "c-parse.y"
                { (yyval.ttype) = parser_build_binary_op ((yyvsp[-1].code), (yyvsp[-2].ttype), (yyvsp[0].ttype)); }
#line 2740 "c-parse.c"
    break;

  case 68:
#line 516 "c-parse.y"
                { (yyval.ttype) = parser_build_binary_op ((yyvsp[-1].code), (yyvsp[-2].ttype), (yyvsp[0].ttype)); }
#line 2746 "c-parse.c"
    break;

  case 69:
#line 518 "c-parse.y"
                { (yyval.ttype) = parser_build_binary_op ((yyvsp[-1].code), (yyvsp[-2].ttype), (yyvsp[0].ttype)); }
#line 2752 "c-parse.c"
    break;

  case 70:
#line 520 "c-parse.y"
                { (yyval.ttype) = parser_build_binary_op ((yyvsp[-1].code), (yyvsp[-2].ttype), (yyvsp[0].ttype)); }
#line 2758 "c-parse.c"
    break;

  case 71:
#line 522 "c-parse.y"
                { (yyval.ttype) = parser_build_binary_op ((yyvsp[-1].code), (yyvsp[-2].ttype), (yyvsp[0].ttype)); }
#line 2764 "c-parse.c"
    break;

  case 72:
#line 524 "c-parse.y"
                { (yyval.ttype) = parser_build_binary_op ((yyvsp[-1].code), (yyvsp[-2].ttype), (yyvsp[0].ttype)); }
#line 2770 "c-parse.c"
    break;

  case 73:
#line 526 "c-parse.y"
                { (yyval.ttype) = parser_build_binary_op ((yyvsp[-1].code), (yyvsp[-2].ttype), (yyvsp[0].ttype)); }
#line 2776 "c-parse.c"
    break;

  case 74:
#line 528 "c-parse.y"
                { (yyval.ttype) = parser_build_binary_op ((yyvsp[-1].code), (yyvsp[-2].ttype), (yyvsp[0].ttype)); }
#line 2782 "c-parse.c"
    break;

  case 75:
#line 530 "c-parse.y"
                { (yyval.ttype) = parser_build_binary_op ((yyvsp[-1].code), (yyvsp[-2].ttype), (yyvsp[0].ttype)); }
#line 2788 "c-parse.c"
    break;

  case 76:
#line 532 "c-parse.y"
                { (yyvsp[-1].ttype) = truthvalue_conversion (default_conversion ((yyvsp[-1].ttype)));
		  skip_evaluation += (yyvsp[-1].ttype) == boolean_false_node; }
#line 2795 "c-parse.c"
    break;

  case 77:
#line 535 "c-parse.y"
                { skip_evaluation -= (yyvsp[-3].ttype) == boolean_false_node;
		  (yyval.ttype) = parser_build_binary_op (TRUTH_ANDIF_EXPR, (yyvsp[-3].ttype), (yyvsp[0].ttype)); }
#line 2802 "c-parse.c"
    break;

  case 78:
#line 538 "c-parse.y"
                { (yyvsp[-1].ttype) = truthvalue_conversion (default_conversion ((yyvsp[-1].ttype)));
		  skip_evaluation += (yyvsp[-1].ttype) == boolean_true_node; }
#line 2809 "c-parse.c"
    break;

  case 79:
#line 541 "c-parse.y"
                { skip_evaluation -= (yyvsp[-3].ttype) == boolean_true_node;
		  (yyval.ttype) = parser_build_binary_op (TRUTH_ORIF_EXPR, (yyvsp[-3].ttype), (yyvsp[0].ttype)); }
#line 2816 "c-parse.c"
    break;

  case 80:
#line 544 "c-parse.y"
                { (yyvsp[-1].ttype) = truthvalue_conversion (default_conversion ((yyvsp[-1].ttype)));
		  skip_evaluation += (yyvsp[-1].ttype) == boolean_false_node; }
#line 2823 "c-parse.c"
    break;

  case 81:
#line 547 "c-parse.y"
                { skip_evaluation += (((yyvsp[-4].ttype) == boolean_true_node)
				      - ((yyvsp[-4].ttype) == boolean_false_node)); }
#line 2830 "c-parse.c"
    break;

  case 82:
#line 550 "c-parse.y"
                { skip_evaluation -= (yyvsp[-6].ttype) == boolean_true_node;
		  (yyval.ttype) = build_conditional_expr ((yyvsp[-6].ttype), (yyvsp[-3].ttype), (yyvsp[0].ttype)); }
#line 2837 "c-parse.c"
    break;

  case 83:
#line 553 "c-parse.y"
                { if (pedantic)
		    pedwarn ("ANSI C forbids omitting the middle term of a ?: expression");
		  /* Make sure first operand is calculated only once.  */
		  (yyvsp[0].ttype) = save_expr ((yyvsp[-1].ttype));
		  (yyvsp[-1].ttype) = truthvalue_conversion (default_conversion ((yyvsp[0].ttype)));
		  skip_evaluation += (yyvsp[-1].ttype) == boolean_true_node; }
#line 2848 "c-parse.c"
    break;

  case 84:
#line 560 "c-parse.y"
                { skip_evaluation -= (yyvsp[-4].ttype) == boolean_true_node;
		  (yyval.ttype) = build_conditional_expr ((yyvsp[-4].ttype), (yyvsp[-3].ttype), (yyvsp[0].ttype)); }
#line 2855 "c-parse.c"
    break;

  case 85:
#line 563 "c-parse.y"
                { char class;
		  (yyval.ttype) = build_modify_expr ((yyvsp[-2].ttype), NOP_EXPR, (yyvsp[0].ttype));
		  class = TREE_CODE_CLASS (TREE_CODE ((yyval.ttype)));
		  if (class == 'e' || class == '1'
		      || class == '2' || class == '<')
		    C_SET_EXP_ORIGINAL_CODE ((yyval.ttype), MODIFY_EXPR);
		}
#line 2867 "c-parse.c"
    break;

  case 86:
#line 571 "c-parse.y"
                { char class;
		  (yyval.ttype) = build_modify_expr ((yyvsp[-2].ttype), (yyvsp[-1].code), (yyvsp[0].ttype));
		  /* This inhibits warnings in truthvalue_conversion.  */
		  class = TREE_CODE_CLASS (TREE_CODE ((yyval.ttype)));
		  if (class == 'e' || class == '1'
		      || class == '2' || class == '<')
		    C_SET_EXP_ORIGINAL_CODE ((yyval.ttype), ERROR_MARK);
		}
#line 2880 "c-parse.c"
    break;

  case 87:
#line 583 "c-parse.y"
                {
		  (yyval.ttype) = lastiddecl;
		  if (!(yyval.ttype) || (yyval.ttype) == error_mark_node)
		    {
		      if (yychar == YYEMPTY)
			yychar = YYLEX;
		      if (yychar == '(')
			{
			    {
			      /* Ordinary implicit function declaration.  */
			      (yyval.ttype) = implicitly_declare ((yyvsp[0].ttype));
			      assemble_external ((yyval.ttype));
			      TREE_USED ((yyval.ttype)) = 1;
			    }
			}
		      else if (current_function_decl == 0)
			{
			  error ("`%s' undeclared here (not in a function)",
				 IDENTIFIER_POINTER ((yyvsp[0].ttype)));
			  (yyval.ttype) = error_mark_node;
			}
		      else
			{
			    {
			      if (IDENTIFIER_GLOBAL_VALUE ((yyvsp[0].ttype)) != error_mark_node
				  || IDENTIFIER_ERROR_LOCUS ((yyvsp[0].ttype)) != current_function_decl)
				{
				  error ("`%s' undeclared (first use in this function)",
					 IDENTIFIER_POINTER ((yyvsp[0].ttype)));

				  if (! undeclared_variable_notice)
				    {
				      error ("(Each undeclared identifier is reported only once");
				      error ("for each function it appears in.)");
				      undeclared_variable_notice = 1;
				    }
				}
			      (yyval.ttype) = error_mark_node;
			      /* Prevent repeated error messages.  */
			      IDENTIFIER_GLOBAL_VALUE ((yyvsp[0].ttype)) = error_mark_node;
			      IDENTIFIER_ERROR_LOCUS ((yyvsp[0].ttype)) = current_function_decl;
			    }
			}
		    }
		  else if (TREE_TYPE ((yyval.ttype)) == error_mark_node)
		    (yyval.ttype) = error_mark_node;
		  else if (C_DECL_ANTICIPATED ((yyval.ttype)))
		    {
		      /* The first time we see a build-in function used,
			 if it has not been declared.  */
		      C_DECL_ANTICIPATED ((yyval.ttype)) = 0;
		      if (yychar == YYEMPTY)
			yychar = YYLEX;
		      if (yychar == '(')
			{
			  /* Omit the implicit declaration we
			     would ordinarily do, so we don't lose
			     the actual built in type.
			     But print a diagnostic for the mismatch.  */
			    if (TREE_CODE ((yyval.ttype)) != FUNCTION_DECL)
			      error ("`%s' implicitly declared as function",
				     IDENTIFIER_POINTER (DECL_NAME ((yyval.ttype))));
			  else if ((TYPE_MODE (TREE_TYPE (TREE_TYPE ((yyval.ttype))))
				    != TYPE_MODE (integer_type_node))
				   && (TREE_TYPE (TREE_TYPE ((yyval.ttype)))
				       != void_type_node))
			    pedwarn ("type mismatch in implicit declaration for built-in function `%s'",
				     IDENTIFIER_POINTER (DECL_NAME ((yyval.ttype))));
			  /* If it really returns void, change that to int.  */
			  if (TREE_TYPE (TREE_TYPE ((yyval.ttype))) == void_type_node)
			    TREE_TYPE ((yyval.ttype))
			      = build_function_type (integer_type_node,
						     TYPE_ARG_TYPES (TREE_TYPE ((yyval.ttype))));
			}
		      else
			pedwarn ("built-in function `%s' used without declaration",
				 IDENTIFIER_POINTER (DECL_NAME ((yyval.ttype))));

		      /* Do what we would ordinarily do when a fn is used.  */
		      assemble_external ((yyval.ttype));
		      TREE_USED ((yyval.ttype)) = 1;
		    }
		  else
		    {
		      assemble_external ((yyval.ttype));
		      TREE_USED ((yyval.ttype)) = 1;
		    }

		  if (TREE_CODE ((yyval.ttype)) == CONST_DECL)
		    {
		      (yyval.ttype) = DECL_INITIAL ((yyval.ttype));
		      /* This is to prevent an enum whose value is 0
			 from being considered a null pointer constant.  */
		      (yyval.ttype) = build1 (NOP_EXPR, TREE_TYPE ((yyval.ttype)), (yyval.ttype));
		      TREE_CONSTANT ((yyval.ttype)) = 1;
		    }
		}
#line 2982 "c-parse.c"
    break;

  case 89:
#line 682 "c-parse.y"
                { (yyval.ttype) = combine_strings ((yyvsp[0].ttype)); }
#line 2988 "c-parse.c"
    break;

  case 90:
#line 684 "c-parse.y"
                { char class = TREE_CODE_CLASS (TREE_CODE ((yyvsp[-1].ttype)));
		  if (class == 'e' || class == '1'
		      || class == '2' || class == '<')
		    C_SET_EXP_ORIGINAL_CODE ((yyvsp[-1].ttype), ERROR_MARK);
		  (yyval.ttype) = (yyvsp[-1].ttype); }
#line 2998 "c-parse.c"
    break;

  case 91:
#line 690 "c-parse.y"
                { (yyval.ttype) = error_mark_node; }
#line 3004 "c-parse.c"
    break;

  case 92:
#line 692 "c-parse.y"
                { if (current_function_decl == 0)
		    {
		      error ("braced-group within expression allowed only inside a function");
		      YYERROR;
		    }
		  /* We must force a BLOCK for this level
		     so that, if it is not expanded later,
		     there is a way to turn off the entire subtree of blocks
		     that are contained in it.  */
		  keep_next_level ();
		  push_iterator_stack ();
		  push_label_level ();
		  (yyval.ttype) = expand_start_stmt_expr (); }
#line 3022 "c-parse.c"
    break;

  case 93:
#line 706 "c-parse.y"
                { tree rtl_exp;
		  if (pedantic)
		    pedwarn ("ANSI C forbids braced-groups within expressions");
		  pop_iterator_stack ();
		  pop_label_level ();
		  rtl_exp = expand_end_stmt_expr ((yyvsp[-2].ttype));
		  /* The statements have side effects, so the group does.  */
		  TREE_SIDE_EFFECTS (rtl_exp) = 1;

		  if (TREE_CODE ((yyvsp[-1].ttype)) == BLOCK)
		    {
		      /* Make a BIND_EXPR for the BLOCK already made.  */
		      (yyval.ttype) = build (BIND_EXPR, TREE_TYPE (rtl_exp),
				  NULL_TREE, rtl_exp, (yyvsp[-1].ttype));
		      /* Remove the block from the tree at this point.
			 It gets put back at the proper place
			 when the BIND_EXPR is expanded.  */
		      delete_block ((yyvsp[-1].ttype));
		    }
		  else
		    (yyval.ttype) = (yyvsp[-1].ttype);
		}
#line 3049 "c-parse.c"
    break;

  case 94:
#line 729 "c-parse.y"
                { (yyval.ttype) = build_function_call ((yyvsp[-3].ttype), (yyvsp[-1].ttype)); }
#line 3055 "c-parse.c"
    break;

  case 95:
#line 731 "c-parse.y"
                { (yyval.ttype) = build_array_ref ((yyvsp[-3].ttype), (yyvsp[-1].ttype)); }
#line 3061 "c-parse.c"
    break;

  case 96:
#line 733 "c-parse.y"
                {
		    (yyval.ttype) = build_component_ref ((yyvsp[-2].ttype), (yyvsp[0].ttype));
		}
#line 3069 "c-parse.c"
    break;

  case 97:
#line 737 "c-parse.y"
                {
                  tree expr = build_indirect_ref ((yyvsp[-2].ttype), "->");

                    (yyval.ttype) = build_component_ref (expr, (yyvsp[0].ttype));
		}
#line 3079 "c-parse.c"
    break;

  case 98:
#line 743 "c-parse.y"
                { (yyval.ttype) = build_unary_op (POSTINCREMENT_EXPR, (yyvsp[-1].ttype), 0); }
#line 3085 "c-parse.c"
    break;

  case 99:
#line 745 "c-parse.y"
                { (yyval.ttype) = build_unary_op (POSTDECREMENT_EXPR, (yyvsp[-1].ttype), 0); }
#line 3091 "c-parse.c"
    break;

  case 101:
#line 752 "c-parse.y"
                { (yyval.ttype) = chainon ((yyvsp[-1].ttype), (yyvsp[0].ttype)); }
#line 3097 "c-parse.c"
    break;

  case 104:
#line 761 "c-parse.y"
                { c_mark_varargs ();
		  if (pedantic)
		    pedwarn ("ANSI C does not permit use of `varargs.h'"); }
#line 3105 "c-parse.c"
    break;

  case 105:
#line 771 "c-parse.y"
                { }
#line 3111 "c-parse.c"
    break;

  case 110:
#line 787 "c-parse.y"
                { current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[-2].itype)); }
#line 3120 "c-parse.c"
    break;

  case 111:
#line 792 "c-parse.y"
                { current_declspecs = TREE_VALUE (declspec_stack);	
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[-2].itype)); }
#line 3129 "c-parse.c"
    break;

  case 112:
#line 797 "c-parse.y"
                { shadow_tag_warned ((yyvsp[-1].ttype), 1);
		  pedwarn ("empty declaration"); }
#line 3136 "c-parse.c"
    break;

  case 113:
#line 800 "c-parse.y"
                { pedwarn ("empty declaration"); }
#line 3142 "c-parse.c"
    break;

  case 114:
#line 809 "c-parse.y"
                { }
#line 3148 "c-parse.c"
    break;

  case 119:
#line 824 "c-parse.y"
                { (yyval.itype) = suspend_momentary ();
		  pending_xref_error ();
		  declspec_stack = tree_cons (prefix_attributes,
					      current_declspecs,
					      declspec_stack);
		  split_specs_attrs ((yyvsp[0].ttype),
				     &current_declspecs, &prefix_attributes); }
#line 3160 "c-parse.c"
    break;

  case 120:
#line 835 "c-parse.y"
                { prefix_attributes = chainon (prefix_attributes, (yyvsp[0].ttype)); }
#line 3166 "c-parse.c"
    break;

  case 121:
#line 840 "c-parse.y"
                { current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[-2].itype)); }
#line 3175 "c-parse.c"
    break;

  case 122:
#line 845 "c-parse.y"
                { current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[-2].itype)); }
#line 3184 "c-parse.c"
    break;

  case 123:
#line 850 "c-parse.y"
                { current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[-1].itype)); }
#line 3193 "c-parse.c"
    break;

  case 124:
#line 855 "c-parse.y"
                { current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[-1].itype)); }
#line 3202 "c-parse.c"
    break;

  case 125:
#line 860 "c-parse.y"
                { shadow_tag ((yyvsp[-1].ttype)); }
#line 3208 "c-parse.c"
    break;

  case 126:
#line 862 "c-parse.y"
                { pedwarn ("empty declaration"); }
#line 3214 "c-parse.c"
    break;

  case 127:
#line 864 "c-parse.y"
                { pedantic = (yyvsp[-1].itype); }
#line 3220 "c-parse.c"
    break;

  case 128:
#line 874 "c-parse.y"
                { (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[-1].ttype), (yyvsp[0].ttype)); }
#line 3226 "c-parse.c"
    break;

  case 129:
#line 876 "c-parse.y"
                { (yyval.ttype) = chainon ((yyvsp[0].ttype), tree_cons (NULL_TREE, (yyvsp[-1].ttype), (yyvsp[-2].ttype))); }
#line 3232 "c-parse.c"
    break;

  case 130:
#line 880 "c-parse.y"
                { (yyval.ttype) = NULL_TREE; }
#line 3238 "c-parse.c"
    break;

  case 131:
#line 882 "c-parse.y"
                { (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[0].ttype), (yyvsp[-1].ttype)); }
#line 3244 "c-parse.c"
    break;

  case 132:
#line 884 "c-parse.y"
                { if (extra_warnings)
		    warning ("`%s' is not at beginning of declaration",
			     IDENTIFIER_POINTER ((yyvsp[0].ttype)));
		  (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[0].ttype), (yyvsp[-1].ttype)); }
#line 3253 "c-parse.c"
    break;

  case 133:
#line 889 "c-parse.y"
                { (yyval.ttype) = tree_cons ((yyvsp[0].ttype), NULL_TREE, (yyvsp[-1].ttype)); }
#line 3259 "c-parse.c"
    break;

  case 134:
#line 894 "c-parse.y"
                { (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[-1].ttype), (yyvsp[0].ttype)); }
#line 3265 "c-parse.c"
    break;

  case 135:
#line 896 "c-parse.y"
                { (yyval.ttype) = chainon ((yyvsp[0].ttype), tree_cons (NULL_TREE, (yyvsp[-1].ttype), (yyvsp[-2].ttype))); }
#line 3271 "c-parse.c"
    break;

  case 136:
#line 901 "c-parse.y"
                { (yyval.ttype) = NULL_TREE; }
#line 3277 "c-parse.c"
    break;

  case 137:
#line 903 "c-parse.y"
                { (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[0].ttype), (yyvsp[-1].ttype)); }
#line 3283 "c-parse.c"
    break;

  case 138:
#line 905 "c-parse.y"
                { if (extra_warnings)
		    warning ("`%s' is not at beginning of declaration",
			     IDENTIFIER_POINTER ((yyvsp[0].ttype)));
		  (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[0].ttype), (yyvsp[-1].ttype)); }
#line 3292 "c-parse.c"
    break;

  case 139:
#line 918 "c-parse.y"
                { (yyval.ttype) = (yyvsp[0].ttype); }
#line 3298 "c-parse.c"
    break;

  case 140:
#line 920 "c-parse.y"
                { (yyval.ttype) = tree_cons ((yyvsp[0].ttype), NULL_TREE, NULL_TREE); }
#line 3304 "c-parse.c"
    break;

  case 141:
#line 922 "c-parse.y"
                { (yyval.ttype) = chainon ((yyvsp[0].ttype), (yyvsp[-1].ttype)); }
#line 3310 "c-parse.c"
    break;

  case 142:
#line 924 "c-parse.y"
                { (yyval.ttype) = tree_cons ((yyvsp[0].ttype), NULL_TREE, (yyvsp[-1].ttype)); }
#line 3316 "c-parse.c"
    break;

  case 143:
#line 929 "c-parse.y"
                { (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[0].ttype), NULL_TREE);
		  TREE_STATIC ((yyval.ttype)) = 1; }
#line 3323 "c-parse.c"
    break;

  case 144:
#line 932 "c-parse.y"
                { (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[0].ttype), NULL_TREE); }
#line 3329 "c-parse.c"
    break;

  case 145:
#line 934 "c-parse.y"
                { (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[0].ttype), (yyvsp[-1].ttype));
		  TREE_STATIC ((yyval.ttype)) = 1; }
#line 3336 "c-parse.c"
    break;

  case 146:
#line 937 "c-parse.y"
                { if (extra_warnings && TREE_STATIC ((yyvsp[-1].ttype)))
		    warning ("`%s' is not at beginning of declaration",
			     IDENTIFIER_POINTER ((yyvsp[0].ttype)));
		  (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[0].ttype), (yyvsp[-1].ttype));
		  TREE_STATIC ((yyval.ttype)) = TREE_STATIC ((yyvsp[-1].ttype)); }
#line 3346 "c-parse.c"
    break;

  case 147:
#line 951 "c-parse.y"
                { (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[-1].ttype), (yyvsp[0].ttype)); }
#line 3352 "c-parse.c"
    break;

  case 148:
#line 953 "c-parse.y"
                { (yyval.ttype) = chainon ((yyvsp[0].ttype), tree_cons (NULL_TREE, (yyvsp[-1].ttype), (yyvsp[-2].ttype))); }
#line 3358 "c-parse.c"
    break;

  case 149:
#line 957 "c-parse.y"
                { (yyval.ttype) = NULL_TREE; }
#line 3364 "c-parse.c"
    break;

  case 150:
#line 959 "c-parse.y"
                { (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[0].ttype), (yyvsp[-1].ttype)); }
#line 3370 "c-parse.c"
    break;

  case 153:
#line 969 "c-parse.y"
                { /* For a typedef name, record the meaning, not the name.
		     In case of `foo foo, bar;'.  */
		  (yyval.ttype) = lookup_name ((yyvsp[0].ttype)); }
#line 3378 "c-parse.c"
    break;

  case 154:
#line 973 "c-parse.y"
                { (yyval.ttype) = TREE_TYPE ((yyvsp[-1].ttype)); }
#line 3384 "c-parse.c"
    break;

  case 155:
#line 975 "c-parse.y"
                { (yyval.ttype) = groktypename ((yyvsp[-1].ttype)); }
#line 3390 "c-parse.c"
    break;

  case 163:
#line 997 "c-parse.y"
                { (yyval.ttype) = NULL_TREE; }
#line 3396 "c-parse.c"
    break;

  case 164:
#line 999 "c-parse.y"
                { if (TREE_CHAIN ((yyvsp[-1].ttype))) (yyvsp[-1].ttype) = combine_strings ((yyvsp[-1].ttype));
		  (yyval.ttype) = (yyvsp[-1].ttype);
		}
#line 3404 "c-parse.c"
    break;

  case 165:
#line 1006 "c-parse.y"
                { (yyval.ttype) = start_decl ((yyvsp[-3].ttype), current_declspecs, 1,
					  (yyvsp[-1].ttype), prefix_attributes);
		  start_init ((yyval.ttype), (yyvsp[-2].ttype), global_bindings_p ()); }
#line 3412 "c-parse.c"
    break;

  case 166:
#line 1011 "c-parse.y"
                { finish_init ();
		  finish_decl ((yyvsp[-1].ttype), (yyvsp[0].ttype), (yyvsp[-4].ttype)); }
#line 3419 "c-parse.c"
    break;

  case 167:
#line 1014 "c-parse.y"
                { tree d = start_decl ((yyvsp[-2].ttype), current_declspecs, 0,
				       (yyvsp[0].ttype), prefix_attributes);
		  finish_decl (d, NULL_TREE, (yyvsp[-1].ttype)); 
                }
#line 3428 "c-parse.c"
    break;

  case 168:
#line 1022 "c-parse.y"
                { (yyval.ttype) = start_decl ((yyvsp[-3].ttype), current_declspecs, 1,
					  (yyvsp[-1].ttype), prefix_attributes);
		  start_init ((yyval.ttype), (yyvsp[-2].ttype), global_bindings_p ()); }
#line 3436 "c-parse.c"
    break;

  case 169:
#line 1027 "c-parse.y"
                { finish_init ();
		  decl_attributes ((yyvsp[-1].ttype), (yyvsp[-3].ttype), prefix_attributes);
		  finish_decl ((yyvsp[-1].ttype), (yyvsp[0].ttype), (yyvsp[-4].ttype)); }
#line 3444 "c-parse.c"
    break;

  case 170:
#line 1031 "c-parse.y"
                { tree d = start_decl ((yyvsp[-2].ttype), current_declspecs, 0,
				       (yyvsp[0].ttype), prefix_attributes);
		  finish_decl (d, NULL_TREE, (yyvsp[-1].ttype)); }
#line 3452 "c-parse.c"
    break;

  case 171:
#line 1039 "c-parse.y"
                { (yyval.ttype) = NULL_TREE; }
#line 3458 "c-parse.c"
    break;

  case 172:
#line 1041 "c-parse.y"
                { (yyval.ttype) = (yyvsp[0].ttype); }
#line 3464 "c-parse.c"
    break;

  case 173:
#line 1046 "c-parse.y"
                { (yyval.ttype) = (yyvsp[0].ttype); }
#line 3470 "c-parse.c"
    break;

  case 174:
#line 1048 "c-parse.y"
                { (yyval.ttype) = chainon ((yyvsp[-1].ttype), (yyvsp[0].ttype)); }
#line 3476 "c-parse.c"
    break;

  case 175:
#line 1053 "c-parse.y"
                { (yyval.ttype) = (yyvsp[-2].ttype); }
#line 3482 "c-parse.c"
    break;

  case 176:
#line 1058 "c-parse.y"
                { (yyval.ttype) = (yyvsp[0].ttype); }
#line 3488 "c-parse.c"
    break;

  case 177:
#line 1060 "c-parse.y"
                { (yyval.ttype) = chainon ((yyvsp[-2].ttype), (yyvsp[0].ttype)); }
#line 3494 "c-parse.c"
    break;

  case 178:
#line 1065 "c-parse.y"
                { (yyval.ttype) = NULL_TREE; }
#line 3500 "c-parse.c"
    break;

  case 179:
#line 1067 "c-parse.y"
                { (yyval.ttype) = build_tree_list ((yyvsp[0].ttype), NULL_TREE); }
#line 3506 "c-parse.c"
    break;

  case 180:
#line 1069 "c-parse.y"
                { (yyval.ttype) = build_tree_list ((yyvsp[-3].ttype), build_tree_list (NULL_TREE, (yyvsp[-1].ttype))); }
#line 3512 "c-parse.c"
    break;

  case 181:
#line 1071 "c-parse.y"
                { (yyval.ttype) = build_tree_list ((yyvsp[-5].ttype), tree_cons (NULL_TREE, (yyvsp[-3].ttype), (yyvsp[-1].ttype))); }
#line 3518 "c-parse.c"
    break;

  case 182:
#line 1073 "c-parse.y"
                { (yyval.ttype) = build_tree_list ((yyvsp[-3].ttype), (yyvsp[-1].ttype)); }
#line 3524 "c-parse.c"
    break;

  case 188:
#line 1091 "c-parse.y"
                { really_start_incremental_init (NULL_TREE);
		  /* Note that the call to clear_momentary
		     is in process_init_element.  */
		  push_momentary (); }
#line 3533 "c-parse.c"
    break;

  case 189:
#line 1096 "c-parse.y"
                { (yyval.ttype) = pop_init_level (0);
		  if ((yyval.ttype) == error_mark_node
		      && ! (yychar == STRING || yychar == CONSTANT))
		    pop_momentary ();
		  else
		    pop_momentary_nofree (); }
#line 3544 "c-parse.c"
    break;

  case 190:
#line 1104 "c-parse.y"
                { (yyval.ttype) = error_mark_node; }
#line 3550 "c-parse.c"
    break;

  case 191:
#line 1110 "c-parse.y"
                { if (pedantic)
		    pedwarn ("ANSI C forbids empty initializer braces"); }
#line 3557 "c-parse.c"
    break;

  case 197:
#line 1126 "c-parse.y"
                { set_init_label ((yyvsp[-1].ttype)); }
#line 3563 "c-parse.c"
    break;

  case 200:
#line 1133 "c-parse.y"
                { push_init_level (0); }
#line 3569 "c-parse.c"
    break;

  case 201:
#line 1135 "c-parse.y"
                { process_init_element (pop_init_level (0)); }
#line 3575 "c-parse.c"
    break;

  case 202:
#line 1137 "c-parse.y"
                { process_init_element ((yyvsp[0].ttype)); }
#line 3581 "c-parse.c"
    break;

  case 206:
#line 1148 "c-parse.y"
                { set_init_label ((yyvsp[0].ttype)); }
#line 3587 "c-parse.c"
    break;

  case 207:
#line 1153 "c-parse.y"
                { set_init_index ((yyvsp[-3].ttype), (yyvsp[-1].ttype)); }
#line 3593 "c-parse.c"
    break;

  case 208:
#line 1155 "c-parse.y"
                { set_init_index ((yyvsp[-1].ttype), NULL_TREE); }
#line 3599 "c-parse.c"
    break;

  case 209:
#line 1160 "c-parse.y"
                { push_c_function_context ();
		  if (! start_function (current_declspecs, (yyvsp[0].ttype),
					prefix_attributes, NULL_TREE, 1))
		    {
		      pop_c_function_context ();
		      YYERROR1;
		    }
		  reinit_parse_for_function (); }
#line 3612 "c-parse.c"
    break;

  case 210:
#line 1169 "c-parse.y"
                { store_parm_decls (); }
#line 3618 "c-parse.c"
    break;

  case 211:
#line 1177 "c-parse.y"
                { finish_function (1);
		  pop_c_function_context (); }
#line 3625 "c-parse.c"
    break;

  case 212:
#line 1183 "c-parse.y"
                { push_c_function_context ();
		  if (! start_function (current_declspecs, (yyvsp[0].ttype),
					prefix_attributes, NULL_TREE, 1))
		    {
		      pop_c_function_context ();
		      YYERROR1;
		    }
		  reinit_parse_for_function (); }
#line 3638 "c-parse.c"
    break;

  case 213:
#line 1192 "c-parse.y"
                { store_parm_decls (); }
#line 3644 "c-parse.c"
    break;

  case 214:
#line 1200 "c-parse.y"
                { finish_function (1);
		  pop_c_function_context (); }
#line 3651 "c-parse.c"
    break;

  case 217:
#line 1216 "c-parse.y"
                { (yyval.ttype) = (yyvsp[-1].ttype); }
#line 3657 "c-parse.c"
    break;

  case 218:
#line 1218 "c-parse.y"
                { (yyval.ttype) = build_nt (CALL_EXPR, (yyvsp[-2].ttype), (yyvsp[0].ttype), NULL_TREE); }
#line 3663 "c-parse.c"
    break;

  case 219:
#line 1223 "c-parse.y"
                { (yyval.ttype) = build_nt (ARRAY_REF, (yyvsp[-3].ttype), (yyvsp[-1].ttype)); }
#line 3669 "c-parse.c"
    break;

  case 220:
#line 1225 "c-parse.y"
                { (yyval.ttype) = build_nt (ARRAY_REF, (yyvsp[-2].ttype), NULL_TREE); }
#line 3675 "c-parse.c"
    break;

  case 221:
#line 1227 "c-parse.y"
                { (yyval.ttype) = make_pointer_declarator ((yyvsp[-1].ttype), (yyvsp[0].ttype)); }
#line 3681 "c-parse.c"
    break;

  case 222:
#line 1234 "c-parse.y"
                { (yyval.ttype) = (yyvsp[0].ttype); }
#line 3687 "c-parse.c"
    break;

  case 224:
#line 1245 "c-parse.y"
                { (yyval.ttype) = build_nt (CALL_EXPR, (yyvsp[-2].ttype), (yyvsp[0].ttype), NULL_TREE); }
#line 3693 "c-parse.c"
    break;

  case 225:
#line 1250 "c-parse.y"
                { (yyval.ttype) = build_nt (ARRAY_REF, (yyvsp[-3].ttype), NULL_TREE);
		  if (! flag_isoc9x)
		    error ("`[*]' in parameter declaration only allowed in ISO C 9x");
		}
#line 3702 "c-parse.c"
    break;

  case 226:
#line 1255 "c-parse.y"
                { (yyval.ttype) = build_nt (ARRAY_REF, (yyvsp[-3].ttype), (yyvsp[-1].ttype)); }
#line 3708 "c-parse.c"
    break;

  case 227:
#line 1257 "c-parse.y"
                { (yyval.ttype) = build_nt (ARRAY_REF, (yyvsp[-2].ttype), NULL_TREE); }
#line 3714 "c-parse.c"
    break;

  case 228:
#line 1259 "c-parse.y"
                { (yyval.ttype) = make_pointer_declarator ((yyvsp[-1].ttype), (yyvsp[0].ttype)); }
#line 3720 "c-parse.c"
    break;

  case 229:
#line 1266 "c-parse.y"
                { (yyval.ttype) = (yyvsp[0].ttype); }
#line 3726 "c-parse.c"
    break;

  case 231:
#line 1275 "c-parse.y"
                { (yyval.ttype) = build_nt (CALL_EXPR, (yyvsp[-2].ttype), (yyvsp[0].ttype), NULL_TREE); }
#line 3732 "c-parse.c"
    break;

  case 232:
#line 1280 "c-parse.y"
                { (yyval.ttype) = (yyvsp[-1].ttype); }
#line 3738 "c-parse.c"
    break;

  case 233:
#line 1282 "c-parse.y"
                { (yyval.ttype) = make_pointer_declarator ((yyvsp[-1].ttype), (yyvsp[0].ttype)); }
#line 3744 "c-parse.c"
    break;

  case 234:
#line 1284 "c-parse.y"
                { (yyval.ttype) = build_nt (ARRAY_REF, (yyvsp[-3].ttype), NULL_TREE);
		  if (! flag_isoc9x)
		    error ("`[*]' in parameter declaration only allowed in ISO C 9x");
		}
#line 3753 "c-parse.c"
    break;

  case 235:
#line 1289 "c-parse.y"
                { (yyval.ttype) = build_nt (ARRAY_REF, (yyvsp[-3].ttype), (yyvsp[-1].ttype)); }
#line 3759 "c-parse.c"
    break;

  case 236:
#line 1291 "c-parse.y"
                { (yyval.ttype) = build_nt (ARRAY_REF, (yyvsp[-2].ttype), NULL_TREE); }
#line 3765 "c-parse.c"
    break;

  case 237:
#line 1298 "c-parse.y"
                { (yyval.ttype) = (yyvsp[0].ttype); }
#line 3771 "c-parse.c"
    break;

  case 239:
#line 1304 "c-parse.y"
                { (yyval.ttype) = NULL_TREE; }
#line 3777 "c-parse.c"
    break;

  case 240:
#line 1306 "c-parse.y"
                { (yyval.ttype) = (yyvsp[0].ttype); }
#line 3783 "c-parse.c"
    break;

  case 241:
#line 1311 "c-parse.y"
                { (yyval.ttype) = NULL_TREE; }
#line 3789 "c-parse.c"
    break;

  case 242:
#line 1313 "c-parse.y"
                { (yyval.ttype) = (yyvsp[0].ttype); }
#line 3795 "c-parse.c"
    break;

  case 243:
#line 1318 "c-parse.y"
                { (yyval.ttype) = NULL_TREE; }
#line 3801 "c-parse.c"
    break;

  case 244:
#line 1320 "c-parse.y"
                { (yyval.ttype) = (yyvsp[0].ttype); }
#line 3807 "c-parse.c"
    break;

  case 245:
#line 1325 "c-parse.y"
                { (yyval.ttype) = start_struct (RECORD_TYPE, (yyvsp[-1].ttype));
		  /* Start scope of tag before parsing components.  */
		}
#line 3815 "c-parse.c"
    break;

  case 246:
#line 1329 "c-parse.y"
                { (yyval.ttype) = finish_struct ((yyvsp[-3].ttype), (yyvsp[-2].ttype), chainon ((yyvsp[-6].ttype), (yyvsp[0].ttype))); }
#line 3821 "c-parse.c"
    break;

  case 247:
#line 1331 "c-parse.y"
                { (yyval.ttype) = finish_struct (start_struct (RECORD_TYPE, NULL_TREE),
				      (yyvsp[-2].ttype), chainon ((yyvsp[-4].ttype), (yyvsp[0].ttype)));
		}
#line 3829 "c-parse.c"
    break;

  case 248:
#line 1335 "c-parse.y"
                { (yyval.ttype) = xref_tag (RECORD_TYPE, (yyvsp[0].ttype)); }
#line 3835 "c-parse.c"
    break;

  case 249:
#line 1337 "c-parse.y"
                { (yyval.ttype) = start_struct (UNION_TYPE, (yyvsp[-1].ttype)); }
#line 3841 "c-parse.c"
    break;

  case 250:
#line 1339 "c-parse.y"
                { (yyval.ttype) = finish_struct ((yyvsp[-3].ttype), (yyvsp[-2].ttype), chainon ((yyvsp[-6].ttype), (yyvsp[0].ttype))); }
#line 3847 "c-parse.c"
    break;

  case 251:
#line 1341 "c-parse.y"
                { (yyval.ttype) = finish_struct (start_struct (UNION_TYPE, NULL_TREE),
				      (yyvsp[-2].ttype), chainon ((yyvsp[-4].ttype), (yyvsp[0].ttype)));
		}
#line 3855 "c-parse.c"
    break;

  case 252:
#line 1345 "c-parse.y"
                { (yyval.ttype) = xref_tag (UNION_TYPE, (yyvsp[0].ttype)); }
#line 3861 "c-parse.c"
    break;

  case 253:
#line 1347 "c-parse.y"
                { (yyvsp[0].itype) = suspend_momentary ();
		  (yyval.ttype) = start_enum ((yyvsp[-1].ttype)); }
#line 3868 "c-parse.c"
    break;

  case 254:
#line 1350 "c-parse.y"
                { (yyval.ttype)= finish_enum ((yyvsp[-4].ttype), nreverse ((yyvsp[-3].ttype)), chainon ((yyvsp[-7].ttype), (yyvsp[0].ttype)));
		  resume_momentary ((yyvsp[-5].itype)); }
#line 3875 "c-parse.c"
    break;

  case 255:
#line 1353 "c-parse.y"
                { (yyvsp[0].itype) = suspend_momentary ();
		  (yyval.ttype) = start_enum (NULL_TREE); }
#line 3882 "c-parse.c"
    break;

  case 256:
#line 1356 "c-parse.y"
                { (yyval.ttype)= finish_enum ((yyvsp[-4].ttype), nreverse ((yyvsp[-3].ttype)), chainon ((yyvsp[-6].ttype), (yyvsp[0].ttype)));
		  resume_momentary ((yyvsp[-5].itype)); }
#line 3889 "c-parse.c"
    break;

  case 257:
#line 1359 "c-parse.y"
                { (yyval.ttype) = xref_tag (ENUMERAL_TYPE, (yyvsp[0].ttype)); }
#line 3895 "c-parse.c"
    break;

  case 261:
#line 1370 "c-parse.y"
                { if (pedantic && ! flag_isoc9x)
		    pedwarn ("comma at end of enumerator list"); }
#line 3902 "c-parse.c"
    break;

  case 262:
#line 1376 "c-parse.y"
                { (yyval.ttype) = (yyvsp[0].ttype); }
#line 3908 "c-parse.c"
    break;

  case 263:
#line 1378 "c-parse.y"
                { (yyval.ttype) = chainon ((yyvsp[-1].ttype), (yyvsp[0].ttype));
		  pedwarn ("no semicolon at end of struct or union"); }
#line 3915 "c-parse.c"
    break;

  case 264:
#line 1383 "c-parse.y"
                { (yyval.ttype) = NULL_TREE; }
#line 3921 "c-parse.c"
    break;

  case 265:
#line 1385 "c-parse.y"
                { (yyval.ttype) = chainon ((yyvsp[-2].ttype), (yyvsp[-1].ttype)); }
#line 3927 "c-parse.c"
    break;

  case 266:
#line 1387 "c-parse.y"
                { if (pedantic)
		    pedwarn ("extra semicolon in struct or union specified"); }
#line 3934 "c-parse.c"
    break;

  case 267:
#line 1402 "c-parse.y"
                { (yyval.ttype) = (yyvsp[0].ttype);
		  current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[-1].itype)); }
#line 3944 "c-parse.c"
    break;

  case 268:
#line 1408 "c-parse.y"
                {
		  /* Support for unnamed structs or unions as members of 
		     structs or unions (which is [a] useful and [b] supports 
		     MS P-SDK).  */
		  if (pedantic)
		    pedwarn ("ANSI C doesn't support unnamed structs/unions");

		  (yyval.ttype) = grokfield((yyvsp[-2].filename), (yyvsp[-1].lineno), NULL, current_declspecs, NULL_TREE);
		  current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[-3].itype));
		}
#line 3962 "c-parse.c"
    break;

  case 269:
#line 1422 "c-parse.y"
                { (yyval.ttype) = (yyvsp[0].ttype);
		  current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[-1].itype)); }
#line 3972 "c-parse.c"
    break;

  case 270:
#line 1428 "c-parse.y"
                { if (pedantic)
		    pedwarn ("ANSI C forbids member declarations with no members");
		  shadow_tag((yyvsp[0].ttype));
		  (yyval.ttype) = NULL_TREE; }
#line 3981 "c-parse.c"
    break;

  case 271:
#line 1433 "c-parse.y"
                { (yyval.ttype) = NULL_TREE; }
#line 3987 "c-parse.c"
    break;

  case 272:
#line 1435 "c-parse.y"
                { (yyval.ttype) = (yyvsp[0].ttype);
		  pedantic = (yyvsp[-1].itype); }
#line 3994 "c-parse.c"
    break;

  case 274:
#line 1442 "c-parse.y"
                { (yyval.ttype) = chainon ((yyvsp[-2].ttype), (yyvsp[0].ttype)); }
#line 4000 "c-parse.c"
    break;

  case 275:
#line 1447 "c-parse.y"
                { (yyval.ttype) = grokfield ((yyvsp[-3].filename), (yyvsp[-2].lineno), (yyvsp[-1].ttype), current_declspecs, NULL_TREE);
		  decl_attributes ((yyval.ttype), (yyvsp[0].ttype), prefix_attributes); }
#line 4007 "c-parse.c"
    break;

  case 276:
#line 1451 "c-parse.y"
                { (yyval.ttype) = grokfield ((yyvsp[-5].filename), (yyvsp[-4].lineno), (yyvsp[-3].ttype), current_declspecs, (yyvsp[-1].ttype));
		  decl_attributes ((yyval.ttype), (yyvsp[0].ttype), prefix_attributes); }
#line 4014 "c-parse.c"
    break;

  case 277:
#line 1454 "c-parse.y"
                { (yyval.ttype) = grokfield ((yyvsp[-4].filename), (yyvsp[-3].lineno), NULL_TREE, current_declspecs, (yyvsp[-1].ttype));
		  decl_attributes ((yyval.ttype), (yyvsp[0].ttype), prefix_attributes); }
#line 4021 "c-parse.c"
    break;

  case 279:
#line 1466 "c-parse.y"
                { if ((yyvsp[-2].ttype) == error_mark_node)
		    (yyval.ttype) = (yyvsp[-2].ttype);
		  else
		    (yyval.ttype) = chainon ((yyvsp[0].ttype), (yyvsp[-2].ttype)); }
#line 4030 "c-parse.c"
    break;

  case 280:
#line 1471 "c-parse.y"
                { (yyval.ttype) = error_mark_node; }
#line 4036 "c-parse.c"
    break;

  case 281:
#line 1477 "c-parse.y"
                { (yyval.ttype) = build_enumerator ((yyvsp[0].ttype), NULL_TREE); }
#line 4042 "c-parse.c"
    break;

  case 282:
#line 1479 "c-parse.y"
                { (yyval.ttype) = build_enumerator ((yyvsp[-2].ttype), (yyvsp[0].ttype)); }
#line 4048 "c-parse.c"
    break;

  case 283:
#line 1484 "c-parse.y"
                { (yyval.ttype) = build_tree_list ((yyvsp[-1].ttype), (yyvsp[0].ttype)); }
#line 4054 "c-parse.c"
    break;

  case 284:
#line 1486 "c-parse.y"
                { (yyval.ttype) = build_tree_list ((yyvsp[-1].ttype), (yyvsp[0].ttype)); }
#line 4060 "c-parse.c"
    break;

  case 285:
#line 1491 "c-parse.y"
                { (yyval.ttype) = NULL_TREE; }
#line 4066 "c-parse.c"
    break;

  case 287:
#line 1497 "c-parse.y"
                { (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[0].ttype), NULL_TREE); }
#line 4072 "c-parse.c"
    break;

  case 288:
#line 1499 "c-parse.y"
                { (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[0].ttype), (yyvsp[-1].ttype)); }
#line 4078 "c-parse.c"
    break;

  case 289:
#line 1504 "c-parse.y"
                { (yyval.ttype) = NULL_TREE; }
#line 4084 "c-parse.c"
    break;

  case 290:
#line 1506 "c-parse.y"
                { (yyval.ttype) = tree_cons (NULL_TREE, (yyvsp[0].ttype), (yyvsp[-1].ttype)); }
#line 4090 "c-parse.c"
    break;

  case 291:
#line 1511 "c-parse.y"
                { (yyval.ttype) = (yyvsp[-1].ttype); }
#line 4096 "c-parse.c"
    break;

  case 292:
#line 1514 "c-parse.y"
                { (yyval.ttype) = make_pointer_declarator ((yyvsp[-1].ttype), (yyvsp[0].ttype)); }
#line 4102 "c-parse.c"
    break;

  case 293:
#line 1516 "c-parse.y"
                { (yyval.ttype) = make_pointer_declarator ((yyvsp[0].ttype), NULL_TREE); }
#line 4108 "c-parse.c"
    break;

  case 294:
#line 1518 "c-parse.y"
                { (yyval.ttype) = build_nt (CALL_EXPR, (yyvsp[-2].ttype), (yyvsp[0].ttype), NULL_TREE); }
#line 4114 "c-parse.c"
    break;

  case 295:
#line 1520 "c-parse.y"
                { (yyval.ttype) = build_nt (ARRAY_REF, (yyvsp[-3].ttype), (yyvsp[-1].ttype)); }
#line 4120 "c-parse.c"
    break;

  case 296:
#line 1522 "c-parse.y"
                { (yyval.ttype) = build_nt (ARRAY_REF, (yyvsp[-2].ttype), NULL_TREE); }
#line 4126 "c-parse.c"
    break;

  case 297:
#line 1524 "c-parse.y"
                { (yyval.ttype) = build_nt (CALL_EXPR, NULL_TREE, (yyvsp[0].ttype), NULL_TREE); }
#line 4132 "c-parse.c"
    break;

  case 298:
#line 1526 "c-parse.y"
                { (yyval.ttype) = build_nt (ARRAY_REF, NULL_TREE, (yyvsp[-1].ttype)); }
#line 4138 "c-parse.c"
    break;

  case 299:
#line 1528 "c-parse.y"
                { (yyval.ttype) = build_nt (ARRAY_REF, NULL_TREE, NULL_TREE); }
#line 4144 "c-parse.c"
    break;

  case 300:
#line 1532 "c-parse.y"
                { (yyval.ttype) = (yyvsp[0].ttype); }
#line 4150 "c-parse.c"
    break;

  case 301:
#line 1541 "c-parse.y"
                {
		  if (pedantic && (yyvsp[0].ends_in_label))
		    pedwarn ("ANSI C forbids label at end of compound statement");
		}
#line 4159 "c-parse.c"
    break;

  case 303:
#line 1550 "c-parse.y"
                { (yyval.ends_in_label) = (yyvsp[0].ends_in_label); }
#line 4165 "c-parse.c"
    break;

  case 304:
#line 1552 "c-parse.y"
                { (yyval.ends_in_label) = 0; }
#line 4171 "c-parse.c"
    break;

  case 308:
#line 1564 "c-parse.y"
                { emit_line_note (input_filename, lineno);
		  pushlevel (0);
		  clear_last_expr ();
		  push_momentary ();
		  expand_start_bindings (0);
		}
#line 4182 "c-parse.c"
    break;

  case 310:
#line 1577 "c-parse.y"
                { if (pedantic)
		    pedwarn ("ANSI C forbids label declarations"); }
#line 4189 "c-parse.c"
    break;

  case 313:
#line 1588 "c-parse.y"
                { tree link;
		  for (link = (yyvsp[-1].ttype); link; link = TREE_CHAIN (link))
		    {
		      tree label = shadow_label (TREE_VALUE (link));
		      C_DECLARED_LABEL_FLAG (label) = 1;
		      declare_nonlocal_label (label);
		    }
		}
#line 4202 "c-parse.c"
    break;

  case 314:
#line 1602 "c-parse.y"
                {}
#line 4208 "c-parse.c"
    break;

  case 316:
#line 1606 "c-parse.y"
                    { compstmt_count++; }
#line 4214 "c-parse.c"
    break;

  case 317:
#line 1609 "c-parse.y"
                { (yyval.ttype) = convert (void_type_node, integer_zero_node); }
#line 4220 "c-parse.c"
    break;

  case 318:
#line 1611 "c-parse.y"
                { emit_line_note (input_filename, lineno);
		  expand_end_bindings (getdecls (), 1, 0);
		  (yyval.ttype) = poplevel (1, 1, 0);
		  if (yychar == CONSTANT || yychar == STRING)
		    pop_momentary_nofree ();
		  else
		    pop_momentary (); }
#line 4232 "c-parse.c"
    break;

  case 319:
#line 1619 "c-parse.y"
                { emit_line_note (input_filename, lineno);
		  expand_end_bindings (getdecls (), kept_level_p (), 0);
		  (yyval.ttype) = poplevel (kept_level_p (), 0, 0);
		  if (yychar == CONSTANT || yychar == STRING)
		    pop_momentary_nofree ();
		  else
		    pop_momentary (); }
#line 4244 "c-parse.c"
    break;

  case 320:
#line 1627 "c-parse.y"
                { emit_line_note (input_filename, lineno);
		  expand_end_bindings (getdecls (), kept_level_p (), 0);
		  (yyval.ttype) = poplevel (kept_level_p (), 0, 0);
		  if (yychar == CONSTANT || yychar == STRING)
		    pop_momentary_nofree ();
		  else
		    pop_momentary (); }
#line 4256 "c-parse.c"
    break;

  case 323:
#line 1647 "c-parse.y"
                { emit_line_note ((yyvsp[(-1) - (4)].filename), (yyvsp[-4].lineno));
		  c_expand_start_cond (truthvalue_conversion ((yyvsp[-1].ttype)), 0, 
				       compstmt_count);
		  (yyval.itype) = stmt_count;
		  if_stmt_file = (yyvsp[(-1) - (4)].filename);
		  if_stmt_line = (yyvsp[-4].lineno);
		  position_after_white_space (); }
#line 4268 "c-parse.c"
    break;

  case 324:
#line 1661 "c-parse.y"
                { stmt_count++;
		  compstmt_count++;
		  emit_line_note ((yyvsp[(-1) - (1)].filename), (yyvsp[-1].lineno));
		  /* See comment in `while' alternative, above.  */
		  emit_nop ();
		  expand_start_loop_continue_elsewhere (1);
		  position_after_white_space (); }
#line 4280 "c-parse.c"
    break;

  case 325:
#line 1669 "c-parse.y"
                { expand_loop_continue_here (); }
#line 4286 "c-parse.c"
    break;

  case 326:
#line 1673 "c-parse.y"
                { (yyval.filename) = input_filename; }
#line 4292 "c-parse.c"
    break;

  case 327:
#line 1677 "c-parse.y"
                { (yyval.lineno) = lineno; }
#line 4298 "c-parse.c"
    break;

  case 328:
#line 1682 "c-parse.y"
                { }
#line 4304 "c-parse.c"
    break;

  case 329:
#line 1687 "c-parse.y"
                { }
#line 4310 "c-parse.c"
    break;

  case 330:
#line 1692 "c-parse.y"
                { (yyval.ends_in_label) = (yyvsp[0].ends_in_label); }
#line 4316 "c-parse.c"
    break;

  case 331:
#line 1697 "c-parse.y"
                { (yyval.ends_in_label) = 0; }
#line 4322 "c-parse.c"
    break;

  case 332:
#line 1699 "c-parse.y"
                { (yyval.ends_in_label) = 1; }
#line 4328 "c-parse.c"
    break;

  case 333:
#line 1705 "c-parse.y"
                { stmt_count++; }
#line 4334 "c-parse.c"
    break;

  case 335:
#line 1708 "c-parse.y"
                { stmt_count++;
		  emit_line_note ((yyvsp[(-1) - (2)].filename), (yyvsp[-2].lineno));
/* It appears that this should not be done--that a non-lvalue array
   shouldn't get an error if the value isn't used.
   Section 3.2.2.1 says that an array lvalue gets converted to a pointer
   if it appears as a top-level expression,
   but says nothing about non-lvalue arrays.  */
#if 0
		  /* Call default_conversion to get an error
		     on referring to a register array if pedantic.  */
		  if (TREE_CODE (TREE_TYPE ((yyvsp[-1].ttype))) == ARRAY_TYPE
		      || TREE_CODE (TREE_TYPE ((yyvsp[-1].ttype))) == FUNCTION_TYPE)
		    (yyvsp[-1].ttype) = default_conversion ((yyvsp[-1].ttype));
#endif
		  iterator_expand ((yyvsp[-1].ttype));
		  clear_momentary (); }
#line 4355 "c-parse.c"
    break;

  case 336:
#line 1725 "c-parse.y"
                { c_expand_start_else ();
		  (yyvsp[-1].itype) = stmt_count;
		  position_after_white_space (); }
#line 4363 "c-parse.c"
    break;

  case 337:
#line 1729 "c-parse.y"
                { c_expand_end_cond ();
		  if (extra_warnings && stmt_count == (yyvsp[-3].itype))
		    warning ("empty body in an else-statement"); }
#line 4371 "c-parse.c"
    break;

  case 338:
#line 1733 "c-parse.y"
                { c_expand_end_cond ();
		  /* This warning is here instead of in simple_if, because we
		     do not want a warning if an empty if is followed by an
		     else statement.  Increment stmt_count so we don't
		     give a second error if this is a nested `if'.  */
		  if (extra_warnings && stmt_count++ == (yyvsp[0].itype))
		    warning_with_file_and_line (if_stmt_file, if_stmt_line,
						"empty body in an if-statement"); }
#line 4384 "c-parse.c"
    break;

  case 339:
#line 1745 "c-parse.y"
                { c_expand_end_cond (); }
#line 4390 "c-parse.c"
    break;

  case 340:
#line 1747 "c-parse.y"
                { stmt_count++;
		  emit_line_note ((yyvsp[(-1) - (1)].filename), (yyvsp[-1].lineno));
		  /* The emit_nop used to come before emit_line_note,
		     but that made the nop seem like part of the preceding line.
		     And that was confusing when the preceding line was
		     inside of an if statement and was not really executed.
		     I think it ought to work to put the nop after the line number.
		     We will see.  --rms, July 15, 1991.  */
		  emit_nop (); }
#line 4404 "c-parse.c"
    break;

  case 341:
#line 1757 "c-parse.y"
                { /* Don't start the loop till we have succeeded
		     in parsing the end test.  This is to make sure
		     that we end every loop we start.  */
		  expand_start_loop (1);
		  emit_line_note (input_filename, lineno);
		  expand_exit_loop_if_false (NULL_PTR,
					     truthvalue_conversion ((yyvsp[-1].ttype)));
		  position_after_white_space (); }
#line 4417 "c-parse.c"
    break;

  case 342:
#line 1766 "c-parse.y"
                { expand_end_loop (); }
#line 4423 "c-parse.c"
    break;

  case 343:
#line 1769 "c-parse.y"
                { emit_line_note (input_filename, lineno);
		  expand_exit_loop_if_false (NULL_PTR,
					     truthvalue_conversion ((yyvsp[-2].ttype)));
		  expand_end_loop ();
		  clear_momentary (); }
#line 4433 "c-parse.c"
    break;

  case 344:
#line 1776 "c-parse.y"
                { expand_end_loop ();
		  clear_momentary (); }
#line 4440 "c-parse.c"
    break;

  case 345:
#line 1780 "c-parse.y"
                { stmt_count++;
		  emit_line_note ((yyvsp[(-1) - (4)].filename), (yyvsp[-4].lineno));
		  /* See comment in `while' alternative, above.  */
		  emit_nop ();
		  if ((yyvsp[-1].ttype)) c_expand_expr_stmt ((yyvsp[-1].ttype));
		  /* Next step is to call expand_start_loop_continue_elsewhere,
		     but wait till after we parse the entire for (...).
		     Otherwise, invalid input might cause us to call that
		     fn without calling expand_end_loop.  */
		}
#line 4455 "c-parse.c"
    break;

  case 346:
#line 1792 "c-parse.y"
                { (yyvsp[0].lineno) = lineno;
		  (yyval.filename) = input_filename; }
#line 4462 "c-parse.c"
    break;

  case 347:
#line 1795 "c-parse.y"
                { 
		  /* Start the loop.  Doing this after parsing
		     all the expressions ensures we will end the loop.  */
		  expand_start_loop_continue_elsewhere (1);
		  /* Emit the end-test, with a line number.  */
		  emit_line_note ((yyvsp[-2].filename), (yyvsp[-3].lineno));
		  if ((yyvsp[-4].ttype))
		    expand_exit_loop_if_false (NULL_PTR,
					       truthvalue_conversion ((yyvsp[-4].ttype)));
		  /* Don't let the tree nodes for $9 be discarded by
		     clear_momentary during the parsing of the next stmt.  */
		  push_momentary ();
		  (yyvsp[-3].lineno) = lineno;
		  (yyvsp[-2].filename) = input_filename;
		  position_after_white_space (); }
#line 4482 "c-parse.c"
    break;

  case 348:
#line 1811 "c-parse.y"
                { /* Emit the increment expression, with a line number.  */
		  emit_line_note ((yyvsp[-4].filename), (yyvsp[-5].lineno));
		  expand_loop_continue_here ();
		  if ((yyvsp[-3].ttype))
		    c_expand_expr_stmt ((yyvsp[-3].ttype));
		  if (yychar == CONSTANT || yychar == STRING)
		    pop_momentary_nofree ();
		  else
		    pop_momentary ();
		  expand_end_loop (); }
#line 4497 "c-parse.c"
    break;

  case 349:
#line 1822 "c-parse.y"
                { stmt_count++;
		  emit_line_note ((yyvsp[(-1) - (4)].filename), (yyvsp[-4].lineno));
		  c_expand_start_case ((yyvsp[-1].ttype));
		  /* Don't let the tree nodes for $3 be discarded by
		     clear_momentary during the parsing of the next stmt.  */
		  push_momentary ();
		  position_after_white_space (); }
#line 4509 "c-parse.c"
    break;

  case 350:
#line 1830 "c-parse.y"
                { expand_end_case ((yyvsp[-3].ttype));
		  if (yychar == CONSTANT || yychar == STRING)
		    pop_momentary_nofree ();
		  else
		    pop_momentary (); }
#line 4519 "c-parse.c"
    break;

  case 351:
#line 1836 "c-parse.y"
                { stmt_count++;
		  emit_line_note ((yyvsp[(-1) - (2)].filename), (yyvsp[-2].lineno));
		  if ( ! expand_exit_something ())
		    error ("break statement not within loop or switch"); }
#line 4528 "c-parse.c"
    break;

  case 352:
#line 1841 "c-parse.y"
                { stmt_count++;
		  emit_line_note ((yyvsp[(-1) - (2)].filename), (yyvsp[-2].lineno));
		  if (! expand_continue_loop (NULL_PTR))
		    error ("continue statement not within a loop"); }
#line 4537 "c-parse.c"
    break;

  case 353:
#line 1846 "c-parse.y"
                { stmt_count++;
		  emit_line_note ((yyvsp[(-1) - (2)].filename), (yyvsp[-2].lineno));
		  c_expand_return (NULL_TREE); }
#line 4545 "c-parse.c"
    break;

  case 354:
#line 1850 "c-parse.y"
                { stmt_count++;
		  emit_line_note ((yyvsp[(-1) - (3)].filename), (yyvsp[-3].lineno));
		  c_expand_return ((yyvsp[-1].ttype)); }
#line 4553 "c-parse.c"
    break;

  case 355:
#line 1854 "c-parse.y"
                { stmt_count++;
		  emit_line_note ((yyvsp[(-1) - (6)].filename), (yyvsp[-6].lineno));
		  STRIP_NOPS ((yyvsp[-2].ttype));
		  if ((TREE_CODE ((yyvsp[-2].ttype)) == ADDR_EXPR
		       && TREE_CODE (TREE_OPERAND ((yyvsp[-2].ttype), 0)) == STRING_CST)
		      || TREE_CODE ((yyvsp[-2].ttype)) == STRING_CST)
		    expand_asm ((yyvsp[-2].ttype));
		  else
		    error ("argument of `asm' is not a constant string"); }
#line 4567 "c-parse.c"
    break;

  case 356:
#line 1865 "c-parse.y"
                { stmt_count++;
		  emit_line_note ((yyvsp[(-1) - (8)].filename), (yyvsp[-8].lineno));
		  c_expand_asm_operands ((yyvsp[-4].ttype), (yyvsp[-2].ttype), NULL_TREE, NULL_TREE,
					 (yyvsp[-6].ttype) == ridpointers[(int)RID_VOLATILE],
					 input_filename, lineno); }
#line 4577 "c-parse.c"
    break;

  case 357:
#line 1872 "c-parse.y"
                { stmt_count++;
		  emit_line_note ((yyvsp[(-1) - (10)].filename), (yyvsp[-10].lineno));
		  c_expand_asm_operands ((yyvsp[-6].ttype), (yyvsp[-4].ttype), (yyvsp[-2].ttype), NULL_TREE,
					 (yyvsp[-8].ttype) == ridpointers[(int)RID_VOLATILE],
					 input_filename, lineno); }
#line 4587 "c-parse.c"
    break;

  case 358:
#line 1880 "c-parse.y"
                { stmt_count++;
		  emit_line_note ((yyvsp[(-1) - (12)].filename), (yyvsp[-12].lineno));
		  c_expand_asm_operands ((yyvsp[-8].ttype), (yyvsp[-6].ttype), (yyvsp[-4].ttype), (yyvsp[-2].ttype),
					 (yyvsp[-10].ttype) == ridpointers[(int)RID_VOLATILE],
					 input_filename, lineno); }
#line 4597 "c-parse.c"
    break;

  case 359:
#line 1886 "c-parse.y"
                { tree decl;
		  stmt_count++;
		  emit_line_note ((yyvsp[(-1) - (3)].filename), (yyvsp[-3].lineno));
		  decl = lookup_label ((yyvsp[-1].ttype));
		  if (decl != 0)
		    {
		      TREE_USED (decl) = 1;
		      expand_goto (decl);
		    }
		}
#line 4612 "c-parse.c"
    break;

  case 360:
#line 1897 "c-parse.y"
                { if (pedantic)
		    pedwarn ("ANSI C forbids `goto *expr;'");
		  stmt_count++;
		  emit_line_note ((yyvsp[(-1) - (4)].filename), (yyvsp[-4].lineno));
		  expand_computed_goto (convert (ptr_type_node, (yyvsp[-1].ttype))); }
#line 4622 "c-parse.c"
    break;

  case 363:
#line 1912 "c-parse.y"
          {
	    /* The value returned by this action is  */
	    /*      1 if everything is OK */ 
	    /*      0 in case of error or already bound iterator */

	    (yyval.itype) = 0;
	    if (TREE_CODE ((yyvsp[-1].ttype)) != VAR_DECL)
	      error ("invalid `for (ITERATOR)' syntax");
	    else if (! ITERATOR_P ((yyvsp[-1].ttype)))
	      error ("`%s' is not an iterator",
		     IDENTIFIER_POINTER (DECL_NAME ((yyvsp[-1].ttype))));
	    else if (ITERATOR_BOUND_P ((yyvsp[-1].ttype)))
	      error ("`for (%s)' inside expansion of same iterator",
		     IDENTIFIER_POINTER (DECL_NAME ((yyvsp[-1].ttype))));
	    else
	      {
		(yyval.itype) = 1;
		iterator_for_loop_start ((yyvsp[-1].ttype));
	      }
	  }
#line 4647 "c-parse.c"
    break;

  case 364:
#line 1933 "c-parse.y"
          {
	    if ((yyvsp[-1].itype))
	      iterator_for_loop_end ((yyvsp[-3].ttype));
	  }
#line 4656 "c-parse.c"
    break;

  case 365:
#line 1968 "c-parse.y"
                { register tree value = check_case_value ((yyvsp[-1].ttype));
		  register tree label
		    = build_decl (LABEL_DECL, NULL_TREE, NULL_TREE);

		  stmt_count++;

		  if (value != error_mark_node)
		    {
		      tree duplicate;
		      int success;

		      if (pedantic && ! INTEGRAL_TYPE_P (TREE_TYPE (value)))
			pedwarn ("label must have integral type in ANSI C");

		      success = pushcase (value, convert_and_check,
					  label, &duplicate);

		      if (success == 1)
			error ("case label not within a switch statement");
		      else if (success == 2)
			{
			  error ("duplicate case value");
			  error_with_decl (duplicate, "this is the first entry for that value");
			}
		      else if (success == 3)
			warning ("case value out of range");
		      else if (success == 5)
			error ("case label within scope of cleanup or variable array");
		    }
		  position_after_white_space (); }
#line 4691 "c-parse.c"
    break;

  case 366:
#line 1999 "c-parse.y"
                { register tree value1 = check_case_value ((yyvsp[-3].ttype));
		  register tree value2 = check_case_value ((yyvsp[-1].ttype));
		  register tree label
		    = build_decl (LABEL_DECL, NULL_TREE, NULL_TREE);

		  if (pedantic)
		    pedwarn ("ANSI C forbids case ranges");
		  stmt_count++;

		  if (value1 != error_mark_node && value2 != error_mark_node)
		    {
		      tree duplicate;
		      int success = pushcase_range (value1, value2,
						    convert_and_check, label,
						    &duplicate);
		      if (success == 1)
			error ("case label not within a switch statement");
		      else if (success == 2)
			{
			  error ("duplicate case value");
			  error_with_decl (duplicate, "this is the first entry for that value");
			}
		      else if (success == 3)
			warning ("case value out of range");
		      else if (success == 4)
			warning ("empty case range");
		      else if (success == 5)
			error ("case label within scope of cleanup or variable array");
		    }
		  position_after_white_space (); }
#line 4726 "c-parse.c"
    break;

  case 367:
#line 2030 "c-parse.y"
                {
		  tree duplicate;
		  register tree label
		    = build_decl (LABEL_DECL, NULL_TREE, NULL_TREE);
		  int success = pushcase (NULL_TREE, 0, label, &duplicate);
		  stmt_count++;
		  if (success == 1)
		    error ("default label not within a switch statement");
		  else if (success == 2)
		    {
		      error ("multiple default labels in one switch");
		      error_with_decl (duplicate, "this is the first default label");
		    }
		  position_after_white_space (); }
#line 4745 "c-parse.c"
    break;

  case 368:
#line 2045 "c-parse.y"
                { tree label = define_label (input_filename, lineno, (yyvsp[-2].ttype));
		  stmt_count++;
		  emit_nop ();
		  if (label)
		    {
		      expand_label (label);
		      decl_attributes (label, (yyvsp[0].ttype), NULL_TREE);
		    }
		  position_after_white_space (); }
#line 4759 "c-parse.c"
    break;

  case 369:
#line 2060 "c-parse.y"
                { emit_line_note (input_filename, lineno);
		  (yyval.ttype) = NULL_TREE; }
#line 4766 "c-parse.c"
    break;

  case 370:
#line 2063 "c-parse.y"
                { emit_line_note (input_filename, lineno); }
#line 4772 "c-parse.c"
    break;

  case 371:
#line 2068 "c-parse.y"
                { (yyval.ttype) = NULL_TREE; }
#line 4778 "c-parse.c"
    break;

  case 373:
#line 2075 "c-parse.y"
                { (yyval.ttype) = NULL_TREE; }
#line 4784 "c-parse.c"
    break;

  case 376:
#line 2082 "c-parse.y"
                { (yyval.ttype) = chainon ((yyvsp[-2].ttype), (yyvsp[0].ttype)); }
#line 4790 "c-parse.c"
    break;

  case 377:
#line 2087 "c-parse.y"
                { (yyval.ttype) = build_tree_list ((yyvsp[-3].ttype), (yyvsp[-1].ttype)); }
#line 4796 "c-parse.c"
    break;

  case 378:
#line 2092 "c-parse.y"
                { (yyval.ttype) = tree_cons (NULL_TREE, combine_strings ((yyvsp[0].ttype)), NULL_TREE); }
#line 4802 "c-parse.c"
    break;

  case 379:
#line 2094 "c-parse.y"
                { (yyval.ttype) = tree_cons (NULL_TREE, combine_strings ((yyvsp[0].ttype)), (yyvsp[-2].ttype)); }
#line 4808 "c-parse.c"
    break;

  case 380:
#line 2100 "c-parse.y"
                { pushlevel (0);
		  clear_parm_order ();
		  declare_parm_level (0); }
#line 4816 "c-parse.c"
    break;

  case 381:
#line 2104 "c-parse.y"
                { (yyval.ttype) = (yyvsp[0].ttype);
		  parmlist_tags_warning ();
		  poplevel (0, 0, 0); }
#line 4824 "c-parse.c"
    break;

  case 383:
#line 2112 "c-parse.y"
                { tree parm;
		  if (pedantic)
		    pedwarn ("ANSI C forbids forward parameter declarations");
		  /* Mark the forward decls as such.  */
		  for (parm = getdecls (); parm; parm = TREE_CHAIN (parm))
		    TREE_ASM_WRITTEN (parm) = 1;
		  clear_parm_order (); }
#line 4836 "c-parse.c"
    break;

  case 384:
#line 2120 "c-parse.y"
                { (yyval.ttype) = (yyvsp[0].ttype); }
#line 4842 "c-parse.c"
    break;

  case 385:
#line 2122 "c-parse.y"
                { (yyval.ttype) = tree_cons (NULL_TREE, NULL_TREE, NULL_TREE); }
#line 4848 "c-parse.c"
    break;

  case 386:
#line 2128 "c-parse.y"
                { (yyval.ttype) = get_parm_info (0); }
#line 4854 "c-parse.c"
    break;

  case 387:
#line 2130 "c-parse.y"
                { (yyval.ttype) = get_parm_info (0);
		  /* Gcc used to allow this as an extension.  However, it does
		     not work for all targets, and thus has been disabled.
		     Also, since func (...) and func () are indistinguishable,
		     it caused problems with the code in expand_builtin which
		     tries to verify that BUILT_IN_NEXT_ARG is being used
		     correctly.  */
		  error ("ANSI C requires a named argument before `...'");
		}
#line 4868 "c-parse.c"
    break;

  case 388:
#line 2140 "c-parse.y"
                { (yyval.ttype) = get_parm_info (1); }
#line 4874 "c-parse.c"
    break;

  case 389:
#line 2142 "c-parse.y"
                { (yyval.ttype) = get_parm_info (0); }
#line 4880 "c-parse.c"
    break;

  case 390:
#line 2147 "c-parse.y"
                { push_parm_decl ((yyvsp[0].ttype)); }
#line 4886 "c-parse.c"
    break;

  case 391:
#line 2149 "c-parse.y"
                { push_parm_decl ((yyvsp[0].ttype)); }
#line 4892 "c-parse.c"
    break;

  case 392:
#line 2156 "c-parse.y"
                { (yyval.ttype) = build_tree_list (build_tree_list (current_declspecs,
							 (yyvsp[-1].ttype)),
					build_tree_list (prefix_attributes,
							 (yyvsp[0].ttype)));
		  current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[-2].itype)); }
#line 4905 "c-parse.c"
    break;

  case 393:
#line 2165 "c-parse.y"
                { (yyval.ttype) = build_tree_list (build_tree_list (current_declspecs,
							 (yyvsp[-1].ttype)),
					build_tree_list (prefix_attributes,
							 (yyvsp[0].ttype))); 
		  current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[-2].itype)); }
#line 4918 "c-parse.c"
    break;

  case 394:
#line 2174 "c-parse.y"
                { (yyval.ttype) = build_tree_list (build_tree_list (current_declspecs,
							 (yyvsp[-1].ttype)),
					build_tree_list (prefix_attributes,
							 (yyvsp[0].ttype)));
		  current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[-2].itype)); }
#line 4931 "c-parse.c"
    break;

  case 395:
#line 2183 "c-parse.y"
                { (yyval.ttype) = build_tree_list (build_tree_list (current_declspecs,
							 (yyvsp[-1].ttype)),
					build_tree_list (prefix_attributes,
							 (yyvsp[0].ttype)));
		  current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[-2].itype));  }
#line 4944 "c-parse.c"
    break;

  case 396:
#line 2193 "c-parse.y"
                { (yyval.ttype) = build_tree_list (build_tree_list (current_declspecs,
							 (yyvsp[-1].ttype)),
					build_tree_list (prefix_attributes,
							 (yyvsp[0].ttype)));
		  current_declspecs = TREE_VALUE (declspec_stack);
		  prefix_attributes = TREE_PURPOSE (declspec_stack);
		  declspec_stack = TREE_CHAIN (declspec_stack);
		  resume_momentary ((yyvsp[-2].itype));  }
#line 4957 "c-parse.c"
    break;

  case 397:
#line 2207 "c-parse.y"
                { pushlevel (0);
		  clear_parm_order ();
		  declare_parm_level (1); }
#line 4965 "c-parse.c"
    break;

  case 398:
#line 2211 "c-parse.y"
                { (yyval.ttype) = (yyvsp[0].ttype);
		  parmlist_tags_warning ();
		  poplevel (0, 0, 0); }
#line 4973 "c-parse.c"
    break;

  case 400:
#line 2219 "c-parse.y"
                { tree t;
		  for (t = (yyvsp[-1].ttype); t; t = TREE_CHAIN (t))
		    if (TREE_VALUE (t) == NULL_TREE)
		      error ("`...' in old-style identifier list");
		  (yyval.ttype) = tree_cons (NULL_TREE, NULL_TREE, (yyvsp[-1].ttype)); }
#line 4983 "c-parse.c"
    break;

  case 401:
#line 2229 "c-parse.y"
                { (yyval.ttype) = build_tree_list (NULL_TREE, (yyvsp[0].ttype)); }
#line 4989 "c-parse.c"
    break;

  case 402:
#line 2231 "c-parse.y"
                { (yyval.ttype) = chainon ((yyvsp[-2].ttype), build_tree_list (NULL_TREE, (yyvsp[0].ttype))); }
#line 4995 "c-parse.c"
    break;

  case 403:
#line 2237 "c-parse.y"
                { (yyval.ttype) = build_tree_list (NULL_TREE, (yyvsp[0].ttype)); }
#line 5001 "c-parse.c"
    break;

  case 404:
#line 2239 "c-parse.y"
                { (yyval.ttype) = chainon ((yyvsp[-2].ttype), build_tree_list (NULL_TREE, (yyvsp[0].ttype))); }
#line 5007 "c-parse.c"
    break;

  case 405:
#line 2244 "c-parse.y"
                { (yyval.itype) = pedantic;
		  pedantic = 0; }
#line 5014 "c-parse.c"
    break;


#line 5018 "c-parse.c"

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
                  yystos[+*yyssp], yyvsp);
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
#line 2248 "c-parse.y"

