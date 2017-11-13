int
ssl_expr_yyparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  register int ssl_expr_yystate;
  register int ssl_expr_yyn;
  register short *ssl_expr_yyssp;
  register YYSTYPE *ssl_expr_yyvsp;
  int ssl_expr_yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int ssl_expr_yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	ssl_expr_yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE ssl_expr_yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *ssl_expr_yyss = ssl_expr_yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *ssl_expr_yyvs = ssl_expr_yyvsa;	/*  to allow ssl_expr_yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE ssl_expr_yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *ssl_expr_yyls = ssl_expr_yylsa;
  YYLTYPE *ssl_expr_yylsp;

#define YYPOPSTACK   (ssl_expr_yyvsp--, ssl_expr_yyssp--, ssl_expr_yylsp--)
#else
#define YYPOPSTACK   (ssl_expr_yyvsp--, ssl_expr_yyssp--)
#endif

  int ssl_expr_yystacksize = YYINITDEPTH;
  int ssl_expr_yyfree_stacks = 0;

#ifdef YYPURE
  int ssl_expr_yychar;
  YYSTYPE ssl_expr_yylval;
  int ssl_expr_yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE ssl_expr_yylloc;
#endif
#endif

  YYSTYPE ssl_expr_yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int ssl_expr_yylen;

#if YYDEBUG != 0
  if (ssl_expr_yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  ssl_expr_yystate = 0;
  ssl_expr_yyerrstatus = 0;
  ssl_expr_yynerrs = 0;
  ssl_expr_yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  ssl_expr_yyssp = ssl_expr_yyss - 1;
  ssl_expr_yyvsp = ssl_expr_yyvs;
#ifdef YYLSP_NEEDED
  ssl_expr_yylsp = ssl_expr_yyls;
#endif

/* Push a new state, which is found in  ssl_expr_yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
ssl_expr_yynewstate:

  *++ssl_expr_yyssp = ssl_expr_yystate;

  if (ssl_expr_yyssp >= ssl_expr_yyss + ssl_expr_yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *ssl_expr_yyvs1 = ssl_expr_yyvs;
      short *ssl_expr_yyss1 = ssl_expr_yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *ssl_expr_yyls1 = ssl_expr_yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = ssl_expr_yyssp - ssl_expr_yyss + 1;

#ifdef ssl_expr_yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if ssl_expr_yyoverflow is a macro.  */
      ssl_expr_yyoverflow("parser stack overflow",
		 &ssl_expr_yyss1, size * sizeof (*ssl_expr_yyssp),
		 &ssl_expr_yyvs1, size * sizeof (*ssl_expr_yyvsp),
		 &ssl_expr_yyls1, size * sizeof (*ssl_expr_yylsp),
		 &ssl_expr_yystacksize);
#else
      ssl_expr_yyoverflow("parser stack overflow",
		 &ssl_expr_yyss1, size * sizeof (*ssl_expr_yyssp),
		 &ssl_expr_yyvs1, size * sizeof (*ssl_expr_yyvsp),
		 &ssl_expr_yystacksize);
#endif

      ssl_expr_yyss = ssl_expr_yyss1; ssl_expr_yyvs = ssl_expr_yyvs1;
#ifdef YYLSP_NEEDED
      ssl_expr_yyls = ssl_expr_yyls1;
#endif
#else /* no ssl_expr_yyoverflow */
      /* Extend the stack our own way.  */
      if (ssl_expr_yystacksize >= YYMAXDEPTH)
	{
	  ssl_expr_yyerror("parser stack overflow");
	  if (ssl_expr_yyfree_stacks)
	    {
	      free (ssl_expr_yyss);
	      free (ssl_expr_yyvs);
#ifdef YYLSP_NEEDED
	      free (ssl_expr_yyls);
#endif
	    }
	  return 2;
	}
      ssl_expr_yystacksize *= 2;
      if (ssl_expr_yystacksize > YYMAXDEPTH)
	ssl_expr_yystacksize = YYMAXDEPTH;
