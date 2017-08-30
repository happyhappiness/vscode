do {                                                            \

  if (yydebug)                                                  \

    yy_stack_print ((Bottom), (Top));                           \

} while (0)





/*------------------------------------------------.

| Report that the YYRULE is going to be reduced.  |

`------------------------------------------------*/



#if defined (__STDC__) || defined (__cplusplus)

static void

yy_reduce_print (int yyrule)

#else

static void

yy_reduce_print (yyrule)

    int yyrule;

#endif

{

  int yyi;

  unsigned int yylno = yyrline[yyrule];

  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",

             yyrule - 1, yylno);

  /* Print the symbols being reduced, and their result.  */

  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)

    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);

  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);

}



# define YY_REDUCE_PRINT(Rule)          \

do {                                    \

  if (yydebug)                          \

    yy_reduce_print (Rule);             \

} while (0)



/* Nonzero means print parse trace.  It is left uninitialized so that

   multiple parsers can coexist.  */

int yydebug;

#else /* !YYDEBUG */

# define YYDPRINTF(Args)

# define YYDSYMPRINT(Args)

# define YYDSYMPRINTF(Title, Token, Value, Location)

# define YY_STACK_PRINT(Bottom, Top)

# define YY_REDUCE_PRINT(Rule)

#endif /* !YYDEBUG */

