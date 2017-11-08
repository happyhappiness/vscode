int
yyparse (ap_expr_parse_ctx_t *ctx)
#else
int
yyparse (ctx)
    ap_expr_parse_ctx_t *ctx;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 112 "util_expr_parse.y"
    { ctx->expr = (yyvsp[(2) - (2)].exVal); }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 113 "util_expr_parse.y"
    { ctx->expr = (yyvsp[(2) - (2)].exVal); }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 114 "util_expr_parse.y"
    { YYABORT; }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 117 "util_expr_parse.y"
    { (yyval.exVal) = ap_expr_make(op_True,        NULL, NULL, ctx); }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 118 "util_expr_parse.y"
    { (yyval.exVal) = ap_expr_make(op_False,       NULL, NULL, ctx); }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 119 "util_expr_parse.y"
    { (yyval.exVal) = ap_expr_make(op_Not,         (yyvsp[(2) - (2)].exVal),   NULL, ctx); }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 120 "util_expr_parse.y"
    { (yyval.exVal) = ap_expr_make(op_Or,          (yyvsp[(1) - (3)].exVal),   (yyvsp[(3) - (3)].exVal),   ctx); }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 121 "util_expr_parse.y"
    { (yyval.exVal) = ap_expr_make(op_And,         (yyvsp[(1) - (3)].exVal),   (yyvsp[(3) - (3)].exVal),   ctx); }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 122 "util_expr_parse.y"
    { (yyval.exVal) = ap_expr_make(op_Comp,        (yyvsp[(1) - (1)].exVal),   NULL, ctx); }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 123 "util_expr_parse.y"
    { (yyval.exVal) = ap_expr_unary_op_make(       (yyvsp[(1) - (2)].cpVal),   (yyvsp[(2) - (2)].exVal),   ctx); }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 124 "util_expr_parse.y"
    { (yyval.exVal) = ap_expr_binary_op_make((yyvsp[(2) - (3)].cpVal),   (yyvsp[(1) - (3)].exVal),   (yyvsp[(3) - (3)].exVal),   ctx); }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 125 "util_expr_parse.y"
    { (yyval.exVal) = (yyvsp[(2) - (3)].exVal); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 126 "util_expr_parse.y"
    { YYABORT; }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 129 "util_expr_parse.y"
    { (yyval.exVal) = ap_expr_make(op_EQ,      (yyvsp[(1) - (3)].exVal), (yyvsp[(3) - (3)].exVal), ctx); }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 130 "util_expr_parse.y"
    { (yyval.exVal) = ap_expr_make(op_NE,      (yyvsp[(1) - (3)].exVal), (yyvsp[(3) - (3)].exVal), ctx); }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 131 "util_expr_parse.y"
    { (yyval.exVal) = ap_expr_make(op_LT,      (yyvsp[(1) - (3)].exVal), (yyvsp[(3) - (3)].exVal), ctx); }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 132 "util_expr_parse.y"
    { (yyval.exVal) = ap_expr_make(op_LE,      (yyvsp[(1) - (3)].exVal), (yyvsp[(3) - (3)].exVal), ctx); }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 133 "util_expr_parse.y"
    { (yyval.exVal) = ap_expr_make(op_GT,      (yyvsp[(1) - (3)].exVal), (yyvsp[(3) - (3)].exVal), ctx); }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 134 "util_expr_parse.y"
    { (yyval.exVal) = ap_expr_make(op_GE,      (yyvsp[(1) - (3)].exVal), (yyvsp[(3) - (3)].exVal), ctx); }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 135 "util_expr_parse.y"
    { (yyval.exVal) = ap_expr_make(op_STR_EQ,  (yyvsp[(1) - (3)].exVal), (yyvsp[(3) - (3)].exVal), ctx); }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 136 "util_expr_parse.y"
    { (yyval.exVal) = ap_expr_make(op_STR_NE,  (yyvsp[(1) - (3)].exVal), (yyvsp[(3) - (3)].exVal), ctx); }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 137 "util_expr_parse.y"
    { (yyval.exVal) = ap_expr_make(op_STR_LT,  (yyvsp[(1) - (3)].exVal), (yyvsp[(3) - (3)].exVal), ctx); }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 138 "util_expr_parse.y"
    { (yyval.exVal) = ap_expr_make(op_STR_LE,  (yyvsp[(1) - (3)].exVal), (yyvsp[(3) - (3)].exVal), ctx); }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 139 "util_expr_parse.y"
    { (yyval.exVal) = ap_expr_make(op_STR_GT,  (yyvsp[(1) - (3)].exVal), (yyvsp[(3) - (3)].exVal), ctx); }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 140 "util_expr_parse.y"
    { (yyval.exVal) = ap_expr_make(op_STR_GE,  (yyvsp[(1) - (3)].exVal), (yyvsp[(3) - (3)].exVal), ctx); }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 141 "util_expr_parse.y"
    { (yyval.exVal) = ap_expr_make(op_IN,      (yyvsp[(1) - (3)].exVal), (yyvsp[(3) - (3)].exVal), ctx); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 142 "util_expr_parse.y"
    { (yyval.exVal) = ap_expr_make(op_REG,     (yyvsp[(1) - (3)].exVal), (yyvsp[(3) - (3)].exVal), ctx); }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 143 "util_expr_parse.y"
    { (yyval.exVal) = ap_expr_make(op_NRE,     (yyvsp[(1) - (3)].exVal), (yyvsp[(3) - (3)].exVal), ctx); }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 146 "util_expr_parse.y"
    { (yyval.exVal) = (yyvsp[(1) - (1)].exVal); }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 147 "util_expr_parse.y"
    { (yyval.exVal) = (yyvsp[(2) - (3)].exVal); }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 150 "util_expr_parse.y"
    { (yyval.exVal) = ap_expr_make(op_ListElement, (yyvsp[(1) - (1)].exVal), NULL, ctx); }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 151 "util_expr_parse.y"
    { (yyval.exVal) = ap_expr_make(op_ListElement, (yyvsp[(3) - (3)].exVal), (yyvsp[(1) - (3)].exVal),   ctx); }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 154 "util_expr_parse.y"
    { (yyval.exVal) = ap_expr_make(op_Concat, (yyvsp[(1) - (2)].exVal), (yyvsp[(2) - (2)].exVal), ctx); }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 155 "util_expr_parse.y"
    { (yyval.exVal) = (yyvsp[(1) - (1)].exVal); }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 156 "util_expr_parse.y"
    { YYABORT; }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 159 "util_expr_parse.y"
    { (yyval.exVal) = ap_expr_make(op_String, (yyvsp[(1) - (1)].cpVal), NULL, ctx); }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 160 "util_expr_parse.y"
    { (yyval.exVal) = (yyvsp[(1) - (1)].exVal); }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 161 "util_expr_parse.y"
    { (yyval.exVal) = (yyvsp[(1) - (1)].exVal); }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 164 "util_expr_parse.y"
    { (yyval.exVal) = ap_expr_var_make((yyvsp[(2) - (3)].cpVal), ctx); }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 165 "util_expr_parse.y"
    { (yyval.exVal) = ap_expr_str_func_make((yyvsp[(2) - (5)].cpVal), (yyvsp[(4) - (5)].exVal), ctx); }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 168 "util_expr_parse.y"
    { (yyval.exVal) = ap_expr_make(op_Digit,  (yyvsp[(1) - (1)].cpVal), NULL, ctx); }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 169 "util_expr_parse.y"
    { (yyval.exVal) = ap_expr_make(op_Concat, (yyvsp[(1) - (3)].exVal), (yyvsp[(3) - (3)].exVal),   ctx); }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 170 "util_expr_parse.y"
    { (yyval.exVal) = (yyvsp[(1) - (1)].exVal); }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 171 "util_expr_parse.y"
    { (yyval.exVal) = (yyvsp[(1) - (1)].exVal); }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 172 "util_expr_parse.y"
    { (yyval.exVal) = (yyvsp[(1) - (1)].exVal); }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 173 "util_expr_parse.y"
    { (yyval.exVal) = (yyvsp[(2) - (3)].exVal); }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 174 "util_expr_parse.y"
    { (yyval.exVal) = ap_expr_make(op_String, "", NULL, ctx); }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 177 "util_expr_parse.y"
    {
                ap_regex_t *regex;
                if ((regex = ap_pregcomp(ctx->pool, (yyvsp[(1) - (1)].cpVal),
                                         AP_REG_EXTENDED|AP_REG_NOSUB)) == NULL) {
                    ctx->error = "Failed to compile regular expression";
                    YYERROR;
                }
                (yyval.exVal) = ap_expr_make(op_Regex, regex, NULL, ctx);
            }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 186 "util_expr_parse.y"
    {
                ap_regex_t *regex;
                if ((regex = ap_pregcomp(ctx->pool, (yyvsp[(1) - (1)].cpVal),
                                         AP_REG_EXTENDED|AP_REG_NOSUB|AP_REG_ICASE)) == NULL) {
                    ctx->error = "Failed to compile regular expression";
                    YYERROR;
                }
                (yyval.exVal) = ap_expr_make(op_Regex, regex, NULL, ctx);
            }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 197 "util_expr_parse.y"
    {
                int *n = apr_palloc(ctx->pool, sizeof(int));
                *n = (yyvsp[(1) - (1)].num);
                (yyval.exVal) = ap_expr_make(op_RegexBackref, n, NULL, ctx);
            }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 204 "util_expr_parse.y"
    { (yyval.exVal) = ap_expr_list_func_make((yyvsp[(1) - (4)].cpVal), (yyvsp[(3) - (4)].exVal), ctx); }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 207 "util_expr_parse.y"
    { (yyval.exVal) = ap_expr_str_func_make((yyvsp[(1) - (4)].cpVal), (yyvsp[(3) - (4)].exVal), ctx); }
    break;



/* Line 1806 of yacc.c  */
#line 1891 "util_expr_parse.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (ctx, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (ctx, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, ctx);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, ctx);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (ctx, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, ctx);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, ctx);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}