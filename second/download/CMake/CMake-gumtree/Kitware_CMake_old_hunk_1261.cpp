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
