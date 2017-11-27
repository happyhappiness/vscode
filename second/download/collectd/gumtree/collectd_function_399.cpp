int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
      yychar = yylex ();
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

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
#line 73 "parser.y" /* yacc.c:1646  */
    {(yyval.string) = unquote ((yyvsp[0].string));}
#line 1265 "parser.c" /* yacc.c:1646  */
    break;

  case 3:
#line 74 "parser.y" /* yacc.c:1646  */
    {(yyval.string) = strdup ((yyvsp[0].string));}
#line 1271 "parser.c" /* yacc.c:1646  */
    break;

  case 4:
#line 78 "parser.y" /* yacc.c:1646  */
    {(yyval.cv).value.number = (yyvsp[0].number); (yyval.cv).type = OCONFIG_TYPE_NUMBER;}
#line 1277 "parser.c" /* yacc.c:1646  */
    break;

  case 5:
#line 79 "parser.y" /* yacc.c:1646  */
    {(yyval.cv).value.boolean = 1; (yyval.cv).type = OCONFIG_TYPE_BOOLEAN;}
#line 1283 "parser.c" /* yacc.c:1646  */
    break;

  case 6:
#line 80 "parser.y" /* yacc.c:1646  */
    {(yyval.cv).value.boolean = 0; (yyval.cv).type = OCONFIG_TYPE_BOOLEAN;}
#line 1289 "parser.c" /* yacc.c:1646  */
    break;

  case 7:
#line 81 "parser.y" /* yacc.c:1646  */
    {(yyval.cv).value.string = (yyvsp[0].string); (yyval.cv).type = OCONFIG_TYPE_STRING;}
#line 1295 "parser.c" /* yacc.c:1646  */
    break;

  case 8:
#line 86 "parser.y" /* yacc.c:1646  */
    {
	 (yyval.al) = (yyvsp[-1].al);
	 (yyval.al).argument_num++;
	 (yyval.al).argument = realloc ((yyval.al).argument, (yyval.al).argument_num * sizeof (oconfig_value_t));
	 (yyval.al).argument[(yyval.al).argument_num-1] = (yyvsp[0].cv);
	}
#line 1306 "parser.c" /* yacc.c:1646  */
    break;

  case 9:
#line 93 "parser.y" /* yacc.c:1646  */
    {
	 (yyval.al).argument = malloc (sizeof (oconfig_value_t));
	 (yyval.al).argument[0] = (yyvsp[0].cv);
	 (yyval.al).argument_num = 1;
	}
#line 1316 "parser.c" /* yacc.c:1646  */
    break;

  case 10:
#line 101 "parser.y" /* yacc.c:1646  */
    {(yyval.string) = strdup ((yyvsp[0].string));}
#line 1322 "parser.c" /* yacc.c:1646  */
    break;

  case 11:
#line 106 "parser.y" /* yacc.c:1646  */
    {
	 memset (&(yyval.ci), '\0', sizeof ((yyval.ci)));
	 (yyval.ci).key = (yyvsp[-2].string);
	 (yyval.ci).values = (yyvsp[-1].al).argument;
	 (yyval.ci).values_num = (yyvsp[-1].al).argument_num;
	}
#line 1333 "parser.c" /* yacc.c:1646  */
    break;

  case 12:
#line 116 "parser.y" /* yacc.c:1646  */
    {
	 memset (&(yyval.ci), '\0', sizeof ((yyval.ci)));
	 (yyval.ci).key = (yyvsp[-2].string);
	}
#line 1342 "parser.c" /* yacc.c:1646  */
    break;

  case 13:
#line 122 "parser.y" /* yacc.c:1646  */
    {
	 memset (&(yyval.ci), '\0', sizeof ((yyval.ci)));
	 (yyval.ci).key = (yyvsp[-3].string);
	 (yyval.ci).values = (yyvsp[-2].al).argument;
	 (yyval.ci).values_num = (yyvsp[-2].al).argument_num;
	}
#line 1353 "parser.c" /* yacc.c:1646  */
    break;

  case 14:
#line 132 "parser.y" /* yacc.c:1646  */
    {
	 (yyval.string) = (yyvsp[-2].string);
	}
#line 1361 "parser.c" /* yacc.c:1646  */
    break;

  case 15:
