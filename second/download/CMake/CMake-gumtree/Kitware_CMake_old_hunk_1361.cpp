do {                                            \

  if (yydebug)                                  \

    YYFPRINTF Args;                             \

} while (0)



# define YYDSYMPRINT(Args)                      \

do {                                            \

  if (yydebug)                                  \

    yysymprint Args;                            \

} while (0)



# define YYDSYMPRINTF(Title, Token, Value, Location)            \

do {                                                            \

  if (yydebug)                                                  \

    {                                                           \

      YYFPRINTF (stderr, "%s ", Title);                         \

      yysymprint (stderr,                                       \

                  Token, Value);        \

      YYFPRINTF (stderr, "\n");                                 \

    }                                                           \

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

