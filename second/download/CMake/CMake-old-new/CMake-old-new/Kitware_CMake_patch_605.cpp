@@ -1,26 +1,97 @@
+/* A Bison parser, made by GNU Bison 1.875a.  */
 
-/*  A Bison parser, made from getdate.y
-    by GNU Bison version 1.28  */
-
-#define YYBISON 1  /* Identify Bison output.  */
-
-#define tAGO    257
-#define tDAY    258
-#define tDAY_UNIT       259
-#define tDAYZONE        260
-#define tDST    261
-#define tHOUR_UNIT      262
-#define tID     263
-#define tMERIDIAN       264
-#define tMINUTE_UNIT    265
-#define tMONTH  266
-#define tMONTH_UNIT     267
-#define tSEC_UNIT       268
-#define tSNUMBER        269
-#define tUNUMBER        270
-#define tYEAR_UNIT      271
-#define tZONE   272
+/* Skeleton parser for Yacc-like parsing with Bison,
+   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.
 
+   This program is free software; you can redistribute it and/or modify
+   it under the terms of the GNU General Public License as published by
+   the Free Software Foundation; either version 2, or (at your option)
+   any later version.
+
+   This program is distributed in the hope that it will be useful,
+   but WITHOUT ANY WARRANTY; without even the implied warranty of
+   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
+   GNU General Public License for more details.
+
+   You should have received a copy of the GNU General Public License
+   along with this program; if not, write to the Free Software
+   Foundation, Inc., 59 Temple Place - Suite 330,
+   Boston, MA 02111-1307, USA.  */
+
+/* As a special exception, when this file is copied by Bison into a
+   Bison output file, you may use that output file without restriction.
+   This special exception was added by the Free Software Foundation
+   in version 1.24 of Bison.  */
+
+/* Written by Richard Stallman by simplifying the original so called
+   ``semantic'' parser.  */
+
+/* All symbols defined below should begin with yy or YY, to avoid
+   infringing on user name space.  This should be done even for local
+   variables, as they might otherwise be expanded by user macros.
+   There are some unavoidable exceptions within include files to
+   define necessary library symbols; they are noted "INFRINGES ON
+   USER NAME SPACE" below.  */
+
+/* Identify Bison output.  */
+#define YYBISON 1
+
+/* Skeleton name.  */
+#define YYSKELETON_NAME "yacc.c"
+
+/* Pure parsers.  */
+#define YYPURE 1
+
+/* Using locations.  */
+#define YYLSP_NEEDED 0
+
+
+
+/* Tokens.  */
+#ifndef YYTOKENTYPE
+# define YYTOKENTYPE
+   /* Put the tokens into the symbol table, so that GDB and other debuggers
+      know about them.  */
+   enum yytokentype {
+     tAGO = 258,
+     tDAY = 259,
+     tDAY_UNIT = 260,
+     tDAYZONE = 261,
+     tDST = 262,
+     tHOUR_UNIT = 263,
+     tID = 264,
+     tMERIDIAN = 265,
+     tMINUTE_UNIT = 266,
+     tMONTH = 267,
+     tMONTH_UNIT = 268,
+     tSEC_UNIT = 269,
+     tSNUMBER = 270,
+     tUNUMBER = 271,
+     tYEAR_UNIT = 272,
+     tZONE = 273
+   };
+#endif
+#define tAGO 258
+#define tDAY 259
+#define tDAY_UNIT 260
+#define tDAYZONE 261
+#define tDST 262
+#define tHOUR_UNIT 263
+#define tID 264
+#define tMERIDIAN 265
+#define tMINUTE_UNIT 266
+#define tMONTH 267
+#define tMONTH_UNIT 268
+#define tSEC_UNIT 269
+#define tSNUMBER 270
+#define tUNUMBER 271
+#define tYEAR_UNIT 272
+#define tZONE 273
+
+
+
+
+/* Copy the first part of user declarations.  */
 #line 1 "getdate.y"
 
 /*
@@ -29,6 +100,9 @@
 **  a couple of people on Usenet.  Completely overhauled by Rich $alz
 **  <rsalz@bbn.com> and Jim Berets <jberets@bbn.com> in August, 1990.
 **
+**  This code has been modified since it was included in curl, to make it
+**  thread-safe and to make compilers complain less about it.
+**
 **  This code is in the public domain and has no copyright.
 */
 
@@ -47,6 +121,11 @@
 #define YYDEBUG 0
 #endif
 
+#ifndef YYSTACK_USE_ALLOCA
+  /* to satisfy gcc -Wundef, we set this to 0 */
+#define YYSTACK_USE_ALLOCA 0
+#endif
+
 /* Since the code of getdate.y is not included in the Emacs executable
    itself, there is no need to #define static in this file.  Even if
    the code were included in the Emacs executable, it probably
@@ -80,13 +159,13 @@
 #if defined (STDC_HEADERS) || (!defined (isascii) && !defined (HAVE_ISASCII))
 # define IN_CTYPE_DOMAIN(c) 1
 #else
-# define IN_CTYPE_DOMAIN(c) isascii((int)(c))
+# define IN_CTYPE_DOMAIN(c) isascii(c)
 #endif
 
-#define ISSPACE(c) (IN_CTYPE_DOMAIN (c) && isspace ((int)(c)))
-#define ISALPHA(c) (IN_CTYPE_DOMAIN (c) && isalpha ((int)(c)))
-#define ISUPPER(c) (IN_CTYPE_DOMAIN (c) && isupper ((int)(c)))
-#define ISDIGIT_LOCALE(c) (IN_CTYPE_DOMAIN (c) && isdigit ((int)(c)))
+#define ISSPACE(c) (IN_CTYPE_DOMAIN (c) && isspace (c))
+#define ISALPHA(c) (IN_CTYPE_DOMAIN (c) && isalpha (c))
+#define ISUPPER(c) (IN_CTYPE_DOMAIN (c) && isupper (c))
+#define ISDIGIT_LOCALE(c) (IN_CTYPE_DOMAIN (c) && isdigit (c))
 
 /* ISDIGIT differs from ISDIGIT_LOCALE, as follows:
    - Its arg may be any int or unsigned int; it need not be an unsigned char.
@@ -102,9 +181,12 @@
 # include <string.h>
 #endif
 
+#include "memory.h"
 /* The last #include file should be: */
-#ifdef MALLOCDEBUG
 #include "memdebug.h"
+
+#ifndef YYMAXDEPTH
+#define YYMAXDEPTH 0
 #endif
 
 #if __GNUC__ < 2 || (__GNUC__ == 2 && __GNUC_MINOR__ < 7)
@@ -169,9 +251,6 @@
 #define yytable  Curl_gd_yytable
 #define yycheck  Curl_gd_yycheck
 
-static int yylex ();
-static int yyerror ();
-
 #define EPOCH           1970
 #define HOUR(x)         ((x) * 60)
 
@@ -195,7 +274,7 @@ typedef enum _MERIDIAN {
 } MERIDIAN;
 
 /* parse results and input string */
