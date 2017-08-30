    int         yyRelMonth;

    int         yyRelSeconds;

    int         yyRelYear;

} CURL_CONTEXT;



/* enable use of extra argument to yyparse and yylex which can be used to pass

**  in a user defined value (CURL_CONTEXT struct in our case)

*/

#define YYPARSE_PARAM cookie

#define YYLEX_PARAM cookie

#define context ((CURL_CONTEXT *) cookie)





/* Enabling traces.  */

#ifndef YYDEBUG

# define YYDEBUG 0

#endif



/* Enabling verbose error messages.  */

#ifdef YYERROR_VERBOSE

# undef YYERROR_VERBOSE

# define YYERROR_VERBOSE 1

#else

# define YYERROR_VERBOSE 0

#endif



#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)

#line 223 "getdate.y"

typedef union YYSTYPE {

    int                 Number;

    enum _MERIDIAN      Meridian;

} YYSTYPE;

/* Line 191 of yacc.c.  */

#line 331 "y.tab.c"

# define yystype YYSTYPE /* obsolescent; will be withdrawn */

# define YYSTYPE_IS_DECLARED 1

# define YYSTYPE_IS_TRIVIAL 1

#endif







/* Copy the second part of user declarations.  */

#line 228 "getdate.y"



static int yylex (YYSTYPE *yylval, void *cookie);

static int yyerror (const char *s);





/* Line 214 of yacc.c.  */

#line 347 "y.tab.c"



#if ! defined (yyoverflow) || YYERROR_VERBOSE



/* The parser invokes alloca or malloc; define the necessary symbols.  */



# if YYSTACK_USE_ALLOCA

#  define YYSTACK_ALLOC alloca

# else

#  ifndef YYSTACK_USE_ALLOCA

#   if defined (alloca) || defined (_ALLOCA_H)

#    define YYSTACK_ALLOC alloca

#   else

#    ifdef __GNUC__

#     define YYSTACK_ALLOC __builtin_alloca

#    endif

#   endif

#  endif

# endif



# ifdef YYSTACK_ALLOC

   /* Pacify GCC's `empty if-body' warning. */

#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)

# else

#  if defined (__STDC__) || defined (__cplusplus)

#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */

#   define YYSIZE_T size_t

#  endif

#  define YYSTACK_ALLOC malloc

#  define YYSTACK_FREE free

# endif

#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */





#if (! defined (yyoverflow) \

     && (! defined (__cplusplus) \

         || (YYSTYPE_IS_TRIVIAL)))



/* A type that is properly aligned for any stack member.  */

union yyalloc

{

  short yyss;

  YYSTYPE yyvs;

  };



/* The size of the maximum gap between one aligned stack and the next.  */

# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)



/* The size of an array large to enough to hold all stacks, each with

   N elements.  */

# define YYSTACK_BYTES(N) \

     ((N) * (sizeof (short) + sizeof (YYSTYPE))                         \

      + YYSTACK_GAP_MAXIMUM)



/* Copy COUNT objects from FROM to TO.  The source and destination do

   not overlap.  */

# ifndef YYCOPY

#  if 1 < __GNUC__

#   define YYCOPY(To, From, Count) \

      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))

#  else

#   define YYCOPY(To, From, Count)              \

      do                                        \

        {                                       \

          register YYSIZE_T yyi;                \

          for (yyi = 0; yyi < (Count); yyi++)   \

            (To)[yyi] = (From)[yyi];            \

        }                                       \

      while (0)

#  endif

# endif



/* Relocate STACK from its old location to the new one.  The

   local variables YYSIZE and YYSTACKSIZE give the old and new number of

   elements in the stack, and YYPTR gives the new location of the

   stack.  Advance YYPTR to a properly aligned location for the next

   stack.  */

# define YYSTACK_RELOCATE(Stack)                                        \

    do                                                                  \

      {                                                                 \

        YYSIZE_T yynewbytes;                                            \

        YYCOPY (&yyptr->Stack, Stack, yysize);                          \

        Stack = &yyptr->Stack;                                          \

        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \

        yyptr += yynewbytes / sizeof (*yyptr);                          \

      }                                                                 \

    while (0)



