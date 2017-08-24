@@ -1,7 +1,9 @@
-/* A Bison parser, made by GNU Bison 1.875d.  */
+/* A Bison parser, made by GNU Bison 2.3.  */
 
-/* Skeleton parser for Yacc-like parsing with Bison, Copyright (C) 1984,
-   1989, 1990, 2000, 2001, 2002, 2003, 2004 Free Software Foundation, Inc.
+/* Skeleton implementation for Bison's Yacc-like parsers in C
+
+   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
+   Free Software Foundation, Inc.
 
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
@@ -15,16 +17,24 @@
 
    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
-   Foundation, Inc., 59 Temple Place - Suite 330,
-   Boston, MA 02111-1307, USA.  */
+   Foundation, Inc., 51 Franklin Street, Fifth Floor,
+   Boston, MA 02110-1301, USA.  */
+
+/* As a special exception, you may create a larger work that contains
+   part or all of the Bison parser skeleton and distribute that work
+   under terms of your choice, so long as that work isn't itself a
+   parser generator using the skeleton or a modified version thereof
+   as a parser skeleton.  Alternatively, if you modify or redistribute
+   the parser skeleton itself, you may (at your option) remove this
+   special exception, which will cause the skeleton and the resulting
+   Bison output files to be licensed under the GNU General Public
+   License without this special exception.
 
-/* As a special exception, when this file is copied by Bison into a
-   Bison output file, you may use that output file without restriction.
-   This special exception was added by the Free Software Foundation
-   in version 1.24 of Bison.  */
+   This special exception was added by the Free Software Foundation in
+   version 2.2 of Bison.  */
 
-/* Written by Richard Stallman by simplifying the original so called
-   ``semantic'' parser.  */
+/* C LALR(1) parser skeleton written by Richard Stallman, by
+   simplifying the original so-called "semantic" parser.  */
 
 /* All symbols defined below should begin with yy or YY, to avoid
    infringing on user name space.  This should be done even for local
@@ -33,15 +43,12 @@
    define necessary library symbols; they are noted "INFRINGES ON
    USER NAME SPACE" below.  */
 
-/* turn off some warning as this is generated code */
-#if defined(_MSC_VER)
-#  pragma warning ( disable : 4244 ) /* loss of precision */
-#  pragma warning ( disable : 4702 ) /* unreachable code */
-#endif
-
 /* Identify Bison output.  */
 #define YYBISON 1
 
+/* Bison version.  */
+#define YYBISON_VERSION "2.3"
+
 /* Skeleton name.  */
 #define YYSKELETON_NAME "yacc.c"
 
@@ -51,8 +58,7 @@
 /* Using locations.  */
 #define YYLSP_NEEDED 0
 
-/* If NAME_PREFIX is specified substitute the variables and functions
-   names.  */
+/* Substitute the variable and function names.  */
 #define yyparse cmDependsFortran_yyparse
 #define yylex   cmDependsFortran_yylex
 #define yyerror cmDependsFortran_yyerror
@@ -68,62 +74,61 @@
    /* Put the tokens into the symbol table, so that GDB and other debuggers
       know about them.  */
    enum yytokentype {
-     USE = 258,
-     F_INCLUDE = 259,
-     MODULE = 260,
-     EOSTMT = 261,
-     CPP_INCLUDE = 262,
-     F90PPR_INCLUDE = 263,
-     COCO_INCLUDE = 264,
-     F90PPR_DEFINE = 265,
-     CPP_DEFINE = 266,
-     F90PPR_UNDEF = 267,
-     CPP_UNDEF = 268,
-     CPP_IFDEF = 269,
-     CPP_IFNDEF = 270,
-     CPP_IF = 271,
-     CPP_ELSE = 272,
-     CPP_ELIF = 273,
-     CPP_ENDIF = 274,
-     F90PPR_IFDEF = 275,
-     F90PPR_IFNDEF = 276,
-     F90PPR_IF = 277,
-     F90PPR_ELSE = 278,
-     F90PPR_ELIF = 279,
-     F90PPR_ENDIF = 280,
+     EOSTMT = 258,
+     ASSIGNMENT_OP = 259,
+     GARBAGE = 260,
+     CPP_INCLUDE = 261,
+     F90PPR_INCLUDE = 262,
+     COCO_INCLUDE = 263,
+     F90PPR_DEFINE = 264,
+     CPP_DEFINE = 265,
+     F90PPR_UNDEF = 266,
+     CPP_UNDEF = 267,
+     CPP_IFDEF = 268,
+     CPP_IFNDEF = 269,
+     CPP_IF = 270,
+     CPP_ELSE = 271,
+     CPP_ELIF = 272,
+     CPP_ENDIF = 273,
+     F90PPR_IFDEF = 274,
+     F90PPR_IFNDEF = 275,
+     F90PPR_IF = 276,
+     F90PPR_ELSE = 277,
+     F90PPR_ELIF = 278,
+     F90PPR_ENDIF = 279,
+     CPP_TOENDL = 280,
      UNTERMINATED_STRING = 281,
-     CPP_TOENDL = 282,
-     STRING = 283,
-     WORD = 284
+     STRING = 282,
+     WORD = 283
    };
 #endif
-#define USE 258
-#define F_INCLUDE 259
-#define MODULE 260
-#define EOSTMT 261
-#define CPP_INCLUDE 262
-#define F90PPR_INCLUDE 263
-#define COCO_INCLUDE 264
-#define F90PPR_DEFINE 265
-#define CPP_DEFINE 266
-#define F90PPR_UNDEF 267
-#define CPP_UNDEF 268
-#define CPP_IFDEF 269
-#define CPP_IFNDEF 270
-#define CPP_IF 271
-#define CPP_ELSE 272
-#define CPP_ELIF 273
-#define CPP_ENDIF 274
-#define F90PPR_IFDEF 275
-#define F90PPR_IFNDEF 276
-#define F90PPR_IF 277
-#define F90PPR_ELSE 278
-#define F90PPR_ELIF 279
-#define F90PPR_ENDIF 280
+/* Tokens.  */
+#define EOSTMT 258
+#define ASSIGNMENT_OP 259
+#define GARBAGE 260
+#define CPP_INCLUDE 261
+#define F90PPR_INCLUDE 262
+#define COCO_INCLUDE 263
+#define F90PPR_DEFINE 264
+#define CPP_DEFINE 265
+#define F90PPR_UNDEF 266
+#define CPP_UNDEF 267
+#define CPP_IFDEF 268
+#define CPP_IFNDEF 269
+#define CPP_IF 270
+#define CPP_ELSE 271
+#define CPP_ELIF 272
+#define CPP_ENDIF 273
+#define F90PPR_IFDEF 274
+#define F90PPR_IFNDEF 275
+#define F90PPR_IF 276
+#define F90PPR_ELSE 277
+#define F90PPR_ELIF 278
+#define F90PPR_ENDIF 279
+#define CPP_TOENDL 280
 #define UNTERMINATED_STRING 281
-#define CPP_TOENDL 282
-#define STRING 283
-#define WORD 284
+#define STRING 282
+#define WORD 283
 
 
 
@@ -163,12 +168,12 @@ This file must be translated to C and modified to build everywhere.
 
 Run bison like this:
 
-  bison --yacc --name-prefix=cmDependsFortran_yy
-  --defines=cmDependsFortranParserTokens.h -ocmDependsFortranParser.cxx
-  cmDependsFortranParser.y
+  bison --yacc --name-prefix=cmDependsFortran_yy --defines=cmDependsFortranParserTokens.h -ocmDependsFortranParser.cxx cmDependsFortranParser.y
 
 Modify cmDependsFortranParser.cxx:
   - remove TABs
+  - add __HP_aCC to the #if test for yyerrorlab warning suppression
+  - add __INTEL_COMPILER to the #if test for yyerrorlab warning suppression
 
 */
 
@@ -220,13 +225,20 @@ static void cmDependsFortranError(yyscan_t yyscanner, const char* message)
 # define YYERROR_VERBOSE 0
 #endif
 
-#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
-#line 75 "cmDependsFortranParser.y"
-typedef union YYSTYPE {
+/* Enabling the token table.  */
+#ifndef YYTOKEN_TABLE
+# define YYTOKEN_TABLE 0
+#endif
+
+#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
+typedef union YYSTYPE
+#line 81 "cmDependsFortranParser.y"
+{
   char* string;
-} YYSTYPE;
-/* Line 191 of yacc.c.  */
-#line 218 "cmDependsFortranParser.cxx"
+}
+/* Line 187 of yacc.c.  */
+#line 241 "cmDependsFortranParser.cxx"
+        YYSTYPE;
 # define yystype YYSTYPE /* obsolescent; will be withdrawn */
 # define YYSTYPE_IS_DECLARED 1
 # define YYSTYPE_IS_TRIVIAL 1
