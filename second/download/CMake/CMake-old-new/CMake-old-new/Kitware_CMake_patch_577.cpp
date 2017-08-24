@@ -1,8 +1,7 @@
-/* A Bison parser, made by GNU Bison 1.875d.  */
+/* A Bison parser, made by GNU Bison 2.1.  */
 
 /* Skeleton parser for Yacc-like parsing with Bison,
-   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004 Free Software
-   Foundation, Inc.
+   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005 Free Software Foundation, Inc.
 
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
@@ -16,8 +15,8 @@
 
    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
-   Foundation, Inc., 59 Temple Place - Suite 330,
-   Boston, MA 02111-1307, USA.  */
+   Foundation, Inc., 51 Franklin Street, Fifth Floor,
+   Boston, MA 02110-1301, USA.  */
 
 /* As a special exception, when this file is copied by Bison into a
    Bison output file, you may use that output file without restriction.
@@ -37,6 +36,9 @@
 /* Identify Bison output.  */
 #define YYBISON 1
 
+/* Bison version.  */
+#define YYBISON_VERSION "2.1"
+
 /* Skeleton name.  */
 #define YYSKELETON_NAME "yacc.c"
 
@@ -46,8 +48,7 @@
 /* Using locations.  */
 #define YYLSP_NEEDED 0
 
-/* If NAME_PREFIX is specified substitute the variables and functions
-   names.  */
+/* Substitute the variable and function names.  */
 #define yyparse cmCommandArgument_yyparse
 #define yylex   cmCommandArgument_yylex
 #define yyerror cmCommandArgument_yyerror
@@ -76,6 +77,7 @@
      cal_ATNAME = 268
    };
 #endif
+/* Tokens.  */
 #define cal_NCURLY 258
 #define cal_DCURLY 259
 #define cal_DOLLAR 260
@@ -92,7 +94,7 @@
 
 
 /* Copy the first part of user declarations.  */
-
+#line 1 "cmCommandArgumentParser.y"
 
 /*=========================================================================
 
@@ -116,9 +118,7 @@ This file must be translated to C and modified to build everywhere.
 
 Run bison like this:
 
-  bison --yacc --name-prefix=cmCommandArgument_yy \
-    --defines=cmCommandArgumentParserTokens.h \
-    -ocmCommandArgumentParser.cxx cmCommandArgumentParser.y
+  bison --yacc --name-prefix=cmCommandArgument_yy --defines=cmCommandArgumentParserTokens.h -ocmCommandArgumentParser.cxx cmCommandArgumentParser.y
 
 Modify cmCommandArgumentParser.cxx:
   - remove TABs
@@ -156,7 +156,7 @@ static void cmCommandArgumentError(yyscan_t yyscanner, const char* message);
 #endif
 #ifdef _MSC_VER
 # pragma warning (disable: 4102) /* Unused goto label.  */
-# pragma warning (disable: 4065) /* Switch contains default but no case. */
+# pragma warning (disable: 4065) /* Switch statement contains default but no case. */
 #endif
 
 
@@ -173,6 +173,11 @@ static void cmCommandArgumentError(yyscan_t yyscanner, const char* message);
 # define YYERROR_VERBOSE 0
 #endif
 
+/* Enabling the token table.  */
+#ifndef YYTOKEN_TABLE
+# define YYTOKEN_TABLE 0
+#endif
+
 #if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
 typedef int YYSTYPE;
 # define yystype YYSTYPE /* obsolescent; will be withdrawn */
@@ -185,51 +190,96 @@ typedef int YYSTYPE;
 /* Copy the second part of user declarations.  */
 
 
-/* Line 214 of yacc.c.  */
+/* Line 219 of yacc.c.  */
+#line 195 "cmCommandArgumentParser.cxx"
 
+#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
+# define YYSIZE_T __SIZE_TYPE__
+#endif
+#if ! defined (YYSIZE_T) && defined (size_t)
+# define YYSIZE_T size_t
+#endif
+#if ! defined (YYSIZE_T) && (defined (__STDC__) || defined (__cplusplus))
+# include <stddef.h> /* INFRINGES ON USER NAME SPACE */
+# define YYSIZE_T size_t
+#endif
+#if ! defined (YYSIZE_T)
+# define YYSIZE_T unsigned int
+#endif
 
-#if ! defined (yyoverflow) || YYERROR_VERBOSE
-
-# ifndef YYFREE
-#  define YYFREE free
+#ifndef YY_
+# if YYENABLE_NLS
+#  if ENABLE_NLS
+#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
+#   define YY_(msgid) dgettext ("bison-runtime", msgid)
+#  endif
 # endif
-# ifndef YYMALLOC
-#  define YYMALLOC malloc
+# ifndef YY_
+#  define YY_(msgid) msgid
 # endif