#endif



#if defined (__STDC__) || defined (__cplusplus)

   typedef signed char yysigned_char;

#else

   typedef short yysigned_char;

#endif



/* YYFINAL -- State number of the termination state. */

#define YYFINAL  2

/* YYLAST -- Last index in YYTABLE.  */

#define YYLAST   50



/* YYNTOKENS -- Number of terminals. */

#define YYNTOKENS  22

/* YYNNTS -- Number of nonterminals. */

#define YYNNTS  11

/* YYNRULES -- Number of rules. */

#define YYNRULES  51

/* YYNRULES -- Number of states. */

#define YYNSTATES  61



/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */

#define YYUNDEFTOK  2

#define YYMAXUTOK   273



#define YYTRANSLATE(YYX)                                                \

  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)



/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */

static const unsigned char yytranslate[] =

{

       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,

       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,

       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,

       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,

       2,     2,     2,     2,    20,     2,     2,    21,     2,     2,

       2,     2,     2,     2,     2,     2,     2,     2,    19,     2,

       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,

       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,

       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,

       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,

       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,

       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,

       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,

       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,

       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,

       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,

       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,

       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,

       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,

       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,

       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,

       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,

       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,

       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,

       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,

       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,

       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,

      15,    16,    17,    18

};



#if YYDEBUG

/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in

   YYRHS.  */

static const unsigned char yyprhs[] =

{

       0,     0,     3,     4,     7,     9,    11,    13,    15,    17,

      19,    22,    27,    32,    39,    46,    48,    50,    53,    55,

      58,    61,    65,    71,    75,    79,    82,    87,    90,    94,

      97,    99,   102,   105,   107,   110,   113,   115,   118,   121,

     123,   126,   129,   131,   134,   137,   139,   142,   145,   147,

     149,   150

};



/* YYRHS -- A `-1'-separated list of the rules' RHS. */

static const yysigned_char yyrhs[] =

{

      23,     0,    -1,    -1,    23,    24,    -1,    25,    -1,    26,

      -1,    28,    -1,    27,    -1,    29,    -1,    31,    -1,    16,

      10,    -1,    16,    19,    16,    32,    -1,    16,    19,    16,

      15,    -1,    16,    19,    16,    19,    16,    32,    -1,    16,

      19,    16,    19,    16,    15,    -1,    18,    -1,     6,    -1,

      18,     7,    -1,     4,    -1,     4,    20,    -1,    16,     4,

      -1,    16,    21,    16,    -1,    16,    21,    16,    21,    16,

      -1,    16,    15,    15,    -1,    16,    12,    15,    -1,    12,

      16,    -1,    12,    16,    20,    16,    -1,    16,    12,    -1,

      16,    12,    16,    -1,    30,     3,    -1,    30,    -1,    16,

      17,    -1,    15,    17,    -1,    17,    -1,    16,    13,    -1,

      15,    13,    -1,    13,    -1,    16,     5,    -1,    15,     5,

      -1,     5,    -1,    16,     8,    -1,    15,     8,    -1,     8,

      -1,    16,    11,    -1,    15,    11,    -1,    11,    -1,    16,

      14,    -1,    15,    14,    -1,    14,    -1,    16,    -1,    -1,

      10,    -1

};



/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */

static const unsigned short yyrline[] =

{

       0,   244,   244,   245,   248,   251,   254,   257,   260,   263,

     266,   272,   278,   287,   293,   305,   308,   312,   317,   321,

     325,   331,   335,   353,   359,   365,   369,   374,   378,   385,

     393,   396,   399,   402,   405,   408,   411,   414,   417,   420,

     423,   426,   429,   432,   435,   438,   441,   444,   447,   452,

     487,   490

};

#endif



#if YYDEBUG || YYERROR_VERBOSE

/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.

   First, the terminals, then, starting at YYNTOKENS, nonterminals. */

static const char *const yytname[] =

