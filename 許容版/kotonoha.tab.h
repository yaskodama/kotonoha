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

#ifndef YY_YY_KOTONOHA_TAB_H_INCLUDED
# define YY_YY_KOTONOHA_TAB_H_INCLUDED
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
    NAME = 258,                    /* NAME  */
    NUMBER = 259,                  /* NUMBER  */
    STRING = 260,                  /* STRING  */
    K_DEFACTOR = 261,              /* K_DEFACTOR  */
    K_HAS = 262,                   /* K_HAS  */
    K_INIT = 263,                  /* K_INIT  */
    K_TOSHI = 264,                 /* K_TOSHI  */
    K_TOSURU = 265,                /* K_TOSURU  */
    T_MSG = 266,                   /* T_MSG  */
    K_RECV = 267,                  /* K_RECV  */
    KORE = 268,                    /* KORE  */
    K_ENDDEF = 269,                /* K_ENDDEF  */
    K_RUN = 270,                   /* K_RUN  */
    K_ENDRUN = 271,                /* K_ENDRUN  */
    MARU = 272,                    /* MARU  */
    TEN = 273,                     /* TEN  */
    SONOATO = 274,                 /* SONOATO  */
    NARABA = 275,                  /* NARABA  */
    DENAKEREBA = 276,              /* DENAKEREBA  */
    YORICHIISA = 277,              /* YORICHIISA  */
    SOUDENAKEREBA = 278,           /* SOUDENAKEREBA  */
    K_BLOCK = 279,                 /* K_BLOCK  */
    IJOU = 280,                    /* IJOU  */
    KARA = 281,                    /* KARA  */
    MADE_NITSUITE = 282,           /* MADE_NITSUITE  */
    WA = 283,                      /* WA  */
    TO = 284,                      /* TO  */
    GA = 285,                      /* GA  */
    NI = 286,                      /* NI  */
    WO = 287,                      /* WO  */
    NO = 288,                      /* NO  */
    NO_MATSUBI = 289,              /* NO_MATSUBI  */
    NO_SENTOU_KARA = 290,          /* NO_SENTOU_KARA  */
    NO_ZENIN = 291,                /* NO_ZENIN  */
    BANME = 292,                   /* BANME  */
    SOREZORE = 293,                /* SOREZORE  */
    T_MOJIRETSU = 294,             /* T_MOJIRETSU  */
    T_ACTOR = 295,                 /* T_ACTOR  */
    ICHITSU = 296,                 /* ICHITSU  */
    HYOUJI_S = 297,                /* HYOUJI_S  */
    HYOUJI_R = 298,                /* HYOUJI_R  */
    OKURU_S = 299,                 /* OKURU_S  */
    OKURU_R = 300,                 /* OKURU_R  */
    HENKOU_S = 301,                /* HENKOU_S  */
    HENKOU_R = 302,                /* HENKOU_R  */
    KUWAE_S = 303,                 /* KUWAE_S  */
    KUWAE_R = 304,                 /* KUWAE_R  */
    KUWAETA = 305,                 /* KUWAETA  */
    TSUIKA_S = 306,                /* TSUIKA_S  */
    TSUIKA_R = 307,                /* TSUIKA_R  */
    TORIDASU_S = 308,              /* TORIDASU_S  */
    TORIDASU_R = 309,              /* TORIDASU_R  */
    NAZUKE_S = 310,                /* NAZUKE_S  */
    NAZUKE_R = 311,                /* NAZUKE_R  */
    SEISEI_R = 312,                /* SEISEI_R  */
    YOUI_R = 313,                  /* YOUI_R  */
    HIITA = 314,                   /* HIITA  */
    WARIAMARI = 315,               /* WARIAMARI  */
    NO_YOUSOSU = 316,              /* NO_YOUSOSU  */
    HAI = 317,                     /* HAI  */
    IIE = 318,                     /* IIE  */
    NASHI = 319,                   /* NASHI  */
    SORA = 320,                    /* SORA  */
    SORA_HAIRETSU = 321,           /* SORA_HAIRETSU  */
    JIBUN = 322,                   /* JIBUN  */
    JIBUN_JISHIN = 323,            /* JIBUN_JISHIN  */
    GENZAI = 324,                  /* GENZAI  */
    SONO = 325,                    /* SONO  */
    LP = 326,                      /* LP  */
    RP = 327                       /* RP  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 33 "kotonoha_nested.y"
 char *s; struct Item *it; 

#line 139 "kotonoha.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_KOTONOHA_TAB_H_INCLUDED  */
