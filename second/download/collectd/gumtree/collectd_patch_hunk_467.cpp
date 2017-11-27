 	 (yyval.ci).children_num = (yyvsp[(2) - (3)].sl).statement_num;
 	}
     break;
 
   case 16:
 
-/* Line 1455 of yacc.c  */
+/* Line 1806 of yacc.c  */
 #line 152 "parser.y"
     {
 	 if (strcmp ((yyvsp[(1) - (2)].ci).key, (yyvsp[(2) - (2)].string)) != 0)
 	 {
 		printf ("block_begin = %s; block_end = %s;\n", (yyvsp[(1) - (2)].ci).key, (yyvsp[(2) - (2)].string));
 		yyerror ("Block not closed..\n");