{

  "$end", "error", "$undefined", "tAGO", "tDAY", "tDAY_UNIT", "tDAYZONE", 

  "tDST", "tHOUR_UNIT", "tID", "tMERIDIAN", "tMINUTE_UNIT", "tMONTH", 

  "tMONTH_UNIT", "tSEC_UNIT", "tSNUMBER", "tUNUMBER", "tYEAR_UNIT", 

  "tZONE", "':'", "','", "'/'", "$accept", "spec", "item", "time", "zone", 

  "day", "date", "rel", "relunit", "number", "o_merid", 0

};

#endif



# ifdef YYPRINT

/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to

   token YYLEX-NUM.  */

static const unsigned short yytoknum[] =

{

       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,

     265,   266,   267,   268,   269,   270,   271,   272,   273,    58,

      44,    47

};

# endif



/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */

static const unsigned char yyr1[] =

{

       0,    22,    23,    23,    24,    24,    24,    24,    24,    24,

      25,    25,    25,    25,    25,    26,    26,    26,    27,    27,

      27,    28,    28,    28,    28,    28,    28,    28,    28,    29,

      29,    30,    30,    30,    30,    30,    30,    30,    30,    30,

      30,    30,    30,    30,    30,    30,    30,    30,    30,    31,

      32,    32

};



/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */

static const unsigned char yyr2[] =

{

       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,

       2,     4,     4,     6,     6,     1,     1,     2,     1,     2,

       2,     3,     5,     3,     3,     2,     4,     2,     3,     2,

       1,     2,     2,     1,     2,     2,     1,     2,     2,     1,

       2,     2,     1,     2,     2,     1,     2,     2,     1,     1,

       0,     1

};



/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state

   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero

   means the default is an error.  */

static const unsigned char yydefact[] =

{

       2,     0,     1,    18,    39,    16,    42,    45,     0,    36,

      48,     0,    49,    33,    15,     3,     4,     5,     7,     6,

       8,    30,     9,    19,    25,    38,    41,    44,    35,    47,

      32,    20,    37,    40,    10,    43,    27,    34,    46,     0,

      31,     0,     0,    17,    29,     0,    24,    28,    23,    50,

      21,    26,    51,    12,     0,    11,     0,    50,    22,    14,

      13

};



/* YYDEFGOTO[NTERM-NUM]. */

static const yysigned_char yydefgoto[] =

{

      -1,     1,    15,    16,    17,    18,    19,    20,    21,    22,

      55

};



/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing

   STATE-NUM.  */

#define YYPACT_NINF -20

static const yysigned_char yypact[] =

{

     -20,     0,   -20,   -19,   -20,   -20,   -20,   -20,   -13,   -20,

     -20,    30,    15,   -20,    14,   -20,   -20,   -20,   -20,   -20,

     -20,    19,   -20,   -20,     4,   -20,   -20,   -20,   -20,   -20,

     -20,   -20,   -20,   -20,   -20,   -20,    -6,   -20,   -20,    16,

     -20,    17,    23,   -20,   -20,    24,   -20,   -20,   -20,    27,

      28,   -20,   -20,   -20,    29,   -20,    32,    -8,   -20,   -20,

     -20

};



/* YYPGOTO[NTERM-NUM].  */

static const yysigned_char yypgoto[] =

{

     -20,   -20,   -20,   -20,   -20,   -20,   -20,   -20,   -20,   -20,

      -7

};



/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If

   positive, shift that token.  If negative, reduce the rule which

   number is the opposite.  If zero, do what YYDEFACT says.

   If YYTABLE_NINF, syntax error.  */

#define YYTABLE_NINF -1

static const unsigned char yytable[] =

{

       2,    23,    52,    24,     3,     4,     5,    59,     6,    46,

      47,     7,     8,     9,    10,    11,    12,    13,    14,    31,

      32,    43,    44,    33,    45,    34,    35,    36,    37,    38,

      39,    48,    40,    49,    41,    25,    42,    52,    26,    50,

      51,    27,    53,    28,    29,    57,    54,    30,    58,    56,

      60

};



static const unsigned char yycheck[] =

{

       0,    20,    10,    16,     4,     5,     6,    15,     8,    15,

      16,    11,    12,    13,    14,    15,    16,    17,    18,     4,

       5,     7,     3,     8,    20,    10,    11,    12,    13,    14,

      15,    15,    17,    16,    19,     5,    21,    10,     8,    16,

      16,    11,    15,    13,    14,    16,    19,    17,    16,    21,

      57

};