+#endif
+
+#if ! defined (yyoverflow) || YYERROR_VERBOSE
 
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
+#   else
+#    define YYSTACK_ALLOC alloca
+#    if defined (__STDC__) || defined (__cplusplus)
+#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
+#     define YYINCLUDED_STDLIB_H
+#    endif
 #   endif
 #  endif
 # endif
 
 # ifdef YYSTACK_ALLOC
    /* Pacify GCC's `empty if-body' warning. */
 #  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
-# else
-#  if defined (__STDC__) || defined (__cplusplus)
-#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
-#   define YYSIZE_T size_t
+#  ifndef YYSTACK_ALLOC_MAXIMUM
+    /* The OS might guarantee only one guard page at the bottom of the stack,
+       and a page size can be as small as 4096 bytes.  So we cannot safely
+       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
+       to allow for a few compiler-allocated temporary stack slots.  */
+#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2005 */
 #  endif
+# else
 #  define YYSTACK_ALLOC YYMALLOC
 #  define YYSTACK_FREE YYFREE
+#  ifndef YYSTACK_ALLOC_MAXIMUM
+#   define YYSTACK_ALLOC_MAXIMUM ((YYSIZE_T) -1)
+#  endif
+#  ifdef __cplusplus
+extern "C" {
+#  endif
+#  ifndef YYMALLOC
+#   define YYMALLOC malloc
+#   if (! defined (malloc) && ! defined (YYINCLUDED_STDLIB_H) \
+        && (defined (__STDC__) || defined (__cplusplus)))
+void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
+#   endif
+#  endif
+#  ifndef YYFREE
+#   define YYFREE free
+#   if (! defined (free) && ! defined (YYINCLUDED_STDLIB_H) \
+        && (defined (__STDC__) || defined (__cplusplus)))
+void free (void *); /* INFRINGES ON USER NAME SPACE */
+#   endif
+#  endif
+#  ifdef __cplusplus
+}
+#  endif
 # endif
 #endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */
 
 
 #if (! defined (yyoverflow) \
      && (! defined (__cplusplus) \
-   || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))
+         || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))
 
 /* A type that is properly aligned for any stack member.  */
 union yyalloc
@@ -244,7 +294,7 @@ union yyalloc
 /* The size of an array large to enough to hold all stacks, each with
    N elements.  */
 # define YYSTACK_BYTES(N) \
-     ((N) * (sizeof (short int) + sizeof (YYSTYPE))      \
+     ((N) * (sizeof (short int) + sizeof (YYSTYPE))                     \
       + YYSTACK_GAP_MAXIMUM)
 
 /* Copy COUNT objects from FROM to TO.  The source and destination do
@@ -254,13 +304,13 @@ union yyalloc
 #   define YYCOPY(To, From, Count) \
       __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
 #  else
-#   define YYCOPY(To, From, Count)    \
-      do          \
-  {          \
-    register YYSIZE_T yyi;    \
-    for (yyi = 0; yyi < (Count); yyi++)  \
-      (To)[yyi] = (From)[yyi];    \
-  }          \
+#   define YYCOPY(To, From, Count)              \
+      do                                        \
+        {                                       \
+          YYSIZE_T yyi;                         \
+          for (yyi = 0; yyi < (Count); yyi++)   \
+            (To)[yyi] = (From)[yyi];            \
+        }                                       \
       while (0)
 #  endif
 # endif
@@ -270,15 +320,15 @@ union yyalloc
    elements in the stack, and YYPTR gives the new location of the
    stack.  Advance YYPTR to a properly aligned location for the next
    stack.  */
-# define YYSTACK_RELOCATE(Stack)          \
-    do                  \
-      {                  \
-  YYSIZE_T yynewbytes;            \
-  YYCOPY (&yyptr->Stack, Stack, yysize);        \
-  Stack = &yyptr->Stack;            \
-  yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
-  yyptr += yynewbytes / sizeof (*yyptr);        \
-      }                  \
+# define YYSTACK_RELOCATE(Stack)                                        \
+    do                                                                  \
+      {                                                                 \
+        YYSIZE_T yynewbytes;                                            \
+        YYCOPY (&yyptr->Stack, Stack, yysize);                          \
+        Stack = &yyptr->Stack;                                          \
+        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
+        yyptr += yynewbytes / sizeof (*yyptr);                          \
+      }                                                                 \
     while (0)
 
 #endif
@@ -307,7 +357,7 @@ union yyalloc
 #define YYUNDEFTOK  2
 #define YYMAXUTOK   268
 
-#define YYTRANSLATE(YYX)             \
+#define YYTRANSLATE(YYX)                                                \
   ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)
 
 /* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
@@ -371,14 +421,14 @@ static const unsigned char yyrline[] =
 };
 #endif
 
-#if YYDEBUG || YYERROR_VERBOSE
-/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
+#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
+/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
    First, the terminals, then, starting at YYNTOKENS, nonterminals. */
 static const char *const yytname[] =
 {
-  "$end", "error", "$undefined", "cal_NCURLY", "cal_DCURLY", "cal_DOLLAR",
-  "cal_LCURLY", "cal_RCURLY", "cal_NAME", "cal_BSLASH", "cal_SYMBOL",
-  "cal_AT", "cal_ERROR", "cal_ATNAME", "$accept", "Start",
+  "$end", "error", "$undefined", "cal_NCURLY", "cal_DCURLY", "\"$\"",
+  "\"{\"", "\"}\"", "cal_NAME", "\"\\\\\"", "cal_SYMBOL", "\"@\"",
+  "cal_ERROR", "cal_ATNAME", "$accept", "Start",
   "GoalWithOptionalBackSlash", "Goal", "String", "OuterText", "Variable",
   "MultipleIds", "ID", 0
 };
