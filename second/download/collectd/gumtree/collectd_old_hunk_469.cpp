

  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 73 "parser.y"
    {(yyval.string) = unquote ((yyvsp[(1) - (1)].string));}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 74 "parser.y"
    {(yyval.string) = strdup ((yyvsp[(1) - (1)].string));}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 78 "parser.y"
    {(yyval.cv).value.number = (yyvsp[(1) - (1)].number); (yyval.cv).type = OCONFIG_TYPE_NUMBER;}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 79 "parser.y"
    {(yyval.cv).value.boolean = 1; (yyval.cv).type = OCONFIG_TYPE_BOOLEAN;}
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 80 "parser.y"
    {(yyval.cv).value.boolean = 0; (yyval.cv).type = OCONFIG_TYPE_BOOLEAN;}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 81 "parser.y"
    {(yyval.cv).value.string = (yyvsp[(1) - (1)].string); (yyval.cv).type = OCONFIG_TYPE_STRING;}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 86 "parser.y"
    {
	 (yyval.al) = (yyvsp[(1) - (2)].al);
	 (yyval.al).argument_num++;
	 (yyval.al).argument = realloc ((yyval.al).argument, (yyval.al).argument_num * sizeof (oconfig_value_t));
	 (yyval.al).argument[(yyval.al).argument_num-1] = (yyvsp[(2) - (2)].cv);
	}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 93 "parser.y"
    {
	 (yyval.al).argument = malloc (sizeof (oconfig_value_t));
	 (yyval.al).argument[0] = (yyvsp[(1) - (1)].cv);
	 (yyval.al).argument_num = 1;
	}
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 101 "parser.y"
    {(yyval.string) = strdup ((yyvsp[(1) - (1)].string));}
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 106 "parser.y"
    {
	 memset (&(yyval.ci), '\0', sizeof ((yyval.ci)));
	 (yyval.ci).key = (yyvsp[(1) - (3)].string);
	 (yyval.ci).values = (yyvsp[(2) - (3)].al).argument;
	 (yyval.ci).values_num = (yyvsp[(2) - (3)].al).argument_num;
	}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 116 "parser.y"
    {
	 memset (&(yyval.ci), '\0', sizeof ((yyval.ci)));
	 (yyval.ci).key = (yyvsp[(2) - (4)].string);
	}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 122 "parser.y"
    {
	 memset (&(yyval.ci), '\0', sizeof ((yyval.ci)));
	 (yyval.ci).key = (yyvsp[(2) - (5)].string);
	 (yyval.ci).values = (yyvsp[(3) - (5)].al).argument;
	 (yyval.ci).values_num = (yyvsp[(3) - (5)].al).argument_num;
	}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 132 "parser.y"
    {
	 (yyval.string) = (yyvsp[(3) - (5)].string);
	}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 139 "parser.y"
    {
	 if (strcmp ((yyvsp[(1) - (3)].ci).key, (yyvsp[(3) - (3)].string)) != 0)
	 {
		printf ("block_begin = %s; block_end = %s;\n", (yyvsp[(1) - (3)].ci).key, (yyvsp[(3) - (3)].string));
	 	yyerror ("Block not closed..\n");
		exit (1);
	 }
	 free ((yyvsp[(3) - (3)].string)); (yyvsp[(3) - (3)].string) = NULL;
	 (yyval.ci) = (yyvsp[(1) - (3)].ci);
	 (yyval.ci).children = (yyvsp[(2) - (3)].sl).statement;
	 (yyval.ci).children_num = (yyvsp[(2) - (3)].sl).statement_num;
	}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 152 "parser.y"
    {
	 if (strcmp ((yyvsp[(1) - (2)].ci).key, (yyvsp[(2) - (2)].string)) != 0)
	 {
		printf ("block_begin = %s; block_end = %s;\n", (yyvsp[(1) - (2)].ci).key, (yyvsp[(2) - (2)].string));
		yyerror ("Block not closed..\n");
		exit (1);
	 }
	 free ((yyvsp[(2) - (2)].string)); (yyvsp[(2) - (2)].string) = NULL;
	 (yyval.ci) = (yyvsp[(1) - (2)].ci);
	 (yyval.ci).children = NULL;
	 (yyval.ci).children_num = 0;
	}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 167 "parser.y"
    {(yyval.ci) = (yyvsp[(1) - (1)].ci);}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 168 "parser.y"
    {(yyval.ci) = (yyvsp[(1) - (1)].ci);}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 169 "parser.y"
    {(yyval.ci).values_num = 0;}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 174 "parser.y"
    {
	 (yyval.sl) = (yyvsp[(1) - (2)].sl);
	 if (((yyvsp[(2) - (2)].ci).values_num > 0) || ((yyvsp[(2) - (2)].ci).children_num > 0))
	 {
		 (yyval.sl).statement_num++;
		 (yyval.sl).statement = realloc ((yyval.sl).statement, (yyval.sl).statement_num * sizeof (oconfig_item_t));
		 (yyval.sl).statement[(yyval.sl).statement_num-1] = (yyvsp[(2) - (2)].ci);
	 }
	}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 184 "parser.y"
    {
	 if (((yyvsp[(1) - (1)].ci).values_num > 0) || ((yyvsp[(1) - (1)].ci).children_num > 0))
	 {
		 (yyval.sl).statement = malloc (sizeof (oconfig_item_t));
		 (yyval.sl).statement[0] = (yyvsp[(1) - (1)].ci);
		 (yyval.sl).statement_num = 1;
	 }
	 else
	 {
	 	(yyval.sl).statement = NULL;
		(yyval.sl).statement_num = 0;
	 }
	}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 201 "parser.y"
    {
	 ci_root = malloc (sizeof (oconfig_item_t));
	 memset (ci_root, '\0', sizeof (oconfig_item_t));
	 ci_root->children = (yyvsp[(1) - (1)].sl).statement;
	 ci_root->children_num = (yyvsp[(1) - (1)].sl).statement_num;
	}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 208 "parser.y"
    {
	 ci_root = malloc (sizeof (oconfig_item_t));
	 memset (ci_root, '\0', sizeof (oconfig_item_t));
	 ci_root->children = NULL;
	 ci_root->children_num = 0;
	}
    break;



/* Line 1806 of yacc.c  */
#line 1648 "parser.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
