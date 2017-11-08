int
ssl_expr_yyparse (YYPARSE_PARAM_ARG)
    YYPARSE_PARAM_DECL
{
    register int ssl_expr_yym, ssl_expr_yyn, ssl_expr_yystate;
#if YYDEBUG
    register const char *ssl_expr_yys;

    if ((ssl_expr_yys = getenv("YYDEBUG")))
    {
        ssl_expr_yyn = *ssl_expr_yys;
        if (ssl_expr_yyn >= '0' && ssl_expr_yyn <= '9')
            ssl_expr_yydebug = ssl_expr_yyn - '0';
    }
#endif

    ssl_expr_yynerrs = 0;
    ssl_expr_yyerrflag = 0;
    ssl_expr_yychar = (-1);

    if (ssl_expr_yyss == NULL && ssl_expr_yygrowstack()) goto ssl_expr_yyoverflow;
    ssl_expr_yyssp = ssl_expr_yyss;
    ssl_expr_yyvsp = ssl_expr_yyvs;
    *ssl_expr_yyssp = ssl_expr_yystate = 0;

ssl_expr_yyloop:
    if ((ssl_expr_yyn = ssl_expr_yydefred[ssl_expr_yystate])) goto ssl_expr_yyreduce;
    if (ssl_expr_yychar < 0)
    {
        if ((ssl_expr_yychar = ssl_expr_yylex()) < 0) ssl_expr_yychar = 0;
#if YYDEBUG
        if (ssl_expr_yydebug)
        {
            ssl_expr_yys = 0;
            if (ssl_expr_yychar <= YYMAXTOKEN) ssl_expr_yys = ssl_expr_yyname[ssl_expr_yychar];
            if (!ssl_expr_yys) ssl_expr_yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, ssl_expr_yystate, ssl_expr_yychar, ssl_expr_yys);
        }
#endif
    }
    if ((ssl_expr_yyn = ssl_expr_yysindex[ssl_expr_yystate]) && (ssl_expr_yyn += ssl_expr_yychar) >= 0 &&
            ssl_expr_yyn <= YYTABLESIZE && ssl_expr_yycheck[ssl_expr_yyn] == ssl_expr_yychar)
    {
#if YYDEBUG
        if (ssl_expr_yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, ssl_expr_yystate, ssl_expr_yytable[ssl_expr_yyn]);
#endif
        if (ssl_expr_yyssp >= ssl_expr_yysslim && ssl_expr_yygrowstack())
        {
            goto ssl_expr_yyoverflow;
        }
        *++ssl_expr_yyssp = ssl_expr_yystate = ssl_expr_yytable[ssl_expr_yyn];
        *++ssl_expr_yyvsp = ssl_expr_yylval;
        ssl_expr_yychar = (-1);
        if (ssl_expr_yyerrflag > 0)  --ssl_expr_yyerrflag;
        goto ssl_expr_yyloop;
    }
    if ((ssl_expr_yyn = ssl_expr_yyrindex[ssl_expr_yystate]) && (ssl_expr_yyn += ssl_expr_yychar) >= 0 &&
            ssl_expr_yyn <= YYTABLESIZE && ssl_expr_yycheck[ssl_expr_yyn] == ssl_expr_yychar)
    {
        ssl_expr_yyn = ssl_expr_yytable[ssl_expr_yyn];
        goto ssl_expr_yyreduce;
    }
    if (ssl_expr_yyerrflag) goto ssl_expr_yyinrecovery;
#if defined(lint) || defined(__GNUC__)
    goto ssl_expr_yynewerror;
#endif
ssl_expr_yynewerror:
    ssl_expr_yyerror("syntax error");
#if defined(lint) || defined(__GNUC__)
    goto ssl_expr_yyerrlab;
#endif
ssl_expr_yyerrlab:
    ++ssl_expr_yynerrs;
