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
  yychar = YYEMPTY;             /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = (short)yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = (int)(yyssp - yyss + 1);

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
         the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
         but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
                 &yyss1, size * sizeof (*yyssp),
                 &yyvs1, size * sizeof (*yyvsp),
                 &yyls1, size * sizeof (*yylsp),
                 &yystacksize);
#else
      yyoverflow("parser stack overflow",
                 &yyss1, size * sizeof (*yyssp),
                 &yyvs1, size * sizeof (*yyvsp),
                 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
        {
          yyerror("parser stack overflow");
          if (yyfree_stacks)
            {
              free (yyss);
              free (yyvs);
#ifdef YYLSP_NEEDED
              free (yyls);
#endif
            }
          return 2;
        }
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
        yystacksize = YYMAXDEPTH;
#ifndef YYSTACK_USE_ALLOCA
      yyfree_stacks = 1;
#endif
      yyss = (short *) YYSTACK_ALLOC (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1,
                   size * (unsigned int) sizeof (*yyssp));
      yyvs = (YYSTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1,
                   size * (unsigned int) sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1,
                   size * (unsigned int) sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
        fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
        YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
        fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)              /* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;           /* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
        fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
        {
          fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
          /* Give the individual parser a way to print the precise meaning
             of a token, for further debugging info.  */
#ifdef YYPRINT
          YYPRINT (stderr, yychar, yylval);
#endif
          fprintf (stderr, ")\n");
        }
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
               yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
        fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 3:
#line 235 "getdate.y"
{
            context->yyHaveTime++;
        ;
    break;}
case 4:
#line 238 "getdate.y"
{
            context->yyHaveZone++;
        ;
    break;}
case 5:
#line 241 "getdate.y"
{
            context->yyHaveDate++;
        ;
    break;}
case 6:
#line 244 "getdate.y"
{
            context->yyHaveDay++;
        ;
    break;}
case 7:
#line 247 "getdate.y"
{
            context->yyHaveRel++;
        ;
    break;}
case 9:
#line 253 "getdate.y"
{
            context->yyHour = yyvsp[-1].Number;
            context->yyMinutes = 0;
            context->yySeconds = 0;
            context->yyMeridian = yyvsp[0].Meridian;
        ;
    break;}
case 10:
#line 259 "getdate.y"
{
            context->yyHour = yyvsp[-3].Number;
            context->yyMinutes = yyvsp[-1].Number;
            context->yySeconds = 0;
            context->yyMeridian = yyvsp[0].Meridian;
        ;
    break;}
case 11:
#line 265 "getdate.y"
{
            context->yyHour = yyvsp[-3].Number;
            context->yyMinutes = yyvsp[-1].Number;
            context->yyMeridian = MER24;
            context->yyHaveZone++;
            context->yyTimezone = (yyvsp[0].Number < 0
                                   ? -yyvsp[0].Number % 100 + (-yyvsp[0].Number / 100) * 60
                                   : - (yyvsp[0].Number % 100 + (yyvsp[0].Number / 100) * 60));
        ;
    break;}
case 12:
#line 274 "getdate.y"
{
            context->yyHour = yyvsp[-5].Number;
            context->yyMinutes = yyvsp[-3].Number;
            context->yySeconds = yyvsp[-1].Number;
            context->yyMeridian = yyvsp[0].Meridian;
        ;
    break;}
case 13:
#line 280 "getdate.y"
{
            context->yyHour = yyvsp[-5].Number;
            context->yyMinutes = yyvsp[-3].Number;
            context->yySeconds = yyvsp[-1].Number;
            context->yyMeridian = MER24;
            context->yyHaveZone++;
            context->yyTimezone = (yyvsp[0].Number < 0
                                   ? -yyvsp[0].Number % 100 + (-yyvsp[0].Number / 100) * 60
                                   : - (yyvsp[0].Number % 100 + (yyvsp[0].Number / 100) * 60));
        ;
    break;}
case 14:
#line 292 "getdate.y"
{
            context->yyTimezone = yyvsp[0].Number;
        ;
    break;}
case 15:
#line 295 "getdate.y"
{
            context->yyTimezone = yyvsp[0].Number - 60;
        ;
    break;}
case 16:
#line 299 "getdate.y"
{
            context->yyTimezone = yyvsp[-1].Number - 60;
        ;
    break;}
