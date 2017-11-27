	}
    break;

  case 16:

/* Line 1455 of yacc.c  */
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

/* Line 1455 of yacc.c  */
#line 167 "parser.y"
    {(yyval.ci) = (yyvsp[(1) - (1)].ci);}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 168 "parser.y"
    {(yyval.ci) = (yyvsp[(1) - (1)].ci);}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 169 "parser.y"
    {(yyval.ci).values_num = 0;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
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

/* Line 1455 of yacc.c  */
#line 184 "parser.y"
    {
	 if (((yyvsp[(1) - (1)].ci).values_num > 0) || ((yyvsp[(1) - (1)].ci).children_num > 0))
	 {
		 (yyval.sl).statement = malloc (sizeof (oconfig_item_t));
		 (yyval.sl).statement[0] = (yyvsp[(1) - (1)].ci);
		 (yyval.sl).statement_num = 1;