-typedef struct _CONTEXT {
+typedef struct _CURL_CONTEXT {
     const char  *yyInput;
     int         yyDayOrdinal;
     int         yyDayNumber;
@@ -218,482 +297,783 @@ typedef struct _CONTEXT {
     int         yyRelMonth;
     int         yyRelSeconds;
     int         yyRelYear;
-} CONTEXT;
+} CURL_CONTEXT;
 
 /* enable use of extra argument to yyparse and yylex which can be used to pass
-**  in a user defined value (CONTEXT struct in our case)
+**  in a user defined value (CURL_CONTEXT struct in our case)
 */
 #define YYPARSE_PARAM cookie
 #define YYLEX_PARAM cookie
-#define context ((CONTEXT *) cookie)
+#define context ((CURL_CONTEXT *) cookie)
 
-#line 215 "getdate.y"
-typedef union {
+
+/* Enabling traces.  */
+#ifndef YYDEBUG
+# define YYDEBUG 0
+#endif
+
+/* Enabling verbose error messages.  */
+#ifdef YYERROR_VERBOSE
+# undef YYERROR_VERBOSE
+# define YYERROR_VERBOSE 1
+#else
+# define YYERROR_VERBOSE 0
+#endif
+
+#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
+#line 223 "getdate.y"
+typedef union YYSTYPE {
     int                 Number;
     enum _MERIDIAN      Meridian;
 } YYSTYPE;
-#include <stdio.h>
-
-#ifndef __cplusplus
-#ifndef __STDC__
-#define const
-#endif
+/* Line 191 of yacc.c.  */
+#line 331 "y.tab.c"
+# define yystype YYSTYPE /* obsolescent; will be withdrawn */
+# define YYSTYPE_IS_DECLARED 1
+# define YYSTYPE_IS_TRIVIAL 1
 #endif
 
 
 
-#define YYFINAL         61
-#define YYFLAG          -32768
-#define YYNTBASE        22
-
-#define YYTRANSLATE(x) ((unsigned)(x) <= 272 ? yytranslate[x] : 32)
-
-static const char yytranslate[] = {     0,
-     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
-     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
-     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
-     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
-     2,     2,     2,    20,     2,     2,    21,     2,     2,     2,
-     2,     2,     2,     2,     2,     2,     2,    19,     2,     2,
-     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
-     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
-     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
-     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
-     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
-     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
-     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
-     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
-     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
-     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
-     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
-     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
-     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
-     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
-     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
-     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
-     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
-     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
-     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
-     2,     2,     2,     2,     2,     1,     3,     4,     5,     6,
-     7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
-    17,    18
-};
+/* Copy the second part of user declarations.  */
+#line 228 "getdate.y"
 
-#if YYDEBUG != 0
-static const short yyprhs[] = {     0,
-     0,     1,     4,     6,     8,    10,    12,    14,    16,    19,
-    24,    29,    36,    43,    45,    47,    50,    52,    55,    58,
-    62,    68,    72,    76,    79,    84,    87,    91,    94,    96,
-    99,   102,   104,   107,   110,   112,   115,   118,   120,   123,
-   126,   128,   131,   134,   136,   139,   142,   144,   146,   147
-};
+static int yylex (YYSTYPE *yylval, void *cookie);
+static int yyerror (const char *s);
 
-static const short yyrhs[] = {    -1,
-    22,    23,     0,    24,     0,    25,     0,    27,     0,    26,
-     0,    28,     0,    30,     0,    16,    10,     0,    16,    19,
-    16,    31,     0,    16,    19,    16,    15,     0,    16,    19,
-    16,    19,    16,    31,     0,    16,    19,    16,    19,    16,
-    15,     0,    18,     0,     6,     0,    18,     7,     0,     4,
-     0,     4,    20,     0,    16,     4,     0,    16,    21,    16,
-     0,    16,    21,    16,    21,    16,     0,    16,    15,    15,
-     0,    16,    12,    15,     0,    12,    16,     0,    12,    16,
-    20,    16,     0,    16,    12,     0,    16,    12,    16,     0,
-    29,     3,     0,    29,     0,    16,    17,     0,    15,    17,
-     0,    17,     0,    16,    13,     0,    15,    13,     0,    13,
-     0,    16,     5,     0,    15,     5,     0,     5,     0,    16,
-     8,     0,    15,     8,     0,     8,     0,    16,    11,     0,
-    15,    11,     0,    11,     0,    16,    14,     0,    15,    14,
-     0,    14,     0,    16,     0,     0,    10,     0
-};
 
-#endif
+/* Line 214 of yacc.c.  */
+#line 347 "y.tab.c"
 
-#if YYDEBUG != 0
-static const short yyrline[] = { 0,
-   231,   232,   235,   238,   241,   244,   247,   250,   253,   259,
-   265,   274,   280,   292,   295,   298,   304,   308,   312,   318,
-   322,   340,   346,   352,   356,   361,   365,   372,   380,   383,
-   386,   389,   392,   395,   398,   401,   404,   407,   410,   413,
-   416,   419,   422,   425,   428,   431,   434,   439,   473,   477
-};
-#endif
+#if ! defined (yyoverflow) || YYERROR_VERBOSE
 
+/* The parser invokes alloca or malloc; define the necessary symbols.  */
 
-#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)
+# if YYSTACK_USE_ALLOCA
+#  define YYSTACK_ALLOC alloca
+# else
+#  ifndef YYSTACK_USE_ALLOCA
+#   if defined (alloca) || defined (_ALLOCA_H)
+#    define YYSTACK_ALLOC alloca
+#   else
+#    ifdef __GNUC__
+#     define YYSTACK_ALLOC __builtin_alloca
+#    endif
+#   endif
+#  endif
+# endif
 
-static const char * const yytname[] = {   "$","error","$undefined.","tAGO","tDAY",
-"tDAY_UNIT","tDAYZONE","tDST","tHOUR_UNIT","tID","tMERIDIAN","tMINUTE_UNIT",
-"tMONTH","tMONTH_UNIT","tSEC_UNIT","tSNUMBER","tUNUMBER","tYEAR_UNIT","tZONE",
-"':'","','","'/'","spec","item","time","zone","day","date","rel","relunit","number",
-"o_merid", NULL
-};
+# ifdef YYSTACK_ALLOC
+   /* Pacify GCC's `empty if-body' warning. */
+#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
+# else
+#  if defined (__STDC__) || defined (__cplusplus)
+#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
+#   define YYSIZE_T size_t
+#  endif
+#  define YYSTACK_ALLOC malloc
+#  define YYSTACK_FREE free
+# endif
+#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */
+
+
+#if (! defined (yyoverflow) \
+     && (! defined (__cplusplus) \
+         || (YYSTYPE_IS_TRIVIAL)))
+
+/* A type that is properly aligned for any stack member.  */
+union yyalloc
+{
+  short yyss;
+  YYSTYPE yyvs;
+  };
+
+/* The size of the maximum gap between one aligned stack and the next.  */
+# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)
+
+/* The size of an array large to enough to hold all stacks, each with
+   N elements.  */
+# define YYSTACK_BYTES(N) \
+     ((N) * (sizeof (short) + sizeof (YYSTYPE))                         \
+      + YYSTACK_GAP_MAXIMUM)
+
+/* Copy COUNT objects from FROM to TO.  The source and destination do
+   not overlap.  */
+# ifndef YYCOPY
+#  if 1 < __GNUC__
+#   define YYCOPY(To, From, Count) \
+      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
+#  else
+#   define YYCOPY(To, From, Count)              \
+      do                                        \
+        {                                       \
+          register YYSIZE_T yyi;                \
+          for (yyi = 0; yyi < (Count); yyi++)   \
+            (To)[yyi] = (From)[yyi];            \
+        }                                       \
+      while (0)
+#  endif
+# endif
+
+/* Relocate STACK from its old location to the new one.  The
+   local variables YYSIZE and YYSTACKSIZE give the old and new number of
+   elements in the stack, and YYPTR gives the new location of the
+   stack.  Advance YYPTR to a properly aligned location for the next
+   stack.  */
+# define YYSTACK_RELOCATE(Stack)                                        \
+    do                                                                  \
+      {                                                                 \
+        YYSIZE_T yynewbytes;                                            \
+        YYCOPY (&yyptr->Stack, Stack, yysize);                          \
+        Stack = &yyptr->Stack;                                          \
+        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
+        yyptr += yynewbytes / sizeof (*yyptr);                          \
+      }                                                                 \
+    while (0)
+
+#endif
+
+#if defined (__STDC__) || defined (__cplusplus)
+   typedef signed char yysigned_char;
+#else
+   typedef short yysigned_char;
 #endif
 
-static const short yyr1[] = {     0,
-    22,    22,    23,    23,    23,    23,    23,    23,    24,    24,
-    24,    24,    24,    25,    25,    25,    26,    26,    26,    27,
-    27,    27,    27,    27,    27,    27,    27,    28,    28,    29,
-    29,    29,    29,    29,    29,    29,    29,    29,    29,    29,
-    29,    29,    29,    29,    29,    29,    29,    30,    31,    31
-};
+/* YYFINAL -- State number of the termination state. */
+#define YYFINAL  2
+/* YYLAST -- Last index in YYTABLE.  */
+#define YYLAST   50
 
-static const short yyr2[] = {     0,
-     0,     2,     1,     1,     1,     1,     1,     1,     2,     4,
-     4,     6,     6,     1,     1,     2,     1,     2,     2,     3,
-     5,     3,     3,     2,     4,     2,     3,     2,     1,     2,
-     2,     1,     2,     2,     1,     2,     2,     1,     2,     2,
-     1,     2,     2,     1,     2,     2,     1,     1,     0,     1
-};
+/* YYNTOKENS -- Number of terminals. */
+#define YYNTOKENS  22
+/* YYNNTS -- Number of nonterminals. */
+#define YYNNTS  11
+/* YYNRULES -- Number of rules. */
+#define YYNRULES  51
+/* YYNRULES -- Number of states. */
+#define YYNSTATES  61
 
-static const short yydefact[] = {     1,
-     0,    17,    38,    15,    41,    44,     0,    35,    47,     0,
-    48,    32,    14,     2,     3,     4,     6,     5,     7,    29,
-     8,    18,    24,    37,    40,    43,    34,    46,    31,    19,
-    36,    39,     9,    42,    26,    33,    45,     0,    30,     0,
-     0,    16,    28,     0,    23,    27,    22,    49,    20,    25,
-    50,    11,     0,    10,     0,    49,    21,    13,    12,     0,
-     0
-};
+/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
+#define YYUNDEFTOK  2
+#define YYMAXUTOK   273
 
-static const short yydefgoto[] = {     1,
-    14,    15,    16,    17,    18,    19,    20,    21,    54
+#define YYTRANSLATE(YYX)                                                \
+  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)
+
+/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
+static const unsigned char yytranslate[] =
+{
+       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
+       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
+       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
+       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
+       2,     2,     2,     2,    20,     2,     2,    21,     2,     2,
+       2,     2,     2,     2,     2,     2,     2,     2,    19,     2,
+       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
+       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
+       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
+       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
+       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
+       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
+       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
+       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
+       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
+       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
+       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
+       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
+       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
+       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
+       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
+       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
+       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
+       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
+       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
+       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
+       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
+      15,    16,    17,    18
 };
 
-static const short yypact[] = {-32768,
-     0,   -19,-32768,-32768,-32768,-32768,   -13,-32768,-32768,    30,
-    15,-32768,    14,-32768,-32768,-32768,-32768,-32768,-32768,    19,
--32768,-32768,     4,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
--32768,-32768,-32768,-32768,    -6,-32768,-32768,    16,-32768,    17,
-    23,-32768,-32768,    24,-32768,-32768,-32768,    27,    28,-32768,
--32768,-32768,    29,-32768,    32,    -8,-32768,-32768,-32768,    50,
--32768
+#if YYDEBUG
+/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
+   YYRHS.  */
+static const unsigned char yyprhs[] =
+{
+       0,     0,     3,     4,     7,     9,    11,    13,    15,    17,
+      19,    22,    27,    32,    39,    46,    48,    50,    53,    55,
+      58,    61,    65,    71,    75,    79,    82,    87,    90,    94,
+      97,    99,   102,   105,   107,   110,   113,   115,   118,   121,
+     123,   126,   129,   131,   134,   137,   139,   142,   145,   147,
+     149,   150
 };
 
-static const short yypgoto[] = {-32768,
--32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    -5
+/* YYRHS -- A `-1'-separated list of the rules' RHS. */
+static const yysigned_char yyrhs[] =
+{
+      23,     0,    -1,    -1,    23,    24,    -1,    25,    -1,    26,
+      -1,    28,    -1,    27,    -1,    29,    -1,    31,    -1,    16,
+      10,    -1,    16,    19,    16,    32,    -1,    16,    19,    16,
+      15,    -1,    16,    19,    16,    19,    16,    32,    -1,    16,
+      19,    16,    19,    16,    15,    -1,    18,    -1,     6,    -1,
+      18,     7,    -1,     4,    -1,     4,    20,    -1,    16,     4,
+      -1,    16,    21,    16,    -1,    16,    21,    16,    21,    16,
+      -1,    16,    15,    15,    -1,    16,    12,    15,    -1,    12,
+      16,    -1,    12,    16,    20,    16,    -1,    16,    12,    -1,
+      16,    12,    16,    -1,    30,     3,    -1,    30,    -1,    16,
+      17,    -1,    15,    17,    -1,    17,    -1,    16,    13,    -1,
+      15,    13,    -1,    13,    -1,    16,     5,    -1,    15,     5,
+      -1,     5,    -1,    16,     8,    -1,    15,     8,    -1,     8,
+      -1,    16,    11,    -1,    15,    11,    -1,    11,    -1,    16,
+      14,    -1,    15,    14,    -1,    14,    -1,    16,    -1,    -1,
+      10,    -1
 };
 
+/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
+static const unsigned short yyrline[] =
+{
+       0,   244,   244,   245,   248,   251,   254,   257,   260,   263,
+     266,   272,   278,   287,   293,   305,   308,   312,   317,   321,
+     325,   331,   335,   353,   359,   365,   369,   374,   378,   385,
+     393,   396,   399,   402,   405,   408,   411,   414,   417,   420,
+     423,   426,   429,   432,   435,   438,   441,   444,   447,   452,
+     487,   490
+};
+#endif
 
-#define YYLAST          51
+#if YYDEBUG || YYERROR_VERBOSE
+/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
+   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
+static const char *const yytname[] =
+{
+  "$end", "error", "$undefined", "tAGO", "tDAY", "tDAY_UNIT", "tDAYZONE", 
+  "tDST", "tHOUR_UNIT", "tID", "tMERIDIAN", "tMINUTE_UNIT", "tMONTH", 
+  "tMONTH_UNIT", "tSEC_UNIT", "tSNUMBER", "tUNUMBER", "tYEAR_UNIT", 
+  "tZONE", "':'", "','", "'/'", "$accept", "spec", "item", "time", "zone", 
+  "day", "date", "rel", "relunit", "number", "o_merid", 0
+};
+#endif
 
+# ifdef YYPRINT
+/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
+   token YYLEX-NUM.  */
+static const unsigned short yytoknum[] =
+{
+       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
+     265,   266,   267,   268,   269,   270,   271,   272,   273,    58,
+      44,    47
+};
+# endif
 
-static const short yytable[] = {    60,
-    22,    51,    23,     2,     3,     4,    58,     5,    45,    46,
-     6,     7,     8,     9,    10,    11,    12,    13,    30,    31,
-    42,    43,    32,    44,    33,    34,    35,    36,    37,    38,
-    47,    39,    48,    40,    24,    41,    51,    25,    49,    50,
-    26,    52,    27,    28,    56,    53,    29,    57,    55,    61,
-    59
+/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
+static const unsigned char yyr1[] =
+{
+       0,    22,    23,    23,    24,    24,    24,    24,    24,    24,
+      25,    25,    25,    25,    25,    26,    26,    26,    27,    27,
+      27,    28,    28,    28,    28,    28,    28,    28,    28,    29,
+      29,    30,    30,    30,    30,    30,    30,    30,    30,    30,
+      30,    30,    30,    30,    30,    30,    30,    30,    30,    31,
+      32,    32
 };
 
-static const short yycheck[] = {     0,
-    20,    10,    16,     4,     5,     6,    15,     8,    15,    16,
-    11,    12,    13,    14,    15,    16,    17,    18,     4,     5,
-     7,     3,     8,    20,    10,    11,    12,    13,    14,    15,
-    15,    17,    16,    19,     5,    21,    10,     8,    16,    16,
-    11,    15,    13,    14,    16,    19,    17,    16,    21,     0,
-    56
+/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
+static const unsigned char yyr2[] =
+{
+       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
+       2,     4,     4,     6,     6,     1,     1,     2,     1,     2,
+       2,     3,     5,     3,     3,     2,     4,     2,     3,     2,
+       1,     2,     2,     1,     2,     2,     1,     2,     2,     1,
+       2,     2,     1,     2,     2,     1,     2,     2,     1,     1,
+       0,     1
 };
-#define YYPURE 1
 
-/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
-#line 3 "/usr/local/share/bison.simple"
-/* This file comes from bison-1.28.  */
+/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
+   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
+   means the default is an error.  */
+static const unsigned char yydefact[] =
+{
+       2,     0,     1,    18,    39,    16,    42,    45,     0,    36,
+      48,     0,    49,    33,    15,     3,     4,     5,     7,     6,
+       8,    30,     9,    19,    25,    38,    41,    44,    35,    47,
+      32,    20,    37,    40,    10,    43,    27,    34,    46,     0,
+      31,     0,     0,    17,    29,     0,    24,    28,    23,    50,
+      21,    26,    51,    12,     0,    11,     0,    50,    22,    14,
+      13
+};
 
-/* Skeleton output parser for bison,
-   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.
+/* YYDEFGOTO[NTERM-NUM]. */
+static const yysigned_char yydefgoto[] =
+{
+      -1,     1,    15,    16,    17,    18,    19,    20,    21,    22,
+      55
+};
 
-   This program is free software; you can redistribute it and/or modify
-   it under the terms of the GNU General Public License as published by
-   the Free Software Foundation; either version 2, or (at your option)
-   any later version.
+/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
+   STATE-NUM.  */
+#define YYPACT_NINF -20
+static const yysigned_char yypact[] =
+{
+     -20,     0,   -20,   -19,   -20,   -20,   -20,   -20,   -13,   -20,
+     -20,    30,    15,   -20,    14,   -20,   -20,   -20,   -20,   -20,
+     -20,    19,   -20,   -20,     4,   -20,   -20,   -20,   -20,   -20,
+     -20,   -20,   -20,   -20,   -20,   -20,    -6,   -20,   -20,    16,
+     -20,    17,    23,   -20,   -20,    24,   -20,   -20,   -20,    27,
+      28,   -20,   -20,   -20,    29,   -20,    32,    -8,   -20,   -20,
+     -20
+};
 
-   This program is distributed in the hope that it will be useful,
-   but WITHOUT ANY WARRANTY; without even the implied warranty of
-   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
-   GNU General Public License for more details.
+/* YYPGOTO[NTERM-NUM].  */
+static const yysigned_char yypgoto[] =
+{
+     -20,   -20,   -20,   -20,   -20,   -20,   -20,   -20,   -20,   -20,
+      -7
+};
 
-   You should have received a copy of the GNU General Public License
-   along with this program; if not, write to the Free Software
-   Foundation, Inc., 59 Temple Place - Suite 330,
-   Boston, MA 02111-1307, USA.  */
+/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
+   positive, shift that token.  If negative, reduce the rule which
+   number is the opposite.  If zero, do what YYDEFACT says.
+   If YYTABLE_NINF, syntax error.  */
+#define YYTABLE_NINF -1
+static const unsigned char yytable[] =
+{
+       2,    23,    52,    24,     3,     4,     5,    59,     6,    46,
+      47,     7,     8,     9,    10,    11,    12,    13,    14,    31,
+      32,    43,    44,    33,    45,    34,    35,    36,    37,    38,
+      39,    48,    40,    49,    41,    25,    42,    52,    26,    50,
+      51,    27,    53,    28,    29,    57,    54,    30,    58,    56,
+      60
+};
 
-/* As a special exception, when this file is copied by Bison into a
-   Bison output file, you may use that output file without restriction.
-   This special exception was added by the Free Software Foundation
-   in version 1.24 of Bison.  */
+static const unsigned char yycheck[] =
+{
+       0,    20,    10,    16,     4,     5,     6,    15,     8,    15,
+      16,    11,    12,    13,    14,    15,    16,    17,    18,     4,
+       5,     7,     3,     8,    20,    10,    11,    12,    13,    14,
+      15,    15,    17,    16,    19,     5,    21,    10,     8,    16,
+      16,    11,    15,    13,    14,    16,    19,    17,    16,    21,
+      57
+};
 
-/* This is the parser code that is written into each bison parser
-  when the %semantic_parser declaration is not specified in the grammar.
-  It was written by Richard Stallman by simplifying the hairy parser
-  used when %semantic_parser is specified.  */
+/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
+   symbol of state STATE-NUM.  */
+static const unsigned char yystos[] =
+{
+       0,    23,     0,     4,     5,     6,     8,    11,    12,    13,
+      14,    15,    16,    17,    18,    24,    25,    26,    27,    28,
+      29,    30,    31,    20,    16,     5,     8,    11,    13,    14,
+      17,     4,     5,     8,    10,    11,    12,    13,    14,    15,
+      17,    19,    21,     7,     3,    20,    15,    16,    15,    16,
+      16,    16,    10,    15,    19,    32,    21,    16,    16,    15,
+      32
+};
 
-#ifndef YYSTACK_USE_ALLOCA
-#ifdef alloca
-#define YYSTACK_USE_ALLOCA
-#else /* alloca not defined */
-#ifdef __GNUC__
-#define YYSTACK_USE_ALLOCA
-#define alloca __builtin_alloca
-#else /* not GNU C.  */
-#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi) || (defined (__sun) && defined (__i386))
-#define YYSTACK_USE_ALLOCA
-#include <alloca.h>
-#else /* not sparc */
-/* We think this test detects Watcom and Microsoft C.  */
-/* This used to test MSDOS, but that is a bad idea
-   since that symbol is in the user namespace.  */
-#if (defined (_MSDOS) || defined (_MSDOS_)) && !defined (__TURBOC__)
-#if 0 /* No need for malloc.h, which pollutes the namespace;
-         instead, just don't use alloca.  */
-#include <malloc.h>
+#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
+# define YYSIZE_T __SIZE_TYPE__
 #endif
-#else /* not MSDOS, or __TURBOC__ */
-#if defined(_AIX)
-/* I don't know what this was needed for, but it pollutes the namespace.
-   So I turned it off.   rms, 2 May 1997.  */
-/* #include <malloc.h>  */
- #pragma alloca
-#define YYSTACK_USE_ALLOCA
-#else /* not MSDOS, or __TURBOC__, or _AIX */
-#if 0
-#ifdef __hpux /* haible@ilog.fr says this works for HPUX 9.05 and up,
-                 and on HPUX 10.  Eventually we can turn this on.  */
-#define YYSTACK_USE_ALLOCA
-#define alloca __builtin_alloca
-#endif /* __hpux */
+#if ! defined (YYSIZE_T) && defined (size_t)
+# define YYSIZE_T size_t
 #endif
-#endif /* not _AIX */
-#endif /* not MSDOS, or __TURBOC__ */
-#endif /* not sparc */
-#endif /* not GNU C */
-#endif /* alloca not defined */
-#endif /* YYSTACK_USE_ALLOCA not defined */
-
-#ifdef YYSTACK_USE_ALLOCA
-#define YYSTACK_ALLOC alloca
-#else
-#define YYSTACK_ALLOC malloc
+#if ! defined (YYSIZE_T)
+# if defined (__STDC__) || defined (__cplusplus)
+#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
+#  define YYSIZE_T size_t
+# endif
+#endif
+#if ! defined (YYSIZE_T)
+# define YYSIZE_T unsigned int
 #endif
-
-/* Note: there must be only one dollar sign in this file.
-   It is replaced by the list of actions, each action
-   as one case of the switch.  */
 
 #define yyerrok         (yyerrstatus = 0)
 #define yyclearin       (yychar = YYEMPTY)
-#define YYEMPTY         -2
+#define YYEMPTY         (-2)
 #define YYEOF           0
+
 #define YYACCEPT        goto yyacceptlab
 #define YYABORT         goto yyabortlab
 #define YYERROR         goto yyerrlab1
-/* Like YYERROR except do call yyerror.
-   This remains here temporarily to ease the
-   transition to the new meaning of YYERROR, for GCC.
+
+
+/* Like YYERROR except do call yyerror.  This remains here temporarily
+   to ease the transition to the new meaning of YYERROR, for GCC.
    Once GCC version 2 has supplanted version 1, this can go.  */
+
 #define YYFAIL          goto yyerrlab
+
 #define YYRECOVERING()  (!!yyerrstatus)
-#define YYBACKUP(token, value) \
+
+#define YYBACKUP(Token, Value)                                  \
 do                                                              \
   if (yychar == YYEMPTY && yylen == 1)                          \
-    { yychar = (token), yylval = (value);                       \
-      yychar1 = YYTRANSLATE (yychar);                           \
+    {                                                           \
+      yychar = (Token);                                         \
+      yylval = (Value);                                         \
+      yytoken = YYTRANSLATE (yychar);                           \
       YYPOPSTACK;                                               \
       goto yybackup;                                            \
     }                                                           \
   else                                                          \
-    { yyerror ("syntax error: cannot back up"); YYERROR; }      \
+    {                                                           \
+      yyerror ("syntax error: cannot back up");\
+      YYERROR;                                                  \
+    }                                                           \
 while (0)
 
 #define YYTERROR        1
 #define YYERRCODE       256
 
-#ifndef YYPURE
-#define YYLEX           yylex()
-#endif
+/* YYLLOC_DEFAULT -- Compute the default location (before the actions
+   are run).  */
 
-#ifdef YYPURE
-#ifdef YYLSP_NEEDED
-#ifdef YYLEX_PARAM
-#define YYLEX           yylex(&yylval, &yylloc, YYLEX_PARAM)
-#else
-#define YYLEX           yylex(&yylval, &yylloc)
+#ifndef YYLLOC_DEFAULT
+# define YYLLOC_DEFAULT(Current, Rhs, N)         \
+  Current.first_line   = Rhs[1].first_line;      \
+  Current.first_column = Rhs[1].first_column;    \
+  Current.last_line    = Rhs[N].last_line;       \
+  Current.last_column  = Rhs[N].last_column;
 #endif
-#else /* not YYLSP_NEEDED */
+
+/* YYLEX -- calling `yylex' with the right arguments.  */
+
 #ifdef YYLEX_PARAM
-#define YYLEX           yylex(&yylval, YYLEX_PARAM)
+# define YYLEX yylex (&yylval, YYLEX_PARAM)
 #else
-#define YYLEX           yylex(&yylval)
-#endif
-#endif /* not YYLSP_NEEDED */
+# define YYLEX yylex (&yylval)
 #endif
 
-/* If nonreentrant, generate the variables here */
+/* Enable debugging if requested.  */
+#if YYDEBUG
+
+# ifndef YYFPRINTF
+#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
+#  define YYFPRINTF fprintf
+# endif
 
-#ifndef YYPURE
+# define YYDPRINTF(Args)                        \
+do {                                            \
+  if (yydebug)                                  \
+    YYFPRINTF Args;                             \
+} while (0)
+
+# define YYDSYMPRINT(Args)                      \
+do {                                            \
+  if (yydebug)                                  \
+    yysymprint Args;                            \
+} while (0)
+
+# define YYDSYMPRINTF(Title, Token, Value, Location)            \
+do {                                                            \
+  if (yydebug)                                                  \
+    {                                                           \
+      YYFPRINTF (stderr, "%s ", Title);                         \
+      yysymprint (stderr,                                       \
+                  Token, Value);        \
+      YYFPRINTF (stderr, "\n");                                 \
+    }                                                           \
+} while (0)
 
-int     yychar;                 /*  the lookahead symbol                */
-YYSTYPE yylval;                 /*  the semantic value of the           */
-                                /*  lookahead symbol                    */
+/*------------------------------------------------------------------.
+| yy_stack_print -- Print the state stack from its BOTTOM up to its |
+| TOP (cinluded).                                                   |
+`------------------------------------------------------------------*/
 
-#ifdef YYLSP_NEEDED
-YYLTYPE yylloc;                 /*  location data for the lookahead     */
-                                /*  symbol                              */
+#if defined (__STDC__) || defined (__cplusplus)
+static void
+yy_stack_print (short *bottom, short *top)
+#else
+static void
+yy_stack_print (bottom, top)
+    short *bottom;
+    short *top;
 #endif
+{
+  YYFPRINTF (stderr, "Stack now");
+  for (/* Nothing. */; bottom <= top; ++bottom)
+    YYFPRINTF (stderr, " %d", *bottom);
+  YYFPRINTF (stderr, "\n");
+}
 
-int yynerrs;                    /*  number of parse errors so far       */
-#endif  /* not YYPURE */
+# define YY_STACK_PRINT(Bottom, Top)                            \
+do {                                                            \
+  if (yydebug)                                                  \
+    yy_stack_print ((Bottom), (Top));                           \
+} while (0)
 
-#if YYDEBUG != 0
-int yydebug;                    /*  nonzero means print parse trace     */
-/* Since this is uninitialized, it does not stop multiple parsers
-   from coexisting.  */
-#endif
 
-/*  YYINITDEPTH indicates the initial size of the parser's stacks       */
+/*------------------------------------------------.
+| Report that the YYRULE is going to be reduced.  |
+`------------------------------------------------*/
 
+#if defined (__STDC__) || defined (__cplusplus)
+static void
+yy_reduce_print (int yyrule)
+#else
+static void
+yy_reduce_print (yyrule)
+    int yyrule;
+#endif
+{
+  int yyi;
+  unsigned int yylineno = yyrline[yyrule];
+  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
+             yyrule - 1, yylineno);
+  /* Print the symbols being reduced, and their result.  */
+  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
+    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
+  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
+}
+
+# define YY_REDUCE_PRINT(Rule)          \
+do {                                    \
+  if (yydebug)                          \
+    yy_reduce_print (Rule);             \
+} while (0)
+
+/* Nonzero means print parse trace.  It is left uninitialized so that
+   multiple parsers can coexist.  */
+int yydebug;
+#else /* !YYDEBUG */
+# define YYDPRINTF(Args)
+# define YYDSYMPRINT(Args)
+# define YYDSYMPRINTF(Title, Token, Value, Location)
+# define YY_STACK_PRINT(Bottom, Top)
+# define YY_REDUCE_PRINT(Rule)
+#endif /* !YYDEBUG */
+
+
+/* YYINITDEPTH -- initial size of the parser's stacks.  */
 #ifndef YYINITDEPTH
-#define YYINITDEPTH 200
+# define YYINITDEPTH 200
 #endif
 
-/*  YYMAXDEPTH is the maximum size the stacks can grow to
-    (effective only if the built-in stack extension method is used).  */
+/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
+   if the built-in stack extension method is used).
+
+   Do not make this value too large; the results are undefined if
+   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
+   evaluated with infinite-precision integer arithmetic.  */
 
 #if YYMAXDEPTH == 0
-#undef YYMAXDEPTH
+# undef YYMAXDEPTH
 #endif
 
 #ifndef YYMAXDEPTH
-#define YYMAXDEPTH 10000
+# define YYMAXDEPTH 10000
 #endif
+
 
-/* Define __yy_memcpy.  Note that the size argument
-   should be passed with type unsigned int, because that is what the non-GCC
-   definitions require.  With GCC, __builtin_memcpy takes an arg
-   of type size_t, but it can handle unsigned int.  */
-
-#if __GNUC__ > 1                /* GNU C and GNU C++ define this.  */
-#define __yy_memcpy(TO,FROM,COUNT)      __builtin_memcpy(TO,FROM,COUNT)
-#else                           /* not GNU C or C++ */
-#ifndef __cplusplus
-
-/* This is the most reliable way to avoid incompatibilities
-   in available built-in functions on various systems.  */
-static void
-__yy_memcpy (to, from, count)
-     char *to;
-     char *from;
-     unsigned int count;
+
+#if YYERROR_VERBOSE
+
+# ifndef yystrlen
+#  if defined (__GLIBC__) && defined (_STRING_H)
+#   define yystrlen strlen
+#  else
+/* Return the length of YYSTR.  */
+static YYSIZE_T
+#   if defined (__STDC__) || defined (__cplusplus)
+yystrlen (const char *yystr)
+#   else
+yystrlen (yystr)
+     const char *yystr;
+#   endif
+{
+  register const char *yys = yystr;
+
+  while (*yys++ != '\0')
+    continue;
+
+  return yys - yystr - 1;
+}
+#  endif
+# endif
+
+# ifndef yystpcpy
+#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
+#   define yystpcpy stpcpy
+#  else
+/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
+   YYDEST.  */
+static char *
+#   if defined (__STDC__) || defined (__cplusplus)
+yystpcpy (char *yydest, const char *yysrc)
+#   else
+yystpcpy (yydest, yysrc)
+     char *yydest;
+     const char *yysrc;
+#   endif
 {
-  register char *f = from;
-  register char *t = to;
-  register int i = count;
+  register char *yyd = yydest;
+  register const char *yys = yysrc;
 
-  while (i-- > 0)
-    *t++ = *f++;
+  while ((*yyd++ = *yys++) != '\0')
+    continue;
+
+  return yyd - 1;
 }
+#  endif
+# endif
 
-#else /* __cplusplus */
+#endif /* !YYERROR_VERBOSE */
 
-/* This is the most reliable way to avoid incompatibilities
-   in available built-in functions on various systems.  */
+
+
+#if YYDEBUG
+/*--------------------------------.
+| Print this symbol on YYOUTPUT.  |
+`--------------------------------*/
+
+#if defined (__STDC__) || defined (__cplusplus)
 static void
-__yy_memcpy (char *to, char *from, unsigned int count)
+yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
+#else
+static void
+yysymprint (yyoutput, yytype, yyvaluep)
+    FILE *yyoutput;
+    int yytype;
+    YYSTYPE *yyvaluep;
+#endif
 {
-  register char *t = to;
-  register char *f = from;
-  register int i = count;
+  /* Pacify ``unused variable'' warnings.  */
+  (void) yyvaluep;
+
+  if (yytype < YYNTOKENS)
+    {
+      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
+# ifdef YYPRINT
+      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
+# endif
+    }
+  else
+    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);
 
-  while (i-- > 0)
-    *t++ = *f++;
+  switch (yytype)
+    {
+      default:
+        break;
+    }
+  YYFPRINTF (yyoutput, ")");
 }
 
+#endif /* ! YYDEBUG */
+/*-----------------------------------------------.
+| Release the memory associated to this symbol.  |
+`-----------------------------------------------*/
+
+#if defined (__STDC__) || defined (__cplusplus)
+static void
+yydestruct (int yytype, YYSTYPE *yyvaluep)
+#else
+static void
+yydestruct (yytype, yyvaluep)
+    int yytype;
+    YYSTYPE *yyvaluep;
 #endif
-#endif
+{
+  /* Pacify ``unused variable'' warnings.  */
+  (void) yyvaluep;
+
+  switch (yytype)
+    {
+
+      default:
+        break;
+    }
+}
 
-#line 217 "/usr/local/share/bison.simple"
 
-/* The user can define YYPARSE_PARAM as the name of an argument to be passed
-   into yyparse.  The argument should have type void *.
-   It should actually point to an object.
-   Grammar actions can access the variable by casting it
-   to the proper pointer type.  */
+/* Prevent warnings from -Wmissing-prototypes.  */
 
 #ifdef YYPARSE_PARAM
-#ifdef __cplusplus
-#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
-#define YYPARSE_PARAM_DECL
-#else /* not __cplusplus */
-#define YYPARSE_PARAM_ARG YYPARSE_PARAM
-#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
-#endif /* not __cplusplus */
-#else /* not YYPARSE_PARAM */
-#define YYPARSE_PARAM_ARG
-#define YYPARSE_PARAM_DECL
-#endif /* not YYPARSE_PARAM */
-
-/* Prevent warning if -Wstrict-prototypes.  */
-#ifdef __GNUC__
-#ifdef YYPARSE_PARAM
-int yyparse (void *);
-#else
+# if defined (__STDC__) || defined (__cplusplus)
+int yyparse (void *YYPARSE_PARAM);
+# else
+int yyparse ();
+# endif
+#else /* ! YYPARSE_PARAM */
+#if defined (__STDC__) || defined (__cplusplus)
 int yyparse (void);
+#else
+int yyparse ();
 #endif
-#endif
+#endif /* ! YYPARSE_PARAM */
 
+
+
+
+
+
+/*----------.
+| yyparse.  |
+`----------*/
+
+#ifdef YYPARSE_PARAM
+# if defined (__STDC__) || defined (__cplusplus)
+int yyparse (void *YYPARSE_PARAM)
+# else
+int yyparse (YYPARSE_PARAM)
+  void *YYPARSE_PARAM;
+# endif
+#else /* ! YYPARSE_PARAM */
+#if defined (__STDC__) || defined (__cplusplus)
 int
-yyparse(YYPARSE_PARAM_ARG)
-     YYPARSE_PARAM_DECL
+yyparse (void)
+#else
+int
+yyparse ()
+
+#endif
+#endif
 {
+  /* The lookahead symbol.  */
+int yychar;
+
+/* The semantic value of the lookahead symbol.  */
+YYSTYPE yylval;
+
+/* Number of syntax errors so far.  */
+int yynerrs;
+
   register int yystate;
   register int yyn;
+  int yyresult;
+  /* Number of tokens to shift before error messages enabled.  */
+  int yyerrstatus;
+  /* Lookahead token as an internal (translated) token number.  */
+  int yytoken = 0;
+
+  /* Three stacks and their tools:
+     `yyss': related to states,
+     `yyvs': related to semantic values,
+     `yyls': related to locations.
+
+     Refer to the stacks thru separate pointers, to allow yyoverflow
+     to reallocate them elsewhere.  */
+
+  /* The state stack.  */
+  short yyssa[YYINITDEPTH];
+  short *yyss = yyssa;
   register short *yyssp;
-  register YYSTYPE *yyvsp;
-  int yyerrstatus;      /*  number of tokens to shift before error messages enabled */
-  int yychar1 = 0;              /*  lookahead token as an internal (translated) token number */
 
-  short yyssa[YYINITDEPTH];     /*  the state stack                     */
-  YYSTYPE yyvsa[YYINITDEPTH];   /*  the semantic value stack            */
+  /* The semantic value stack.  */
+  YYSTYPE yyvsa[YYINITDEPTH];
+  YYSTYPE *yyvs = yyvsa;
+  register YYSTYPE *yyvsp;
 
-  short *yyss = yyssa;          /*  refer to the stacks thru separate pointers */
-  YYSTYPE *yyvs = yyvsa;        /*  to allow yyoverflow to reallocate them elsewhere */
 
-#ifdef YYLSP_NEEDED
-  YYLTYPE yylsa[YYINITDEPTH];   /*  the location stack                  */
-  YYLTYPE *yyls = yylsa;
-  YYLTYPE *yylsp;
 
-#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
-#else
 #define YYPOPSTACK   (yyvsp--, yyssp--)
-#endif
 
-  int yystacksize = YYINITDEPTH;
-  int yyfree_stacks = 0;
+  YYSIZE_T yystacksize = YYINITDEPTH;
 
-#ifdef YYPURE
-  int yychar;
-  YYSTYPE yylval;
-  int yynerrs;
-#ifdef YYLSP_NEEDED
-  YYLTYPE yylloc;
-#endif
-#endif
+  /* The variables used to return semantic value and location from the
+     action routines.  */
+  YYSTYPE yyval;
 
-  YYSTYPE yyval;                /*  the variable used to return         */
-                                /*  semantic values from the action     */
-                                /*  routines                            */
 
+  /* When reducing, the number of symbols on the RHS of the reduced
+     rule.  */
   int yylen;
 
-#if YYDEBUG != 0
-  if (yydebug)
-    fprintf(stderr, "Starting parse\n");
-#endif
+  YYDPRINTF ((stderr, "Starting parse\n"));
 
-  yylval.Number = 0;
-  yyval.Number = 0;
-   
   yystate = 0;
   yyerrstatus = 0;
   yynerrs = 0;
@@ -704,110 +1084,96 @@ yyparse(YYPARSE_PARAM_ARG)
      so that they stay on the same level as the state stack.
      The wasted elements are never initialized.  */
 
-  yyssp = yyss - 1;
+  yyssp = yyss;
   yyvsp = yyvs;
-#ifdef YYLSP_NEEDED
-  yylsp = yyls;
-#endif
 
-/* Push a new state, which is found in  yystate  .  */
-/* In all cases, when you get here, the value and location stacks
-   have just been pushed. so pushing a state here evens the stacks.  */
-yynewstate:
+  goto yysetstate;
 
-  *++yyssp = (short)yystate;
+/*------------------------------------------------------------.
+| yynewstate -- Push a new state, which is found in yystate.  |
+`------------------------------------------------------------*/
+ yynewstate:
+  /* In all cases, when you get here, the value and location stacks
+     have just been pushed. so pushing a state here evens the stacks.
+     */
+  yyssp++;
 
-  if (yyssp >= yyss + yystacksize - 1)
-    {
-      /* Give user a chance to reallocate the stack */
-      /* Use copies of these so that the &'s don't force the real ones into memory. */
-      YYSTYPE *yyvs1 = yyvs;
-      short *yyss1 = yyss;
-#ifdef YYLSP_NEEDED
-      YYLTYPE *yyls1 = yyls;
-#endif
+ yysetstate:
+  *yyssp = yystate;
 
+  if (yyss + yystacksize - 1 <= yyssp)
+    {
       /* Get the current used size of the three stacks, in elements.  */
-      int size = (int)(yyssp - yyss + 1);
+      YYSIZE_T yysize = yyssp - yyss + 1;
 
 #ifdef yyoverflow
-      /* Each stack pointer address is followed by the size of
-         the data in use in that stack, in bytes.  */
-#ifdef YYLSP_NEEDED
-      /* This used to be a conditional around just the two extra args,
-         but that might be undefined if yyoverflow is a macro.  */
-      yyoverflow("parser stack overflow",
-                 &yyss1, size * sizeof (*yyssp),
-                 &yyvs1, size * sizeof (*yyvsp),
-                 &yyls1, size * sizeof (*yylsp),
-                 &yystacksize);
-#else
-      yyoverflow("parser stack overflow",
-                 &yyss1, size * sizeof (*yyssp),
-                 &yyvs1, size * sizeof (*yyvsp),
-                 &yystacksize);
-#endif
+      {
+        /* Give user a chance to reallocate the stack. Use copies of
+           these so that the &'s don't force the real ones into
+           memory.  */
+        YYSTYPE *yyvs1 = yyvs;
+        short *yyss1 = yyss;
 
-      yyss = yyss1; yyvs = yyvs1;
-#ifdef YYLSP_NEEDED
-      yyls = yyls1;
-#endif
+
+        /* Each stack pointer address is followed by the size of the
+           data in use in that stack, in bytes.  This used to be a
+           conditional around just the two extra args, but that might
+           be undefined if yyoverflow is a macro.  */
+        yyoverflow ("parser stack overflow",
+                    &yyss1, yysize * sizeof (*yyssp),
+                    &yyvs1, yysize * sizeof (*yyvsp),
+
+                    &yystacksize);
+
+        yyss = yyss1;
+        yyvs = yyvs1;
+      }
 #else /* no yyoverflow */
+# ifndef YYSTACK_RELOCATE
+      goto yyoverflowlab;
+# else
       /* Extend the stack our own way.  */
-      if (yystacksize >= YYMAXDEPTH)
-        {
-          yyerror("parser stack overflow");
-          if (yyfree_stacks)
-            {
-              free (yyss);
-              free (yyvs);
-#ifdef YYLSP_NEEDED
-              free (yyls);
-#endif
-            }
-          return 2;
-        }
+      if (YYMAXDEPTH <= yystacksize)
+        goto yyoverflowlab;
       yystacksize *= 2;
-      if (yystacksize > YYMAXDEPTH)
+      if (YYMAXDEPTH < yystacksize)
         yystacksize = YYMAXDEPTH;
-#ifndef YYSTACK_USE_ALLOCA
-      yyfree_stacks = 1;
-#endif
-      yyss = (short *) YYSTACK_ALLOC (yystacksize * sizeof (*yyssp));
-      __yy_memcpy ((char *)yyss, (char *)yyss1,
-                   size * (unsigned int) sizeof (*yyssp));
-      yyvs = (YYSTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yyvsp));
-      __yy_memcpy ((char *)yyvs, (char *)yyvs1,
-                   size * (unsigned int) sizeof (*yyvsp));
-#ifdef YYLSP_NEEDED
-      yyls = (YYLTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yylsp));
-      __yy_memcpy ((char *)yyls, (char *)yyls1,
-                   size * (unsigned int) sizeof (*yylsp));
-#endif
+
+      {
+        short *yyss1 = yyss;
+        union yyalloc *yyptr =
+          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
+        if (! yyptr)
+          goto yyoverflowlab;
+        YYSTACK_RELOCATE (yyss);
+        YYSTACK_RELOCATE (yyvs);
+
+#  undef YYSTACK_RELOCATE
+        if (yyss1 != yyssa)
+          YYSTACK_FREE (yyss1);
+      }
+# endif
 #endif /* no yyoverflow */
 
-      yyssp = yyss + size - 1;
-      yyvsp = yyvs + size - 1;
-#ifdef YYLSP_NEEDED
-      yylsp = yyls + size - 1;
-#endif
+      yyssp = yyss + yysize - 1;
+      yyvsp = yyvs + yysize - 1;
 
-#if YYDEBUG != 0
-      if (yydebug)
-        fprintf(stderr, "Stack size increased to %d\n", yystacksize);
-#endif
 
-      if (yyssp >= yyss + yystacksize - 1)
+      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
+                  (unsigned long int) yystacksize));
+
+      if (yyss + yystacksize - 1 <= yyssp)
         YYABORT;
     }
 
-#if YYDEBUG != 0
-  if (yydebug)
-    fprintf(stderr, "Entering state %d\n", yystate);
-#endif
+  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
 
   goto yybackup;
- yybackup:
+
+/*-----------.
+| yybackup.  |
+`-----------*/
+yybackup:
 
 /* Do appropriate processing given the current state.  */
 /* Read a lookahead token if we need one and don't already have one.  */
@@ -816,204 +1182,177 @@ yyparse(YYPARSE_PARAM_ARG)
   /* First try to decide what to do without reference to lookahead token.  */
 
   yyn = yypact[yystate];
-  if (yyn == YYFLAG)
+  if (yyn == YYPACT_NINF)
     goto yydefault;
 
   /* Not known => get a lookahead token if don't already have one.  */
 
-  /* yychar is either YYEMPTY or YYEOF
-     or a valid token in external form.  */
-
+  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
   if (yychar == YYEMPTY)
     {
-#if YYDEBUG != 0
-      if (yydebug)
-        fprintf(stderr, "Reading a token: ");
-#endif
+      YYDPRINTF ((stderr, "Reading a token: "));
       yychar = YYLEX;
     }
 
-  /* Convert token to internal form (in yychar1) for indexing tables with */
-
-  if (yychar <= 0)              /* This means end of input. */
+  if (yychar <= YYEOF)
     {
-      yychar1 = 0;
-      yychar = YYEOF;           /* Don't call YYLEX any more */
-
-#if YYDEBUG != 0
-      if (yydebug)
-        fprintf(stderr, "Now at end of input.\n");
-#endif
+      yychar = yytoken = YYEOF;
+      YYDPRINTF ((stderr, "Now at end of input.\n"));
     }
   else
     {
-      yychar1 = YYTRANSLATE(yychar);
-
-#if YYDEBUG != 0
-      if (yydebug)
-        {
-          fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
-          /* Give the individual parser a way to print the precise meaning
-             of a token, for further debugging info.  */
-#ifdef YYPRINT
-          YYPRINT (stderr, yychar, yylval);
-#endif
-          fprintf (stderr, ")\n");
-        }
-#endif
+      yytoken = YYTRANSLATE (yychar);
+      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
     }
 
-  yyn += yychar1;
-  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
+  /* If the proper action on seeing token YYTOKEN is to reduce or to
+     detect an error, take that action.  */
+  yyn += yytoken;
+  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
     goto yydefault;
-
   yyn = yytable[yyn];
-
-  /* yyn is what to do for this token type in this state.
-     Negative => reduce, -yyn is rule number.
-     Positive => shift, yyn is new state.
-       New state is final state => don't bother to shift,
-       just return success.
-     0, or most negative number => error.  */
-
-  if (yyn < 0)
+  if (yyn <= 0)
     {
-      if (yyn == YYFLAG)
+      if (yyn == 0 || yyn == YYTABLE_NINF)
         goto yyerrlab;
       yyn = -yyn;
       goto yyreduce;
     }
-  else if (yyn == 0)
-    goto yyerrlab;
 
   if (yyn == YYFINAL)
     YYACCEPT;
 
   /* Shift the lookahead token.  */
-
-#if YYDEBUG != 0
-  if (yydebug)
-    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
-#endif
+  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));
 
   /* Discard the token being shifted unless it is eof.  */
   if (yychar != YYEOF)
     yychar = YYEMPTY;
 
   *++yyvsp = yylval;