#ifndef YYSTACK_USE_ALLOCA
      ssl_expr_yyfree_stacks = 1;
#endif
      ssl_expr_yyss = (short *) YYSTACK_ALLOC (ssl_expr_yystacksize * sizeof (*ssl_expr_yyssp));
      __ssl_expr_yy_memcpy ((char *)ssl_expr_yyss, (char *)ssl_expr_yyss1,
		   size * (unsigned int) sizeof (*ssl_expr_yyssp));
      ssl_expr_yyvs = (YYSTYPE *) YYSTACK_ALLOC (ssl_expr_yystacksize * sizeof (*ssl_expr_yyvsp));
      __ssl_expr_yy_memcpy ((char *)ssl_expr_yyvs, (char *)ssl_expr_yyvs1,
		   size * (unsigned int) sizeof (*ssl_expr_yyvsp));
#ifdef YYLSP_NEEDED
      ssl_expr_yyls = (YYLTYPE *) YYSTACK_ALLOC (ssl_expr_yystacksize * sizeof (*ssl_expr_yylsp));
      __ssl_expr_yy_memcpy ((char *)ssl_expr_yyls, (char *)ssl_expr_yyls1,
		   size * (unsigned int) sizeof (*ssl_expr_yylsp));
#endif
#endif /* no ssl_expr_yyoverflow */

      ssl_expr_yyssp = ssl_expr_yyss + size - 1;
      ssl_expr_yyvsp = ssl_expr_yyvs + size - 1;
#ifdef YYLSP_NEEDED
      ssl_expr_yylsp = ssl_expr_yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (ssl_expr_yydebug)
	fprintf(stderr, "Stack size increased to %d\n", ssl_expr_yystacksize);
