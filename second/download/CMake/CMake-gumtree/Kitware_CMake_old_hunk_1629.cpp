    int         yyRelMonth;
    int         yyRelSeconds;
    int         yyRelYear;
} CONTEXT;

/* enable use of extra argument to yyparse and yylex which can be used to pass
**  in a user defined value (CONTEXT struct in our case)
*/
#define YYPARSE_PARAM cookie
#define YYLEX_PARAM cookie
#define context ((CONTEXT *) cookie)

#line 215 "getdate.y"
typedef union {
    int                 Number;
    enum _MERIDIAN      Meridian;
} YYSTYPE;
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define YYFINAL         61
#define YYFLAG          -32768
#define YYNTBASE        22

#define YYTRANSLATE(x) ((unsigned)(x) <= 272 ? yytranslate[x] : 32)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,    20,     2,     2,    21,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,    19,     2,     2,
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
     2,     2,     2,     2,     2,     1,     3,     4,     5,     6,
     7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
    17,    18
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,     4,     6,     8,    10,    12,    14,    16,    19,
    24,    29,    36,    43,    45,    47,    50,    52,    55,    58,
    62,    68,    72,    76,    79,    84,    87,    91,    94,    96,
    99,   102,   104,   107,   110,   112,   115,   118,   120,   123,
   126,   128,   131,   134,   136,   139,   142,   144,   146,   147
};

static const short yyrhs[] = {    -1,
    22,    23,     0,    24,     0,    25,     0,    27,     0,    26,
     0,    28,     0,    30,     0,    16,    10,     0,    16,    19,
    16,    31,     0,    16,    19,    16,    15,     0,    16,    19,
    16,    19,    16,    31,     0,    16,    19,    16,    19,    16,
    15,     0,    18,     0,     6,     0,    18,     7,     0,     4,
     0,     4,    20,     0,    16,     4,     0,    16,    21,    16,
     0,    16,    21,    16,    21,    16,     0,    16,    15,    15,
     0,    16,    12,    15,     0,    12,    16,     0,    12,    16,
    20,    16,     0,    16,    12,     0,    16,    12,    16,     0,
    29,     3,     0,    29,     0,    16,    17,     0,    15,    17,
     0,    17,     0,    16,    13,     0,    15,    13,     0,    13,
     0,    16,     5,     0,    15,     5,     0,     5,     0,    16,
     8,     0,    15,     8,     0,     8,     0,    16,    11,     0,
    15,    11,     0,    11,     0,    16,    14,     0,    15,    14,
     0,    14,     0,    16,     0,     0,    10,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   231,   232,   235,   238,   241,   244,   247,   250,   253,   259,
   265,   274,   280,   292,   295,   298,   304,   308,   312,   318,
   322,   340,   346,   352,   356,   361,   365,   372,   380,   383,
   386,   389,   392,   395,   398,   401,   404,   407,   410,   413,
   416,   419,   422,   425,   428,   431,   434,   439,   473,   477
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","tAGO","tDAY",
"tDAY_UNIT","tDAYZONE","tDST","tHOUR_UNIT","tID","tMERIDIAN","tMINUTE_UNIT",
"tMONTH","tMONTH_UNIT","tSEC_UNIT","tSNUMBER","tUNUMBER","tYEAR_UNIT","tZONE",
"':'","','","'/'","spec","item","time","zone","day","date","rel","relunit","number",
"o_merid", NULL
};
#endif

static const short yyr1[] = {     0,
    22,    22,    23,    23,    23,    23,    23,    23,    24,    24,
    24,    24,    24,    25,    25,    25,    26,    26,    26,    27,
    27,    27,    27,    27,    27,    27,    27,    28,    28,    29,
    29,    29,    29,    29,    29,    29,    29,    29,    29,    29,
    29,    29,    29,    29,    29,    29,    29,    30,    31,    31
};

static const short yyr2[] = {     0,
     0,     2,     1,     1,     1,     1,     1,     1,     2,     4,
     4,     6,     6,     1,     1,     2,     1,     2,     2,     3,
     5,     3,     3,     2,     4,     2,     3,     2,     1,     2,
     2,     1,     2,     2,     1,     2,     2,     1,     2,     2,
     1,     2,     2,     1,     2,     2,     1,     1,     0,     1
};

static const short yydefact[] = {     1,
     0,    17,    38,    15,    41,    44,     0,    35,    47,     0,
    48,    32,    14,     2,     3,     4,     6,     5,     7,    29,
     8,    18,    24,    37,    40,    43,    34,    46,    31,    19,
    36,    39,     9,    42,    26,    33,    45,     0,    30,     0,
     0,    16,    28,     0,    23,    27,    22,    49,    20,    25,
    50,    11,     0,    10,     0,    49,    21,    13,    12,     0,
     0
};

static const short yydefgoto[] = {     1,
    14,    15,    16,    17,    18,    19,    20,    21,    54
};