@@ -470,71 +520,88 @@ static const unsigned char yystos[] =
       21,     0,     9,    17,     7,    21,     7
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
-#define yyerrok    (yyerrstatus = 0)
-#define yyclearin  (yychar = YYEMPTY)
-#define YYEMPTY    (-2)
-#define YYEOF    0
+#define yyerrok         (yyerrstatus = 0)
+#define yyclearin       (yychar = YYEMPTY)
+#define YYEMPTY         (-2)
+#define YYEOF           0
 
-#define YYACCEPT  goto yyacceptlab
-#define YYABORT    goto yyabortlab
-#define YYERROR    goto yyerrorlab
+#define YYACCEPT        goto yyacceptlab
+#define YYABORT         goto yyabortlab
+#define YYERROR         goto yyerrorlab
 
 
 /* Like YYERROR except do call yyerror.  This remains here temporarily
    to ease the transition to the new meaning of YYERROR, for GCC.
    Once GCC version 2 has supplanted version 1, this can go.  */
 
-#define YYFAIL    goto yyerrlab
+#define YYFAIL          goto yyerrlab
 
 #define YYRECOVERING()  (!!yyerrstatus)
 
-#define YYBACKUP(Token, Value)          \
-do                \
-  if (yychar == YYEMPTY && yylen == 1)        \
-    {                \
-      yychar = (Token);            \
-      yylval = (Value);            \
-      yytoken = YYTRANSLATE (yychar);        \
-      YYPOPSTACK;            \
-      goto yybackup;            \
-    }                \
-  else                \
-    {                 \
-      yyerror ("syntax error: cannot back up");\
-      YYERROR;              \
-    }                \
+#define YYBACKUP(Token, Value)                                  \
+do                                                              \
+  if (yychar == YYEMPTY && yylen == 1)                          \
+    {                                                           \
+      yychar = (Token);                                         \
+      yylval = (Value);                                         \
+      yytoken = YYTRANSLATE (yychar);                           \
+      YYPOPSTACK;                                               \
+      goto yybackup;                                            \
+    }                                                           \
+  else                                                          \
+    {                                                           \
+      yyerror (YY_("syntax error: cannot back up")); \
+      YYERROR;                                                  \
+    }                                                           \
 while (0)
 
-#define YYTERROR  1
-#define YYERRCODE  256
 
-/* YYLLOC_DEFAULT -- Compute the default location (before the actions
-   are run).  */
+#define YYTERROR        1
+#define YYERRCODE       256
+
 
+/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
+   If N is 0, then set CURRENT to the empty location which ends
+   the previous symbol: RHS[0] (always defined).  */
+
+#define YYRHSLOC(Rhs, K) ((Rhs)[K])
 #ifndef YYLLOC_DEFAULT
-# define YYLLOC_DEFAULT(Current, Rhs, N)    \
-   ((Current).first_line   = (Rhs)[1].first_line,  \
-    (Current).first_column = (Rhs)[1].first_column,  \
-    (Current).last_line    = (Rhs)[N].last_line,  \
-    (Current).last_column  = (Rhs)[N].last_column)
+# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
+    do                                                                  \
+      if (N)                                                            \
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
+    while (0)
 #endif
 
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
+#endif
+
+
 /* YYLEX -- calling `yylex' with the right arguments.  */
 
 #ifdef YYLEX_PARAM
@@ -551,27 +618,21 @@ while (0)
 #  define YYFPRINTF fprintf
 # endif
 