/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing

   symbol of state STATE-NUM.  */

static const unsigned char yystos[] =

{

       0,    23,     0,     4,     5,     6,     8,    11,    12,    13,

      14,    15,    16,    17,    18,    24,    25,    26,    27,    28,

      29,    30,    31,    20,    16,     5,     8,    11,    13,    14,

      17,     4,     5,     8,    10,    11,    12,    13,    14,    15,

      17,    19,    21,     7,     3,    20,    15,    16,    15,    16,

      16,    16,    10,    15,    19,    32,    21,    16,    16,    15,

      32

};



#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)

# define YYSIZE_T __SIZE_TYPE__

#endif

#if ! defined (YYSIZE_T) && defined (size_t)

# define YYSIZE_T size_t

#endif

#if ! defined (YYSIZE_T)

# if defined (__STDC__) || defined (__cplusplus)

#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */

#  define YYSIZE_T size_t

# endif

#endif

#if ! defined (YYSIZE_T)

# define YYSIZE_T unsigned int

#endif



#define yyerrok         (yyerrstatus = 0)

#define yyclearin       (yychar = YYEMPTY)

#define YYEMPTY         (-2)

#define YYEOF           0



#define YYACCEPT        goto yyacceptlab

#define YYABORT         goto yyabortlab

#define YYERROR         goto yyerrlab1





/* Like YYERROR except do call yyerror.  This remains here temporarily

   to ease the transition to the new meaning of YYERROR, for GCC.

   Once GCC version 2 has supplanted version 1, this can go.  */



#define YYFAIL          goto yyerrlab



#define YYRECOVERING()  (!!yyerrstatus)



#define YYBACKUP(Token, Value)                                  \

do                                                              \

  if (yychar == YYEMPTY && yylen == 1)                          \

    {                                                           \

      yychar = (Token);                                         \

      yylval = (Value);                                         \

      yytoken = YYTRANSLATE (yychar);                           \

      YYPOPSTACK;                                               \

      goto yybackup;                                            \

    }                                                           \

  else                                                          \

    {                                                           \

      yyerror ("syntax error: cannot back up");\

      YYERROR;                                                  \

    }                                                           \

while (0)



#define YYTERROR        1

#define YYERRCODE       256



/* YYLLOC_DEFAULT -- Compute the default location (before the actions

   are run).  */



#ifndef YYLLOC_DEFAULT

# define YYLLOC_DEFAULT(Current, Rhs, N)         \

  Current.first_line   = Rhs[1].first_line;      \

  Current.first_column = Rhs[1].first_column;    \

  Current.last_line    = Rhs[N].last_line;       \

  Current.last_column  = Rhs[N].last_column;

#endif



/* YYLEX -- calling `yylex' with the right arguments.  */



#ifdef YYLEX_PARAM

# define YYLEX yylex (&yylval, YYLEX_PARAM)

#else

# define YYLEX yylex (&yylval)

#endif



/* Enable debugging if requested.  */

#if YYDEBUG



# ifndef YYFPRINTF

#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */

#  define YYFPRINTF fprintf

# endif



# define YYDPRINTF(Args)                        \

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

| TOP (cinluded).                                                   |

`------------------------------------------------------------------*/



#if defined (__STDC__) || defined (__cplusplus)

static void

yy_stack_print (short *bottom, short *top)

#else

static void

yy_stack_print (bottom, top)

    short *bottom;

    short *top;

#endif

{

  YYFPRINTF (stderr, "Stack now");

  for (/* Nothing. */; bottom <= top; ++bottom)

    YYFPRINTF (stderr, " %d", *bottom);

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

  unsigned int yylineno = yyrline[yyrule];

  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",

             yyrule - 1, yylineno);

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





/* YYINITDEPTH -- initial size of the parser's stacks.  */

#ifndef YYINITDEPTH

# define YYINITDEPTH 200

#endif



/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only

   if the built-in stack extension method is used).



   Do not make this value too large; the results are undefined if

   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)

   evaluated with infinite-precision integer arithmetic.  */



#if YYMAXDEPTH == 0

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

  register const char *yys = yystr;



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

  register char *yyd = yydest;

  register const char *yys = yysrc;



  while ((*yyd++ = *yys++) != '\0')

    continue;



  return yyd - 1;

}

#  endif

# endif



#endif /* !YYERROR_VERBOSE */







#if YYDEBUG

/*--------------------------------.

| Print this symbol on YYOUTPUT.  |

`--------------------------------*/