static const short yypact[] = {-32768,
     0,   -19,-32768,-32768,-32768,-32768,   -13,-32768,-32768,    30,
    15,-32768,    14,-32768,-32768,-32768,-32768,-32768,-32768,    19,
-32768,-32768,     4,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,    -6,-32768,-32768,    16,-32768,    17,
    23,-32768,-32768,    24,-32768,-32768,-32768,    27,    28,-32768,
-32768,-32768,    29,-32768,    32,    -8,-32768,-32768,-32768,    50,
-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    -5
};


#define YYLAST          51


static const short yytable[] = {    60,
    22,    51,    23,     2,     3,     4,    58,     5,    45,    46,
     6,     7,     8,     9,    10,    11,    12,    13,    30,    31,
    42,    43,    32,    44,    33,    34,    35,    36,    37,    38,
    47,    39,    48,    40,    24,    41,    51,    25,    49,    50,
    26,    52,    27,    28,    56,    53,    29,    57,    55,    61,
    59
};

static const short yycheck[] = {     0,
    20,    10,    16,     4,     5,     6,    15,     8,    15,    16,
    11,    12,    13,    14,    15,    16,    17,    18,     4,     5,
     7,     3,     8,    20,    10,    11,    12,    13,    14,    15,
    15,    17,    16,    19,     5,    21,    10,     8,    16,    16,
    11,    15,    13,    14,    16,    19,    17,    16,    21,     0,
    56
};
#define YYPURE 1

/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/local/share/bison.simple"
/* This file comes from bison-1.28.  */

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

#ifndef YYSTACK_USE_ALLOCA
#ifdef alloca
#define YYSTACK_USE_ALLOCA
#else /* alloca not defined */
#ifdef __GNUC__
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi) || (defined (__sun) && defined (__i386))
#define YYSTACK_USE_ALLOCA
#include <alloca.h>
#else /* not sparc */
/* We think this test detects Watcom and Microsoft C.  */
/* This used to test MSDOS, but that is a bad idea
   since that symbol is in the user namespace.  */
#if (defined (_MSDOS) || defined (_MSDOS_)) && !defined (__TURBOC__)
#if 0 /* No need for malloc.h, which pollutes the namespace;
         instead, just don't use alloca.  */
#include <malloc.h>
#endif
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
/* I don't know what this was needed for, but it pollutes the namespace.
   So I turned it off.   rms, 2 May 1997.  */
/* #include <malloc.h>  */
 #pragma alloca
#define YYSTACK_USE_ALLOCA
#else /* not MSDOS, or __TURBOC__, or _AIX */
#if 0
#ifdef __hpux /* haible@ilog.fr says this works for HPUX 9.05 and up,
                 and on HPUX 10.  Eventually we can turn this on.  */
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#endif /* __hpux */
#endif
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc */
#endif /* not GNU C */
#endif /* alloca not defined */
#endif /* YYSTACK_USE_ALLOCA not defined */

#ifdef YYSTACK_USE_ALLOCA
#define YYSTACK_ALLOC alloca
#else
#define YYSTACK_ALLOC malloc
#endif

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         -2
#define YYEOF           0
#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL          goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do                                                              \
  if (yychar == YYEMPTY && yylen == 1)                          \
    { yychar = (token), yylval = (value);                       \
      yychar1 = YYTRANSLATE (yychar);                           \
      YYPOPSTACK;                                               \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    { yyerror ("syntax error: cannot back up"); YYERROR; }      \
while (0)

#define YYTERROR        1
#define YYERRCODE       256

#ifndef YYPURE
#define YYLEX           yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX           yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX           yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX           yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX           yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int     yychar;                 /*  the lookahead symbol                */
YYSTYPE yylval;                 /*  the semantic value of the           */
                                /*  lookahead symbol                    */

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;                 /*  location data for the lookahead     */
                                /*  symbol                              */
#endif

int yynerrs;                    /*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;                    /*  nonzero means print parse trace     */
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks       */

#ifndef YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Define __yy_memcpy.  Note that the size argument
   should be passed with type unsigned int, because that is what the non-GCC
   definitions require.  With GCC, __builtin_memcpy takes an arg
   of type size_t, but it can handle unsigned int.  */

#if __GNUC__ > 1                /* GNU C and GNU C++ define this.  */
#define __yy_memcpy(TO,FROM,COUNT)      __builtin_memcpy(TO,FROM,COUNT)
#else                           /* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (to, from, count)
     char *to;
     char *from;
     unsigned int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *to, char *from, unsigned int count)
{
  register char *t = to;
  register char *f = from;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 217 "/usr/local/share/bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
#ifdef YYPARSE_PARAM
int yyparse (void *);
#else
int yyparse (void);
#endif
#endif

int
yyparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;      /*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;              /*  lookahead token as an internal (translated) token number */

  short yyssa[YYINITDEPTH];     /*  the state stack                     */
  YYSTYPE yyvsa[YYINITDEPTH];   /*  the semantic value stack            */

  short *yyss = yyssa;          /*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;        /*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];   /*  the location stack                  */
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;
  int yyfree_stacks = 0;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;                /*  the variable used to return         */
                                /*  semantic values from the action     */
                                /*  routines                            */

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yylval.Number = 0;
  yyval.Number = 0;
   
  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