-#ifdef YYLSP_NEEDED
-  *++yylsp = yylloc;
-#endif
 
-  /* count tokens shifted since error; after three, turn off error status.  */
-  if (yyerrstatus) yyerrstatus--;
+
+  /* Count tokens shifted since error; after three, turn off error
+     status.  */
+  if (yyerrstatus)
+    yyerrstatus--;
 
   yystate = yyn;
   goto yynewstate;
 
-/* Do the default action for the current state.  */
-yydefault:
 
+/*-----------------------------------------------------------.
+| yydefault -- do the default action for the current state.  |
+`-----------------------------------------------------------*/
+yydefault:
   yyn = yydefact[yystate];
   if (yyn == 0)
     goto yyerrlab;
+  goto yyreduce;
+
 
-/* Do a reduction.  yyn is the number of a rule to reduce with.  */
+/*-----------------------------.
+| yyreduce -- Do a reduction.  |
+`-----------------------------*/
 yyreduce:
+  /* yyn is the number of a rule to reduce with.  */
   yylen = yyr2[yyn];
-  if (yylen > 0)
-    yyval = yyvsp[1-yylen]; /* implement default value of the action */
 
-#if YYDEBUG != 0
-  if (yydebug)
-    {
-      int i;
-
-      fprintf (stderr, "Reducing via rule %d (line %d), ",
-               yyn, yyrline[yyn]);
+  /* If YYLEN is nonzero, implement the default value of the action:
+     `$$ = $1'.
 
-      /* Print the symbols being reduced, and their result.  */
-      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
-        fprintf (stderr, "%s ", yytname[yyrhs[i]]);
-      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
-    }
-#endif
+     Otherwise, the following line sets YYVAL to garbage.
+     This behavior is undocumented and Bison
+     users should not rely upon it.  Assigning to YYVAL
+     unconditionally makes the parser a bit smaller, and it avoids a
+     GCC warning that YYVAL may be used uninitialized.  */
+  yyval = yyvsp[1-yylen];
 
 
-  switch (yyn) {
-
-case 3:
-#line 235 "getdate.y"
-{
+  YY_REDUCE_PRINT (yyn);
+  switch (yyn)
+    {
+        case 4:
+#line 248 "getdate.y"
+    {
             context->yyHaveTime++;
-        ;
-    break;}
-case 4:
-#line 238 "getdate.y"
-{
+        }
+    break;
+
+  case 5:
+#line 251 "getdate.y"
+    {
             context->yyHaveZone++;
-        ;
-    break;}
-case 5:
-#line 241 "getdate.y"
-{
+        }
+    break;
+
+  case 6:
+#line 254 "getdate.y"
+    {
             context->yyHaveDate++;
-        ;
-    break;}
-case 6:
-#line 244 "getdate.y"
-{
+        }
+    break;
+
+  case 7:
+#line 257 "getdate.y"
+    {
             context->yyHaveDay++;
-        ;
-    break;}
-case 7:
-#line 247 "getdate.y"
-{
+        }
+    break;
+
+  case 8:
+#line 260 "getdate.y"
+    {
             context->yyHaveRel++;
-        ;
-    break;}
-case 9:
-#line 253 "getdate.y"
-{
+        }
+    break;
+
+  case 10:
+#line 266 "getdate.y"
+    {
             context->yyHour = yyvsp[-1].Number;
             context->yyMinutes = 0;
             context->yySeconds = 0;
             context->yyMeridian = yyvsp[0].Meridian;
-        ;
-    break;}
-case 10:
-#line 259 "getdate.y"
-{
+        }
+    break;
+
+  case 11:
+#line 272 "getdate.y"
+    {
             context->yyHour = yyvsp[-3].Number;
             context->yyMinutes = yyvsp[-1].Number;
             context->yySeconds = 0;
             context->yyMeridian = yyvsp[0].Meridian;
-        ;
-    break;}
-case 11:
-#line 265 "getdate.y"
-{
+        }
+    break;
+
+  case 12:
+#line 278 "getdate.y"
+    {
             context->yyHour = yyvsp[-3].Number;
             context->yyMinutes = yyvsp[-1].Number;
             context->yyMeridian = MER24;
             context->yyHaveZone++;
             context->yyTimezone = (yyvsp[0].Number < 0
                                    ? -yyvsp[0].Number % 100 + (-yyvsp[0].Number / 100) * 60
                                    : - (yyvsp[0].Number % 100 + (yyvsp[0].Number / 100) * 60));
-        ;
-    break;}
-case 12:
-#line 274 "getdate.y"
-{
+        }
+    break;
+
+  case 13:
+#line 287 "getdate.y"
+    {
             context->yyHour = yyvsp[-5].Number;
             context->yyMinutes = yyvsp[-3].Number;
             context->yySeconds = yyvsp[-1].Number;
             context->yyMeridian = yyvsp[0].Meridian;
-        ;
-    break;}
-case 13:
-#line 280 "getdate.y"
-{
+        }
+    break;
+
+  case 14:
+#line 293 "getdate.y"
+    {
             context->yyHour = yyvsp[-5].Number;
             context->yyMinutes = yyvsp[-3].Number;
             context->yySeconds = yyvsp[-1].Number;
@@ -1022,57 +1361,65 @@ case 13:
             context->yyTimezone = (yyvsp[0].Number < 0
                                    ? -yyvsp[0].Number % 100 + (-yyvsp[0].Number / 100) * 60
                                    : - (yyvsp[0].Number % 100 + (yyvsp[0].Number / 100) * 60));
-        ;
-    break;}
-case 14:
-#line 292 "getdate.y"
-{
+        }
+    break;
+
+  case 15:
+#line 305 "getdate.y"
+    {
             context->yyTimezone = yyvsp[0].Number;
-        ;
-    break;}
-case 15:
-#line 295 "getdate.y"
-{
+        }
+    break;
+
+  case 16:
+#line 308 "getdate.y"
+    {
             context->yyTimezone = yyvsp[0].Number - 60;
-        ;
-    break;}
-case 16:
-#line 299 "getdate.y"
-{
+        }
+    break;
+
+  case 17:
+#line 312 "getdate.y"
+    {
             context->yyTimezone = yyvsp[-1].Number - 60;
-        ;
-    break;}
-case 17:
-#line 304 "getdate.y"
-{
+        }
+    break;
+
+  case 18:
+#line 317 "getdate.y"
+    {
             context->yyDayOrdinal = 1;
             context->yyDayNumber = yyvsp[0].Number;
-        ;
-    break;}
-case 18:
-#line 308 "getdate.y"
-{
+        }
+    break;
+
+  case 19:
+#line 321 "getdate.y"
+    {
             context->yyDayOrdinal = 1;
             context->yyDayNumber = yyvsp[-1].Number;
-        ;
-    break;}
-case 19:
-#line 312 "getdate.y"
-{
+        }
+    break;
+
+  case 20:
+#line 325 "getdate.y"
+    {
             context->yyDayOrdinal = yyvsp[-1].Number;
             context->yyDayNumber = yyvsp[0].Number;
-        ;
-    break;}
-case 20:
-#line 318 "getdate.y"
-{
+        }
+    break;
+
+  case 21:
+#line 331 "getdate.y"
+    {
             context->yyMonth = yyvsp[-2].Number;
             context->yyDay = yyvsp[0].Number;
-        ;
-    break;}
-case 21:
-#line 322 "getdate.y"
-{
+        }
+    break;
+
+  case 22:
+#line 335 "getdate.y"
+    {
           /* Interpret as YYYY/MM/DD if $1 >= 1000, otherwise as MM/DD/YY.
              The goal in recognizing YYYY/MM/DD is solely to support legacy
              machine-generated dates like those in an RCS log listing.  If
@@ -1089,178 +1436,204 @@ case 21:
               context->yyDay = yyvsp[-2].Number;
               context->yyYear = yyvsp[0].Number;
             }
-        ;
-    break;}
-case 22:
-#line 340 "getdate.y"
-{
+        }
+    break;
+
+  case 23:
+#line 353 "getdate.y"
+    {
             /* ISO 8601 format.  yyyy-mm-dd.  */
             context->yyYear = yyvsp[-2].Number;
             context->yyMonth = -yyvsp[-1].Number;
             context->yyDay = -yyvsp[0].Number;
-        ;
-    break;}
-case 23:
-#line 346 "getdate.y"
-{
+        }
+    break;
+
+  case 24:
+#line 359 "getdate.y"
+    {
             /* e.g. 17-JUN-1992.  */
             context->yyDay = yyvsp[-2].Number;
             context->yyMonth = yyvsp[-1].Number;
             context->yyYear = -yyvsp[0].Number;
-        ;
-    break;}
-case 24:
-#line 352 "getdate.y"
-{
+        }
+    break;
+
+  case 25:
+#line 365 "getdate.y"
+    {
             context->yyMonth = yyvsp[-1].Number;
             context->yyDay = yyvsp[0].Number;
-        ;
-    break;}
-case 25:
-#line 356 "getdate.y"
-{
+        }
+    break;
+
+  case 26:
+#line 369 "getdate.y"
+    {
             context->yyMonth = yyvsp[-3].Number;
             context->yyDay = yyvsp[-2].Number;
             context->yyYear = yyvsp[0].Number;
-        ;
-    break;}
-case 26:
-#line 361 "getdate.y"
-{
+        }
+    break;
+
+  case 27:
+#line 374 "getdate.y"
+    {
             context->yyMonth = yyvsp[0].Number;
             context->yyDay = yyvsp[-1].Number;
-        ;
-    break;}
-case 27:
-#line 365 "getdate.y"
-{
+        }
+    break;
+
+  case 28:
+#line 378 "getdate.y"
+    {
             context->yyMonth = yyvsp[-1].Number;
             context->yyDay = yyvsp[-2].Number;
             context->yyYear = yyvsp[0].Number;
-        ;
-    break;}
-case 28:
-#line 372 "getdate.y"
-{
+        }
+    break;
+
+  case 29:
+#line 385 "getdate.y"
+    {
             context->yyRelSeconds = -context->yyRelSeconds;
             context->yyRelMinutes = -context->yyRelMinutes;
             context->yyRelHour = -context->yyRelHour;
             context->yyRelDay = -context->yyRelDay;
             context->yyRelMonth = -context->yyRelMonth;
             context->yyRelYear = -context->yyRelYear;
-        ;
-    break;}
-case 30:
-#line 383 "getdate.y"
-{
+        }
+    break;
+
+  case 31:
+#line 396 "getdate.y"
+    {
             context->yyRelYear += yyvsp[-1].Number * yyvsp[0].Number;
-        ;
-    break;}
-case 31:
-#line 386 "getdate.y"
-{
+        }
+    break;
+
+  case 32:
+#line 399 "getdate.y"
+    {
             context->yyRelYear += yyvsp[-1].Number * yyvsp[0].Number;
-        ;
-    break;}
-case 32:
-#line 389 "getdate.y"
-{
+        }
+    break;
+
+  case 33:
+#line 402 "getdate.y"
+    {
             context->yyRelYear += yyvsp[0].Number;
-        ;
-    break;}
-case 33:
-#line 392 "getdate.y"
-{
+        }
+    break;
+
+  case 34:
+#line 405 "getdate.y"
+    {
             context->yyRelMonth += yyvsp[-1].Number * yyvsp[0].Number;
-        ;
-    break;}
-case 34:
-#line 395 "getdate.y"
-{
+        }
+    break;
+
+  case 35:
+#line 408 "getdate.y"
+    {
             context->yyRelMonth += yyvsp[-1].Number * yyvsp[0].Number;
-        ;
-    break;}
-case 35:
-#line 398 "getdate.y"
-{
+        }
+    break;
+
+  case 36:
+#line 411 "getdate.y"
+    {
             context->yyRelMonth += yyvsp[0].Number;
-        ;
-    break;}
-case 36:
-#line 401 "getdate.y"
-{
+        }
+    break;
+
+  case 37:
+#line 414 "getdate.y"
+    {
             context->yyRelDay += yyvsp[-1].Number * yyvsp[0].Number;
-        ;
-    break;}
-case 37:
-#line 404 "getdate.y"
-{
+        }
+    break;
+
+  case 38:
+#line 417 "getdate.y"
+    {
             context->yyRelDay += yyvsp[-1].Number * yyvsp[0].Number;
-        ;
-    break;}
-case 38:
-#line 407 "getdate.y"
-{
+        }
+    break;
+
+  case 39:
+#line 420 "getdate.y"
+    {
             context->yyRelDay += yyvsp[0].Number;
-        ;
-    break;}
-case 39:
-#line 410 "getdate.y"
-{
+        }
+    break;
+
+  case 40:
+#line 423 "getdate.y"
+    {
             context->yyRelHour += yyvsp[-1].Number * yyvsp[0].Number;
-        ;
-    break;}
-case 40:
-#line 413 "getdate.y"
-{
+        }
+    break;
+
+  case 41:
+#line 426 "getdate.y"
+    {
             context->yyRelHour += yyvsp[-1].Number * yyvsp[0].Number;
-        ;
-    break;}
-case 41:
-#line 416 "getdate.y"
-{
+        }
+    break;
+
+  case 42:
+#line 429 "getdate.y"
+    {
             context->yyRelHour += yyvsp[0].Number;
-        ;
-    break;}
-case 42:
-#line 419 "getdate.y"
-{
+        }
+    break;
+
+  case 43:
+#line 432 "getdate.y"
+    {
             context->yyRelMinutes += yyvsp[-1].Number * yyvsp[0].Number;
-        ;
-    break;}
-case 43:
-#line 422 "getdate.y"
-{
+        }
+    break;
+
+  case 44:
+#line 435 "getdate.y"
+    {
             context->yyRelMinutes += yyvsp[-1].Number * yyvsp[0].Number;
-        ;
-    break;}
-case 44:
-#line 425 "getdate.y"
-{
+        }
+    break;
+
+  case 45:
+#line 438 "getdate.y"
+    {
             context->yyRelMinutes += yyvsp[0].Number;
-        ;
-    break;}
-case 45:
-#line 428 "getdate.y"
-{
+        }
+    break;
+
+  case 46:
+#line 441 "getdate.y"
+    {
             context->yyRelSeconds += yyvsp[-1].Number * yyvsp[0].Number;
-        ;
-    break;}
-case 46:
-#line 431 "getdate.y"
-{
+        }
+    break;
+
+  case 47:
+#line 444 "getdate.y"
+    {
             context->yyRelSeconds += yyvsp[-1].Number * yyvsp[0].Number;
-        ;
-    break;}
-case 47:
-#line 434 "getdate.y"
-{
+        }
+    break;
+
+  case 48:
+#line 447 "getdate.y"
+    {
             context->yyRelSeconds += yyvsp[0].Number;
-        ;
-    break;}
-case 48:
-#line 440 "getdate.y"
-{
+        }
+    break;
+
+  case 49:
+#line 453 "getdate.y"
+    {
             if (context->yyHaveTime && context->yyHaveDate &&
                 !context->yyHaveRel)
               context->yyYear = yyvsp[0].Number;
@@ -1290,243 +1663,222 @@ case 48:
                     context->yyMeridian = MER24;
                   }
               }
-          ;
-    break;}
-case 49:
-#line 474 "getdate.y"
-{
+          }
+    break;
+
+  case 50:
+#line 487 "getdate.y"
+    {
             yyval.Meridian = MER24;
-          ;
-    break;}
-case 50:
-#line 478 "getdate.y"
-{
+          }
+    break;
+
+  case 51:
+#line 491 "getdate.y"
+    {
             yyval.Meridian = yyvsp[0].Meridian;
-          ;
-    break;}
-}
-   /* the action file gets copied in in place of this dollarsign */
-#line 543 "/usr/local/share/bison.simple"
+          }
+    break;
+
+
+    }
+
+/* Line 999 of yacc.c.  */
+#line 1688 "y.tab.c"
 
   yyvsp -= yylen;
   yyssp -= yylen;