-# define YYDPRINTF(Args)      \
-do {            \
-  if (yydebug)          \
-    YYFPRINTF Args;        \
-} while (0)
-
-# define YYDSYMPRINT(Args)      \
-do {            \
-  if (yydebug)          \
-    yysymprint Args;        \
+# define YYDPRINTF(Args)                        \
+do {                                            \
+  if (yydebug)                                  \
+    YYFPRINTF Args;                             \
 } while (0)
 
-# define YYDSYMPRINTF(Title, Token, Value, Location)    \
-do {                \
-  if (yydebug)              \
-    {                \
-      YYFPRINTF (stderr, "%s ", Title);        \
-      yysymprint (stderr,           \
-                  Token, Value);  \
-      YYFPRINTF (stderr, "\n");          \
-    }                \
+# define YY_SYMBOL_PRINT(Title, Type, Value, Location)          \
+do {                                                            \
+  if (yydebug)                                                  \
+    {                                                           \
+      YYFPRINTF (stderr, "%s ", Title);                         \
+      yysymprint (stderr,                                       \
+                  Type, Value); \
+      YYFPRINTF (stderr, "\n");                                 \
+    }                                                           \
 } while (0)
 
 /*------------------------------------------------------------------.
@@ -595,10 +656,10 @@ yy_stack_print (bottom, top)
   YYFPRINTF (stderr, "\n");
 }
 
-# define YY_STACK_PRINT(Bottom, Top)        \
-do {                \
-  if (yydebug)              \
-    yy_stack_print ((Bottom), (Top));        \
+# define YY_STACK_PRINT(Bottom, Top)                            \
+do {                                                            \
+  if (yydebug)                                                  \
+    yy_stack_print ((Bottom), (Top));                           \
 } while (0)
 
 
@@ -616,49 +677,44 @@ yy_reduce_print (yyrule)
 #endif
 {
   int yyi;
-  unsigned int yylno = yyrline[yyrule];
-  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
+  unsigned long int yylno = yyrline[yyrule];
+  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu), ",
              yyrule - 1, yylno);
   /* Print the symbols being reduced, and their result.  */
   for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
-    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
-  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
+    YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
+  YYFPRINTF (stderr, "-> %s\n", yytname[yyr1[yyrule]]);
 }
 
-# define YY_REDUCE_PRINT(Rule)    \
-do {          \
-  if (yydebug)        \
-    yy_reduce_print (Rule);    \
+# define YY_REDUCE_PRINT(Rule)          \
+do {                                    \
+  if (yydebug)                          \
+    yy_reduce_print (Rule);             \
 } while (0)
 
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
 
 
 /* YYINITDEPTH -- initial size of the parser's stacks.  */
-#ifndef  YYINITDEPTH
+#ifndef YYINITDEPTH
 # define YYINITDEPTH 200
 #endif
 
 /* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
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
@@ -680,7 +736,7 @@ yystrlen (yystr)
      const char *yystr;
 #   endif
 {
-  register const char *yys = yystr;
+  const char *yys = yystr;
 
   while (*yys++ != '\0')
     continue;
@@ -705,8 +761,8 @@ yystpcpy (yydest, yysrc)
      const char *yysrc;
 #   endif
 {
-  register char *yyd = yydest;
-  register const char *yys = yysrc;
+  char *yyd = yydest;
+  const char *yys = yysrc;
 
   while ((*yyd++ = *yys++) != '\0')
     continue;
@@ -716,7 +772,55 @@ yystpcpy (yydest, yysrc)
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
+      size_t yyn = 0;
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
+
+  if (! yyres)
+    return yystrlen (yystr);
+
+  return yystpcpy (yyres, yystr) - yyres;
+}
+# endif
+
+#endif /* YYERROR_VERBOSE */
 
 
 
@@ -740,15 +844,15 @@ yysymprint (yyoutput, yytype, yyvaluep)
   (void) yyvaluep;
 
   if (yytype < YYNTOKENS)
-    {
-      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
-# ifdef YYPRINT
-      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
-# endif
-    }
+    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
   else
     YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);
 
+
+# ifdef YYPRINT
+  if (yytype < YYNTOKENS)
+    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
+# endif
   switch (yytype)
     {
       default:
@@ -764,17 +868,22 @@ yysymprint (yyoutput, yytype, yyvaluep)
 
 #if defined (__STDC__) || defined (__cplusplus)
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
   /* Pacify ``unused variable'' warnings.  */
   (void) yyvaluep;
 
+  if (!yymsg)
+    yymsg = "Deleting";
+  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);
+
   switch (yytype)
     {
 
@@ -823,25 +932,25 @@ yyparse (void)
 #else
 int
 yyparse ()
-
+    ;
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
 
   /* Three stacks and their tools:
@@ -855,12 +964,12 @@ int yynerrs;
   /* The state stack.  */
   short int yyssa[YYINITDEPTH];
   short int *yyss = yyssa;
-  register short int *yyssp;
+  short int *yyssp;
 
   /* The semantic value stack.  */
   YYSTYPE yyvsa[YYINITDEPTH];
   YYSTYPE *yyvs = yyvsa;
-  register YYSTYPE *yyvsp;
+  YYSTYPE *yyvsp;
 
 
 
@@ -882,7 +991,7 @@ int yynerrs;
   yystate = 0;
   yyerrstatus = 0;
   yynerrs = 0;
-  yychar = YYEMPTY;    /* Cause a token to be read.  */
+  yychar = YYEMPTY;             /* Cause a token to be read.  */
 
   /* Initialize stack pointers.
      Waste one element of value and location stack
@@ -892,7 +1001,6 @@ int yynerrs;
   yyssp = yyss;
   yyvsp = yyvs;
 
-
   goto yysetstate;
 
 /*------------------------------------------------------------.
@@ -914,49 +1022,49 @@ int yynerrs;
 
 #ifdef yyoverflow
       {
-  /* Give user a chance to reallocate the stack. Use copies of
-     these so that the &'s don't force the real ones into
-     memory.  */
-  YYSTYPE *yyvs1 = yyvs;
-  short int *yyss1 = yyss;
+        /* Give user a chance to reallocate the stack. Use copies of
+           these so that the &'s don't force the real ones into
+           memory.  */
+        YYSTYPE *yyvs1 = yyvs;
+        short int *yyss1 = yyss;
 
 
-  /* Each stack pointer address is followed by the size of the
-     data in use in that stack, in bytes.  This used to be a
-     conditional around just the two extra args, but that might
-     be undefined if yyoverflow is a macro.  */
-  yyoverflow ("parser stack overflow",
-        &yyss1, yysize * sizeof (*yyssp),
-        &yyvs1, yysize * sizeof (*yyvsp),
+        /* Each stack pointer address is followed by the size of the
+           data in use in that stack, in bytes.  This used to be a
+           conditional around just the two extra args, but that might
+           be undefined if yyoverflow is a macro.  */
+        yyoverflow (YY_("memory exhausted"),
+                    &yyss1, yysize * sizeof (*yyssp),
+                    &yyvs1, yysize * sizeof (*yyvsp),
 
-        &yystacksize);
+                    &yystacksize);
 
-  yyss = yyss1;
-  yyvs = yyvs1;
+        yyss = yyss1;
+        yyvs = yyvs1;
       }
 #else /* no yyoverflow */
 # ifndef YYSTACK_RELOCATE
-      goto yyoverflowlab;
+      goto yyexhaustedlab;
 # else
       /* Extend the stack our own way.  */
       if (YYMAXDEPTH <= yystacksize)
-  goto yyoverflowlab;
+        goto yyexhaustedlab;
       yystacksize *= 2;
       if (YYMAXDEPTH < yystacksize)
-  yystacksize = YYMAXDEPTH;
+        yystacksize = YYMAXDEPTH;
 
       {
-  short int *yyss1 = yyss;
-  union yyalloc *yyptr =
-    (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
-  if (! yyptr)
-    goto yyoverflowlab;
-  YYSTACK_RELOCATE (yyss);
-  YYSTACK_RELOCATE (yyvs);
+        short int *yyss1 = yyss;
+        union yyalloc *yyptr =
+          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
+        if (! yyptr)
+          goto yyexhaustedlab;
+        YYSTACK_RELOCATE (yyss);
+        YYSTACK_RELOCATE (yyvs);
 
 #  undef YYSTACK_RELOCATE
-  if (yyss1 != yyssa)
-    YYSTACK_FREE (yyss1);
+        if (yyss1 != yyssa)
+          YYSTACK_FREE (yyss1);
       }
 # endif
 #endif /* no yyoverflow */
@@ -966,10 +1074,10 @@ int yynerrs;
 
 
       YYDPRINTF ((stderr, "Stack size increased to %lu\n",
-      (unsigned long int) yystacksize));
+                  (unsigned long int) yystacksize));
 
       if (yyss + yystacksize - 1 <= yyssp)
