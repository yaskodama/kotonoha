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
#line 12 "kotonoha_nested.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
int yylex(void);
void yyerror(const char *);
char *cat(int n, ...);
char *ind(const char *);
char *join(const char *, const char *);
char *initlines(char *, char *);
char *bnd(char *);
typedef struct Item { int kind; char *actor, *h, *s; struct Item *next; } Item;
Item *mkitem(int kind, char *actor, char *h, char *s);
Item *append(Item *a, Item *b);
char *print_def(char *name, char *decl, Item *items, char *endname);
extern int curline; extern char curtext[];
static char *output;
#define SEP "\x1f"   /* 並び（〜と〜と〜）の区切り */

#line 92 "kotonoha.tab.c"

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

#include "kotonoha.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NAME = 3,                       /* NAME  */
  YYSYMBOL_NUMBER = 4,                     /* NUMBER  */
  YYSYMBOL_STRING = 5,                     /* STRING  */
  YYSYMBOL_K_DEFACTOR = 6,                 /* K_DEFACTOR  */
  YYSYMBOL_K_HAS = 7,                      /* K_HAS  */
  YYSYMBOL_K_INIT = 8,                     /* K_INIT  */
  YYSYMBOL_K_TOSHI = 9,                    /* K_TOSHI  */
  YYSYMBOL_K_TOSURU = 10,                  /* K_TOSURU  */
  YYSYMBOL_T_MSG = 11,                     /* T_MSG  */
  YYSYMBOL_K_RECV = 12,                    /* K_RECV  */
  YYSYMBOL_KORE = 13,                      /* KORE  */
  YYSYMBOL_K_ENDDEF = 14,                  /* K_ENDDEF  */
  YYSYMBOL_K_RUN = 15,                     /* K_RUN  */
  YYSYMBOL_K_ENDRUN = 16,                  /* K_ENDRUN  */
  YYSYMBOL_MARU = 17,                      /* MARU  */
  YYSYMBOL_TEN = 18,                       /* TEN  */
  YYSYMBOL_SONOATO = 19,                   /* SONOATO  */
  YYSYMBOL_NARABA = 20,                    /* NARABA  */
  YYSYMBOL_DENAKEREBA = 21,                /* DENAKEREBA  */
  YYSYMBOL_YORICHIISA = 22,                /* YORICHIISA  */
  YYSYMBOL_SOUDENAKEREBA = 23,             /* SOUDENAKEREBA  */
  YYSYMBOL_K_BLOCK = 24,                   /* K_BLOCK  */
  YYSYMBOL_IJOU = 25,                      /* IJOU  */
  YYSYMBOL_KARA = 26,                      /* KARA  */
  YYSYMBOL_MADE_NITSUITE = 27,             /* MADE_NITSUITE  */
  YYSYMBOL_WA = 28,                        /* WA  */
  YYSYMBOL_TO = 29,                        /* TO  */
  YYSYMBOL_GA = 30,                        /* GA  */
  YYSYMBOL_NI = 31,                        /* NI  */
  YYSYMBOL_WO = 32,                        /* WO  */
  YYSYMBOL_NO = 33,                        /* NO  */
  YYSYMBOL_NO_MATSUBI = 34,                /* NO_MATSUBI  */
  YYSYMBOL_NO_SENTOU_KARA = 35,            /* NO_SENTOU_KARA  */
  YYSYMBOL_NO_ZENIN = 36,                  /* NO_ZENIN  */
  YYSYMBOL_BANME = 37,                     /* BANME  */
  YYSYMBOL_SOREZORE = 38,                  /* SOREZORE  */
  YYSYMBOL_T_MOJIRETSU = 39,               /* T_MOJIRETSU  */
  YYSYMBOL_T_ACTOR = 40,                   /* T_ACTOR  */
  YYSYMBOL_ICHITSU = 41,                   /* ICHITSU  */
  YYSYMBOL_HYOUJI_S = 42,                  /* HYOUJI_S  */
  YYSYMBOL_HYOUJI_R = 43,                  /* HYOUJI_R  */
  YYSYMBOL_OKURU_S = 44,                   /* OKURU_S  */
  YYSYMBOL_OKURU_R = 45,                   /* OKURU_R  */
  YYSYMBOL_HENKOU_S = 46,                  /* HENKOU_S  */
  YYSYMBOL_HENKOU_R = 47,                  /* HENKOU_R  */
  YYSYMBOL_KUWAE_S = 48,                   /* KUWAE_S  */
  YYSYMBOL_KUWAE_R = 49,                   /* KUWAE_R  */
  YYSYMBOL_KUWAETA = 50,                   /* KUWAETA  */
  YYSYMBOL_TSUIKA_S = 51,                  /* TSUIKA_S  */
  YYSYMBOL_TSUIKA_R = 52,                  /* TSUIKA_R  */
  YYSYMBOL_TORIDASU_S = 53,                /* TORIDASU_S  */
  YYSYMBOL_TORIDASU_R = 54,                /* TORIDASU_R  */
  YYSYMBOL_NAZUKE_S = 55,                  /* NAZUKE_S  */
  YYSYMBOL_NAZUKE_R = 56,                  /* NAZUKE_R  */
  YYSYMBOL_SEISEI_R = 57,                  /* SEISEI_R  */
  YYSYMBOL_YOUI_R = 58,                    /* YOUI_R  */
  YYSYMBOL_HIITA = 59,                     /* HIITA  */
  YYSYMBOL_WARIAMARI = 60,                 /* WARIAMARI  */
  YYSYMBOL_NO_YOUSOSU = 61,                /* NO_YOUSOSU  */
  YYSYMBOL_HAI = 62,                       /* HAI  */
  YYSYMBOL_IIE = 63,                       /* IIE  */
  YYSYMBOL_NASHI = 64,                     /* NASHI  */
  YYSYMBOL_SORA = 65,                      /* SORA  */
  YYSYMBOL_SORA_HAIRETSU = 66,             /* SORA_HAIRETSU  */
  YYSYMBOL_JIBUN = 67,                     /* JIBUN  */
  YYSYMBOL_JIBUN_JISHIN = 68,              /* JIBUN_JISHIN  */
  YYSYMBOL_GENZAI = 69,                    /* GENZAI  */
  YYSYMBOL_SONO = 70,                      /* SONO  */
  YYSYMBOL_LP = 71,                        /* LP  */
  YYSYMBOL_RP = 72,                        /* RP  */
  YYSYMBOL_YYACCEPT = 73,                  /* $accept  */
  YYSYMBOL_program = 74,                   /* program  */
  YYSYMBOL_defs = 75,                      /* defs  */
  YYSYMBOL_def = 76,                       /* def  */
  YYSYMBOL_decl = 77,                      /* decl  */
  YYSYMBOL_names = 78,                     /* names  */
  YYSYMBOL_items = 79,                     /* items  */
  YYSYMBOL_item = 80,                      /* item  */
  YYSYMBOL_init = 81,                      /* init  */
  YYSYMBOL_inits = 82,                     /* inits  */
  YYSYMBOL_initp = 83,                     /* initp  */
  YYSYMBOL_header = 84,                    /* header  */
  YYSYMBOL_stmts = 85,                     /* stmts  */
  YYSYMBOL_stmt = 86,                      /* stmt  */
  YYSYMBOL_body = 87,                      /* body  */
  YYSYMBOL_ifstmt = 88,                    /* ifstmt  */
  YYSYMBOL_part = 89,                      /* part  */
  YYSYMBOL_cond = 90,                      /* cond  */
  YYSYMBOL_loop = 91,                      /* loop  */
  YYSYMBOL_clause_s = 92,                  /* clause_s  */
  YYSYMBOL_clause_r = 93,                  /* clause_r  */
  YYSYMBOL_disp = 94,                      /* disp  */
  YYSYMBOL_send = 95,                      /* send  */
  YYSYMBOL_sendarg = 96,                   /* sendarg  */
  YYSYMBOL_chg = 97,                       /* chg  */
  YYSYMBOL_add = 98,                       /* add  */
  YYSYMBOL_push = 99,                      /* push  */
  YYSYMBOL_take = 100,                     /* take  */
  YYSYMBOL_bind = 101,                     /* bind  */
  YYSYMBOL_maker = 102,                    /* maker  */
  YYSYMBOL_exprs = 103,                    /* exprs  */
  YYSYMBOL_expr = 104,                     /* expr  */
  YYSYMBOL_term = 105,                     /* term  */
  YYSYMBOL_arith = 106,                    /* arith  */
  YYSYMBOL_idx = 107                       /* idx  */
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