-#ifdef YYLSP_NEEDED
-  yylsp -= yylen;
-#endif
 
-#if YYDEBUG != 0
-  if (yydebug)
-    {
-      short *ssp1 = yyss - 1;
-      fprintf (stderr, "state stack now");
-      while (ssp1 != yyssp)
-        fprintf (stderr, " %d", *++ssp1);
-      fprintf (stderr, "\n");
-    }
-#endif
+
+  YY_STACK_PRINT (yyss, yyssp);
 
   *++yyvsp = yyval;
 
-#ifdef YYLSP_NEEDED
-  yylsp++;
-  if (yylen == 0)
-    {
-      yylsp->first_line = yylloc.first_line;
-      yylsp->first_column = yylloc.first_column;
-      yylsp->last_line = (yylsp-1)->last_line;
-      yylsp->last_column = (yylsp-1)->last_column;
-      yylsp->text = 0;
-    }
-  else
-    {
-      yylsp->last_line = (yylsp+yylen-1)->last_line;
-      yylsp->last_column = (yylsp+yylen-1)->last_column;
-    }
-#endif
 
-  /* Now "shift" the result of the reduction.
-     Determine what state that goes to,
-     based on the state we popped back to
-     and the rule number reduced by.  */
+  /* Now `shift' the result of the reduction.  Determine what state
+     that goes to, based on the state we popped back to and the rule
+     number reduced by.  */
 
   yyn = yyr1[yyn];
 