#endif

      if (ssl_expr_yyssp >= ssl_expr_yyss + ssl_expr_yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (ssl_expr_yydebug)
    fprintf(stderr, "Entering state %d\n", ssl_expr_yystate);
#endif

  goto ssl_expr_yybackup;
 ssl_expr_yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* ssl_expr_yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  ssl_expr_yyn = ssl_expr_yypact[ssl_expr_yystate];
  if (ssl_expr_yyn == YYFLAG)
    goto ssl_expr_yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* ssl_expr_yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (ssl_expr_yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (ssl_expr_yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      ssl_expr_yychar = YYLEX;
    }

  /* Convert token to internal form (in ssl_expr_yychar1) for indexing tables with */

  if (ssl_expr_yychar <= 0)		/* This means end of input. */
    {
      ssl_expr_yychar1 = 0;
      ssl_expr_yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (ssl_expr_yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      ssl_expr_yychar1 = YYTRANSLATE(ssl_expr_yychar);

#if YYDEBUG != 0
      if (ssl_expr_yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", ssl_expr_yychar, ssl_expr_yytname[ssl_expr_yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, ssl_expr_yychar, ssl_expr_yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  ssl_expr_yyn += ssl_expr_yychar1;
  if (ssl_expr_yyn < 0 || ssl_expr_yyn > YYLAST || ssl_expr_yycheck[ssl_expr_yyn] != ssl_expr_yychar1)
    goto ssl_expr_yydefault;

  ssl_expr_yyn = ssl_expr_yytable[ssl_expr_yyn];

  /* ssl_expr_yyn is what to do for this token type in this state.
     Negative => reduce, -ssl_expr_yyn is rule number.
     Positive => shift, ssl_expr_yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (ssl_expr_yyn < 0)
    {
      if (ssl_expr_yyn == YYFLAG)
	goto ssl_expr_yyerrlab;
      ssl_expr_yyn = -ssl_expr_yyn;
      goto ssl_expr_yyreduce;
    }
  else if (ssl_expr_yyn == 0)
    goto ssl_expr_yyerrlab;

  if (ssl_expr_yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (ssl_expr_yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", ssl_expr_yychar, ssl_expr_yytname[ssl_expr_yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (ssl_expr_yychar != YYEOF)
    ssl_expr_yychar = YYEMPTY;

  *++ssl_expr_yyvsp = ssl_expr_yylval;
#ifdef YYLSP_NEEDED
  *++ssl_expr_yylsp = ssl_expr_yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (ssl_expr_yyerrstatus) ssl_expr_yyerrstatus--;

  ssl_expr_yystate = ssl_expr_yyn;
  goto ssl_expr_yynewstate;

/* Do the default action for the current state.  */
ssl_expr_yydefault:

  ssl_expr_yyn = ssl_expr_yydefact[ssl_expr_yystate];
  if (ssl_expr_yyn == 0)
    goto ssl_expr_yyerrlab;

/* Do a reduction.  ssl_expr_yyn is the number of a rule to reduce with.  */
ssl_expr_yyreduce:
  ssl_expr_yylen = ssl_expr_yyr2[ssl_expr_yyn];
  if (ssl_expr_yylen > 0)
    ssl_expr_yyval = ssl_expr_yyvsp[1-ssl_expr_yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (ssl_expr_yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       ssl_expr_yyn, ssl_expr_yyrline[ssl_expr_yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = ssl_expr_yyprhs[ssl_expr_yyn]; ssl_expr_yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", ssl_expr_yytname[ssl_expr_yyrhs[i]]);
      fprintf (stderr, " -> %s\n", ssl_expr_yytname[ssl_expr_yyr1[ssl_expr_yyn]]);
    }
#endif


  switch (ssl_expr_yyn) {

case 1:
#line 115 "ssl_expr_parse.y"
{ ssl_expr_info.expr = ssl_expr_yyvsp[0].exVal; ;
    break;}
case 2:
#line 118 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_True,  NULL, NULL); ;
    break;}
case 3:
#line 119 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_False, NULL, NULL); ;
    break;}
case 4:
#line 120 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_Not,   ssl_expr_yyvsp[0].exVal,   NULL); ;
    break;}
case 5:
#line 121 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_Or,    ssl_expr_yyvsp[-2].exVal,   ssl_expr_yyvsp[0].exVal);   ;
    break;}
case 6:
#line 122 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_And,   ssl_expr_yyvsp[-2].exVal,   ssl_expr_yyvsp[0].exVal);   ;
    break;}
case 7:
#line 123 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_Comp,  ssl_expr_yyvsp[0].exVal,   NULL); ;
    break;}
case 8:
#line 124 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_yyvsp[-1].exVal; ;
    break;}
case 9:
#line 127 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_EQ,  ssl_expr_yyvsp[-2].exVal, ssl_expr_yyvsp[0].exVal); ;
    break;}
case 10:
#line 128 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_NE,  ssl_expr_yyvsp[-2].exVal, ssl_expr_yyvsp[0].exVal); ;
    break;}
case 11:
#line 129 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_LT,  ssl_expr_yyvsp[-2].exVal, ssl_expr_yyvsp[0].exVal); ;
    break;}
case 12:
#line 130 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_LE,  ssl_expr_yyvsp[-2].exVal, ssl_expr_yyvsp[0].exVal); ;
    break;}
case 13:
#line 131 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_GT,  ssl_expr_yyvsp[-2].exVal, ssl_expr_yyvsp[0].exVal); ;
    break;}
case 14:
#line 132 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_GE,  ssl_expr_yyvsp[-2].exVal, ssl_expr_yyvsp[0].exVal); ;
    break;}
case 15:
#line 133 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_IN,  ssl_expr_yyvsp[-4].exVal, ssl_expr_yyvsp[-1].exVal); ;
    break;}
case 16:
#line 134 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_REG, ssl_expr_yyvsp[-2].exVal, ssl_expr_yyvsp[0].exVal); ;
    break;}
case 17:
#line 135 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_NRE, ssl_expr_yyvsp[-2].exVal, ssl_expr_yyvsp[0].exVal); ;
    break;}
case 18:
#line 138 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_ListElement, ssl_expr_yyvsp[0].exVal, NULL); ;
    break;}
case 19:
#line 139 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_ListElement, ssl_expr_yyvsp[0].exVal, ssl_expr_yyvsp[-2].exVal);   ;
    break;}
