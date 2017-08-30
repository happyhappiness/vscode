  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
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
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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
        case 4:
#line 248 "getdate.y"
    {
            context->yyHaveTime++;
        }
    break;

  case 5:
#line 251 "getdate.y"
    {
            context->yyHaveZone++;
        }
    break;

  case 6:
#line 254 "getdate.y"
    {
            context->yyHaveDate++;
        }
    break;

  case 7:
#line 257 "getdate.y"
    {
            context->yyHaveDay++;
        }
    break;

  case 8:
#line 260 "getdate.y"
    {
            context->yyHaveRel++;
        }
    break;

  case 10:
#line 266 "getdate.y"
    {
            context->yyHour = yyvsp[-1].Number;
            context->yyMinutes = 0;
            context->yySeconds = 0;
            context->yyMeridian = yyvsp[0].Meridian;
        }
    break;

  case 11:
#line 272 "getdate.y"
    {
            context->yyHour = yyvsp[-3].Number;
            context->yyMinutes = yyvsp[-1].Number;
            context->yySeconds = 0;
            context->yyMeridian = yyvsp[0].Meridian;
        }
    break;

  case 12:
#line 278 "getdate.y"
    {
            context->yyHour = yyvsp[-3].Number;
            context->yyMinutes = yyvsp[-1].Number;
            context->yyMeridian = MER24;
            context->yyHaveZone++;
            context->yyTimezone = (yyvsp[0].Number < 0
                                   ? -yyvsp[0].Number % 100 + (-yyvsp[0].Number / 100) * 60
                                   : - (yyvsp[0].Number % 100 + (yyvsp[0].Number / 100) * 60));
        }
    break;

  case 13:
#line 287 "getdate.y"
    {
            context->yyHour = yyvsp[-5].Number;
            context->yyMinutes = yyvsp[-3].Number;
            context->yySeconds = yyvsp[-1].Number;
            context->yyMeridian = yyvsp[0].Meridian;
        }
    break;

  case 14:
#line 293 "getdate.y"
    {
            context->yyHour = yyvsp[-5].Number;
            context->yyMinutes = yyvsp[-3].Number;
            context->yySeconds = yyvsp[-1].Number;