-  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
-  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
+  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
+  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
     yystate = yytable[yystate];
   else
-    yystate = yydefgoto[yyn - YYNTBASE];
+    yystate = yydefgoto[yyn - YYNTOKENS];
 
   goto yynewstate;
 
-yyerrlab:   /* here on detecting error */
 
-  if (! yyerrstatus)
-    /* If not already recovering from an error, report this error.  */
+/*------------------------------------.
+| yyerrlab -- here on detecting error |
+`------------------------------------*/
+yyerrlab:
+  /* If not already recovering from an error, report this error.  */
+  if (!yyerrstatus)
     {
       ++yynerrs;
-
-#ifdef YYERROR_VERBOSE
+#if YYERROR_VERBOSE
       yyn = yypact[yystate];
 
-      if (yyn > YYFLAG && yyn < YYLAST)
+      if (YYPACT_NINF < yyn && yyn < YYLAST)
         {
-          int size = 0;
-          char *msg;
-          int x, count;
-
-          count = 0;
-          /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
-          for (x = (yyn < 0 ? -yyn : 0);
-               x < (sizeof(yytname) / sizeof(char *)); x++)
-            if (yycheck[x + yyn] == x)
-              size += strlen(yytname[x]) + 15, count++;
-          msg = (char *) malloc(size + 15);
-          if (msg != 0)
+          YYSIZE_T yysize = 0;
+          int yytype = YYTRANSLATE (yychar);
+          char *yymsg;
+          int yyx, yycount;
+
+          yycount = 0;
+          /* Start YYX at -YYN if negative to avoid negative indexes in
+             YYCHECK.  */
+          for (yyx = yyn < 0 ? -yyn : 0;
+               yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
+            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
+              yysize += yystrlen (yytname[yyx]) + 15, yycount++;
+          yysize += yystrlen ("syntax error, unexpected ") + 1;
+          yysize += yystrlen (yytname[yytype]);
+          yymsg = (char *) YYSTACK_ALLOC (yysize);
+          if (yymsg != 0)
             {
-              strcpy(msg, "parse error");
+              char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
+              yyp = yystpcpy (yyp, yytname[yytype]);
 
-              if (count < 5)
+              if (yycount < 5)
                 {
-                  count = 0;
-                  for (x = (yyn < 0 ? -yyn : 0);
-                       x < (sizeof(yytname) / sizeof(char *)); x++)
-                    if (yycheck[x + yyn] == x)
+                  yycount = 0;
+                  for (yyx = yyn < 0 ? -yyn : 0;
+                       yyx < (int) (sizeof (yytname) / sizeof (char *));
+                       yyx++)
+                    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
                       {
-                        strcat(msg, count == 0 ? ", expecting `" : " or `");
-                        strcat(msg, yytname[x]);
-                        strcat(msg, "'");
-                        count++;
+                        const char *yyq = ! yycount ? ", expecting " : " or ";
+                        yyp = yystpcpy (yyp, yyq);
+                        yyp = yystpcpy (yyp, yytname[yyx]);
+                        yycount++;
                       }
                 }
-              yyerror(msg);
-              free(msg);
+              yyerror (yymsg);
+              YYSTACK_FREE (yymsg);
             }
           else
-            yyerror ("parse error; also virtual memory exceeded");
+            yyerror ("syntax error; also virtual memory exhausted");
         }
       else
 #endif /* YYERROR_VERBOSE */
-        yyerror("parse error");
+        yyerror ("syntax error");
     }
 
-  goto yyerrlab1;
-yyerrlab1:   /* here on error raised explicitly by an action */
+
 
   if (yyerrstatus == 3)
     {
-      /* if just tried and failed to reuse lookahead token after an error, discard it.  */
+      /* If just tried and failed to reuse lookahead token after an
+         error, discard it.  */
 
-      /* return failure if at end of input */
+      /* Return failure if at end of input.  */
       if (yychar == YYEOF)
-        YYABORT;
-
-#if YYDEBUG != 0
-      if (yydebug)
-        fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
-#endif
+        {
+          /* Pop the error token.  */
+          YYPOPSTACK;
+          /* Pop the rest of the stack.  */
+          while (yyss < yyssp)
+            {
+              YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
+              yydestruct (yystos[*yyssp], yyvsp);
+              YYPOPSTACK;
+            }
+          YYABORT;
+        }
 
+      YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
+      yydestruct (yytoken, &yylval);
       yychar = YYEMPTY;
-    }
-
-  /* Else will try to reuse lookahead token
-     after shifting the error token.  */
 
-  yyerrstatus = 3;              /* Each real token shifted decrements this */
-
-  goto yyerrhandle;
-
-yyerrdefault:  /* current state does not do anything special for the error token. */
+    }
 