@@ -237,56 +249,171 @@ typedef union YYSTYPE {
 /* Copy the second part of user declarations.  */
 
 
-/* Line 214 of yacc.c.  */
-#line 230 "cmDependsFortranParser.cxx"
+/* Line 216 of yacc.c.  */
+#line 254 "cmDependsFortranParser.cxx"
+
+#ifdef short
+# undef short
+#endif
 
-#if ! defined (yyoverflow) || YYERROR_VERBOSE
+#ifdef YYTYPE_UINT8
+typedef YYTYPE_UINT8 yytype_uint8;
+#else
+typedef unsigned char yytype_uint8;
+#endif
 
-# ifndef YYFREE
-#  define YYFREE free
+#ifdef YYTYPE_INT8
+typedef YYTYPE_INT8 yytype_int8;
+#elif (defined __STDC__ || defined __C99__FUNC__ \
+     || defined __cplusplus || defined _MSC_VER)
+typedef signed char yytype_int8;
+#else
+typedef short int yytype_int8;
+#endif
+
+#ifdef YYTYPE_UINT16
+typedef YYTYPE_UINT16 yytype_uint16;
+#else
+typedef unsigned short int yytype_uint16;
+#endif
+
+#ifdef YYTYPE_INT16
+typedef YYTYPE_INT16 yytype_int16;
+#else
+typedef short int yytype_int16;
+#endif
+
+#ifndef YYSIZE_T
+# ifdef __SIZE_TYPE__
+#  define YYSIZE_T __SIZE_TYPE__
+# elif defined size_t
+#  define YYSIZE_T size_t
+# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
+     || defined __cplusplus || defined _MSC_VER)
+#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
+#  define YYSIZE_T size_t
+# else
+#  define YYSIZE_T unsigned int
 # endif
-# ifndef YYMALLOC
-#  define YYMALLOC malloc
+#endif
+
+#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)
+
+#ifndef YY_
+# if YYENABLE_NLS
+#  if ENABLE_NLS
+#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
+#   define YY_(msgid) dgettext ("bison-runtime", msgid)
+#  endif
 # endif
+# ifndef YY_
+#  define YY_(msgid) msgid
+# endif
+#endif
+
+/* Suppress unused-variable warnings by "using" E.  */
+#if ! defined lint || defined __GNUC__
+# define YYUSE(e) ((void) (e))
+#else
+# define YYUSE(e) /* empty */
+#endif
+
+/* Identity function, used to suppress warnings about constant conditions.  */
+#ifndef lint
+# define YYID(n) (n)
+#else
+#if (defined __STDC__ || defined __C99__FUNC__ \
+     || defined __cplusplus || defined _MSC_VER)
+static int
+YYID (int i)
+#else
+static int
+YYID (i)
+    int i;
+#endif
+{
+  return i;
+}
+#endif
+
+#if ! defined yyoverflow || YYERROR_VERBOSE
 
 /* The parser invokes alloca or malloc; define the necessary symbols.  */
 
 # ifdef YYSTACK_USE_ALLOCA
 #  if YYSTACK_USE_ALLOCA
-#   define YYSTACK_ALLOC alloca
-#  endif
-# else
-#  if defined (alloca) || defined (_ALLOCA_H)
-#   define YYSTACK_ALLOC alloca
-#  else
 #   ifdef __GNUC__
 #    define YYSTACK_ALLOC __builtin_alloca
+#   elif defined __BUILTIN_VA_ARG_INCR
+#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
+#   elif defined _AIX
+#    define YYSTACK_ALLOC __alloca
+#   elif defined _MSC_VER
+#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
+#    define alloca _alloca
+#   else
+#    define YYSTACK_ALLOC alloca
+#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
+     || defined __cplusplus || defined _MSC_VER)
+#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
+#     ifndef _STDLIB_H
+#      define _STDLIB_H 1
+#     endif
+#    endif
 #   endif
 #  endif
 # endif
 
 # ifdef YYSTACK_ALLOC
-   /* Pacify GCC's `empty if-body' warning. */
-#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
-# else
-#  if defined (__STDC__) || defined (__cplusplus)
-#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
-#   define YYSIZE_T size_t
+   /* Pacify GCC's `empty if-body' warning.  */
+#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
+#  ifndef YYSTACK_ALLOC_MAXIMUM
+    /* The OS might guarantee only one guard page at the bottom of the stack,
+       and a page size can be as small as 4096 bytes.  So we cannot safely
+       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
+       to allow for a few compiler-allocated temporary stack slots.  */
+#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
 #  endif
+# else
 #  define YYSTACK_ALLOC YYMALLOC
 #  define YYSTACK_FREE YYFREE
+#  ifndef YYSTACK_ALLOC_MAXIMUM
+#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
+#  endif
+#  if (defined __cplusplus && ! defined _STDLIB_H \
+       && ! ((defined YYMALLOC || defined malloc) \
+             && (defined YYFREE || defined free)))
+#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
+#   ifndef _STDLIB_H
+#    define _STDLIB_H 1
+#   endif
+#  endif
+#  ifndef YYMALLOC
+#   define YYMALLOC malloc
+#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
+     || defined __cplusplus || defined _MSC_VER)
+void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
+#   endif
+#  endif
+#  ifndef YYFREE
+#   define YYFREE free
+#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
+     || defined __cplusplus || defined _MSC_VER)
+void free (void *); /* INFRINGES ON USER NAME SPACE */
+#   endif
+#  endif
 # endif
-#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */
+#endif /* ! defined yyoverflow || YYERROR_VERBOSE */
 
 
-#if (! defined (yyoverflow) \
-     && (! defined (__cplusplus) \
-         || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))
+#if (! defined yyoverflow \
+     && (! defined __cplusplus \
+         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))
 
 /* A type that is properly aligned for any stack member.  */
 union yyalloc
 {
-  short int yyss;
+  yytype_int16 yyss;
   YYSTYPE yyvs;
   };
 
@@ -296,24 +423,24 @@ union yyalloc
 /* The size of an array large to enough to hold all stacks, each with
    N elements.  */
 # define YYSTACK_BYTES(N) \
-     ((N) * (sizeof (short int) + sizeof (YYSTYPE))                     \
+     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
       + YYSTACK_GAP_MAXIMUM)
 
 /* Copy COUNT objects from FROM to TO.  The source and destination do
    not overlap.  */
 # ifndef YYCOPY
-#  if defined (__GNUC__) && 1 < __GNUC__
+#  if defined __GNUC__ && 1 < __GNUC__
 #   define YYCOPY(To, From, Count) \
       __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
 #  else
 #   define YYCOPY(To, From, Count)              \
       do                                        \
         {                                       \
-          register YYSIZE_T yyi;                \
+          YYSIZE_T yyi;                         \
           for (yyi = 0; yyi < (Count); yyi++)   \
             (To)[yyi] = (From)[yyi];            \
         }                                       \
-      while (0)
+      while (YYID (0))
 #  endif
 # endif
 
@@ -331,39 +458,33 @@ union yyalloc
         yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
         yyptr += yynewbytes / sizeof (*yyptr);                          \
       }                                                                 \
-    while (0)
-
-#endif
+    while (YYID (0))
 
-#if defined (__STDC__) || defined (__cplusplus)
-   typedef signed char yysigned_char;
-#else
-   typedef short int yysigned_char;
 #endif
 
-/* YYFINAL -- State number of the termination state. */
+/* YYFINAL -- State number of the termination state.  */
 #define YYFINAL  2
 /* YYLAST -- Last index in YYTABLE.  */
-#define YYLAST   67
+#define YYLAST   139
 
-/* YYNTOKENS -- Number of terminals. */
-#define YYNTOKENS  30
-/* YYNNTS -- Number of nonterminals. */
+/* YYNTOKENS -- Number of terminals.  */
+#define YYNTOKENS  29
+/* YYNNTS -- Number of nonterminals.  */
 #define YYNNTS  15
-/* YYNRULES -- Number of rules. */
-#define YYNRULES  43
-/* YYNRULES -- Number of states. */
-#define YYNSTATES  73
+/* YYNRULES -- Number of rules.  */
+#define YYNRULES  45
+/* YYNRULES -- Number of states.  */
+#define YYNSTATES  79
 
 /* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
 #define YYUNDEFTOK  2
-#define YYMAXUTOK   284
+#define YYMAXUTOK   283
 
 #define YYTRANSLATE(YYX)                                                \
   ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)
 
 /* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
-static const unsigned char yytranslate[] =
+static const yytype_uint8 yytranslate[] =
 {
        0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
@@ -393,197 +514,197 @@ static const unsigned char yytranslate[] =
        2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
        5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
       15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
-      25,    26,    27,    28,    29
+      25,    26,    27,    28
 };
 
 #if YYDEBUG
 /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
    YYRHS.  */
-static const unsigned char yyprhs[] =
+static const yytype_uint8 yyprhs[] =
 {
-       0,     0,     3,     4,     7,    12,    17,    22,    26,    31,
-      36,    41,    46,    50,    54,    58,    62,    65,    66,    68,
-      70,    72,    74,    76,    78,    80,    82,    84,    86,    88,
-      90,    92,    94,    96,    98,   100,   102,   104,   106,   108,
-     109,   112,   114,   116
+       0,     0,     3,     4,     7,     9,    11,    16,    19,    24,
+      29,    34,    39,    44,    49,    54,    58,    62,    66,    70,
+      75,    79,    81,    83,    85,    87,    89,    91,    93,    95,
+      97,    99,   101,   103,   105,   107,   109,   111,   113,   115,
+     116,   119,   121,   123,   125,   127
 };
 