case 17:
#line 304 "getdate.y"
{
            context->yyDayOrdinal = 1;
            context->yyDayNumber = yyvsp[0].Number;
        ;
    break;}
case 18:
#line 308 "getdate.y"
{
            context->yyDayOrdinal = 1;
            context->yyDayNumber = yyvsp[-1].Number;
        ;
    break;}
case 19:
#line 312 "getdate.y"
{
            context->yyDayOrdinal = yyvsp[-1].Number;
            context->yyDayNumber = yyvsp[0].Number;
        ;
    break;}
case 20:
#line 318 "getdate.y"
{
            context->yyMonth = yyvsp[-2].Number;
            context->yyDay = yyvsp[0].Number;
        ;
    break;}
case 21:
#line 322 "getdate.y"
{
          /* Interpret as YYYY/MM/DD if $1 >= 1000, otherwise as MM/DD/YY.
             The goal in recognizing YYYY/MM/DD is solely to support legacy
             machine-generated dates like those in an RCS log listing.  If
             you want portability, use the ISO 8601 format.  */
          if (yyvsp[-4].Number >= 1000)
            {
              context->yyYear = yyvsp[-4].Number;
              context->yyMonth = yyvsp[-2].Number;
              context->yyDay = yyvsp[0].Number;
            }
          else
            {
              context->yyMonth = yyvsp[-4].Number;
              context->yyDay = yyvsp[-2].Number;
              context->yyYear = yyvsp[0].Number;
            }
        ;
    break;}
case 22:
#line 340 "getdate.y"
{
            /* ISO 8601 format.  yyyy-mm-dd.  */
            context->yyYear = yyvsp[-2].Number;
            context->yyMonth = -yyvsp[-1].Number;
            context->yyDay = -yyvsp[0].Number;
        ;
    break;}
case 23:
#line 346 "getdate.y"
{
            /* e.g. 17-JUN-1992.  */
            context->yyDay = yyvsp[-2].Number;
            context->yyMonth = yyvsp[-1].Number;
            context->yyYear = -yyvsp[0].Number;
        ;
    break;}
case 24:
#line 352 "getdate.y"
{
            context->yyMonth = yyvsp[-1].Number;
            context->yyDay = yyvsp[0].Number;
        ;
    break;}
case 25:
#line 356 "getdate.y"
{
            context->yyMonth = yyvsp[-3].Number;
            context->yyDay = yyvsp[-2].Number;
            context->yyYear = yyvsp[0].Number;
        ;
    break;}
case 26:
#line 361 "getdate.y"
{
            context->yyMonth = yyvsp[0].Number;
            context->yyDay = yyvsp[-1].Number;
        ;
    break;}
case 27:
#line 365 "getdate.y"
{
            context->yyMonth = yyvsp[-1].Number;
            context->yyDay = yyvsp[-2].Number;
            context->yyYear = yyvsp[0].Number;
        ;
    break;}
case 28:
#line 372 "getdate.y"
{
            context->yyRelSeconds = -context->yyRelSeconds;
            context->yyRelMinutes = -context->yyRelMinutes;
            context->yyRelHour = -context->yyRelHour;
            context->yyRelDay = -context->yyRelDay;
            context->yyRelMonth = -context->yyRelMonth;
            context->yyRelYear = -context->yyRelYear;
        ;
    break;}
case 30:
#line 383 "getdate.y"
{
            context->yyRelYear += yyvsp[-1].Number * yyvsp[0].Number;
        ;
    break;}
case 31:
#line 386 "getdate.y"
{
            context->yyRelYear += yyvsp[-1].Number * yyvsp[0].Number;
        ;
    break;}
case 32:
#line 389 "getdate.y"
{
            context->yyRelYear += yyvsp[0].Number;
        ;
    break;}
case 33:
#line 392 "getdate.y"
{
            context->yyRelMonth += yyvsp[-1].Number * yyvsp[0].Number;
        ;
    break;}
case 34:
#line 395 "getdate.y"
{
            context->yyRelMonth += yyvsp[-1].Number * yyvsp[0].Number;
        ;
    break;}
case 35:
#line 398 "getdate.y"
{
            context->yyRelMonth += yyvsp[0].Number;
        ;
    break;}