-#if 0
-  /* This is wrong; only states that explicitly want error tokens
-     should shift them.  */
-  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
-  if (yyn) goto yydefault;
-#endif
+  /* Else will try to reuse lookahead token after shifting the error
+     token.  */
+  goto yyerrlab1;
 
-yyerrpop:   /* pop the current state because it cannot handle the error token */
 
-  if (yyssp == yyss) YYABORT;
-  yyvsp--;
-  yystate = *--yyssp;
-#ifdef YYLSP_NEEDED
-  yylsp--;
-#endif
+/*----------------------------------------------------.
+| yyerrlab1 -- error raised explicitly by an action.  |
+`----------------------------------------------------*/
+yyerrlab1:
+  yyerrstatus = 3;      /* Each real token shifted decrements this.  */
 
-#if YYDEBUG != 0
-  if (yydebug)
+  for (;;)
     {
-      short *ssp1 = yyss - 1;
-      fprintf (stderr, "Error: state stack now");
-      while (ssp1 != yyssp)
-        fprintf (stderr, " %d", *++ssp1);
-      fprintf (stderr, "\n");
-    }
-#endif
-
-yyerrhandle:
+      yyn = yypact[yystate];
+      if (yyn != YYPACT_NINF)
+        {
+          yyn += YYTERROR;
+          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
+            {
+              yyn = yytable[yyn];
+              if (0 < yyn)
+                break;
+            }
+        }
 
