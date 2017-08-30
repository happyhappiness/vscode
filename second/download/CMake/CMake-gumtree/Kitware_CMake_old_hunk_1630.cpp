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