-/* YYRHS -- A `-1'-separated list of the rules' RHS. */
-static const yysigned_char yyrhs[] =
+/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
+static const yytype_int8 yyrhs[] =
 {
-      31,     0,    -1,    -1,    31,    32,    -1,     3,    29,    43,
-      33,    -1,    34,    28,    43,    33,    -1,     7,    29,    43,
-      33,    -1,     5,    29,    33,    -1,    35,    29,    43,    33,
-      -1,    36,    29,    43,    33,    -1,    37,    29,    43,    33,
-      -1,    38,    29,    43,    33,    -1,    39,    43,    33,    -1,
-      40,    43,    33,    -1,    41,    43,    33,    -1,    42,    43,
-      33,    -1,    43,    33,    -1,    -1,     6,    -1,     4,    -1,
-       7,    -1,     8,    -1,     9,    -1,    11,    -1,    10,    -1,
-      13,    -1,    12,    -1,    14,    -1,    20,    -1,    15,    -1,
-      21,    -1,    16,    -1,    22,    -1,    18,    -1,    24,    -1,
-      17,    -1,    23,    -1,    19,    -1,    25,    -1,    -1,    43,
-      44,    -1,    29,    -1,    28,    -1,    26,    -1
+      30,     0,    -1,    -1,    30,    31,    -1,    33,    -1,    32,
+      -1,    28,     4,    42,     3,    -1,    28,     3,    -1,    28,
+      28,    42,     3,    -1,    28,    27,    42,     3,    -1,     6,
+      28,    42,     3,    -1,    34,    28,    42,     3,    -1,    35,
+      28,    42,     3,    -1,    36,    28,    42,     3,    -1,    37,
+      28,    42,     3,    -1,    38,    42,     3,    -1,    39,    42,
+       3,    -1,    40,    42,     3,    -1,    41,    42,     3,    -1,
+      28,     5,    42,     3,    -1,     5,    42,     3,    -1,     3,
+      -1,     1,    -1,    10,    -1,     9,    -1,    12,    -1,    11,
+      -1,    13,    -1,    19,    -1,    14,    -1,    20,    -1,    15,
+      -1,    21,    -1,    17,    -1,    23,    -1,    16,    -1,    22,
+      -1,    18,    -1,    24,    -1,    -1,    42,    43,    -1,    28,
+      -1,    27,    -1,     5,    -1,     4,    -1,    26,    -1
 };
 
 /* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
-static const unsigned char yyrline[] =
+static const yytype_uint8 yyrline[] =
 {
-       0,    93,    93,    93,    96,   102,   108,   109,   115,   121,
-     127,   133,   139,   144,   149,   154,   159,   162,   162,   163,
-     163,   163,   163,   164,   164,   165,   165,   166,   166,   167,
-     167,   168,   168,   169,   169,   170,   170,   171,   171,   172,
-     172,   175,   176,   177
+       0,   100,   100,   100,   102,   102,   104,   107,   116,   144,
+     154,   155,   161,   167,   173,   179,   184,   189,   194,   199,
+     200,   201,   202,   208,   208,   209,   209,   210,   210,   211,
+     211,   212,   212,   213,   213,   214,   214,   215,   215,   216,
+     216,   219,   220,   221,   222,   223
 };
 #endif
 
-#if YYDEBUG || YYERROR_VERBOSE
-/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
-   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
+#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
+/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
+   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
 static const char *const yytname[] =
 {
-  "$end", "error", "$undefined", "USE", "F_INCLUDE", "MODULE", "EOSTMT",
+  "$end", "error", "$undefined", "EOSTMT", "ASSIGNMENT_OP", "GARBAGE",
   "CPP_INCLUDE", "F90PPR_INCLUDE", "COCO_INCLUDE", "F90PPR_DEFINE",
   "CPP_DEFINE", "F90PPR_UNDEF", "CPP_UNDEF", "CPP_IFDEF", "CPP_IFNDEF",
   "CPP_IF", "CPP_ELSE", "CPP_ELIF", "CPP_ENDIF", "F90PPR_IFDEF",
   "F90PPR_IFNDEF", "F90PPR_IF", "F90PPR_ELSE", "F90PPR_ELIF",
-  "F90PPR_ENDIF", "UNTERMINATED_STRING", "CPP_TOENDL", "STRING", "WORD",
-  "$accept", "code", "stmt", "eostmt", "include", "define", "undef",
-  "ifdef", "ifndef", "if", "elif", "else", "endif", "other", "misc_code", 0
+  "F90PPR_ENDIF", "CPP_TOENDL", "UNTERMINATED_STRING", "STRING", "WORD",
+  "$accept", "code", "stmt", "assignment_stmt", "keyword_stmt", "define",
+  "undef", "ifdef", "ifndef", "if", "elif", "else", "endif", "other",
+  "misc_code", 0
 };
 #endif
 
 # ifdef YYPRINT
 /* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
    token YYLEX-NUM.  */
-static const unsigned short int yytoknum[] =
+static const yytype_uint16 yytoknum[] =
 {
        0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
      265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
-     275,   276,   277,   278,   279,   280,   281,   282,   283,   284
+     275,   276,   277,   278,   279,   280,   281,   282,   283
 };
 # endif
 
 /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
-static const unsigned char yyr1[] =
+static const yytype_uint8 yyr1[] =
 {
-       0,    30,    31,    31,    32,    32,    32,    32,    32,    32,
-      32,    32,    32,    32,    32,    32,    32,    33,    33,    34,
-      34,    34,    34,    35,    35,    36,    36,    37,    37,    38,
-      38,    39,    39,    40,    40,    41,    41,    42,    42,    43,
-      43,    44,    44,    44
+       0,    29,    30,    30,    31,    31,    32,    33,    33,    33,
+      33,    33,    33,    33,    33,    33,    33,    33,    33,    33,
+      33,    33,    33,    34,    34,    35,    35,    36,    36,    37,
+      37,    38,    38,    39,    39,    40,    40,    41,    41,    42,
+      42,    43,    43,    43,    43,    43
 };
 
 /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
-static const unsigned char yyr2[] =
+static const yytype_uint8 yyr2[] =
 {
-       0,     2,     0,     2,     4,     4,     4,     3,     4,     4,
-       4,     4,     3,     3,     3,     3,     2,     0,     1,     1,
-       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
+       0,     2,     0,     2,     1,     1,     4,     2,     4,     4,
+       4,     4,     4,     4,     4,     3,     3,     3,     3,     4,
+       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
        1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
-       2,     1,     1,     1
+       2,     1,     1,     1,     1,     1
 };
 
 /* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
    STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
    means the default is an error.  */
-static const unsigned char yydefact[] =
+static const yytype_uint8 yydefact[] =
 {
-       2,    39,     1,     0,    19,     0,    20,    21,    22,    24,
-      23,    26,    25,    27,    29,    31,    35,    33,    37,    28,
-      30,    32,    36,    34,    38,     3,     0,     0,     0,     0,
-       0,    39,    39,    39,    39,    17,    39,    17,    39,    39,
-      39,    39,    39,    39,    17,    17,    17,    17,    18,    43,
-      42,    41,    16,    40,    17,     7,    17,    17,    17,    17,
-      17,    17,    12,    13,    14,    15,     4,     6,     5,     8,
-       9,    10,    11
+       2,     0,     1,    22,    21,    39,     0,    24,    23,    26,
+      25,    27,    29,    31,    35,    33,    37,    28,    30,    32,
+      36,    34,    38,     0,     3,     5,     4,     0,     0,     0,
+       0,    39,    39,    39,    39,     0,    39,     7,    39,    39,
+      39,    39,    39,    39,    39,    39,     0,     0,     0,     0,
+      20,    44,    43,    45,    42,    41,    40,     0,     0,     0,
+       0,     0,     0,     0,     0,     0,    15,    16,    17,    18,
+      10,     6,    19,     9,     8,    11,    12,    13,    14
 };
 
-/* YYDEFGOTO[NTERM-NUM]. */
-static const yysigned_char yydefgoto[] =
+/* YYDEFGOTO[NTERM-NUM].  */
+static const yytype_int8 yydefgoto[] =
 {
-      -1,     1,    25,    52,    26,    27,    28,    29,    30,    31,
-      32,    33,    34,    35,    53
+      -1,     1,    24,    25,    26,    27,    28,    29,    30,    31,
+      32,    33,    34,    35,    56
 };
 
 /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    STATE-NUM.  */
-#define YYPACT_NINF -29
-static const yysigned_char yypact[] =
+#define YYPACT_NINF -27
+static const yytype_int8 yypact[] =
 {
-     -29,     0,   -29,   -28,   -29,   -27,   -23,   -29,   -29,   -29,
-     -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29,
-     -29,   -29,   -29,   -29,   -29,   -29,    -1,     1,     3,     8,
-       9,   -29,   -29,   -29,   -29,    25,   -29,    22,   -29,   -29,
-     -29,   -29,   -29,   -29,    25,    25,    25,    25,   -29,   -29,
-     -29,   -29,   -29,   -29,    25,   -29,    25,    25,    25,    25,
-      25,    25,   -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29,
-     -29,   -29,   -29
+     -27,     0,   -27,   -27,   -27,   -27,   -26,   -27,   -27,   -27,
+     -27,   -27,   -27,   -27,   -27,   -27,   -27,   -27,   -27,   -27,
+     -27,   -27,   -27,   111,   -27,   -27,   -27,   -24,   -21,   -20,
+      19,   -27,   -27,   -27,   -27,    22,   -27,   -27,   -27,   -27,
+     -27,   -27,   -27,   -27,   -27,   -27,    26,    29,    32,    35,
+     -27,   -27,   -27,   -27,   -27,   -27,   -27,    38,    41,    67,
+      70,    73,    76,    79,    82,    85,   -27,   -27,   -27,   -27,
+     -27,   -27,   -27,   -27,   -27,   -27,   -27,   -27,   -27
 };
 
 /* YYPGOTO[NTERM-NUM].  */