-  YYABORT;
+        YYABORT;
     }
 
   YYDPRINTF ((stderr, "Entering state %d\n", yystate));
@@ -982,18 +1090,18 @@ int yynerrs;
 yybackup:
 
 /* Do appropriate processing given the current state.  */
-/* Read a lookahead token if we need one and don't already have one.  */
+/* Read a look-ahead token if we need one and don't already have one.  */
 /* yyresume: */
 
-  /* First try to decide what to do without reference to lookahead token.  */
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
@@ -1008,7 +1116,7 @@ int yynerrs;
   else
     {
       yytoken = YYTRANSLATE (yychar);
-      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
+      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
     }
 
   /* If the proper action on seeing token YYTOKEN is to reduce or to
@@ -1020,16 +1128,16 @@ int yynerrs;
   if (yyn <= 0)
     {
       if (yyn == 0 || yyn == YYTABLE_NINF)
-  goto yyerrlab;
+        goto yyerrlab;
       yyn = -yyn;
       goto yyreduce;
     }
 
   if (yyn == YYFINAL)
     YYACCEPT;
 
-  /* Shift the lookahead token.  */
-  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));
+  /* Shift the look-ahead token.  */
+  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
 
   /* Discard the token being shifted unless it is eof.  */
   if (yychar != YYEOF)