ssl_expr_yyinrecovery:
    if (ssl_expr_yyerrflag < 3)
    {
        ssl_expr_yyerrflag = 3;
        for (;;)
        {
            if ((ssl_expr_yyn = ssl_expr_yysindex[*ssl_expr_yyssp]) && (ssl_expr_yyn += YYERRCODE) >= 0 &&
                    ssl_expr_yyn <= YYTABLESIZE && ssl_expr_yycheck[ssl_expr_yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (ssl_expr_yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *ssl_expr_yyssp, ssl_expr_yytable[ssl_expr_yyn]);
#endif
                if (ssl_expr_yyssp >= ssl_expr_yysslim && ssl_expr_yygrowstack())
                {
                    goto ssl_expr_yyoverflow;
                }
                *++ssl_expr_yyssp = ssl_expr_yystate = ssl_expr_yytable[ssl_expr_yyn];
                *++ssl_expr_yyvsp = ssl_expr_yylval;
                goto ssl_expr_yyloop;
            }
            else
            {
#if YYDEBUG
                if (ssl_expr_yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *ssl_expr_yyssp);
#endif
                if (ssl_expr_yyssp <= ssl_expr_yyss) goto ssl_expr_yyabort;
                --ssl_expr_yyssp;
                --ssl_expr_yyvsp;
            }
        }
    }
    else
    {
        if (ssl_expr_yychar == 0) goto ssl_expr_yyabort;
#if YYDEBUG
        if (ssl_expr_yydebug)
        {
            ssl_expr_yys = 0;
            if (ssl_expr_yychar <= YYMAXTOKEN) ssl_expr_yys = ssl_expr_yyname[ssl_expr_yychar];
            if (!ssl_expr_yys) ssl_expr_yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, ssl_expr_yystate, ssl_expr_yychar, ssl_expr_yys);
        }
#endif
        ssl_expr_yychar = (-1);
        goto ssl_expr_yyloop;
    }
ssl_expr_yyreduce:
#if YYDEBUG
    if (ssl_expr_yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, ssl_expr_yystate, ssl_expr_yyn, ssl_expr_yyrule[ssl_expr_yyn]);