-static const yysigned_char yypgoto[] =
+static const yytype_int8 yypgoto[] =
 {
-     -29,   -29,   -29,   -11,   -29,   -29,   -29,   -29,   -29,   -29,
-     -29,   -29,   -29,    24,   -29
+     -27,   -27,   -27,   -27,   -27,   -27,   -27,   -27,   -27,   -27,
+     -27,   -27,   -27,    86,   -27
 };
 
 /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
    positive, shift that token.  If negative, reduce the rule which
    number is the opposite.  If zero, do what YYDEFACT says.
    If YYTABLE_NINF, syntax error.  */
 #define YYTABLE_NINF -1
-static const unsigned char yytable[] =
+static const yytype_uint8 yytable[] =
 {
-       2,    36,    37,     3,     4,     5,    38,     6,     7,     8,
-       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
-      19,    20,    21,    22,    23,    24,    55,    39,    48,     0,
-      40,    48,    41,    62,    63,    64,    65,    42,    43,     0,
-       0,     0,     0,    66,     0,    67,    68,    69,    70,    71,
-      72,    49,     0,    50,    51,    44,    45,    46,    47,     0,
-      54,     0,    56,    57,    58,    59,    60,    61
+       2,     3,    36,     4,    42,     5,     6,    43,    44,     7,
+       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
+      18,    19,    20,    21,    22,    50,    51,    52,    23,    66,
+      51,    52,    67,    51,    52,    68,    51,    52,    69,    51,
+      52,    70,    51,    52,    71,    51,    52,    45,    53,    54,
+      55,     0,    53,    54,    55,    53,    54,    55,    53,    54,
+      55,    53,    54,    55,    53,    54,    55,    53,    54,    55,
+      72,    51,    52,    73,    51,    52,    74,    51,    52,    75,
+      51,    52,    76,    51,    52,    77,    51,    52,    78,    51,
+      52,     0,     0,    53,    54,    55,    53,    54,    55,    53,
+      54,    55,    53,    54,    55,    53,    54,    55,    53,    54,
+      55,    53,    54,    55,    37,    38,    39,    46,    47,    48,
+      49,     0,    57,     0,    58,    59,    60,    61,    62,    63,
+      64,    65,     0,     0,     0,     0,     0,     0,    40,    41
 };
 
-static const yysigned_char yycheck[] =
+static const yytype_int8 yycheck[] =
 {
-       0,    29,    29,     3,     4,     5,    29,     7,     8,     9,
+       0,     1,    28,     3,    28,     5,     6,    28,    28,     9,
       10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
-      20,    21,    22,    23,    24,    25,    37,    28,     6,    -1,
-      29,     6,    29,    44,    45,    46,    47,    29,    29,    -1,
-      -1,    -1,    -1,    54,    -1,    56,    57,    58,    59,    60,
-      61,    26,    -1,    28,    29,    31,    32,    33,    34,    -1,
-      36,    -1,    38,    39,    40,    41,    42,    43
+      20,    21,    22,    23,    24,     3,     4,     5,    28,     3,
+       4,     5,     3,     4,     5,     3,     4,     5,     3,     4,
+       5,     3,     4,     5,     3,     4,     5,    28,    26,    27,
+      28,    -1,    26,    27,    28,    26,    27,    28,    26,    27,
+      28,    26,    27,    28,    26,    27,    28,    26,    27,    28,
+       3,     4,     5,     3,     4,     5,     3,     4,     5,     3,
+       4,     5,     3,     4,     5,     3,     4,     5,     3,     4,
+       5,    -1,    -1,    26,    27,    28,    26,    27,    28,    26,
+      27,    28,    26,    27,    28,    26,    27,    28,    26,    27,
+      28,    26,    27,    28,     3,     4,     5,    31,    32,    33,
+      34,    -1,    36,    -1,    38,    39,    40,    41,    42,    43,
+      44,    45,    -1,    -1,    -1,    -1,    -1,    -1,    27,    28
 };
 
 /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
    symbol of state STATE-NUM.  */
-static const unsigned char yystos[] =
+static const yytype_uint8 yystos[] =
 {
-       0,    31,     0,     3,     4,     5,     7,     8,     9,    10,
-      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
-      21,    22,    23,    24,    25,    32,    34,    35,    36,    37,
-      38,    39,    40,    41,    42,    43,    29,    29,    29,    28,
-      29,    29,    29,    29,    43,    43,    43,    43,     6,    26,
-      28,    29,    33,    44,    43,    33,    43,    43,    43,    43,
-      43,    43,    33,    33,    33,    33,    33,    33,    33,    33,
-      33,    33,    33
+       0,    30,     0,     1,     3,     5,     6,     9,    10,    11,
+      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
+      22,    23,    24,    28,    31,    32,    33,    34,    35,    36,
+      37,    38,    39,    40,    41,    42,    28,     3,     4,     5,
+      27,    28,    28,    28,    28,    28,    42,    42,    42,    42,
+       3,     4,     5,    26,    27,    28,    43,    42,    42,    42,
+      42,    42,    42,    42,    42,    42,     3,     3,     3,     3,
+       3,     3,     3,     3,     3,     3,     3,     3,     3
 };
 
-#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
-# define YYSIZE_T __SIZE_TYPE__
-#endif
-#if ! defined (YYSIZE_T) && defined (size_t)
-# define YYSIZE_T size_t
-#endif
-#if ! defined (YYSIZE_T)
-# if defined (__STDC__) || defined (__cplusplus)
-#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
-#  define YYSIZE_T size_t
-# endif
-#endif
-#if ! defined (YYSIZE_T)
-# define YYSIZE_T unsigned int
-#endif
-
 #define yyerrok         (yyerrstatus = 0)
 #define yyclearin       (yychar = YYEMPTY)
 #define YYEMPTY         (-2)
@@ -609,30 +730,63 @@ do                                                              \
       yychar = (Token);                                         \
       yylval = (Value);                                         \
       yytoken = YYTRANSLATE (yychar);                           \
-      YYPOPSTACK;                                               \
+      YYPOPSTACK (1);                                           \
       goto yybackup;                                            \
     }                                                           \
   else                                                          \
     {                                                           \
-      yyerror ("syntax error: cannot back up");\
+      yyerror (YY_("syntax error: cannot back up")); \
       YYERROR;                                                  \
     }                                                           \
-while (0)
+while (YYID (0))
+
 
 #define YYTERROR        1
 #define YYERRCODE       256
 
-/* YYLLOC_DEFAULT -- Compute the default location (before the actions
-   are run).  */
 
+/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
+   If N is 0, then set CURRENT to the empty location which ends
+   the previous symbol: RHS[0] (always defined).  */
+
+#define YYRHSLOC(Rhs, K) ((Rhs)[K])
 #ifndef YYLLOC_DEFAULT
-# define YYLLOC_DEFAULT(Current, Rhs, N)                \
-   ((Current).first_line   = (Rhs)[1].first_line,       \
-    (Current).first_column = (Rhs)[1].first_column,     \
-    (Current).last_line    = (Rhs)[N].last_line,        \
-    (Current).last_column  = (Rhs)[N].last_column)
+# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
+    do                                                                  \
+      if (YYID (N))                                                    \
+        {                                                               \
+          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
+          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
+          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
+          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
+        }                                                               \
+      else                                                              \
+        {                                                               \
+          (Current).first_line   = (Current).last_line   =              \
+            YYRHSLOC (Rhs, 0).last_line;                                \
+          (Current).first_column = (Current).last_column =              \
+            YYRHSLOC (Rhs, 0).last_column;                              \
+        }                                                               \
+    while (YYID (0))
+#endif
+
+
+/* YY_LOCATION_PRINT -- Print the location on the stream.
+   This macro was not mandated originally: define only if we know
+   we won't break user code: when these are the locations we know.  */
+
+#ifndef YY_LOCATION_PRINT
+# if YYLTYPE_IS_TRIVIAL
+#  define YY_LOCATION_PRINT(File, Loc)                  \
+     fprintf (File, "%d.%d-%d.%d",                      \
+              (Loc).first_line, (Loc).first_column,     \
+              (Loc).last_line,  (Loc).last_column)
+# else
+#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
+# endif
 #endif
 
+
 /* YYLEX -- calling `yylex' with the right arguments.  */
 
 #ifdef YYLEX_PARAM
@@ -653,42 +807,96 @@ while (0)
 do {                                            \
   if (yydebug)                                  \
     YYFPRINTF Args;                             \
-} while (0)
+} while (YYID (0))
 
-# define YYDSYMPRINT(Args)                      \
-do {                                            \
-  if (yydebug)                                  \
-    yysymprint Args;                            \
-} while (0)
+# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
+do {                                                                      \
+  if (yydebug)                                                            \
+    {                                                                     \
+      YYFPRINTF (stderr, "%s ", Title);                                   \
+      yy_symbol_print (stderr,                                            \
+                  Type, Value); \
+      YYFPRINTF (stderr, "\n");                                           \
+    }                                                                     \
+} while (YYID (0))
 