@@ -1079,151 +1187,154 @@ int yynerrs;
   switch (yyn)
     {
         case 2:
-
+#line 96 "cmCommandArgumentParser.y"
     {
-  yyval.str = 0;
-  yyGetParser->SetResult(yyvsp[0].str);
+  (yyval.str) = 0;
+  yyGetParser->SetResult((yyvsp[0].str));
 }
     break;
 
   case 3:
-
+#line 103 "cmCommandArgumentParser.y"
     {
-  yyval.str = yyvsp[0].str;
+  (yyval.str) = (yyvsp[0].str);
 }
     break;
 
   case 4:
-
+#line 108 "cmCommandArgumentParser.y"
     {
-  yyval.str = yyGetParser->CombineUnions(yyvsp[-1].str, yyvsp[0].str);
+  (yyval.str) = yyGetParser->CombineUnions((yyvsp[-1].str), (yyvsp[0].str));
 }
     break;
 
   case 5:
-
+#line 113 "cmCommandArgumentParser.y"
     {
-  yyval.str = 0;
+  (yyval.str) = 0;
 }
     break;
 
   case 6:
-
+#line 118 "cmCommandArgumentParser.y"
     {
-  yyval.str = yyGetParser->CombineUnions(yyvsp[-1].str, yyvsp[0].str);
+  (yyval.str) = yyGetParser->CombineUnions((yyvsp[-1].str), (yyvsp[0].str));
 }
     break;
 
   case 7:
-
+#line 124 "cmCommandArgumentParser.y"
     {
-  yyval.str = yyvsp[0].str;
+  (yyval.str) = (yyvsp[0].str);
 }
     break;
 
   case 8:
-
+#line 129 "cmCommandArgumentParser.y"
     {
-  yyval.str = yyvsp[0].str;
+  (yyval.str) = (yyvsp[0].str);
 }
     break;
 
   case 9:
-
+#line 135 "cmCommandArgumentParser.y"
     {
-  yyval.str = yyvsp[0].str;
+  (yyval.str) = (yyvsp[0].str);
 }
     break;
 
   case 10:
-
+#line 140 "cmCommandArgumentParser.y"
     {
-  yyval.str = yyvsp[0].str;
+  (yyval.str) = (yyvsp[0].str);
 }
     break;
 
   case 11:
-
+#line 145 "cmCommandArgumentParser.y"
     {
-  yyval.str = yyvsp[0].str;
+  (yyval.str) = (yyvsp[0].str);
 }
     break;
 
   case 12:
-
+#line 150 "cmCommandArgumentParser.y"
     {
-  yyval.str = yyvsp[0].str;
+  (yyval.str) = (yyvsp[0].str);
 }
     break;
 
   case 13:
-
+#line 155 "cmCommandArgumentParser.y"
     {
-  yyval.str = yyvsp[0].str;
+  (yyval.str) = (yyvsp[0].str);
 }
     break;
 
   case 14:
-
+#line 160 "cmCommandArgumentParser.y"
     {
-  yyval.str = yyvsp[0].str;
+  (yyval.str) = (yyvsp[0].str);
 }
     break;
 
   case 15:
-
+#line 166 "cmCommandArgumentParser.y"
     {
-  yyval.str = yyGetParser->ExpandSpecialVariable(yyvsp[-2].str,yyvsp[-1].str);
+  (yyval.str) = yyGetParser->ExpandSpecialVariable((yyvsp[-2].str),(yyvsp[-1].str));
+  //std::cerr << __LINE__ << " here: [" << $<str>1 << "] [" << $<str>2 << "] [" << $<str>3 << "]" << std::endl;
 }
     break;
 
   case 16:
-
+#line 172 "cmCommandArgumentParser.y"
     {
-  yyval.str = yyGetParser->ExpandVariable(yyvsp[-1].str);
+  (yyval.str) = yyGetParser->ExpandVariable((yyvsp[-1].str));
+  //std::cerr << __LINE__ << " here: [" << $<str>1 << "] [" << $<str>2 << "] [" << $<str>3 << "]" << std::endl;
 }
     break;
 
   case 17:
-
+#line 178 "cmCommandArgumentParser.y"
     {
-  yyval.str = yyGetParser->ExpandVariable(yyvsp[0].str);
+  (yyval.str) = yyGetParser->ExpandVariable((yyvsp[0].str));
 }
     break;
 
   case 18:
-
+#line 183 "cmCommandArgumentParser.y"
     {
-  yyval.str = 0;
+  (yyval.str) = 0;
 }
     break;
 
   case 19:
-
+#line 188 "cmCommandArgumentParser.y"
     {
-  yyval.str = yyGetParser->CombineUnions(yyvsp[-1].str, yyvsp[0].str);
+  (yyval.str) = yyGetParser->CombineUnions((yyvsp[-1].str), (yyvsp[0].str));
 }
     break;
 
   case 20:
-
+#line 194 "cmCommandArgumentParser.y"
     {
-  yyval.str = yyvsp[0].str;
+  (yyval.str) = (yyvsp[0].str);
 }
     break;
 
   case 21:
-
+#line 199 "cmCommandArgumentParser.y"
     {
-  yyval.str = yyvsp[0].str;
+  (yyval.str) = (yyvsp[0].str);
 }
     break;
 
 
+      default: break;
     }
 