#endif
    ssl_expr_yym = ssl_expr_yylen[ssl_expr_yyn];
    ssl_expr_yyval = ssl_expr_yyvsp[1-ssl_expr_yym];
    switch (ssl_expr_yyn)
    {
case 1:
#line 84 "ssl_expr_parse.y"
{ ssl_expr_info.expr = ssl_expr_yyvsp[0].exVal; }
break;
case 2:
#line 87 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_True,  NULL, NULL); }
break;
case 3:
#line 88 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_False, NULL, NULL); }
break;
case 4:
#line 89 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_Not,   ssl_expr_yyvsp[0].exVal,   NULL); }
break;
case 5:
#line 90 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_Or,    ssl_expr_yyvsp[-2].exVal,   ssl_expr_yyvsp[0].exVal);   }
break;
case 6:
#line 91 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_And,   ssl_expr_yyvsp[-2].exVal,   ssl_expr_yyvsp[0].exVal);   }
break;
case 7:
#line 92 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_Comp,  ssl_expr_yyvsp[0].exVal,   NULL); }
break;
case 8:
#line 93 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_yyvsp[-1].exVal; }
break;
case 9:
#line 96 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_EQ,  ssl_expr_yyvsp[-2].exVal, ssl_expr_yyvsp[0].exVal); }
break;
case 10:
#line 97 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_NE,  ssl_expr_yyvsp[-2].exVal, ssl_expr_yyvsp[0].exVal); }
break;
case 11:
#line 98 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_LT,  ssl_expr_yyvsp[-2].exVal, ssl_expr_yyvsp[0].exVal); }
break;
case 12:
#line 99 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_LE,  ssl_expr_yyvsp[-2].exVal, ssl_expr_yyvsp[0].exVal); }
break;
case 13:
#line 100 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_GT,  ssl_expr_yyvsp[-2].exVal, ssl_expr_yyvsp[0].exVal); }
break;
case 14:
#line 101 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_GE,  ssl_expr_yyvsp[-2].exVal, ssl_expr_yyvsp[0].exVal); }
break;
case 15:
#line 102 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_IN,  ssl_expr_yyvsp[-2].exVal, ssl_expr_yyvsp[0].exVal); }
break;
case 16:
#line 103 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_REG, ssl_expr_yyvsp[-2].exVal, ssl_expr_yyvsp[0].exVal); }
break;
case 17:
#line 104 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_NRE, ssl_expr_yyvsp[-2].exVal, ssl_expr_yyvsp[0].exVal); }
break;
case 18:
#line 107 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_OidListElement, ssl_expr_yyvsp[-1].exVal, NULL); }
break;
case 19:
#line 108 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_yyvsp[-1].exVal ; }
break;
case 20:
#line 111 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_ListElement, ssl_expr_yyvsp[0].exVal, NULL); }
break;
case 21:
#line 112 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_ListElement, ssl_expr_yyvsp[0].exVal, ssl_expr_yyvsp[-2].exVal);   }
break;
case 22:
#line 115 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_Digit,  ssl_expr_yyvsp[0].cpVal, NULL); }
break;
case 23:
#line 116 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_String, ssl_expr_yyvsp[0].cpVal, NULL); }
break;
case 24:
#line 117 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_make(op_Var,    ssl_expr_yyvsp[-1].cpVal, NULL); }
break;
case 25:
#line 118 "ssl_expr_parse.y"
{ ssl_expr_yyval.exVal = ssl_expr_yyvsp[0].exVal; }
break;
case 26:
#line 121 "ssl_expr_parse.y"
{
                ap_regex_t *regex;
                if ((regex = ap_pregcomp(ssl_expr_info.pool, ssl_expr_yyvsp[0].cpVal,
                                         AP_REG_EXTENDED|AP_REG_NOSUB)) == NULL) {
                    ssl_expr_error = "Failed to compile regular expression";
                    YYERROR;
                }
                ssl_expr_yyval.exVal = ssl_expr_make(op_Regex, regex, NULL);
            }
break;
case 27:
#line 130 "ssl_expr_parse.y"
{
                ap_regex_t *regex;
                if ((regex = ap_pregcomp(ssl_expr_info.pool, ssl_expr_yyvsp[0].cpVal,
                                         AP_REG_EXTENDED|AP_REG_NOSUB|AP_REG_ICASE)) == NULL) {
                    ssl_expr_error = "Failed to compile regular expression";
                    YYERROR;
                }
                ssl_expr_yyval.exVal = ssl_expr_make(op_Regex, regex, NULL);
            }
break;
case 28:
#line 141 "ssl_expr_parse.y"
{
               ssl_expr *args = ssl_expr_make(op_ListElement, ssl_expr_yyvsp[-1].cpVal, NULL);
               ssl_expr_yyval.exVal = ssl_expr_make(op_Func, "file", args);
            }
break;
#line 563 "y.tab.c"
    }
    ssl_expr_yyssp -= ssl_expr_yym;
    ssl_expr_yystate = *ssl_expr_yyssp;
    ssl_expr_yyvsp -= ssl_expr_yym;
    ssl_expr_yym = ssl_expr_yylhs[ssl_expr_yyn];
    if (ssl_expr_yystate == 0 && ssl_expr_yym == 0)
    {
#if YYDEBUG
        if (ssl_expr_yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        ssl_expr_yystate = YYFINAL;
        *++ssl_expr_yyssp = YYFINAL;
        *++ssl_expr_yyvsp = ssl_expr_yyval;
        if (ssl_expr_yychar < 0)
        {
            if ((ssl_expr_yychar = ssl_expr_yylex()) < 0) ssl_expr_yychar = 0;
#if YYDEBUG
            if (ssl_expr_yydebug)
            {
                ssl_expr_yys = 0;
                if (ssl_expr_yychar <= YYMAXTOKEN) ssl_expr_yys = ssl_expr_yyname[ssl_expr_yychar];
                if (!ssl_expr_yys) ssl_expr_yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, ssl_expr_yychar, ssl_expr_yys);
            }
#endif
        }
        if (ssl_expr_yychar == 0) goto ssl_expr_yyaccept;
        goto ssl_expr_yyloop;
    }
    if ((ssl_expr_yyn = ssl_expr_yygindex[ssl_expr_yym]) && (ssl_expr_yyn += ssl_expr_yystate) >= 0 &&
            ssl_expr_yyn <= YYTABLESIZE && ssl_expr_yycheck[ssl_expr_yyn] == ssl_expr_yystate)
        ssl_expr_yystate = ssl_expr_yytable[ssl_expr_yyn];
    else
        ssl_expr_yystate = ssl_expr_yydgoto[ssl_expr_yym];
#if YYDEBUG
    if (ssl_expr_yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *ssl_expr_yyssp, ssl_expr_yystate);
#endif
    if (ssl_expr_yyssp >= ssl_expr_yysslim && ssl_expr_yygrowstack())
    {
        goto ssl_expr_yyoverflow;
    }
    *++ssl_expr_yyssp = ssl_expr_yystate;
    *++ssl_expr_yyvsp = ssl_expr_yyval;
    goto ssl_expr_yyloop;
ssl_expr_yyoverflow:
    ssl_expr_yyerror("yacc stack overflow");
ssl_expr_yyabort:
    return (1);
ssl_expr_yyaccept:
    return (0);
}