case 36:
#line 401 "getdate.y"
{
            context->yyRelDay += yyvsp[-1].Number * yyvsp[0].Number;
        ;
    break;}
case 37:
#line 404 "getdate.y"
{
            context->yyRelDay += yyvsp[-1].Number * yyvsp[0].Number;
        ;
    break;}
case 38:
#line 407 "getdate.y"
{
            context->yyRelDay += yyvsp[0].Number;
        ;
    break;}
case 39:
#line 410 "getdate.y"
{
            context->yyRelHour += yyvsp[-1].Number * yyvsp[0].Number;
        ;
    break;}
case 40:
#line 413 "getdate.y"
{
            context->yyRelHour += yyvsp[-1].Number * yyvsp[0].Number;
        ;
    break;}
case 41:
#line 416 "getdate.y"
{
            context->yyRelHour += yyvsp[0].Number;
        ;
    break;}
case 42:
#line 419 "getdate.y"
{
            context->yyRelMinutes += yyvsp[-1].Number * yyvsp[0].Number;
        ;
    break;}
case 43:
#line 422 "getdate.y"
{
            context->yyRelMinutes += yyvsp[-1].Number * yyvsp[0].Number;
        ;
    break;}
case 44:
#line 425 "getdate.y"
{
            context->yyRelMinutes += yyvsp[0].Number;
        ;
    break;}
case 45:
#line 428 "getdate.y"
{
            context->yyRelSeconds += yyvsp[-1].Number * yyvsp[0].Number;
        ;
    break;}
case 46:
#line 431 "getdate.y"
{
            context->yyRelSeconds += yyvsp[-1].Number * yyvsp[0].Number;
        ;
    break;}
case 47:
#line 434 "getdate.y"
{
            context->yyRelSeconds += yyvsp[0].Number;
        ;
    break;}
case 48:
#line 440 "getdate.y"
{
            if (context->yyHaveTime && context->yyHaveDate &&
                !context->yyHaveRel)
              context->yyYear = yyvsp[0].Number;
            else
              {
                if (yyvsp[0].Number>10000)
                  {
                    context->yyHaveDate++;
                    context->yyDay= (yyvsp[0].Number)%100;
                    context->yyMonth= (yyvsp[0].Number/100)%100;
                    context->yyYear = yyvsp[0].Number/10000;
                  }
                else
                  {
                    context->yyHaveTime++;
                    if (yyvsp[0].Number < 100)
                      {
                        context->yyHour = yyvsp[0].Number;
                        context->yyMinutes = 0;
                      }
                    else
                      {
                        context->yyHour = yyvsp[0].Number / 100;
                        context->yyMinutes = yyvsp[0].Number % 100;
                      }
                    context->yySeconds = 0;
                    context->yyMeridian = MER24;
                  }
              }
          ;
    break;}
case 49:
#line 474 "getdate.y"
{
            yyval.Meridian = MER24;
          ;
    break;}
case 50:
#line 478 "getdate.y"
{
            yyval.Meridian = yyvsp[0].Meridian;
          ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 543 "/usr/local/share/bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
        fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
        {
          int size = 0;
          char *msg;
          int x, count;

          count = 0;
          /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
          for (x = (yyn < 0 ? -yyn : 0);
               x < (sizeof(yytname) / sizeof(char *)); x++)
            if (yycheck[x + yyn] == x)
              size += strlen(yytname[x]) + 15, count++;
          msg = (char *) malloc(size + 15);
          if (msg != 0)
            {
              strcpy(msg, "parse error");

              if (count < 5)
                {
                  count = 0;
                  for (x = (yyn < 0 ? -yyn : 0);
                       x < (sizeof(yytname) / sizeof(char *)); x++)
                    if (yycheck[x + yyn] == x)
                      {
                        strcat(msg, count == 0 ? ", expecting `" : " or `");
                        strcat(msg, yytname[x]);
                        strcat(msg, "'");
                        count++;
                      }
                }
              yyerror(msg);
              free(msg);
            }
          else
            yyerror ("parse error; also virtual memory exceeded");
        }
      else
#endif /* YYERROR_VERBOSE */
        yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
        YYABORT;

#if YYDEBUG != 0
      if (yydebug)
        fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;              /* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
        fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
        goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;

 yyacceptlab:
  /* YYACCEPT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 0;

 yyabortlab:
  /* YYABORT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 1;
}