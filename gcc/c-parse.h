/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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
    _RETURN = 280,
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

#line 123 "c-parse.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_C_PARSE_H_INCLUDED  */