case 20:
#line 142 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_Digit,  ssl_expr_yyvsp[0].cpVal, NULL); ;
    break;}
case 21:
#line 143 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_String, ssl_expr_yyvsp[0].cpVal, NULL); ;
    break;}
case 22:
#line 144 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_Var,    ssl_expr_yyvsp[-1].cpVal, NULL); ;
    break;}
case 23:
#line 145 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_yyvsp[0].exVal; ;
    break;}
case 24:
#line 148 "ssl_expr_parse.y"
{ 
                regex_t *regex;
                if ((regex = ap_pregcomp(ssl_expr_info.pool, ssl_expr_yyvsp[0].cpVal, 
                                         REG_EXTENDED|REG_NOSUB)) == NULL) {
                    ssl_expr_error = "Failed to compile regular expression";
                    YYERROR;
                    regex = NULL;
                }
                ssl_expr_yyval.exVal = ssl_expr_make(op_Regex, regex, NULL);
            ;
    break;}
case 25:
#line 158 "ssl_expr_parse.y"
{
                regex_t *regex;
                if ((regex = ap_pregcomp(ssl_expr_info.pool, ssl_expr_yyvsp[0].cpVal, 
                                         REG_EXTENDED|REG_NOSUB|REG_ICASE)) == NULL) {
                    ssl_expr_error = "Failed to compile regular expression";
                    YYERROR;
                    regex = NULL;
                }
                ssl_expr_yyval.exVal = ssl_expr_make(op_Regex, regex, NULL);
            ;
    break;}
