#  define YYFPRINTF fprintf

# endif



# define YYDPRINTF(Args)                        \

do {                                            \

  if (yydebug)                                  \

    YYFPRINTF Args;                             \

} while (0)



# define YY_SYMBOL_PRINT(Title, Type, Value, Location)          \

do {                                                            \

  if (yydebug)                                                  \

    {                                                           \

      YYFPRINTF (stderr, "%s ", Title);                         \

      yysymprint (stderr,                                       \

                  Type, Value); \

      YYFPRINTF (stderr, "\n");                                 \

    }                                                           \

} while (0)



/*------------------------------------------------------------------.

