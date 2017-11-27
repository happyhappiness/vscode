 # endif
 
 # define YYDPRINTF(Args)			\
 do {						\
   if (yydebug)					\
     YYFPRINTF Args;				\
-} while (0)
+} while (YYID (0))
 
-# define YYDSYMPRINT(Args)			\
-do {						\
-  if (yydebug)					\
-    yysymprint Args;				\
-} while (0)
+# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
+do {									  \
+  if (yydebug)								  \
+    {									  \
+      YYFPRINTF (stderr, "%s ", Title);					  \
+      yy_symbol_print (stderr,						  \
+		  Type, Value); \
+      YYFPRINTF (stderr, "\n");						  \
+    }									  \
+} while (YYID (0))
 
-# define YYDSYMPRINTF(Title, Token, Value, Location)		\
-do {								\
-  if (yydebug)							\
-    {								\
-      YYFPRINTF (stderr, "%s ", Title);				\
-      yysymprint (stderr, 					\
-                  Token, Value);	\
-      YYFPRINTF (stderr, "\n");					\
-    }								\
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
+	break;
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
 
 # define YY_STACK_PRINT(Bottom, Top)				\
 do {								\
   if (yydebug)							\
     yy_stack_print ((Bottom), (Top));				\
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
+		       &(yyvsp[(yyi + 1) - (yynrhs)])
+		       		       );
+      fprintf (stderr, "\n");
+    }
 }
 
 # define YY_REDUCE_PRINT(Rule)		\
 do {					\
   if (yydebug)				\
-    yy_reduce_print (Rule);		\
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
 
 
 /* YYINITDEPTH -- initial size of the parser's stacks.  */