#line 139 "parser.y" /* yacc.c:1646  */
    {
	 if (strcmp ((yyvsp[-2].ci).key, (yyvsp[0].string)) != 0)
	 {
		printf ("block_begin = %s; block_end = %s;\n", (yyvsp[-2].ci).key, (yyvsp[0].string));
	 	yyerror ("Block not closed..\n");
		exit (1);
	 }
	 free ((yyvsp[0].string)); (yyvsp[0].string) = NULL;
	 (yyval.ci) = (yyvsp[-2].ci);
	 (yyval.ci).children = (yyvsp[-1].sl).statement;
	 (yyval.ci).children_num = (yyvsp[-1].sl).statement_num;
	}
#line 1378 "parser.c" /* yacc.c:1646  */
    break;

  case 16:
#line 152 "parser.y" /* yacc.c:1646  */
    {
	 if (strcmp ((yyvsp[-1].ci).key, (yyvsp[0].string)) != 0)
	 {
		printf ("block_begin = %s; block_end = %s;\n", (yyvsp[-1].ci).key, (yyvsp[0].string));
		yyerror ("Block not closed..\n");
		exit (1);
	 }
	 free ((yyvsp[0].string)); (yyvsp[0].string) = NULL;
	 (yyval.ci) = (yyvsp[-1].ci);
	 (yyval.ci).children = NULL;
	 (yyval.ci).children_num = 0;
	}
#line 1395 "parser.c" /* yacc.c:1646  */
    break;

  case 17:
#line 167 "parser.y" /* yacc.c:1646  */
    {(yyval.ci) = (yyvsp[0].ci);}
#line 1401 "parser.c" /* yacc.c:1646  */
    break;

  case 18:
#line 168 "parser.y" /* yacc.c:1646  */
    {(yyval.ci) = (yyvsp[0].ci);}
#line 1407 "parser.c" /* yacc.c:1646  */
    break;

  case 19:
#line 169 "parser.y" /* yacc.c:1646  */
    {(yyval.ci).values_num = 0;}
#line 1413 "parser.c" /* yacc.c:1646  */
    break;

  case 20:
#line 174 "parser.y" /* yacc.c:1646  */
    {
	 (yyval.sl) = (yyvsp[-1].sl);
	 if (((yyvsp[0].ci).values_num > 0) || ((yyvsp[0].ci).children_num > 0))
	 {
		 (yyval.sl).statement_num++;
		 (yyval.sl).statement = realloc ((yyval.sl).statement, (yyval.sl).statement_num * sizeof (oconfig_item_t));
		 (yyval.sl).statement[(yyval.sl).statement_num-1] = (yyvsp[0].ci);
	 }
	}
#line 1427 "parser.c" /* yacc.c:1646  */
    break;

  case 21:
#line 184 "parser.y" /* yacc.c:1646  */
    {
	 if (((yyvsp[0].ci).values_num > 0) || ((yyvsp[0].ci).children_num > 0))
	 {
		 (yyval.sl).statement = malloc (sizeof (oconfig_item_t));
		 (yyval.sl).statement[0] = (yyvsp[0].ci);
		 (yyval.sl).statement_num = 1;
	 }
	 else
	 {
	 	(yyval.sl).statement = NULL;
		(yyval.sl).statement_num = 0;
	 }
	}
#line 1445 "parser.c" /* yacc.c:1646  */
    break;

  case 22:
#line 201 "parser.y" /* yacc.c:1646  */
    {
	 ci_root = malloc (sizeof (oconfig_item_t));
	 memset (ci_root, '\0', sizeof (oconfig_item_t));
	 ci_root->children = (yyvsp[0].sl).statement;
	 ci_root->children_num = (yyvsp[0].sl).statement_num;
	}
#line 1456 "parser.c" /* yacc.c:1646  */
    break;

  case 23:
#line 208 "parser.y" /* yacc.c:1646  */
    {
	 ci_root = malloc (sizeof (oconfig_item_t));
	 memset (ci_root, '\0', sizeof (oconfig_item_t));
	 ci_root->children = NULL;
	 ci_root->children_num = 0;
	}
#line 1467 "parser.c" /* yacc.c:1646  */
    break;


#line 1471 "parser.c" /* yacc.c:1646  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
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
        yyerror (yymsgp);
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
                      yytoken, &yylval);
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
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
  return yyresult;
}