-/* Line 1010 of yacc.c.  */
-
+/* Line 1126 of yacc.c.  */
+#line 1338 "cmCommandArgumentParser.cxx"
 
   yyvsp -= yylen;
   yyssp -= yylen;
@@ -1261,95 +1372,129 @@ int yynerrs;
       yyn = yypact[yystate];
 
       if (YYPACT_NINF < yyn && yyn < YYLAST)
-  {
-    YYSIZE_T yysize = 0;
-    int yytype = YYTRANSLATE (yychar);
-    const char* yyprefix;
-    char *yymsg;
-    int yyx;
-
-    /* Start YYX at -YYN if negative to avoid negative indexes in
-       YYCHECK.  */
-    int yyxbegin = yyn < 0 ? -yyn : 0;
-
-    /* Stay within bounds of both yycheck and yytname.  */
-    int yychecklim = YYLAST - yyn;
-    int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
-    int yycount = 0;
-
-    yyprefix = ", expecting ";
-    for (yyx = yyxbegin; yyx < yyxend; ++yyx)
-      if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
         {
-    yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
-    yycount += 1;
-    if (yycount == 5)
-      {
-        yysize = 0;
-        break;
-      }
+          int yytype = YYTRANSLATE (yychar);
+          YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
+          YYSIZE_T yysize = yysize0;
+          YYSIZE_T yysize1;
+          int yysize_overflow = 0;
+          char *yymsg = 0;
+#         define YYERROR_VERBOSE_ARGS_MAXIMUM 5
+          char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
+          int yyx;
+
+#if 0
+          /* This is so xgettext sees the translatable formats that are
+             constructed on the fly.  */
+          YY_("syntax error, unexpected %s");
+          YY_("syntax error, unexpected %s, expecting %s");
+          YY_("syntax error, unexpected %s, expecting %s or %s");
+          YY_("syntax error, unexpected %s, expecting %s or %s or %s");
+          YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
+#endif
+          char *yyfmt;
+          char const *yyf;
+          static char const yyunexpected[] = "syntax error, unexpected %s";
+          static char const yyexpecting[] = ", expecting %s";
+          static char const yyor[] = " or %s";
+          char yyformat[sizeof yyunexpected
+                        + sizeof yyexpecting - 1
+                        + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
+                           * (sizeof yyor - 1))];
+          char const *yyprefix = yyexpecting;
+
+          /* Start YYX at -YYN if negative to avoid negative indexes in
+             YYCHECK.  */
+          int yyxbegin = yyn < 0 ? -yyn : 0;
+
+          /* Stay within bounds of both yycheck and yytname.  */
+          int yychecklim = YYLAST - yyn;
+          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
+          int yycount = 1;
+
+          yyarg[0] = yytname[yytype];
+          yyfmt = yystpcpy (yyformat, yyunexpected);
+
+          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
+            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
+              {
+                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
+                  {
+                    yycount = 1;
+                    yysize = yysize0;
+                    yyformat[sizeof yyunexpected - 1] = '\0';
+                    break;
+                  }
+                yyarg[yycount++] = yytname[yyx];
+                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
+                yysize_overflow |= yysize1 < yysize;
+                yysize = yysize1;
+                yyfmt = yystpcpy (yyfmt, yyprefix);
+                yyprefix = yyor;
+              }
+
+          yyf = YY_(yyformat);
+          yysize1 = yysize + yystrlen (yyf);
+          yysize_overflow |= yysize1 < yysize;
+          yysize = yysize1;
+
+          if (!yysize_overflow && yysize <= YYSTACK_ALLOC_MAXIMUM)
+            yymsg = (char *) YYSTACK_ALLOC (yysize);
+          if (yymsg)
+            {
+              /* Avoid sprintf, as that infringes on the user's name space.
+                 Don't have undefined behavior even if the translation
+                 produced a string with the wrong number of "%s"s.  */
+              char *yyp = yymsg;
+              int yyi = 0;
+              while ((*yyp = *yyf))
+                {
+                  if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
+                    {
+                      yyp += yytnamerr (yyp, yyarg[yyi++]);
+                      yyf += 2;
+                    }
+                  else
+                    {
+                      yyp++;
+                      yyf++;
+                    }
+                }
+              yyerror (yymsg);
+              YYSTACK_FREE (yymsg);
+            }
+          else
+            {
+              yyerror (YY_("syntax error"));
+              goto yyexhaustedlab;
+            }
         }