-  yyn = yypact[yystate];
-  if (yyn == YYFLAG)
-    goto yyerrdefault;
+      /* Pop the current state because it cannot handle the error token.  */
+      if (yyssp == yyss)
+        YYABORT;
 
-  yyn += YYTERROR;
-  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
-    goto yyerrdefault;
+      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
+      yydestruct (yystos[yystate], yyvsp);
+      yyvsp--;
+      yystate = *--yyssp;
 
-  yyn = yytable[yyn];
-  if (yyn < 0)
-    {
-      if (yyn == YYFLAG)
-        goto yyerrpop;
-      yyn = -yyn;
-      goto yyreduce;
+      YY_STACK_PRINT (yyss, yyssp);
     }
-  else if (yyn == 0)
-    goto yyerrpop;
 
   if (yyn == YYFINAL)
     YYACCEPT;
 
-#if YYDEBUG != 0
-  if (yydebug)
-    fprintf(stderr, "Shifting error token, ");
-#endif
+  YYDPRINTF ((stderr, "Shifting error token, "));
 
   *++yyvsp = yylval;
-#ifdef YYLSP_NEEDED
-  *++yylsp = yylloc;
-#endif
+
 
   yystate = yyn;
   goto yynewstate;
 
- yyacceptlab:
-  /* YYACCEPT comes here.  */
-  if (yyfree_stacks)
-    {
-      free (yyss);
-      free (yyvs);
-#ifdef YYLSP_NEEDED
-      free (yyls);
-#endif
-    }
-  return 0;
 
