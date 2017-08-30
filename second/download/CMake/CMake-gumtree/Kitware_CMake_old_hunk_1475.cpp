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

