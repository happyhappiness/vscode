
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 69 "parser.y"
    {(yyval.string) = unquote ((yyvsp[(1) - (1)].string));}
    break;

  case 3:
#line 70 "parser.y"
    {(yyval.string) = strdup ((yyvsp[(1) - (1)].string));}
    break;

  case 4:
#line 74 "parser.y"
    {(yyval.cv).value.number = (yyvsp[(1) - (1)].number); (yyval.cv).type = OCONFIG_TYPE_NUMBER;}
    break;

  case 5:
#line 75 "parser.y"
    {(yyval.cv).value.boolean = 1; (yyval.cv).type = OCONFIG_TYPE_BOOLEAN;}
    break;

  case 6:
#line 76 "parser.y"
    {(yyval.cv).value.boolean = 0; (yyval.cv).type = OCONFIG_TYPE_BOOLEAN;}
    break;

  case 7:
#line 77 "parser.y"
    {(yyval.cv).value.string = (yyvsp[(1) - (1)].string); (yyval.cv).type = OCONFIG_TYPE_STRING;}
    break;

  case 8:
#line 82 "parser.y"
    {
	 (yyval.al) = (yyvsp[(1) - (2)].al);
	 (yyval.al).argument_num++;
	 (yyval.al).argument = realloc ((yyval.al).argument, (yyval.al).argument_num * sizeof (oconfig_value_t));
	 (yyval.al).argument[(yyval.al).argument_num-1] = (yyvsp[(2) - (2)].cv);
	}
    break;

  case 9:
#line 89 "parser.y"
    {
	 (yyval.al).argument = malloc (sizeof (oconfig_value_t));
	 (yyval.al).argument[0] = (yyvsp[(1) - (1)].cv);
	 (yyval.al).argument_num = 1;
	}
    break;

  case 10:
#line 97 "parser.y"
    {(yyval.string) = strdup ((yyvsp[(1) - (1)].string));}
    break;

  case 11:
#line 102 "parser.y"
    {
	 memset (&(yyval.ci), '\0', sizeof ((yyval.ci)));
	 (yyval.ci).key = (yyvsp[(1) - (3)].string);
	 (yyval.ci).values = (yyvsp[(2) - (3)].al).argument;
	 (yyval.ci).values_num = (yyvsp[(2) - (3)].al).argument_num;
	}
    break;

  case 12:
#line 112 "parser.y"
    {
	 memset (&(yyval.ci), '\0', sizeof ((yyval.ci)));
	 (yyval.ci).key = (yyvsp[(2) - (5)].string);
	 (yyval.ci).values = (yyvsp[(3) - (5)].al).argument;
	 (yyval.ci).values_num = (yyvsp[(3) - (5)].al).argument_num;
	}
    break;

  case 13:
#line 122 "parser.y"
    {
	 (yyval.string) = (yyvsp[(3) - (5)].string);
	}
    break;

  case 14:
#line 129 "parser.y"
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

  case 15:
#line 144 "parser.y"
    {(yyval.ci) = (yyvsp[(1) - (1)].ci);}
    break;

  case 16:
#line 145 "parser.y"
    {(yyval.ci) = (yyvsp[(1) - (1)].ci);}
    break;

  case 17:
#line 146 "parser.y"
    {(yyval.ci).values_num = 0;}
    break;

  case 18:
#line 151 "parser.y"
    {
	 (yyval.sl) = (yyvsp[(1) - (2)].sl);
	 if ((yyvsp[(2) - (2)].ci).values_num > 0)
	 {
		 (yyval.sl).statement_num++;
		 (yyval.sl).statement = realloc ((yyval.sl).statement, (yyval.sl).statement_num * sizeof (oconfig_item_t));
		 (yyval.sl).statement[(yyval.sl).statement_num-1] = (yyvsp[(2) - (2)].ci);
	 }
	}
    break;

  case 19:
#line 161 "parser.y"
    {
	 if ((yyvsp[(1) - (1)].ci).values_num > 0)
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

  case 20:
#line 178 "parser.y"
    {
	 ci_root = malloc (sizeof (oconfig_item_t));
	 memset (ci_root, '\0', sizeof (oconfig_item_t));
	 ci_root->children = (yyvsp[(1) - (1)].sl).statement;
	 ci_root->children_num = (yyvsp[(1) - (1)].sl).statement_num;
	}
    break;


/* Line 1267 of yacc.c.  */
#line 1523 "parser.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
