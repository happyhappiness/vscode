#  define YYFPRINTF fprintf

# endif



# define YYDPRINTF(Args)      \

do {            \

  if (yydebug)          \

    YYFPRINTF Args;        \

} while (0)



# define YYDSYMPRINT(Args)      \

do {            \

  if (yydebug)          \

    yysymprint Args;        \

} while (0)



# define YYDSYMPRINTF(Title, Token, Value, Location)    \

do {                \

  if (yydebug)              \

    {                \

      YYFPRINTF (stderr, "%s ", Title);        \

      yysymprint (stderr,           \

                  Token, Value);  \

      YYFPRINTF (stderr, "\n");          \

    }                \

} while (0)



/*------------------------------------------------------------------.

| yy_stack_print -- Print the state stack from its BOTTOM up to its |

| TOP (included).                                                   |

`------------------------------------------------------------------*/



#if defined (__STDC__) || defined (__cplusplus)

static void

yy_stack_print (short int *bottom, short int *top)

#else

static void

yy_stack_print (bottom, top)

    short int *bottom;

    short int *top;

#endif

{

  YYFPRINTF (stderr, "Stack now");

  for (/* Nothing. */; bottom <= top; ++bottom)

    YYFPRINTF (stderr, " %d", *bottom);

  YYFPRINTF (stderr, "\n");

}



# define YY_STACK_PRINT(Bottom, Top)        \

do {                \

  if (yydebug)              \

    yy_stack_print ((Bottom), (Top));        \

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



# define YY_REDUCE_PRINT(Rule)    \

do {          \

  if (yydebug)        \

    yy_reduce_print (Rule);    \

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





/* YYINITDEPTH -- initial size of the parser's stacks.  */

#ifndef  YYINITDEPTH

# define YYINITDEPTH 200

#endif



/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only

   if the built-in stack extension method is used).



   Do not make this value too large; the results are undefined if

   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)

   evaluated with infinite-precision integer arithmetic.  */



#if defined (YYMAXDEPTH) && YYMAXDEPTH == 0

# undef YYMAXDEPTH

#endif



#ifndef YYMAXDEPTH

# define YYMAXDEPTH 10000

#endif







#if YYERROR_VERBOSE



# ifndef yystrlen

#  if defined (__GLIBC__) && defined (_STRING_H)

#   define yystrlen strlen

#  else

/* Return the length of YYSTR.  */

static YYSIZE_T

#   if defined (__STDC__) || defined (__cplusplus)

yystrlen (const char *yystr)

#   else

yystrlen (yystr)

     const char *yystr;

#   endif

{

  const char *yys = yystr;



  while (*yys++ != '\0')

    continue;



  return yys - yystr - 1;

}

#  endif

# endif



# ifndef yystpcpy

#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)

#   define yystpcpy stpcpy

#  else

/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in

   YYDEST.  */

static char *

#   if defined (__STDC__) || defined (__cplusplus)

yystpcpy (char *yydest, const char *yysrc)

#   else

yystpcpy (yydest, yysrc)

     char *yydest;

     const char *yysrc;

#   endif

{

  char *yyd = yydest;

  const char *yys = yysrc;