-# define YYDSYMPRINTF(Title, Token, Value, Location)            \
-do {                                                            \
-  if (yydebug)                                                  \
-    {                                                           \
-      YYFPRINTF (stderr, "%s ", Title);                         \
-      yysymprint (stderr,                                       \
-                  Token, Value);        \
-      YYFPRINTF (stderr, "\n");                                 \
-    }                                                           \
-} while (0)
+
+/*--------------------------------.
+| Print this symbol on YYOUTPUT.  |
+`--------------------------------*/
+
+/*ARGSUSED*/
+#if (defined __STDC__ || defined __C99__FUNC__ \
+     || defined __cplusplus || defined _MSC_VER)
+static void
+yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
+#else
+static void
+yy_symbol_value_print (yyoutput, yytype, yyvaluep)
+    FILE *yyoutput;
+    int yytype;
+    YYSTYPE const * const yyvaluep;
+#endif
+{
+  if (!yyvaluep)
+    return;
+# ifdef YYPRINT
+  if (yytype < YYNTOKENS)
+    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
+# else
+  YYUSE (yyoutput);
+# endif
+  switch (yytype)
+    {
+      default:
+        break;
+    }
+}
+
+
+/*--------------------------------.
+| Print this symbol on YYOUTPUT.  |
+`--------------------------------*/
+
+#if (defined __STDC__ || defined __C99__FUNC__ \
+     || defined __cplusplus || defined _MSC_VER)
+static void
+yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
+#else
+static void
+yy_symbol_print (yyoutput, yytype, yyvaluep)
+    FILE *yyoutput;
+    int yytype;
+    YYSTYPE const * const yyvaluep;
+#endif
+{
+  if (yytype < YYNTOKENS)
+    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
+  else
+    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);
+
+  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
+  YYFPRINTF (yyoutput, ")");
+}
 
 /*------------------------------------------------------------------.
 | yy_stack_print -- Print the state stack from its BOTTOM up to its |
 | TOP (included).                                                   |
 `------------------------------------------------------------------*/
 
-#if defined (__STDC__) || defined (__cplusplus)
+#if (defined __STDC__ || defined __C99__FUNC__ \
+     || defined __cplusplus || defined _MSC_VER)
 static void
-yy_stack_print (short int *bottom, short int *top)
+yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
 #else
 static void
 yy_stack_print (bottom, top)
-    short int *bottom;
-    short int *top;
+    yytype_int16 *bottom;
+    yytype_int16 *top;
 #endif
 {
   YYFPRINTF (stderr, "Stack now");
-  for (/* Nothing. */; bottom <= top; ++bottom)
+  for (; bottom <= top; ++bottom)
     YYFPRINTF (stderr, " %d", *bottom);
   YYFPRINTF (stderr, "\n");
 }
@@ -697,45 +905,52 @@ yy_stack_print (bottom, top)
 do {                                                            \
   if (yydebug)                                                  \
     yy_stack_print ((Bottom), (Top));                           \
-} while (0)
+} while (YYID (0))
 
 
 /*------------------------------------------------.
 | Report that the YYRULE is going to be reduced.  |
 `------------------------------------------------*/
 
-#if defined (__STDC__) || defined (__cplusplus)
+#if (defined __STDC__ || defined __C99__FUNC__ \
+     || defined __cplusplus || defined _MSC_VER)
 static void
-yy_reduce_print (int yyrule)
+yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
 #else
 static void
-yy_reduce_print (yyrule)
+yy_reduce_print (yyvsp, yyrule)
+    YYSTYPE *yyvsp;
     int yyrule;
 #endif
 {
+  int yynrhs = yyr2[yyrule];
   int yyi;
-  unsigned int yylno = yyrline[yyrule];
-  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
+  unsigned long int yylno = yyrline[yyrule];
+  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
              yyrule - 1, yylno);
-  /* Print the symbols being reduced, and their result.  */
-  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
-    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
-  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
+  /* The symbols being reduced.  */
+  for (yyi = 0; yyi < yynrhs; yyi++)
+    {
+      fprintf (stderr, "   $%d = ", yyi + 1);
+      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
+                       &(yyvsp[(yyi + 1) - (yynrhs)])
+                                       );
+      fprintf (stderr, "\n");
+    }
 }
 
 # define YY_REDUCE_PRINT(Rule)          \
 do {                                    \
   if (yydebug)                          \
-    yy_reduce_print (Rule);             \
-} while (0)
+    yy_reduce_print (yyvsp, Rule); \
+} while (YYID (0))
 
 /* Nonzero means print parse trace.  It is left uninitialized so that
    multiple parsers can coexist.  */
 int yydebug;
 #else /* !YYDEBUG */
 # define YYDPRINTF(Args)
-# define YYDSYMPRINT(Args)
-# define YYDSYMPRINTF(Title, Token, Value, Location)
+# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
 # define YY_STACK_PRINT(Bottom, Top)
 # define YY_REDUCE_PRINT(Rule)
 #endif /* !YYDEBUG */
@@ -750,13 +965,9 @@ int yydebug;
    if the built-in stack extension method is used).
 
    Do not make this value too large; the results are undefined if
-   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
+   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
    evaluated with infinite-precision integer arithmetic.  */
 
-#if defined (YYMAXDEPTH) && YYMAXDEPTH == 0
-# undef YYMAXDEPTH
-#endif
-
 #ifndef YYMAXDEPTH
 # define YYMAXDEPTH 10000
 #endif
@@ -766,45 +977,47 @@ int yydebug;
 #if YYERROR_VERBOSE
 
 # ifndef yystrlen
-#  if defined (__GLIBC__) && defined (_STRING_H)
+#  if defined __GLIBC__ && defined _STRING_H
 #   define yystrlen strlen
 #  else
 /* Return the length of YYSTR.  */
+#if (defined __STDC__ || defined __C99__FUNC__ \
+     || defined __cplusplus || defined _MSC_VER)
 static YYSIZE_T
-#   if defined (__STDC__) || defined (__cplusplus)
 yystrlen (const char *yystr)
-#   else
+#else
+static YYSIZE_T
 yystrlen (yystr)
-     const char *yystr;
-#   endif
+    const char *yystr;
+#endif
 {
-  register const char *yys = yystr;
-
-  while (*yys++ != '\0')
+  YYSIZE_T yylen;
+  for (yylen = 0; yystr[yylen]; yylen++)
     continue;
-
-  return yys - yystr - 1;
+  return yylen;
 }
 #  endif
 # endif
 
 # ifndef yystpcpy
-#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
+#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
 #   define yystpcpy stpcpy
 #  else
 /* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
    YYDEST.  */
+#if (defined __STDC__ || defined __C99__FUNC__ \
+     || defined __cplusplus || defined _MSC_VER)
 static char *
-#   if defined (__STDC__) || defined (__cplusplus)
 yystpcpy (char *yydest, const char *yysrc)
-#   else
+#else
+static char *
 yystpcpy (yydest, yysrc)