-    yysize += (sizeof ("syntax error, unexpected ")
-         + yystrlen (yytname[yytype]));
-    yymsg = (char *) YYSTACK_ALLOC (yysize);
-    if (yymsg != 0)
-      {
-        char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
-        yyp = yystpcpy (yyp, yytname[yytype]);
-
-        if (yycount < 5)
-    {
-      yyprefix = ", expecting ";
-      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
-        if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
-          {
-      yyp = yystpcpy (yyp, yyprefix);
-      yyp = yystpcpy (yyp, yytname[yyx]);
-      yyprefix = " or ";
-          }
-    }
-        yyerror (yymsg);
-        YYSTACK_FREE (yymsg);
-      }
-    else
-      yyerror ("syntax error; also virtual memory exhausted");
-  }
       else
 #endif /* YYERROR_VERBOSE */
-  yyerror ("syntax error");
+        yyerror (YY_("syntax error"));
     }
 
 
 
   if (yyerrstatus == 3)
     {
-      /* If just tried and failed to reuse lookahead token after an
-   error, discard it.  */
+      /* If just tried and failed to reuse look-ahead token after an
+         error, discard it.  */
 
       if (yychar <= YYEOF)
         {
-          /* If at end of input, pop the error token,
-       then the rest of the stack, then return failure.  */
-    if (yychar == YYEOF)
-       for (;;)
-         {
-     YYPOPSTACK;
-     if (yyssp == yyss)
-       YYABORT;
-     YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
-     yydestruct (yystos[*yyssp], yyvsp);
-         }
+          /* Return failure if at end of input.  */
+          if (yychar == YYEOF)
+            YYABORT;
         }
       else
-  {
-    YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
-    yydestruct (yytoken, &yylval);
-    yychar = YYEMPTY;
-
-  }
+        {
+          yydestruct ("Error: discarding", yytoken, &yylval);
+          yychar = YYEMPTY;
+        }
     }
 
-  /* Else will try to reuse lookahead token after shifting the error
+  /* Else will try to reuse look-ahead token after shifting the error
      token.  */
   goto yyerrlab1;
 
@@ -1359,14 +1504,13 @@ int yynerrs;
 `---------------------------------------------------*/
 yyerrorlab:
 
-#if defined (__GNUC__) || defined (__HP_aCC)
-  /* Pacify GCC when the user code never invokes YYERROR and the label
-     yyerrorlab therefore never appears in user code.  */
+  /* Pacify compilers like GCC when the user code never invokes
+     YYERROR and the label yyerrorlab therefore never appears in user
+     code.  */
   if (0)
      goto yyerrorlab;
-#endif
 
-  yyvsp -= yylen;
+yyvsp -= yylen;
   yyssp -= yylen;
   yystate = *yyssp;
   goto yyerrlab1;
@@ -1376,28 +1520,28 @@ int yynerrs;
 | yyerrlab1 -- common code for both syntax error and YYERROR.  |
 `-------------------------------------------------------------*/
 yyerrlab1:
-  yyerrstatus = 3;  /* Each real token shifted decrements this.  */
+  yyerrstatus = 3;      /* Each real token shifted decrements this.  */
 
   for (;;)
     {
       yyn = yypact[yystate];
       if (yyn != YYPACT_NINF)
-  {
-    yyn += YYTERROR;
-    if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
-      {
-        yyn = yytable[yyn];
-        if (0 < yyn)
-    break;
-      }
-  }
+        {
+          yyn += YYTERROR;
+          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
+            {
+              yyn = yytable[yyn];
+              if (0 < yyn)
+                break;
+            }
+        }
 
       /* Pop the current state because it cannot handle the error token.  */
       if (yyssp == yyss)
-  YYABORT;
+        YYABORT;
+
 
-      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
-      yydestruct (yystos[yystate], yyvsp);
+      yydestruct ("Error: popping", yystos[yystate], yyvsp);
       YYPOPSTACK;
       yystate = *yyssp;
       YY_STACK_PRINT (yyss, yyssp);
@@ -1406,11 +1550,12 @@ int yynerrs;
   if (yyn == YYFINAL)
     YYACCEPT;
 
-  YYDPRINTF ((stderr, "Shifting error token, "));
-
   *++yyvsp = yylval;
 
 
+  /* Shift the error token. */
+  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);
+
   yystate = yyn;
   goto yynewstate;
 
@@ -1430,16 +1575,25 @@ int yynerrs;
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
+  while (yyssp != yyss)
+    {
+      yydestruct ("Cleanup: popping",
+                  yystos[*yyssp], yyvsp);
+      YYPOPSTACK;
+    }
 #ifndef yyoverflow
   if (yyss != yyssa)
     YYSTACK_FREE (yyss);
@@ -1448,7 +1602,7 @@ int yynerrs;
 }
 
 
-
+#line 204 "cmCommandArgumentParser.y"
 
 /* End of grammar */
 
@@ -1457,5 +1611,3 @@ void cmCommandArgumentError(yyscan_t yyscanner, const char* message)
 {
   yyGetParser->Error(message);
 }
-
-