#if 1

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
#endif /* 1 */

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   315

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  73
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  92
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  186

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   327


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
      65,    66,    67,    68,    69,    70,    71,    72
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    55,    55,    58,    59,    64,    68,    70,    71,    75,
      76,    78,    79,    80,    83,    85,    86,    88,    93,    94,
      98,    99,   101,   102,   103,   104,   105,   108,   109,   113,
     114,   116,   117,   118,   120,   121,   122,   126,   131,   131,
     131,   132,   132,   132,   133,   135,   135,   135,   136,   136,
     136,   137,   140,   143,   144,   145,   147,   148,   151,   154,
     157,   158,   161,   164,   166,   167,   171,   172,   174,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   195,   196,   197,   199,
     200,   201,   202
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NAME", "NUMBER",
  "STRING", "K_DEFACTOR", "K_HAS", "K_INIT", "K_TOSHI", "K_TOSURU",
  "T_MSG", "K_RECV", "KORE", "K_ENDDEF", "K_RUN", "K_ENDRUN", "MARU",
  "TEN", "SONOATO", "NARABA", "DENAKEREBA", "YORICHIISA", "SOUDENAKEREBA",
  "K_BLOCK", "IJOU", "KARA", "MADE_NITSUITE", "WA", "TO", "GA", "NI", "WO",
  "NO", "NO_MATSUBI", "NO_SENTOU_KARA", "NO_ZENIN", "BANME", "SOREZORE",
  "T_MOJIRETSU", "T_ACTOR", "ICHITSU", "HYOUJI_S", "HYOUJI_R", "OKURU_S",
  "OKURU_R", "HENKOU_S", "HENKOU_R", "KUWAE_S", "KUWAE_R", "KUWAETA",
  "TSUIKA_S", "TSUIKA_R", "TORIDASU_S", "TORIDASU_R", "NAZUKE_S",
  "NAZUKE_R", "SEISEI_R", "YOUI_R", "HIITA", "WARIAMARI", "NO_YOUSOSU",
  "HAI", "IIE", "NASHI", "SORA", "SORA_HAIRETSU", "JIBUN", "JIBUN_JISHIN",
  "GENZAI", "SONO", "LP", "RP", "$accept", "program", "defs", "def",
  "decl", "names", "items", "item", "init", "inits", "initp", "header",
  "stmts", "stmt", "body", "ifstmt", "part", "cond", "loop", "clause_s",
  "clause_r", "disp", "send", "sendarg", "chg", "add", "push", "take",
  "bind", "maker", "exprs", "expr", "term", "arith", "idx", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-121)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-61)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -121,    19,    10,  -121,    17,  -121,  -121,    27,    36,     6,
    -121,   -12,  -121,    -3,    47,   215,  -121,  -121,  -121,  -121,
    -121,  -121,  -121,  -121,    79,   228,  -121,    35,  -121,   133,
    -121,  -121,    48,    18,    44,    50,    63,    64,    67,    73,
      96,    55,    -4,   -26,  -121,   114,   105,    99,  -121,  -121,
     117,  -121,    29,  -121,  -121,    49,  -121,  -121,   127,  -121,
     128,   215,  -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,
    -121,  -121,  -121,  -121,  -121,  -121,   142,   228,   145,   159,
     228,   228,   143,   121,     5,  -121,  -121,    14,   150,  -121,
    -121,   123,  -121,   175,  -121,    25,    32,   113,  -121,   228,
     228,   228,   122,  -121,   133,  -121,   104,   129,  -121,     3,
     151,   134,  -121,    -7,   132,    57,   149,   155,  -121,  -121,
    -121,   228,  -121,   124,  -121,   162,   163,   228,  -121,  -121,
     228,   244,   125,   173,   174,   176,  -121,  -121,  -121,   205,
     224,  -121,    91,   219,   133,  -121,  -121,  -121,  -121,   240,
     -21,  -121,  -121,  -121,  -121,     8,  -121,  -121,     7,  -121,
     193,   203,   182,   228,   223,   205,  -121,  -121,   205,  -121,
       0,   184,   185,  -121,  -121,  -121,   226,   227,  -121,   257,
    -121,  -121,  -121,  -121,   249,  -121
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     0,     1,     0,    20,     4,     0,     0,     0,
       9,    69,    71,    72,     0,     0,    74,    75,    76,    77,
      78,    79,    80,    81,     0,     0,    21,     0,    24,     0,
      26,    27,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    66,    68,    85,     0,     0,     0,    73,     2,
       0,    25,    66,    70,    69,     0,    22,    20,     0,    33,
      29,     0,    38,    45,    39,    46,    40,    47,    41,    48,
      42,    49,    43,    50,    44,    51,     0,     0,     0,    52,
       0,     0,     0,     0,     0,    84,     7,     0,     0,    10,
      11,     0,    15,     0,    13,     0,    66,     0,    23,     0,
       0,     0,     0,    31,     0,    28,    66,     0,    67,    72,
       0,     0,    65,     0,     0,     0,     0,     0,    82,    89,
      90,     0,    92,     0,     6,     0,     0,     0,    14,    12,
       0,     0,     0,     0,     0,     0,    32,    30,    63,    56,
       0,    59,    58,     0,     0,    34,    35,    36,    62,     0,
       0,    83,     8,     5,    16,     0,    66,    17,    72,    64,
       0,     0,     0,     0,     0,    56,    61,    37,    56,    91,
       0,     0,     0,    88,    57,    53,     0,     0,    18,     0,
      87,    86,    54,    55,     0,    19
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,
     135,  -121,   206,   -43,   -14,    -9,  -100,  -121,  -121,  -121,
    -121,  -121,  -121,  -120,  -121,  -121,  -121,  -121,  -121,  -121,
     -44,    -8,  -121,   180,  -121
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     6,    10,    87,    46,    89,    90,    91,
      92,    93,     8,    26,    27,    28,    60,    29,    30,    31,
      32,    33,    34,   164,    35,    36,    37,    38,    39,    40,
      41,    52,    43,    44,   123
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      42,    50,    95,    94,   137,    99,    51,    84,   118,   119,
     100,   101,   178,     4,   139,    58,   130,    55,   170,     3,
      59,   124,    80,     7,   142,     5,    81,   143,    47,   179,
       9,    82,    83,   130,    45,    85,    48,    77,    96,    11,
      12,    13,    48,   125,   167,   176,    48,   105,   177,    14,
     129,   169,    56,   106,    77,    15,    78,    79,    80,    81,
      62,    63,   131,    49,    82,    83,    61,    82,    83,   108,
     111,   113,   114,   115,   120,    99,   121,   145,   146,   147,
     100,   101,    53,   155,    77,    42,    78,    79,    64,    65,
      58,   133,   134,   135,    42,    59,    66,    67,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    11,    12,
      13,    68,    69,   150,    76,    70,    71,    86,    88,   156,
      72,    73,   157,   115,    15,    11,    12,    13,    74,    75,
      58,    97,   127,   128,    98,    59,    11,    12,    13,    82,
      83,    15,   -60,   -60,   103,   107,   116,   136,    54,    12,
     109,   104,   117,   126,   132,   174,   140,    57,   138,   144,
     149,   151,    54,    12,    13,   152,   141,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,   153,    11,    12,
      13,   148,   159,   110,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,   160,   161,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,   112,    11,    12,
      13,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    54,    12,    13,   163,   165,   162,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    54,    12,   158,
     166,   168,   171,   172,   173,   175,   180,   181,   182,   183,
     184,   185,   154,   102,   122,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,     0,     0,     0,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
       0,     0,     0,     0,     0,     0,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25
};