-     char *yydest;
-     const char *yysrc;
-#   endif
+    char *yydest;
+    const char *yysrc;
+#endif
 {
-  register char *yyd = yydest;
-  register const char *yys = yysrc;
+  char *yyd = yydest;
+  const char *yys = yysrc;
 
   while ((*yyd++ = *yys++) != '\0')
     continue;
@@ -814,64 +1027,186 @@ yystpcpy (yydest, yysrc)
 #  endif
 # endif
 
-#endif /* !YYERROR_VERBOSE */
+# ifndef yytnamerr
+/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
+   quotes and backslashes, so that it's suitable for yyerror.  The
+   heuristic is that double-quoting is unnecessary unless the string
+   contains an apostrophe, a comma, or backslash (other than
+   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
+   null, do not copy; instead, return the length of what the result
+   would have been.  */
+static YYSIZE_T
+yytnamerr (char *yyres, const char *yystr)
+{
+  if (*yystr == '"')
+    {
+      YYSIZE_T yyn = 0;
+      char const *yyp = yystr;
+
+      for (;;)
+        switch (*++yyp)
+          {
+          case '\'':
+          case ',':
+            goto do_not_strip_quotes;
+
+          case '\\':
+            if (*++yyp != '\\')
+              goto do_not_strip_quotes;
+            /* Fall through.  */
+          default:
+            if (yyres)
+              yyres[yyn] = *yyp;
+            yyn++;
+            break;
+
+          case '"':
+            if (yyres)
+              yyres[yyn] = '\0';
+            return yyn;
+          }
+    do_not_strip_quotes: ;
+    }
 
-
+  if (! yyres)
+    return yystrlen (yystr);
 
-#if YYDEBUG
-/*--------------------------------.
-| Print this symbol on YYOUTPUT.  |
-`--------------------------------*/
+  return yystpcpy (yyres, yystr) - yyres;
+}
+# endif
 
-#if defined (__STDC__) || defined (__cplusplus)
-static void
-yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
-#else
-static void
-yysymprint (yyoutput, yytype, yyvaluep)
-    FILE *yyoutput;
-    int yytype;
-    YYSTYPE *yyvaluep;
-#endif
+/* Copy into YYRESULT an error message about the unexpected token
+   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
+   including the terminating null byte.  If YYRESULT is null, do not
+   copy anything; just return the number of bytes that would be
+   copied.  As a special case, return 0 if an ordinary "syntax error"
+   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
+   size calculation.  */
+static YYSIZE_T
+yysyntax_error (char *yyresult, int yystate, int yychar)
 {
-  /* Pacify ``unused variable'' warnings.  */
-  (void) yyvaluep;
+  int yyn = yypact[yystate];
 
-  if (yytype < YYNTOKENS)
-    {
-      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
-# ifdef YYPRINT
-      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
-# endif
-    }
+  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
+    return 0;
   else
-    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);
-
-  switch (yytype)
     {
-      default:
-        break;
+      int yytype = YYTRANSLATE (yychar);
+      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
+      YYSIZE_T yysize = yysize0;
+      YYSIZE_T yysize1;
+      int yysize_overflow = 0;
+      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
+      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
+      int yyx;
+
+# if 0
+      /* This is so xgettext sees the translatable formats that are
+         constructed on the fly.  */
+      YY_("syntax error, unexpected %s");
+      YY_("syntax error, unexpected %s, expecting %s");
+      YY_("syntax error, unexpected %s, expecting %s or %s");
+      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
+      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
+# endif
+      char *yyfmt;
+      char const *yyf;
+      static char const yyunexpected[] = "syntax error, unexpected %s";
+      static char const yyexpecting[] = ", expecting %s";
+      static char const yyor[] = " or %s";
+      char yyformat[sizeof yyunexpected
+                    + sizeof yyexpecting - 1
+                    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
+                       * (sizeof yyor - 1))];
+      char const *yyprefix = yyexpecting;
+
+      /* Start YYX at -YYN if negative to avoid negative indexes in
+         YYCHECK.  */
+      int yyxbegin = yyn < 0 ? -yyn : 0;
+
+      /* Stay within bounds of both yycheck and yytname.  */
+      int yychecklim = YYLAST - yyn + 1;
+      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
+      int yycount = 1;
+
+      yyarg[0] = yytname[yytype];
+      yyfmt = yystpcpy (yyformat, yyunexpected);
+
+      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
+        if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
+          {
+            if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
+              {
+                yycount = 1;
+                yysize = yysize0;
+                yyformat[sizeof yyunexpected - 1] = '\0';
+                break;
+              }
+            yyarg[yycount++] = yytname[yyx];
+            yysize1 = yysize + yytnamerr (0, yytname[yyx]);
+            yysize_overflow |= (yysize1 < yysize);
+            yysize = yysize1;
+            yyfmt = yystpcpy (yyfmt, yyprefix);
+            yyprefix = yyor;
+          }
+
+      yyf = YY_(yyformat);
+      yysize1 = yysize + yystrlen (yyf);
+      yysize_overflow |= (yysize1 < yysize);
+      yysize = yysize1;
+
+      if (yysize_overflow)
+        return YYSIZE_MAXIMUM;
+
+      if (yyresult)
+        {
+          /* Avoid sprintf, as that infringes on the user's name space.
+             Don't have undefined behavior even if the translation
+             produced a string with the wrong number of "%s"s.  */
+          char *yyp = yyresult;
+          int yyi = 0;
+          while ((*yyp = *yyf) != '\0')
+            {
+              if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
+                {
+                  yyp += yytnamerr (yyp, yyarg[yyi++]);
+                  yyf += 2;
+                }
+              else
+                {
+                  yyp++;
+                  yyf++;
+                }
+            }
+        }
+      return yysize;
     }
-  YYFPRINTF (yyoutput, ")");
 }
+#endif /* YYERROR_VERBOSE */
+
 
-#endif /* ! YYDEBUG */
 /*-----------------------------------------------.
 | Release the memory associated to this symbol.  |
 `-----------------------------------------------*/
 
-#if defined (__STDC__) || defined (__cplusplus)
+/*ARGSUSED*/
+#if (defined __STDC__ || defined __C99__FUNC__ \
+     || defined __cplusplus || defined _MSC_VER)
 static void
-yydestruct (int yytype, YYSTYPE *yyvaluep)
+yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
 #else
 static void
