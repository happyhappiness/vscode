#  define YYFPRINTF fprintf

# endif



# define YYDPRINTF(Args)                        \

do {                                            \

  if (yydebug)                                  \

    YYFPRINTF Args;                             \

} while (0)



/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT

# define YY_LOCATION_PRINT(File, Loc) ((void) 0)

#endif





# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \

do {                                                                      \

  if (yydebug)                                                            \

    {                                                                     \

      YYFPRINTF (stderr, "%s ", Title);                                   \

      yy_symbol_print (stderr,                                            \

                  Type, Value, yyscanner); \

      YYFPRINTF (stderr, "\n");                                           \

    }                                                                     \

} while (0)





/*----------------------------------------.

| Print this symbol's value on YYOUTPUT.  |

`----------------------------------------*/



static void

yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, yyscan_t yyscanner)

{

  FILE *yyo = yyoutput;

  YYUSE (yyo);

  YYUSE (yyscanner);

  if (!yyvaluep)

    return;

# ifdef YYPRINT

  if (yytype < YYNTOKENS)

    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);

# endif

  YYUSE (yytype);

}





/*--------------------------------.

| Print this symbol on YYOUTPUT.  |

`--------------------------------*/



static void

yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, yyscan_t yyscanner)

{

  YYFPRINTF (yyoutput, "%s %s (",

             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);



  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yyscanner);

  YYFPRINTF (yyoutput, ")");

}



/*------------------------------------------------------------------.

| yy_stack_print -- Print the state stack from its BOTTOM up to its |

| TOP (included).                                                   |

`------------------------------------------------------------------*/



static void

yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)

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

yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule, yyscan_t yyscanner)

{

  unsigned long int yylno = yyrline[yyrule];

  int yynrhs = yyr2[yyrule];

  int yyi;

  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",

             yyrule - 1, yylno);

  /* The symbols being reduced.  */

  for (yyi = 0; yyi < yynrhs; yyi++)

    {

      YYFPRINTF (stderr, "   $%d = ", yyi + 1);

      yy_symbol_print (stderr,

                       yystos[yyssp[yyi + 1 - yynrhs]],

                       &(yyvsp[(yyi + 1) - (yynrhs)])

                                              , yyscanner);

      YYFPRINTF (stderr, "\n");

    }

}



# define YY_REDUCE_PRINT(Rule)          \

do {                                    \

  if (yydebug)                          \

    yy_reduce_print (yyssp, yyvsp, Rule, yyscanner); \

} while (0)



/* Nonzero means print parse trace.  It is left uninitialized so that

   multiple parsers can coexist.  */

int yydebug;

#else /* !YYDEBUG */

# define YYDPRINTF(Args)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)

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





#if YYERROR_VERBOSE



# ifndef yystrlen

#  if defined __GLIBC__ && defined _STRING_H

#   define yystrlen strlen

#  else

/* Return the length of YYSTR.  */

static YYSIZE_T

yystrlen (const char *yystr)

{

  YYSIZE_T yylen;

  for (yylen = 0; yystr[yylen]; yylen++)

    continue;

  return yylen;

}

#  endif

# endif



# ifndef yystpcpy

#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE

#   define yystpcpy stpcpy

#  else

/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in

   YYDEST.  */

static char *

yystpcpy (char *yydest, const char *yysrc)

{

  char *yyd = yydest;

  const char *yys = yysrc;