case 26:
#line 170 "ssl_expr_parse.y"
{ 
               ssl_expr *args = ssl_expr_make(op_ListElement, ssl_expr_yyvsp[-1].cpVal, NULL);
               ssl_expr_yyval.exVal = ssl_expr_make(op_Func, "file", args);
            ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 543 "/usr/local/share/bison.simple"

  ssl_expr_yyvsp -= ssl_expr_yylen;
  ssl_expr_yyssp -= ssl_expr_yylen;
#ifdef YYLSP_NEEDED
  ssl_expr_yylsp -= ssl_expr_yylen;
#endif

#if YYDEBUG != 0
  if (ssl_expr_yydebug)
    {
      short *ssp1 = ssl_expr_yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != ssl_expr_yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++ssl_expr_yyvsp = ssl_expr_yyval;

#ifdef YYLSP_NEEDED
  ssl_expr_yylsp++;
  if (ssl_expr_yylen == 0)
    {
      ssl_expr_yylsp->first_line = ssl_expr_yylloc.first_line;
      ssl_expr_yylsp->first_column = ssl_expr_yylloc.first_column;
      ssl_expr_yylsp->last_line = (ssl_expr_yylsp-1)->last_line;
      ssl_expr_yylsp->last_column = (ssl_expr_yylsp-1)->last_column;
      ssl_expr_yylsp->text = 0;
    }
  else
    {
      ssl_expr_yylsp->last_line = (ssl_expr_yylsp+ssl_expr_yylen-1)->last_line;
      ssl_expr_yylsp->last_column = (ssl_expr_yylsp+ssl_expr_yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  ssl_expr_yyn = ssl_expr_yyr1[ssl_expr_yyn];

  ssl_expr_yystate = ssl_expr_yypgoto[ssl_expr_yyn - YYNTBASE] + *ssl_expr_yyssp;
  if (ssl_expr_yystate >= 0 && ssl_expr_yystate <= YYLAST && ssl_expr_yycheck[ssl_expr_yystate] == *ssl_expr_yyssp)
    ssl_expr_yystate = ssl_expr_yytable[ssl_expr_yystate];
  else
    ssl_expr_yystate = ssl_expr_yydefgoto[ssl_expr_yyn - YYNTBASE];

  goto ssl_expr_yynewstate;

ssl_expr_yyerrlab:   /* here on detecting error */

  if (! ssl_expr_yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++ssl_expr_yynerrs;

#ifdef YYERROR_VERBOSE
      ssl_expr_yyn = ssl_expr_yypact[ssl_expr_yystate];

      if (ssl_expr_yyn > YYFLAG && ssl_expr_yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -ssl_expr_yyn if nec to avoid negative indexes in ssl_expr_yycheck.  */
	  for (x = (ssl_expr_yyn < 0 ? -ssl_expr_yyn : 0);
	       x < (sizeof(ssl_expr_yytname) / sizeof(char *)); x++)
	    if (ssl_expr_yycheck[x + ssl_expr_yyn] == x)
	      size += strlen(ssl_expr_yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (ssl_expr_yyn < 0 ? -ssl_expr_yyn : 0);
		       x < (sizeof(ssl_expr_yytname) / sizeof(char *)); x++)
		    if (ssl_expr_yycheck[x + ssl_expr_yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, ssl_expr_yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      ssl_expr_yyerror(msg);
	      free(msg);
	    }
	  else
	    ssl_expr_yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	ssl_expr_yyerror("parse error");
    }

  goto ssl_expr_yyerrlab1;
ssl_expr_yyerrlab1:   /* here on error raised explicitly by an action */

  if (ssl_expr_yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (ssl_expr_yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (ssl_expr_yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", ssl_expr_yychar, ssl_expr_yytname[ssl_expr_yychar1]);
#endif

      ssl_expr_yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  ssl_expr_yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto ssl_expr_yyerrhandle;

ssl_expr_yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  ssl_expr_yyn = ssl_expr_yydefact[ssl_expr_yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (ssl_expr_yyn) goto ssl_expr_yydefault;
#endif

ssl_expr_yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (ssl_expr_yyssp == ssl_expr_yyss) YYABORT;
  ssl_expr_yyvsp--;
  ssl_expr_yystate = *--ssl_expr_yyssp;
#ifdef YYLSP_NEEDED
  ssl_expr_yylsp--;
#endif

#if YYDEBUG != 0
  if (ssl_expr_yydebug)
    {
      short *ssp1 = ssl_expr_yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != ssl_expr_yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

ssl_expr_yyerrhandle:

  ssl_expr_yyn = ssl_expr_yypact[ssl_expr_yystate];
  if (ssl_expr_yyn == YYFLAG)
    goto ssl_expr_yyerrdefault;

  ssl_expr_yyn += YYTERROR;
  if (ssl_expr_yyn < 0 || ssl_expr_yyn > YYLAST || ssl_expr_yycheck[ssl_expr_yyn] != YYTERROR)
    goto ssl_expr_yyerrdefault;

  ssl_expr_yyn = ssl_expr_yytable[ssl_expr_yyn];
  if (ssl_expr_yyn < 0)
    {
      if (ssl_expr_yyn == YYFLAG)
	goto ssl_expr_yyerrpop;
      ssl_expr_yyn = -ssl_expr_yyn;
      goto ssl_expr_yyreduce;
    }
  else if (ssl_expr_yyn == 0)
    goto ssl_expr_yyerrpop;

  if (ssl_expr_yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (ssl_expr_yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++ssl_expr_yyvsp = ssl_expr_yylval;
#ifdef YYLSP_NEEDED
  *++ssl_expr_yylsp = ssl_expr_yylloc;
#endif

  ssl_expr_yystate = ssl_expr_yyn;
  goto ssl_expr_yynewstate;

 ssl_expr_yyacceptlab:
  /* YYACCEPT comes here.  */
  if (ssl_expr_yyfree_stacks)
    {
      free (ssl_expr_yyss);
      free (ssl_expr_yyvs);
#ifdef YYLSP_NEEDED
      free (ssl_expr_yyls);
#endif
    }
  return 0;

 ssl_expr_yyabortlab:
  /* YYABORT comes here.  */
  if (ssl_expr_yyfree_stacks)
    {
      free (ssl_expr_yyss);
      free (ssl_expr_yyvs);
#ifdef YYLSP_NEEDED
      free (ssl_expr_yyls);
#endif
    }
  return 1;
}