- yyabortlab:
-  /* YYABORT comes here.  */
-  if (yyfree_stacks)
-    {
-      free (yyss);
-      free (yyvs);
-#ifdef YYLSP_NEEDED
-      free (yyls);
-#endif
-    }
-  return 1;
+/*-------------------------------------.
+| yyacceptlab -- YYACCEPT comes here.  |
+`-------------------------------------*/
+yyacceptlab:
+  yyresult = 0;
+  goto yyreturn;
+
+/*-----------------------------------.
+| yyabortlab -- YYABORT comes here.  |
+`-----------------------------------*/
+yyabortlab:
+  yyresult = 1;
+  goto yyreturn;
+
+#ifndef yyoverflow
+/*----------------------------------------------.
+| yyoverflowlab -- parser overflow comes here.  |
+`----------------------------------------------*/
+yyoverflowlab:
+  yyerror ("parser stack overflow");
+  yyresult = 2;
+  /* Fall through.  */
+#endif
+
+yyreturn:
+#ifndef yyoverflow
+  if (yyss != yyssa)
+    YYSTACK_FREE (yyss);
+#endif
+  return yyresult;
 }
-#line 483 "getdate.y"
+
+
+#line 496 "getdate.y"
 
 
 /* Include this file down here because bison inserts code above which
@@ -1535,9 +1887,9 @@ case 50:
 #include "getdate.h"
 
 #ifndef WIN32 /* the windows dudes don't need these, does anyone really? */
-extern struct tm        *gmtime (const time_t *timer);
-extern struct tm        *localtime (const time_t *timer);
-extern time_t           mktime (struct tm *timeptr);
+extern struct tm        *gmtime (const time_t *);
+extern struct tm        *localtime (const time_t *);
+extern time_t           mktime (struct tm *);
 #endif
 
 /* Month and day table. */
@@ -1729,17 +2081,13 @@ static TABLE const MilitaryTable[] = {
 
 /* ARGSUSED */
 static int
-yyerror (s)
-     char *s ATTRIBUTE_UNUSED;
+yyerror (const char *s ATTRIBUTE_UNUSED)
 {
-  (void)s;
   return 0;
 }
 
 static int
-ToHour (Hours, Meridian)
-     int Hours;
-     MERIDIAN Meridian;
+ToHour (int Hours, MERIDIAN Meridian)
 {
   switch (Meridian)
     {
@@ -1760,14 +2108,14 @@ ToHour (Hours, Meridian)
         Hours = 0;
       return Hours + 12;
     default:
-      abort ();
+      break; /* used to do abort() here */
     }
-  /* NOTREACHED */
+  /* NOTREACHED - but make gcc happy! */
+  return -1;
 }
 
 static int
-ToYear (Year)
-     int Year;
+ToYear (int Year)
 {
   if (Year < 0)
     Year = -Year;
@@ -1783,20 +2131,18 @@ ToYear (Year)
 }
 
 static int
-LookupWord (yylval, buff)
-     YYSTYPE *yylval;
-     char *buff;
+LookupWord (YYSTYPE *yylval, char *buff)
 {
-  register char *p;
-  register char *q;
-  register const TABLE *tp;
-  int i;
+  char *p;
+  char *q;
+  const TABLE *tp;
+  size_t i;
   int abbrev;
 
   /* Make it lowercase. */
   for (p = buff; *p; p++)
-    if (ISUPPER ((unsigned int)(*p)))
-      *p = (char)tolower ((unsigned int)(*p));
+    if (ISUPPER ((unsigned char) *p))
+      *p = tolower ((int)*p);
 
   if (strcmp (buff, "am") == 0 || strcmp (buff, "a.m.") == 0)
     {
@@ -1855,7 +2201,7 @@ LookupWord (yylval, buff)
       }
 
   /* Strip off any plural and try the units table again. */
-  i = (int)strlen (buff) - 1;
+  i = strlen (buff) - 1;
   if (buff[i] == 's')
     {
       buff[i] = '\0';
@@ -1905,9 +2251,7 @@ LookupWord (yylval, buff)
 }
 
 static int
-yylex (yylval, cookie)
-     YYSTYPE *yylval;
-     void *cookie;
+yylex (YYSTYPE *yylval, void *cookie)
 {
   register unsigned char c;
   register char *p;
@@ -1992,7 +2336,7 @@ curl_getdate (const char *p, const time_t *now)
 {
   struct tm tm, tm0, *tmp;
   time_t Start;
-  CONTEXT cookie;
+  CURL_CONTEXT cookie;
 #ifdef HAVE_LOCALTIME_R
   struct tm keeptime;
 #endif
@@ -2025,7 +2369,7 @@ curl_getdate (const char *p, const time_t *now)
   cookie.yyHaveTime = 0;
   cookie.yyHaveZone = 0;
 
-  if (yyparse ((void*)&cookie)
+  if (yyparse (&cookie)
       || cookie.yyHaveTime > 1 || cookie.yyHaveZone > 1 ||
       cookie.yyHaveDate > 1 || cookie.yyHaveDay > 1)
     return -1;
@@ -2106,8 +2450,8 @@ curl_getdate (const char *p, const time_t *now)
       struct tm *gmt;
 #ifdef HAVE_GMTIME_R
       /* thread-safe version */
-      struct tm keeptime;
-      gmt = (struct tm *)gmtime_r(&Start, &keeptime);
+      struct tm keeptime2;
+      gmt = (struct tm *)gmtime_r(&Start, &keeptime2);
 #else
       gmt = gmtime(&Start);
 #endif
@@ -2122,32 +2466,4 @@ curl_getdate (const char *p, const time_t *now)
   return Start;
 }
 
-#if     defined (TEST)
-
-/* ARGSUSED */
-int
-main (ac, av)
-     int ac;
-     char *av[];
-{
-  char buff[MAX_BUFF_LEN + 1];
-  time_t d;
-
-  (void) printf ("Enter date, or blank line to exit.\n\t> ");
-  (void) fflush (stdout);
 
-  buff[MAX_BUFF_LEN] = 0;
-  while (fgets (buff, MAX_BUFF_LEN, stdin) && buff[0])
-    {
-      d = curl_getdate (buff, (time_t *) NULL);
-      if (d == -1)
-        (void) printf ("Bad format - couldn't convert.\n");
-      else
-        (void) printf ("%s", ctime (&d));
-      (void) printf ("\t> ");
-      (void) fflush (stdout);
-    }
-  exit (0);
-  /* NOTREACHED */
-}
-#endif /* defined (TEST) */