static const yytype_int16 yycheck[] =
{
       8,    15,    46,    46,   104,    26,    15,    33,     3,     4,
      31,    32,    12,     3,    11,    29,     8,    25,    11,     0,
      29,     7,    26,     6,    31,    15,    30,    34,    40,    29,
       3,    35,    36,     8,    28,    61,    39,    29,    46,     3,
       4,     5,    39,    29,   144,   165,    39,    61,   168,    13,
      93,    72,    17,    61,    29,    19,    31,    32,    26,    30,
      42,    43,    30,    16,    35,    36,    18,    35,    36,    77,
      78,    79,    80,    81,    69,    26,    71,    20,    21,    22,
      31,    32,     3,   127,    29,    93,    31,    32,    44,    45,
     104,    99,   100,   101,   102,   104,    46,    47,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,     3,     4,
       5,    48,    49,   121,    18,    51,    52,     3,    13,   127,
      53,    54,   130,   131,    19,     3,     4,     5,    55,    56,
     144,    32,     9,    10,    17,   144,     3,     4,     5,    35,
      36,    19,    51,    52,    17,     3,     3,    25,     3,     4,
       5,    23,    31,     3,    41,   163,     5,    24,    29,    27,
       5,    37,     3,     4,     5,     3,    32,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    14,     3,     4,
       5,    32,    57,    38,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    19,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    32,    32,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    58,     3,     4,
       5,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,     3,     4,     5,    29,    11,    60,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,     3,     4,     5,
      31,    11,    59,    50,    72,    32,    72,    72,    32,    32,
       3,    12,   127,    57,    84,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    -1,    -1,    -1,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      -1,    -1,    -1,    -1,    -1,    -1,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    74,    75,     0,     3,    15,    76,     6,    85,     3,
      77,     3,     4,     5,    13,    19,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    86,    87,    88,    90,
      91,    92,    93,    94,    95,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,    28,    79,    40,    39,    16,
      87,    88,   104,     3,     3,   104,    17,    24,    87,    88,
      89,    18,    42,    43,    44,    45,    46,    47,    48,    49,
      51,    52,    53,    54,    55,    56,    18,    29,    31,    32,
      26,    30,    35,    36,    33,    61,     3,    78,    13,    80,
      81,    82,    83,    84,    86,   103,   104,    32,    17,    26,
      31,    32,    85,    17,    23,    87,   104,     3,   104,     5,
      38,   104,    58,   104,   104,   104,     3,    31,     3,     4,
      69,    71,   106,   107,     7,    29,     3,     9,    10,    86,
       8,    30,    41,   104,   104,   104,    25,    89,    29,    11,
       5,    32,    31,    34,    27,    20,    21,    22,    32,     5,
     104,    37,     3,    14,    83,   103,   104,   104,     5,    57,
      32,    32,    60,    29,    96,    11,    31,    89,    11,    72,
      11,    59,    50,    72,   104,    32,    96,    96,    12,    29,
      72,    72,    32,    32,     3,    12
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    73,    74,    75,    75,    76,    77,    78,    78,    79,
      79,    80,    80,    80,    81,    82,    82,    83,    84,    84,
      85,    85,    86,    86,    86,    86,    86,    87,    87,    88,
      88,    89,    89,    89,    90,    90,    90,    91,    92,    92,
      92,    92,    92,    92,    92,    93,    93,    93,    93,    93,
      93,    93,    94,    95,    95,    95,    96,    96,    97,    98,
      99,    99,   100,   101,   102,   102,   103,   103,   104,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   106,   106,   106,   107,
     107,   107,   107
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     5,     0,     2,     7,     4,     1,     3,     0,
       2,     1,     2,     1,     2,     1,     3,     3,     5,     7,
       0,     2,     2,     3,     1,     2,     1,     1,     3,     2,
       4,     2,     3,     1,     4,     4,     4,     5,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     6,     7,     7,     0,     2,     4,     4,
       4,     5,     4,     4,     5,     3,     1,     3,     1,     1,
       2,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     4,     2,     1,     7,     7,     6,     1,
       1,     3,     1
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
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
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
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
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
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

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

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
  case 2: /* program: defs K_RUN stmts KORE K_ENDRUN  */
#line 56 "kotonoha_nested.y"
            { output = cat(4, (yyvsp[-4].s), "実行を始める。\n", ind((yyvsp[-2].s)), "実行を終わる。\n"); }
#line 1612 "kotonoha.tab.c"
    break;

  case 3: /* defs: %empty  */
#line 58 "kotonoha_nested.y"
                            { (yyval.s) = ""; }
#line 1618 "kotonoha.tab.c"
    break;

  case 4: /* defs: defs def  */
#line 59 "kotonoha_nested.y"
                            { (yyval.s) = cat(3, (yyvsp[-1].s), (yyvsp[0].s), "\n"); }
#line 1624 "kotonoha.tab.c"
    break;

  case 5: /* def: NAME K_DEFACTOR decl items KORE NAME K_ENDDEF  */
#line 65 "kotonoha_nested.y"
            { (yyval.s) = print_def((yyvsp[-6].s), (yyvsp[-4].s), (yyvsp[-3].it), (yyvsp[-1].s)); }
#line 1630 "kotonoha.tab.c"
    break;

  case 6: /* decl: NAME WA names K_HAS  */
#line 68 "kotonoha_nested.y"
                                { (yyval.s) = (yyvsp[-1].s); }
#line 1636 "kotonoha.tab.c"
    break;

  case 7: /* names: NAME  */
#line 70 "kotonoha_nested.y"
                                { (yyval.s) = (yyvsp[0].s); }
#line 1642 "kotonoha.tab.c"
    break;

  case 8: /* names: names TO NAME  */
#line 71 "kotonoha_nested.y"
                                { (yyval.s) = cat(3, (yyvsp[-2].s), SEP, (yyvsp[0].s)); }
#line 1648 "kotonoha.tab.c"
    break;

  case 9: /* items: %empty  */
#line 75 "kotonoha_nested.y"
                                { (yyval.it) = NULL; }
#line 1654 "kotonoha.tab.c"
    break;

  case 10: /* items: items item  */
#line 76 "kotonoha_nested.y"
                                { (yyval.it) = append((yyvsp[-1].it), (yyvsp[0].it)); }
#line 1660 "kotonoha.tab.c"
    break;

  case 11: /* item: init  */
#line 78 "kotonoha_nested.y"
                                { (yyval.it) = mkitem(0, NULL, NULL, (yyvsp[0].s)); }
#line 1666 "kotonoha.tab.c"
    break;

  case 12: /* item: header stmt  */
#line 79 "kotonoha_nested.y"
                                { (yyval.it) = mkitem(1, NULL, (yyvsp[-1].s), (yyvsp[0].s)); }
#line 1672 "kotonoha.tab.c"
    break;

  case 13: /* item: stmt  */
#line 80 "kotonoha_nested.y"
                                { (yyval.it) = mkitem(2, NULL, NULL, (yyvsp[0].s)); }
#line 1678 "kotonoha.tab.c"
    break;

  case 14: /* init: inits K_TOSURU  */
#line 83 "kotonoha_nested.y"
                                { (yyval.s) = (yyvsp[-1].s); }
#line 1684 "kotonoha.tab.c"
    break;

  case 15: /* inits: initp  */
#line 85 "kotonoha_nested.y"
                                { (yyval.s) = (yyvsp[0].s); }
#line 1690 "kotonoha.tab.c"
    break;

  case 16: /* inits: inits K_TOSHI initp  */
#line 86 "kotonoha_nested.y"
                                { (yyval.s) = cat(2, (yyvsp[-2].s), (yyvsp[0].s)); }
#line 1696 "kotonoha.tab.c"
    break;

  case 17: /* initp: exprs K_INIT expr  */
#line 89 "kotonoha_nested.y"
            { (yyval.s) = initlines((yyvsp[-2].s), (yyvsp[0].s)); }
#line 1702 "kotonoha.tab.c"
    break;

  case 18: /* header: expr GA STRING T_MSG K_RECV  */
#line 93 "kotonoha_nested.y"
                                                   { (yyval.s) = cat(2, (yyvsp[-2].s), "を受け取ったとき、"); }
#line 1708 "kotonoha.tab.c"
    break;

  case 19: /* header: expr GA STRING T_MSG TO NAME K_RECV  */
#line 94 "kotonoha_nested.y"
                                                   { (yyval.s) = cat(4, (yyvsp[-4].s), "と ", (yyvsp[-1].s), " を受け取ったとき、"); }
#line 1714 "kotonoha.tab.c"
    break;

  case 20: /* stmts: %empty  */
#line 98 "kotonoha_nested.y"
                                { (yyval.s) = ""; }
#line 1720 "kotonoha.tab.c"
    break;

  case 21: /* stmts: stmts stmt  */
#line 99 "kotonoha_nested.y"
                                { (yyval.s) = cat(2, (yyvsp[-1].s), (yyvsp[0].s)); }
#line 1726 "kotonoha.tab.c"
    break;

  case 22: /* stmt: body MARU  */
#line 101 "kotonoha_nested.y"
                                { (yyval.s) = (yyvsp[-1].s); }
#line 1732 "kotonoha.tab.c"
    break;

  case 23: /* stmt: SONOATO body MARU  */
#line 102 "kotonoha_nested.y"
                                { (yyval.s) = (yyvsp[-1].s); }
#line 1738 "kotonoha.tab.c"
    break;

  case 24: /* stmt: ifstmt  */
#line 103 "kotonoha_nested.y"
                                { (yyval.s) = (yyvsp[0].s); }
#line 1744 "kotonoha.tab.c"
    break;

  case 25: /* stmt: SONOATO ifstmt  */
#line 104 "kotonoha_nested.y"
                                { (yyval.s) = (yyvsp[0].s); }
#line 1750 "kotonoha.tab.c"
    break;

  case 26: /* stmt: loop  */
#line 105 "kotonoha_nested.y"
                                { (yyval.s) = (yyvsp[0].s); }
#line 1756 "kotonoha.tab.c"
    break;

  case 27: /* body: clause_s  */
#line 108 "kotonoha_nested.y"
                                { (yyval.s) = cat(2, (yyvsp[0].s), "。\n"); }
#line 1762 "kotonoha.tab.c"
    break;

  case 28: /* body: clause_r TEN body  */
#line 109 "kotonoha_nested.y"
                                { (yyval.s) = cat(3, (yyvsp[-2].s), "。\n", (yyvsp[0].s)); }
#line 1768 "kotonoha.tab.c"
    break;

  case 29: /* ifstmt: cond part  */
#line 113 "kotonoha_nested.y"
                                            { (yyval.s) = cat(4, (yyvsp[-1].s), "\n", ind((yyvsp[0].s)), "以上。\n"); }
#line 1774 "kotonoha.tab.c"
    break;

  case 30: /* ifstmt: cond part SOUDENAKEREBA part  */
#line 114 "kotonoha_nested.y"
                                            { (yyval.s) = cat(6, (yyvsp[-3].s), "\n", ind((yyvsp[-2].s)), "そうでなければ、\n", ind((yyvsp[0].s)), "以上。\n"); }
#line 1780 "kotonoha.tab.c"
    break;

  case 31: /* part: body MARU  */
#line 116 "kotonoha_nested.y"
                                    { (yyval.s) = (yyvsp[-1].s); }
#line 1786 "kotonoha.tab.c"
    break;

  case 32: /* part: K_BLOCK stmts IJOU  */
#line 117 "kotonoha_nested.y"
                                    { (yyval.s) = (yyvsp[-1].s); }
#line 1792 "kotonoha.tab.c"
    break;

  case 33: /* part: ifstmt  */
#line 118 "kotonoha_nested.y"
                                    { (yyval.s) = (yyvsp[0].s); }
#line 1798 "kotonoha.tab.c"
    break;

  case 34: /* cond: expr GA expr NARABA  */
#line 120 "kotonoha_nested.y"
                                    { (yyval.s) = cat(5, "もし ", (yyvsp[-3].s), " が ", (yyvsp[-1].s), " ならば、"); }
#line 1804 "kotonoha.tab.c"
    break;

  case 35: /* cond: expr GA expr DENAKEREBA  */
#line 121 "kotonoha_nested.y"
                                    { (yyval.s) = cat(5, "もし ", (yyvsp[-3].s), " が ", (yyvsp[-1].s), " でない ならば、"); }
#line 1810 "kotonoha.tab.c"
    break;

  case 36: /* cond: expr GA expr YORICHIISA  */
#line 122 "kotonoha_nested.y"
                                    { (yyval.s) = cat(5, "もし ", (yyvsp[-3].s), " が ", (yyvsp[-1].s), " より小さい ならば、"); }
#line 1816 "kotonoha.tab.c"
    break;

  case 37: /* loop: expr KARA expr MADE_NITSUITE part  */
#line 127 "kotonoha_nested.y"
            { (yyval.s) = cat(6, bnd((yyvsp[-4].s)), "から", bnd((yyvsp[-2].s)), "まで繰り返す。\n", ind((yyvsp[0].s)), "以上。\n"); }
#line 1822 "kotonoha.tab.c"
    break;

  case 38: /* clause_s: disp HYOUJI_S  */
#line 131 "kotonoha_nested.y"
                          { (yyval.s) = (yyvsp[-1].s); }
#line 1828 "kotonoha.tab.c"
    break;

  case 39: /* clause_s: send OKURU_S  */
#line 131 "kotonoha_nested.y"
                                                         { (yyval.s) = (yyvsp[-1].s); }
#line 1834 "kotonoha.tab.c"
    break;

  case 40: /* clause_s: chg HENKOU_S  */
#line 131 "kotonoha_nested.y"
                                                                                     { (yyval.s) = (yyvsp[-1].s); }
#line 1840 "kotonoha.tab.c"
    break;

  case 41: /* clause_s: add KUWAE_S  */
#line 132 "kotonoha_nested.y"
                          { (yyval.s) = (yyvsp[-1].s); }
#line 1846 "kotonoha.tab.c"
    break;

  case 42: /* clause_s: push TSUIKA_S  */
#line 132 "kotonoha_nested.y"
                                                         { (yyval.s) = (yyvsp[-1].s); }
#line 1852 "kotonoha.tab.c"
    break;

  case 43: /* clause_s: take TORIDASU_S  */
#line 132 "kotonoha_nested.y"
                                                                                        { (yyval.s) = (yyvsp[-1].s); }
#line 1858 "kotonoha.tab.c"
    break;

  case 44: /* clause_s: bind NAZUKE_S  */
#line 133 "kotonoha_nested.y"
                          { (yyval.s) = (yyvsp[-1].s); }
#line 1864 "kotonoha.tab.c"
    break;

  case 45: /* clause_r: disp HYOUJI_R  */
#line 135 "kotonoha_nested.y"
                          { (yyval.s) = (yyvsp[-1].s); }
#line 1870 "kotonoha.tab.c"
    break;

  case 46: /* clause_r: send OKURU_R  */
#line 135 "kotonoha_nested.y"
                                                         { (yyval.s) = (yyvsp[-1].s); }
#line 1876 "kotonoha.tab.c"
    break;

  case 47: /* clause_r: chg HENKOU_R  */
#line 135 "kotonoha_nested.y"
                                                                                     { (yyval.s) = (yyvsp[-1].s); }
#line 1882 "kotonoha.tab.c"
    break;

  case 48: /* clause_r: add KUWAE_R  */
#line 136 "kotonoha_nested.y"
                          { (yyval.s) = (yyvsp[-1].s); }
#line 1888 "kotonoha.tab.c"
    break;

  case 49: /* clause_r: push TSUIKA_R  */
#line 136 "kotonoha_nested.y"
                                                         { (yyval.s) = (yyvsp[-1].s); }
#line 1894 "kotonoha.tab.c"
    break;

  case 50: /* clause_r: take TORIDASU_R  */
#line 136 "kotonoha_nested.y"
                                                                                        { (yyval.s) = (yyvsp[-1].s); }
#line 1900 "kotonoha.tab.c"
    break;

  case 51: /* clause_r: bind NAZUKE_R  */
#line 137 "kotonoha_nested.y"
                          { (yyval.s) = (yyvsp[-1].s); }
#line 1906 "kotonoha.tab.c"
    break;

  case 52: /* disp: exprs WO  */
#line 140 "kotonoha_nested.y"
                                                     { (yyval.s) = cat(2, join((yyvsp[-1].s), " と "), " を表示する"); }
#line 1912 "kotonoha.tab.c"
    break;

  case 53: /* send: exprs NI STRING T_MSG sendarg WO  */
#line 143 "kotonoha_nested.y"
                                                     { (yyval.s) = cat(5, join((yyvsp[-5].s), " と "), " に", (yyvsp[-3].s), (yyvsp[-1].s), "を送る"); }
#line 1918 "kotonoha.tab.c"
    break;

  case 54: /* send: exprs NI SOREZORE STRING T_MSG sendarg WO  */
#line 144 "kotonoha_nested.y"
                                                     { (yyval.s) = cat(5, join((yyvsp[-6].s), " と "), " に それぞれ", (yyvsp[-3].s), (yyvsp[-1].s), "を送る"); }
#line 1924 "kotonoha.tab.c"
    break;

  case 55: /* send: expr NO_ZENIN NI STRING T_MSG sendarg WO  */
#line 145 "kotonoha_nested.y"
                                                     { (yyval.s) = cat(5, (yyvsp[-6].s), " の全員に", (yyvsp[-3].s), (yyvsp[-1].s), "を送る"); }
#line 1930 "kotonoha.tab.c"
    break;

  case 56: /* sendarg: %empty  */
#line 147 "kotonoha_nested.y"
                                { (yyval.s) = ""; }
#line 1936 "kotonoha.tab.c"
    break;

  case 57: /* sendarg: TO expr  */
#line 148 "kotonoha_nested.y"
                                { (yyval.s) = cat(3, "と ", (yyvsp[0].s), " "); }
#line 1942 "kotonoha.tab.c"
    break;

  case 58: /* chg: exprs WO expr NI  */
#line 151 "kotonoha_nested.y"
                                                     { (yyval.s) = cat(3, join((yyvsp[-3].s), " と "), " は ", (yyvsp[-1].s)); }
#line 1948 "kotonoha.tab.c"
    break;

  case 59: /* add: exprs NI expr WO  */
#line 154 "kotonoha_nested.y"
                                                     { (yyval.s) = cat(5, (yyvsp[-3].s), " は ", (yyvsp[-3].s), " 足す ", (yyvsp[-1].s)); }
#line 1954 "kotonoha.tab.c"
    break;

  case 60: /* push: exprs WO expr NI  */
#line 157 "kotonoha_nested.y"
                                                     { (yyval.s) = cat(4, (yyvsp[-1].s), " に ", join((yyvsp[-3].s), " と "), " を追加する"); }
#line 1960 "kotonoha.tab.c"
    break;

  case 61: /* push: exprs WO expr NO_MATSUBI NI  */
#line 158 "kotonoha_nested.y"
                                                     { (yyval.s) = cat(4, (yyvsp[-2].s), " に ", join((yyvsp[-4].s), " と "), " を追加する"); }
#line 1966 "kotonoha.tab.c"
    break;

  case 62: /* take: expr NO_SENTOU_KARA NAME WO  */
#line 161 "kotonoha_nested.y"
                                                     { (yyval.s) = cat(4, (yyvsp[-1].s), " は ", (yyvsp[-3].s), " の先頭を取り出す"); }
#line 1972 "kotonoha.tab.c"
    break;

  case 63: /* bind: maker TEN NAME TO  */
#line 164 "kotonoha_nested.y"
                                                     { (yyval.s) = cat(3, (yyvsp[-1].s), " は ", (yyvsp[-3].s)); }
#line 1978 "kotonoha.tab.c"
    break;

  case 64: /* maker: NAME T_ACTOR WO ICHITSU SEISEI_R  */
#line 166 "kotonoha_nested.y"
                                                     { (yyval.s) = cat(3, "「", (yyvsp[-4].s), "」の新しいアクター"); }
#line 1984 "kotonoha.tab.c"
    break;

  case 65: /* maker: exprs WO YOUI_R  */
#line 167 "kotonoha_nested.y"
                                                     { (yyval.s) = (yyvsp[-2].s); }
#line 1990 "kotonoha.tab.c"
    break;

  case 66: /* exprs: expr  */
#line 171 "kotonoha_nested.y"
                                { (yyval.s) = (yyvsp[0].s); }
#line 1996 "kotonoha.tab.c"
    break;

  case 67: /* exprs: exprs TO expr  */
#line 172 "kotonoha_nested.y"
                                { (yyval.s) = cat(3, (yyvsp[-2].s), SEP, (yyvsp[0].s)); }
#line 2002 "kotonoha.tab.c"
    break;

  case 68: /* expr: term  */
#line 174 "kotonoha_nested.y"
                                { (yyval.s) = (yyvsp[0].s); }
#line 2008 "kotonoha.tab.c"
    break;

  case 69: /* term: NAME  */
#line 176 "kotonoha_nested.y"
                                { (yyval.s) = (yyvsp[0].s); }
#line 2014 "kotonoha.tab.c"
    break;

  case 70: /* term: SONO NAME  */
#line 177 "kotonoha_nested.y"
                                { (yyval.s) = (yyvsp[0].s); }
#line 2020 "kotonoha.tab.c"
    break;

  case 71: /* term: NUMBER  */
#line 178 "kotonoha_nested.y"
                                { (yyval.s) = (yyvsp[0].s); }
#line 2026 "kotonoha.tab.c"
    break;

  case 72: /* term: STRING  */
#line 179 "kotonoha_nested.y"
                                { (yyval.s) = (yyvsp[0].s); }
#line 2032 "kotonoha.tab.c"
    break;

  case 73: /* term: STRING T_MOJIRETSU  */
#line 180 "kotonoha_nested.y"
                                { (yyval.s) = (yyvsp[-1].s); }
#line 2038 "kotonoha.tab.c"
    break;

  case 74: /* term: HAI  */
#line 181 "kotonoha_nested.y"
                                { (yyval.s) = "はい"; }
#line 2044 "kotonoha.tab.c"
    break;

  case 75: /* term: IIE  */
#line 182 "kotonoha_nested.y"
                                { (yyval.s) = "いいえ"; }
#line 2050 "kotonoha.tab.c"
    break;

  case 76: /* term: NASHI  */
#line 183 "kotonoha_nested.y"
                                { (yyval.s) = "なし"; }
#line 2056 "kotonoha.tab.c"
    break;

  case 77: /* term: SORA  */
#line 184 "kotonoha_nested.y"
                                { (yyval.s) = "空"; }
#line 2062 "kotonoha.tab.c"
    break;

  case 78: /* term: SORA_HAIRETSU  */
#line 185 "kotonoha_nested.y"
                                { (yyval.s) = "空の配列"; }
#line 2068 "kotonoha.tab.c"
    break;

  case 79: /* term: JIBUN  */
#line 186 "kotonoha_nested.y"
                                { (yyval.s) = "自分"; }
#line 2074 "kotonoha.tab.c"
    break;

  case 80: /* term: JIBUN_JISHIN  */
#line 187 "kotonoha_nested.y"
                                { (yyval.s) = "自分"; }
#line 2080 "kotonoha.tab.c"
    break;

  case 81: /* term: GENZAI  */
#line 188 "kotonoha_nested.y"
                                { (yyval.s) = "現在の番号"; }
#line 2086 "kotonoha.tab.c"
    break;

  case 82: /* term: term NO NAME  */
#line 189 "kotonoha_nested.y"
                                { (yyval.s) = cat(3, (yyvsp[-2].s), "の", (yyvsp[0].s)); }
#line 2092 "kotonoha.tab.c"
    break;

  case 83: /* term: term NO idx BANME  */
#line 190 "kotonoha_nested.y"
                                { (yyval.s) = cat(4, (yyvsp[-3].s), "の ", (yyvsp[-1].s), " 番目"); }
#line 2098 "kotonoha.tab.c"
    break;

  case 84: /* term: term NO_YOUSOSU  */
#line 191 "kotonoha_nested.y"
                                { (yyval.s) = cat(2, (yyvsp[-1].s), " の要素数"); }
#line 2104 "kotonoha.tab.c"
    break;

  case 85: /* term: arith  */
#line 192 "kotonoha_nested.y"
                                { (yyval.s) = (yyvsp[0].s); }
#line 2110 "kotonoha.tab.c"
    break;

  case 86: /* arith: LP expr NI expr WO KUWAETA RP  */
#line 195 "kotonoha_nested.y"
                                            { (yyval.s) = cat(5, "（", (yyvsp[-5].s), " 足す ", (yyvsp[-3].s), "）"); }
#line 2116 "kotonoha.tab.c"
    break;

  case 87: /* arith: LP expr KARA expr WO HIITA RP  */
#line 196 "kotonoha_nested.y"
                                            { (yyval.s) = cat(5, "（", (yyvsp[-5].s), " 引く ", (yyvsp[-3].s), "）"); }
#line 2122 "kotonoha.tab.c"
    break;

  case 88: /* arith: LP expr WO expr WARIAMARI RP  */
#line 197 "kotonoha_nested.y"
                                            { (yyval.s) = cat(5, "（", (yyvsp[-4].s), " を ", (yyvsp[-2].s), " で割った余り）"); }
#line 2128 "kotonoha.tab.c"
    break;

  case 89: /* idx: NUMBER  */
#line 199 "kotonoha_nested.y"
                                { (yyval.s) = (yyvsp[0].s); }
#line 2134 "kotonoha.tab.c"
    break;

  case 90: /* idx: GENZAI  */
#line 200 "kotonoha_nested.y"
                                { (yyval.s) = "現在の番号"; }
#line 2140 "kotonoha.tab.c"
    break;

  case 91: /* idx: LP expr RP  */
#line 201 "kotonoha_nested.y"
                                { (yyval.s) = (yyvsp[-1].s); }
#line 2146 "kotonoha.tab.c"
    break;

  case 92: /* idx: arith  */
#line 202 "kotonoha_nested.y"
                                { (yyval.s) = (yyvsp[0].s); }
#line 2152 "kotonoha.tab.c"
    break;


#line 2156 "kotonoha.tab.c"

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
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
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
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 204 "kotonoha_nested.y"


int curline; char curtext[4096];

int yylex(void) {
    int code; char buf[4096];
    if (!fgets(buf, sizeof buf, stdin)) return 0;
    buf[strcspn(buf, "\n")] = 0;
    char *p = strchr(buf, '\t'), *q = p ? strchr(p + 1, '\t') : NULL;
    code = atoi(buf); curline = p ? atoi(p + 1) : 0;
    strcpy(curtext, q ? q + 1 : "");
    yylval.s = strdup(curtext);
    return code;
}
void yyerror(const char *m) {
    fprintf(stderr, "構文エラー %d行 「%s」の所: %s\n", curline, curtext, m);
}
char *cat(int n, ...) {
    va_list ap; size_t len = 1; int i;
    va_start(ap, n); for (i = 0; i < n; i++) len += strlen(va_arg(ap, char *)); va_end(ap);
    char *r = malloc(len); r[0] = 0;
    va_start(ap, n); for (i = 0; i < n; i++) strcat(r, va_arg(ap, char *)); va_end(ap);
    return r;
}
char *ind(const char *s) {               /* 各行の頭に4字下げ */
    char *r = malloc(strlen(s) * 2 + 8), *w = r; int bol = 1;
    for (; *s; s++) { if (bol && *s != '\n') { memcpy(w, "    ", 4); w += 4; } *w++ = *s; bol = (*s == '\n'); }
    *w = 0; return r;
}
char *join(const char *s, const char *sep) {
    char *r = strdup(""), *p = strdup(s), *q; int first = 1;
    for (q = strtok(p, SEP); q; q = strtok(NULL, SEP)) { r = cat(3, r, first ? "" : sep, q); first = 0; }
    return r;
}
char *initlines(char *names, char *v) {
    char *r = "", *p = strdup(names), *q;
    for (q = strtok(p, SEP); q; q = strtok(NULL, SEP)) r = cat(5, r, q, " は ", v, "。\n");
    return r;
}
/* 繰り返しの範囲: 数ならそのまま、全体が（…）ならそのまま、それ以外は（…）で囲む（構造化形式で読みやすく） */
char *bnd(char *s) {
    const char *p = s; int d = 0;
    while (*p >= '0' && *p <= '9') p++;
    if (!*p && p != s) return s;
    if (strncmp(s, "（", 3)) return cat(3, "（", s, "）");
    for (p = s; *p; ) {
        if (!strncmp(p, "（", 3)) { d++; p += 3; }
        else if (!strncmp(p, "）", 3)) { d--; p += 3; if (!d) return *p ? cat(3, "（", s, "）") : s; }
        else p++;
    }
    return s;
}
Item *mkitem(int kind, char *actor, char *h, char *s) {
    Item *it = calloc(1, sizeof *it); it->kind = kind; it->actor = actor; it->h = h; it->s = s; return it;
}
Item *append(Item *a, Item *b) { Item *p = a; if (!a) return b; while (p->next) p = p->next; p->next = b; return a; }

/* 平らな並びを、初期状態と受信節ごとのかたまりに振り分けて字下げ出力する */
char *print_def(char *name, char *decl, Item *items, char *endname) {
    char *init = "", *body = "", *cur = NULL; Item *it;
    if (strcmp(name, endname)) { fprintf(stderr, "意味エラー: 「%s」の定義を「%s」で閉じている\n", name, endname); exit(1); }
    for (it = items; it; it = it->next) {
        if (it->kind == 0) { if (cur || *body) { fprintf(stderr, "意味エラー: %s の初期値の文は受信節より前に書く\n", name); exit(1); } init = cat(2, init, it->s); }
        else if (it->kind == 1) { if (cur) body = cat(4, body, cur, "以上。\n", ""); cur = cat(3, it->h, "\n", ind(it->s)); }
        else { if (!cur) { fprintf(stderr, "意味エラー: %s で受信節の外に文がある\n", name); exit(1); } cur = cat(2, cur, ind(it->s)); }
    }
    if (cur) body = cat(3, body, cur, "以上。\n");
    char *in = *init ? cat(3, "初期状態は\n", ind(init), "以上。\n") : "";
    return cat(7, "「", name, "」というアクターを定義する。\n",
               ind(cat(3, "状態は ", join(decl, "、"), "。\n")), ind(in), ind(body), "定義を終わる。\n");
}

int main(void) {
    if (yyparse()) return 1;
    fputs(output, stdout);
    return 0;
}