#if defined (__STDC__) || defined (__cplusplus)

static void

yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)

#else

static void

yysymprint (yyoutput, yytype, yyvaluep)

    FILE *yyoutput;

    int yytype;

    YYSTYPE *yyvaluep;

#endif

{

  /* Pacify ``unused variable'' warnings.  */

  (void) yyvaluep;



  if (yytype < YYNTOKENS)

    {

      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);

# ifdef YYPRINT

      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);

# endif

    }

  else

    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);



  switch (yytype)

    {

      default:

        break;

    }

  YYFPRINTF (yyoutput, ")");

}



#endif /* ! YYDEBUG */

/*-----------------------------------------------.

| Release the memory associated to this symbol.  |

`-----------------------------------------------*/



#if defined (__STDC__) || defined (__cplusplus)

static void

yydestruct (int yytype, YYSTYPE *yyvaluep)

#else

static void

yydestruct (yytype, yyvaluep)

    int yytype;

    YYSTYPE *yyvaluep;

#endif

{

  /* Pacify ``unused variable'' warnings.  */

  (void) yyvaluep;



  switch (yytype)

    {



      default:

        break;

    }

}





/* Prevent warnings from -Wmissing-prototypes.  */



#ifdef YYPARSE_PARAM

# if defined (__STDC__) || defined (__cplusplus)

int yyparse (void *YYPARSE_PARAM);

# else

int yyparse ();

# endif

#else /* ! YYPARSE_PARAM */

#if defined (__STDC__) || defined (__cplusplus)

int yyparse (void);

#else

int yyparse ();

#endif

#endif /* ! YYPARSE_PARAM */













/*----------.

| yyparse.  |

`----------*/



#ifdef YYPARSE_PARAM

# if defined (__STDC__) || defined (__cplusplus)

int yyparse (void *YYPARSE_PARAM)

# else

int yyparse (YYPARSE_PARAM)

  void *YYPARSE_PARAM;

# endif

#else /* ! YYPARSE_PARAM */

#if defined (__STDC__) || defined (__cplusplus)

int

yyparse (void)

#else

int

yyparse ()



#endif

#endif

{

  /* The lookahead symbol.  */

int yychar;



/* The semantic value of the lookahead symbol.  */

YYSTYPE yylval;



/* Number of syntax errors so far.  */

int yynerrs;



  register int yystate;

  register int yyn;

  int yyresult;

  /* Number of tokens to shift before error messages enabled.  */

  int yyerrstatus;

  /* Lookahead token as an internal (translated) token number.  */

  int yytoken = 0;



  /* Three stacks and their tools:

     `yyss': related to states,

     `yyvs': related to semantic values,

     `yyls': related to locations.



     Refer to the stacks thru separate pointers, to allow yyoverflow

     to reallocate them elsewhere.  */



  /* The state stack.  */

  short yyssa[YYINITDEPTH];

  short *yyss = yyssa;

  register short *yyssp;



  /* The semantic value stack.  */

  YYSTYPE yyvsa[YYINITDEPTH];

  YYSTYPE *yyvs = yyvsa;

  register YYSTYPE *yyvsp;







#define YYPOPSTACK   (yyvsp--, yyssp--)



  YYSIZE_T yystacksize = YYINITDEPTH;



  /* The variables used to return semantic value and location from the

     action routines.  */

  YYSTYPE yyval;





  /* When reducing, the number of symbols on the RHS of the reduced

     rule.  */

  int yylen;



  YYDPRINTF ((stderr, "Starting parse\n"));



  yystate = 0;

  yyerrstatus = 0;

  yynerrs = 0;

