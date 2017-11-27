	}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 154 "parser.y"
    {(yyval.ci) = (yyvsp[(1) - (1)].ci);}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 155 "parser.y"
    {(yyval.ci) = (yyvsp[(1) - (1)].ci);}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 156 "parser.y"
    {(yyval.ci).values_num = 0;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 161 "parser.y"
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

  case 20:

/* Line 1455 of yacc.c  */
#line 171 "parser.y"
    {
	 if (((yyvsp[(1) - (1)].ci).values_num > 0) || ((yyvsp[(1) - (1)].ci).children_num > 0))
	 {
		 (yyval.sl).statement = malloc (sizeof (oconfig_item_t));
		 (yyval.sl).statement[0] = (yyvsp[(1) - (1)].ci);
		 (yyval.sl).statement_num = 1;