-yydestruct (yytype, yyvaluep)
+yydestruct (yymsg, yytype, yyvaluep)
+    const char *yymsg;
     int yytype;
     YYSTYPE *yyvaluep;
 #endif
 {
-  /* Pacify ``unused variable'' warnings.  */
-  (void) yyvaluep;
+  YYUSE (yyvaluep);
+
+  if (!yymsg)
+    yymsg = "Deleting";
+  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);
 
   switch (yytype)
     {
@@ -885,13 +1220,13 @@ yydestruct (yytype, yyvaluep)
 /* Prevent warnings from -Wmissing-prototypes.  */
 
 #ifdef YYPARSE_PARAM
-# if defined (__STDC__) || defined (__cplusplus)
+#if defined __STDC__ || defined __cplusplus
 int yyparse (void *YYPARSE_PARAM);
-# else
+#else
 int yyparse ();
-# endif
+#endif
 #else /* ! YYPARSE_PARAM */
-#if defined (__STDC__) || defined (__cplusplus)
+#if defined __STDC__ || defined __cplusplus
 int yyparse (void);
 #else
 int yyparse ();
@@ -908,14 +1243,18 @@ int yyparse ();
 `----------*/
 
 #ifdef YYPARSE_PARAM
-# if defined (__STDC__) || defined (__cplusplus)
-int yyparse (void *YYPARSE_PARAM)
-# else
-int yyparse (YYPARSE_PARAM)
-  void *YYPARSE_PARAM;
-# endif
+#if (defined __STDC__ || defined __C99__FUNC__ \
+     || defined __cplusplus || defined _MSC_VER)
+int
+yyparse (void *YYPARSE_PARAM)
+#else
+int
+yyparse (YYPARSE_PARAM)
+    void *YYPARSE_PARAM;
+#endif
 #else /* ! YYPARSE_PARAM */
-#if defined (__STDC__) || defined (__cplusplus)
+#if (defined __STDC__ || defined __C99__FUNC__ \
+     || defined __cplusplus || defined _MSC_VER)
 int
 yyparse (void)
 #else
@@ -925,22 +1264,28 @@ yyparse ()
 #endif
 #endif
 {
-  /* The lookahead symbol.  */
+  /* The look-ahead symbol.  */
 int yychar;
 
-/* The semantic value of the lookahead symbol.  */
+/* The semantic value of the look-ahead symbol.  */
 YYSTYPE yylval;
 
 /* Number of syntax errors so far.  */
 int yynerrs;
 
-  register int yystate;
-  register int yyn;
+  int yystate;
+  int yyn;
   int yyresult;
   /* Number of tokens to shift before error messages enabled.  */
   int yyerrstatus;
-  /* Lookahead token as an internal (translated) token number.  */
+  /* Look-ahead token as an internal (translated) token number.  */
   int yytoken = 0;
+#if YYERROR_VERBOSE
+  /* Buffer for error messages, and its allocated size.  */
+  char yymsgbuf[128];
+  char *yymsg = yymsgbuf;
+  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
+#endif
 
   /* Three stacks and their tools:
      `yyss': related to states,
@@ -951,18 +1296,18 @@ int yynerrs;
      to reallocate them elsewhere.  */
 
   /* The state stack.  */
-  short int yyssa[YYINITDEPTH];
-  short int *yyss = yyssa;
-  register short int *yyssp;
+  yytype_int16 yyssa[YYINITDEPTH];
+  yytype_int16 *yyss = yyssa;
+  yytype_int16 *yyssp;
 
   /* The semantic value stack.  */
   YYSTYPE yyvsa[YYINITDEPTH];
   YYSTYPE *yyvs = yyvsa;
-  register YYSTYPE *yyvsp;
+  YYSTYPE *yyvsp;
 
 
 
-#define YYPOPSTACK   (yyvsp--, yyssp--)
+#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))
 
   YYSIZE_T yystacksize = YYINITDEPTH;
 
@@ -971,9 +1316,9 @@ int yynerrs;
   YYSTYPE yyval;
 
 
-  /* When reducing, the number of symbols on the RHS of the reduced
-     rule.  */
-  int yylen;
+  /* The number of symbols on the RHS of the reduced rule.
+     Keep to zero when no symbol should be popped.  */
+  int yylen = 0;
 
   YYDPRINTF ((stderr, "Starting parse\n"));
 
@@ -990,16 +1335,14 @@ int yynerrs;
   yyssp = yyss;
   yyvsp = yyvs;
 
-
   goto yysetstate;
 
 /*------------------------------------------------------------.
 | yynewstate -- Push a new state, which is found in yystate.  |
 `------------------------------------------------------------*/
  yynewstate:
   /* In all cases, when you get here, the value and location stacks
-     have just been pushed. so pushing a state here evens the stacks.
-     */
+     have just been pushed.  So pushing a state here evens the stacks.  */
   yyssp++;
 
  yysetstate:
@@ -1012,18 +1355,18 @@ int yynerrs;
 
 #ifdef yyoverflow
       {
-        /* Give user a chance to reallocate the stack. Use copies of
+        /* Give user a chance to reallocate the stack.  Use copies of
            these so that the &'s don't force the real ones into
            memory.  */
         YYSTYPE *yyvs1 = yyvs;
-        short int *yyss1 = yyss;
+        yytype_int16 *yyss1 = yyss;
 
 
         /* Each stack pointer address is followed by the size of the
            data in use in that stack, in bytes.  This used to be a
            conditional around just the two extra args, but that might
            be undefined if yyoverflow is a macro.  */
-        yyoverflow ("parser stack overflow",
+        yyoverflow (YY_("memory exhausted"),
                     &yyss1, yysize * sizeof (*yyssp),
                     &yyvs1, yysize * sizeof (*yyvsp),
 
@@ -1034,21 +1377,21 @@ int yynerrs;
       }
 #else /* no yyoverflow */
 # ifndef YYSTACK_RELOCATE
-      goto yyoverflowlab;
+      goto yyexhaustedlab;
 # else
       /* Extend the stack our own way.  */
       if (YYMAXDEPTH <= yystacksize)
-        goto yyoverflowlab;
+        goto yyexhaustedlab;
       yystacksize *= 2;
       if (YYMAXDEPTH < yystacksize)
         yystacksize = YYMAXDEPTH;
 
       {
-        short int *yyss1 = yyss;
+        yytype_int16 *yyss1 = yyss;
         union yyalloc *yyptr =
           (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
         if (! yyptr)
-          goto yyoverflowlab;
+          goto yyexhaustedlab;
         YYSTACK_RELOCATE (yyss);
         YYSTACK_RELOCATE (yyvs);
 
@@ -1079,19 +1422,17 @@ int yynerrs;
 `-----------*/
 yybackup:
 
-/* Do appropriate processing given the current state.  */
-/* Read a lookahead token if we need one and don't already have one.  */
-/* yyresume: */
-
-  /* First try to decide what to do without reference to lookahead token.  */
+  /* Do appropriate processing given the current state.  Read a
+     look-ahead token if we need one and don't already have one.  */
 
+  /* First try to decide what to do without reference to look-ahead token.  */
   yyn = yypact[yystate];
   if (yyn == YYPACT_NINF)
     goto yydefault;
 
-  /* Not known => get a lookahead token if don't already have one.  */
+  /* Not known => get a look-ahead token if don't already have one.  */
 
-  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
+  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
   if (yychar == YYEMPTY)
     {
       YYDPRINTF ((stderr, "Reading a token: "));
@@ -1106,7 +1447,7 @@ int yynerrs;
   else
     {
       yytoken = YYTRANSLATE (yychar);
-      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
+      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
     }
 
   /* If the proper action on seeing token YYTOKEN is to reduce or to
@@ -1126,22 +1467,21 @@ int yynerrs;
   if (yyn == YYFINAL)
     YYACCEPT;
 
-  /* Shift the lookahead token.  */
-  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));
-
-  /* Discard the token being shifted unless it is eof.  */
-  if (yychar != YYEOF)
-    yychar = YYEMPTY;
-
-  *++yyvsp = yylval;
-
-
   /* Count tokens shifted since error; after three, turn off error
      status.  */
   if (yyerrstatus)
     yyerrstatus--;
 
+  /* Shift the look-ahead token.  */
+  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
+
+  /* Discard the shifted token unless it is eof.  */
+  if (yychar != YYEOF)
+    yychar = YYEMPTY;
+
   yystate = yyn;
+  *++yyvsp = yylval;
+
   goto yynewstate;
 
 
@@ -1176,121 +1516,149 @@ int yynerrs;
   YY_REDUCE_PRINT (yyn);
   switch (yyn)
     {
-        case 4:
-#line 97 "cmDependsFortranParser.y"
+        case 7:
+#line 108 "cmDependsFortranParser.y"
     {
-    cmDependsFortranParser* parser = cmDependsFortran_yyget_extra(yyscanner);
-    cmDependsFortranParser_RuleUse(parser, yyvsp[-2].string);
-    free(yyvsp[-2].string);
+    if (strcasecmp((yyvsp[(1) - (2)].string), "interface") == 0)
+      {
+      cmDependsFortranParser* parser = cmDependsFortran_yyget_extra(yyscanner);
+      cmDependsFortranParser_SetInInterface(parser, true);
+      }
+    free((yyvsp[(1) - (2)].string));
     }
     break;
 
-  case 5:
-#line 103 "cmDependsFortranParser.y"
+  case 8:
+#line 117 "cmDependsFortranParser.y"
     {
-    cmDependsFortranParser* parser = cmDependsFortran_yyget_extra(yyscanner);
-    cmDependsFortranParser_RuleInclude(parser, yyvsp[-2].string);
-    free(yyvsp[-2].string);
+    if (strcasecmp((yyvsp[(1) - (4)].string), "use") == 0)
+      {
+      cmDependsFortranParser* parser = cmDependsFortran_yyget_extra(yyscanner);
+      cmDependsFortranParser_RuleUse(parser, (yyvsp[(2) - (4)].string));
+      free((yyvsp[(2) - (4)].string));
+      }
+    else if (strcasecmp((yyvsp[(1) - (4)].string), "module") == 0)
+      {
+      cmDependsFortranParser* parser = cmDependsFortran_yyget_extra(yyscanner);
+      cmDependsFortranParser_RuleModule(parser, (yyvsp[(2) - (4)].string));
+      free((yyvsp[(2) - (4)].string));
+      }
+    else if (strcasecmp((yyvsp[(1) - (4)].string), "interface") == 0)
+      {
+      cmDependsFortranParser* parser = cmDependsFortran_yyget_extra(yyscanner);
+      cmDependsFortranParser_SetInInterface(parser, true);
+      free((yyvsp[(2) - (4)].string));
+      }
+    else if (strcasecmp((yyvsp[(2) - (4)].string), "interface") == 0 && strcasecmp((yyvsp[(1) - (4)].string), "end") == 0)
+      {
+      cmDependsFortranParser* parser = cmDependsFortran_yyget_extra(yyscanner);
+      cmDependsFortranParser_SetInInterface(parser, false);
+      free((yyvsp[(2) - (4)].string));
+      }
+    free((yyvsp[(1) - (4)].string));
     }
     break;
 
-  case 7:
-#line 110 "cmDependsFortranParser.y"
+  case 9:
+#line 145 "cmDependsFortranParser.y"
     {
-    cmDependsFortranParser* parser = cmDependsFortran_yyget_extra(yyscanner);
-    cmDependsFortranParser_RuleModule(parser, yyvsp[-1].string);
-    free(yyvsp[-1].string);
+    if (strcasecmp((yyvsp[(1) - (4)].string), "include") == 0)
+      {
+      cmDependsFortranParser* parser = cmDependsFortran_yyget_extra(yyscanner);
+      cmDependsFortranParser_RuleInclude(parser, (yyvsp[(2) - (4)].string));
+      }
+    free((yyvsp[(1) - (4)].string));
+    free((yyvsp[(2) - (4)].string));
     }
     break;
 
-  case 8:
-#line 116 "cmDependsFortranParser.y"
+  case 11:
+#line 156 "cmDependsFortranParser.y"
     {
     cmDependsFortranParser* parser = cmDependsFortran_yyget_extra(yyscanner);
-    cmDependsFortranParser_RuleDefine(parser, yyvsp[-2].string);
-    free(yyvsp[-2].string);
+    cmDependsFortranParser_RuleDefine(parser, (yyvsp[(2) - (4)].string));
+    free((yyvsp[(2) - (4)].string));
     }
     break;
 
-  case 9:
-#line 122 "cmDependsFortranParser.y"
+  case 12:
+#line 162 "cmDependsFortranParser.y"
     {
     cmDependsFortranParser* parser = cmDependsFortran_yyget_extra(yyscanner);
-    cmDependsFortranParser_RuleUndef(parser, yyvsp[-2].string);
-    free(yyvsp[-2].string);
+    cmDependsFortranParser_RuleUndef(parser, (yyvsp[(2) - (4)].string));
+    free((yyvsp[(2) - (4)].string));
     }
     break;
 
-  case 10:
-#line 128 "cmDependsFortranParser.y"
+  case 13:
+#line 168 "cmDependsFortranParser.y"
     {
     cmDependsFortranParser* parser = cmDependsFortran_yyget_extra(yyscanner);
-    cmDependsFortranParser_RuleIfdef(parser, yyvsp[-2].string);
-    free(yyvsp[-2].string);
+    cmDependsFortranParser_RuleIfdef(parser, (yyvsp[(2) - (4)].string));
+    free((yyvsp[(2) - (4)].string));
     }
     break;
 
-  case 11:
-#line 134 "cmDependsFortranParser.y"
+  case 14:
+#line 174 "cmDependsFortranParser.y"
     {
     cmDependsFortranParser* parser = cmDependsFortran_yyget_extra(yyscanner);
-    cmDependsFortranParser_RuleIfndef(parser, yyvsp[-2].string);
-    free(yyvsp[-2].string);
+    cmDependsFortranParser_RuleIfndef(parser, (yyvsp[(2) - (4)].string));
+    free((yyvsp[(2) - (4)].string));
     }
     break;
 
-  case 12:
-#line 140 "cmDependsFortranParser.y"
+  case 15:
+#line 180 "cmDependsFortranParser.y"
     {
     cmDependsFortranParser* parser = cmDependsFortran_yyget_extra(yyscanner);
     cmDependsFortranParser_RuleIf(parser);
     }
     break;
 
-  case 13:
-#line 145 "cmDependsFortranParser.y"
+  case 16:
+#line 185 "cmDependsFortranParser.y"
     {
     cmDependsFortranParser* parser = cmDependsFortran_yyget_extra(yyscanner);
     cmDependsFortranParser_RuleElif(parser);
     }
     break;
 
-  case 14:
-#line 150 "cmDependsFortranParser.y"
+  case 17:
+#line 190 "cmDependsFortranParser.y"
     {
     cmDependsFortranParser* parser = cmDependsFortran_yyget_extra(yyscanner);
     cmDependsFortranParser_RuleElse(parser);
     }
     break;
 
-  case 15:
-#line 155 "cmDependsFortranParser.y"
+  case 18:
+#line 195 "cmDependsFortranParser.y"
     {
     cmDependsFortranParser* parser = cmDependsFortran_yyget_extra(yyscanner);
     cmDependsFortranParser_RuleEndif(parser);
     }
     break;
 
   case 41:
-#line 175 "cmDependsFortranParser.y"
-    { free (yyvsp[0].string); }
+#line 219 "cmDependsFortranParser.y"
+    { free ((yyvsp[(1) - (1)].string)); }
     break;
 
   case 42:
-#line 176 "cmDependsFortranParser.y"
-    { free (yyvsp[0].string); }
+#line 220 "cmDependsFortranParser.y"
+    { free ((yyvsp[(1) - (1)].string)); }
     break;
 
 
+/* Line 1267 of yacc.c.  */
+#line 1656 "cmDependsFortranParser.cxx"
+      default: break;
     }
+  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);
 
-/* Line 1010 of yacc.c.  */
-#line 1277 "cmDependsFortranParser.cxx"
-
-  yyvsp -= yylen;
-  yyssp -= yylen;
-
-
+  YYPOPSTACK (yylen);
+  yylen = 0;
   YY_STACK_PRINT (yyss, yyssp);
 
   *++yyvsp = yyval;
@@ -1319,100 +1687,65 @@ int yynerrs;
   if (!yyerrstatus)
     {
       ++yynerrs;
-#if YYERROR_VERBOSE
-      yyn = yypact[yystate];
-
-      if (YYPACT_NINF < yyn && yyn < YYLAST)
-        {
-          YYSIZE_T yysize = 0;
-          int yytype = YYTRANSLATE (yychar);
-          const char* yyprefix;
-          char *yymsg;
-          int yyx;
-
-          /* Start YYX at -YYN if negative to avoid negative indexes in
-             YYCHECK.  */
-          int yyxbegin = yyn < 0 ? -yyn : 0;
-
-          /* Stay within bounds of both yycheck and yytname.  */
-          int yychecklim = YYLAST - yyn;
-          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
-          int yycount = 0;
-
-          yyprefix = ", expecting ";
-          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
-            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
+#if ! YYERROR_VERBOSE
+      yyerror (YY_("syntax error"));
+#else
+      {
+        YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
+        if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
+          {
+            YYSIZE_T yyalloc = 2 * yysize;
+            if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
+              yyalloc = YYSTACK_ALLOC_MAXIMUM;
+            if (yymsg != yymsgbuf)
+              YYSTACK_FREE (yymsg);
+            yymsg = (char *) YYSTACK_ALLOC (yyalloc);
+            if (yymsg)
+              yymsg_alloc = yyalloc;
+            else
               {
-                yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
-                yycount += 1;
-                if (yycount == 5)
-                  {
-                    yysize = 0;
-                    break;
-                  }
+                yymsg = yymsgbuf;
+                yymsg_alloc = sizeof yymsgbuf;
               }
-          yysize += (sizeof ("syntax error, unexpected ")
-                     + yystrlen (yytname[yytype]));
-          yymsg = (char *) YYSTACK_ALLOC (yysize);
-          if (yymsg != 0)
-            {
-              char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
-              yyp = yystpcpy (yyp, yytname[yytype]);
-
-              if (yycount < 5)
-                {
-                  yyprefix = ", expecting ";
-                  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
-                    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
-                      {
-                        yyp = yystpcpy (yyp, yyprefix);
-                        yyp = yystpcpy (yyp, yytname[yyx]);
-                        yyprefix = " or ";
-                      }
-                }
-              yyerror (yymsg);
-              YYSTACK_FREE (yymsg);
-            }
-          else
-            yyerror ("syntax error; also virtual memory exhausted");
-        }
-      else
-#endif /* YYERROR_VERBOSE */
-        yyerror ("syntax error");
+          }
+
+        if (0 < yysize && yysize <= yymsg_alloc)
+          {
+            (void) yysyntax_error (yymsg, yystate, yychar);
+            yyerror (yymsg);
+          }
+        else
+          {
+            yyerror (YY_("syntax error"));
+            if (yysize != 0)
+              goto yyexhaustedlab;
+          }
+      }
+#endif
     }
 
 
 
   if (yyerrstatus == 3)
     {
-      /* If just tried and failed to reuse lookahead token after an
+      /* If just tried and failed to reuse look-ahead token after an
          error, discard it.  */
 
       if (yychar <= YYEOF)
         {
-          /* If at end of input, pop the error token,
-             then the rest of the stack, then return failure.  */
+          /* Return failure if at end of input.  */
           if (yychar == YYEOF)
-             for (;;)
-               {
-                 YYPOPSTACK;
-                 if (yyssp == yyss)
-                   YYABORT;
-                 YYDSYMPRINTF ("Error: popping", yystos[*yyssp], 
-                               yyvsp, yylsp);
-                 yydestruct (yystos[*yyssp], yyvsp);
-               }
+            YYABORT;
         }
       else
         {
-          YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
-          yydestruct (yytoken, &yylval);
+          yydestruct ("Error: discarding",
+                      yytoken, &yylval);
           yychar = YYEMPTY;
-
         }
     }
 
-  /* Else will try to reuse lookahead token after shifting the error
+  /* Else will try to reuse look-ahead token after shifting the error
      token.  */
   goto yyerrlab1;
 
@@ -1422,15 +1755,17 @@ int yynerrs;
 `---------------------------------------------------*/
 yyerrorlab:
 
-#if defined(__GNUC__) || defined(__HP_aCC) || defined(__INTEL_COMPILER)
-  /* Pacify GCC when the user code never invokes YYERROR and the label
-     yyerrorlab therefore never appears in user code.  */
-  if (0)
+  /* Pacify compilers like GCC when the user code never invokes
+     YYERROR and the label yyerrorlab therefore never appears in user
+     code.  */
+  if (/*CONSTCOND*/ 0)
      goto yyerrorlab;
-#endif
 
-  yyvsp -= yylen;
-  yyssp -= yylen;
+  /* Do not reclaim the symbols of the rule which action triggered
+     this YYERROR.  */
+  YYPOPSTACK (yylen);
+  yylen = 0;
+  YY_STACK_PRINT (yyss, yyssp);
   yystate = *yyssp;
   goto yyerrlab1;
 
@@ -1459,21 +1794,23 @@ int yynerrs;
       if (yyssp == yyss)
         YYABORT;
 
-      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
-      yydestruct (yystos[yystate], yyvsp);
-      YYPOPSTACK;
+
+      yydestruct ("Error: popping",
+                  yystos[yystate], yyvsp);
+      YYPOPSTACK (1);
       yystate = *yyssp;
       YY_STACK_PRINT (yyss, yyssp);
     }
 
   if (yyn == YYFINAL)
     YYACCEPT;
 
-  YYDPRINTF ((stderr, "Shifting error token, "));
-
   *++yyvsp = yylval;
 
 
+  /* Shift the error token.  */
+  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);
+
   yystate = yyn;
   goto yynewstate;
 
@@ -1493,25 +1830,43 @@ int yynerrs;
   goto yyreturn;
 
 #ifndef yyoverflow
-/*----------------------------------------------.
-| yyoverflowlab -- parser overflow comes here.  |
-`----------------------------------------------*/
-yyoverflowlab:
-  yyerror ("parser stack overflow");
+/*-------------------------------------------------.
+| yyexhaustedlab -- memory exhaustion comes here.  |
+`-------------------------------------------------*/
+yyexhaustedlab:
+  yyerror (YY_("memory exhausted"));
   yyresult = 2;
   /* Fall through.  */
 #endif
 
 yyreturn:
+  if (yychar != YYEOF && yychar != YYEMPTY)
+     yydestruct ("Cleanup: discarding lookahead",
+                 yytoken, &yylval);
+  /* Do not reclaim the symbols of the rule which action triggered
+     this YYABORT or YYACCEPT.  */
+  YYPOPSTACK (yylen);
+  YY_STACK_PRINT (yyss, yyssp);
+  while (yyssp != yyss)
+    {
+      yydestruct ("Cleanup: popping",
+                  yystos[*yyssp], yyvsp);
+      YYPOPSTACK (1);
+    }
 #ifndef yyoverflow
   if (yyss != yyssa)
     YYSTACK_FREE (yyss);
 #endif
-  return yyresult;
+#if YYERROR_VERBOSE
+  if (yymsg != yymsgbuf)
+    YYSTACK_FREE (yymsg);
+#endif
+  /* Make sure YYID is used.  */
+  return YYID (yyresult);
 }
 
 
-#line 180 "cmDependsFortranParser.y"
+#line 226 "cmDependsFortranParser.y"
 
 /* End of grammar */
 