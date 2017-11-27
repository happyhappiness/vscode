 do								\
   if (yychar == YYEMPTY && yylen == 1)				\
     {								\
       yychar = (Token);						\
       yylval = (Value);						\
       yytoken = YYTRANSLATE (yychar);				\
-      YYPOPSTACK;						\
+      YYPOPSTACK (1);						\
       goto yybackup;						\
     }								\
   else								\
     { 								\
-      yyerror ("syntax error: cannot back up");\
+      yyerror (YY_("syntax error: cannot back up")); \
       YYERROR;							\
     }								\
-while (0)
+while (YYID (0))
+
 
 #define YYTERROR	1
 #define YYERRCODE	256
 
-/* YYLLOC_DEFAULT -- Compute the default location (before the actions
-   are run).  */
 
+/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
+   If N is 0, then set CURRENT to the empty location which ends
+   the previous symbol: RHS[0] (always defined).  */
+
+#define YYRHSLOC(Rhs, K) ((Rhs)[K])
 #ifndef YYLLOC_DEFAULT
-# define YYLLOC_DEFAULT(Current, Rhs, N)		\
-   ((Current).first_line   = (Rhs)[1].first_line,	\
-    (Current).first_column = (Rhs)[1].first_column,	\
-    (Current).last_line    = (Rhs)[N].last_line,	\
-    (Current).last_column  = (Rhs)[N].last_column)
+# define YYLLOC_DEFAULT(Current, Rhs, N)				\
+    do									\
+      if (YYID (N))                                                    \
+	{								\
+	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
+	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
+	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
+	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
+	}								\
+      else								\
+	{								\
+	  (Current).first_line   = (Current).last_line   =		\
+	    YYRHSLOC (Rhs, 0).last_line;				\
+	  (Current).first_column = (Current).last_column =		\
+	    YYRHSLOC (Rhs, 0).last_column;				\
+	}								\
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
+#  define YY_LOCATION_PRINT(File, Loc)			\
+     fprintf (File, "%d.%d-%d.%d",			\
+	      (Loc).first_line, (Loc).first_column,	\
+	      (Loc).last_line,  (Loc).last_column)
+# else
+#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
+# endif
 #endif
 
+
 /* YYLEX -- calling `yylex' with the right arguments.  */
 
 #ifdef YYLEX_PARAM
 # define YYLEX yylex (YYLEX_PARAM)
 #else
 # define YYLEX yylex ()
