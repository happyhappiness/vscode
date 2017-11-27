 
 
   YY_REDUCE_PRINT (yyn);
   switch (yyn)
     {
         case 2:
-#line 73 "parser.y" /* yacc.c:1646  */
+#line 74 "parser.y" /* yacc.c:1646  */
     {(yyval.string) = unquote ((yyvsp[0].string));}
-#line 1265 "parser.c" /* yacc.c:1646  */
+#line 1266 "parser.c" /* yacc.c:1646  */
     break;
 
   case 3:
-#line 74 "parser.y" /* yacc.c:1646  */
+#line 75 "parser.y" /* yacc.c:1646  */
     {(yyval.string) = strdup ((yyvsp[0].string));}
-#line 1271 "parser.c" /* yacc.c:1646  */
+#line 1272 "parser.c" /* yacc.c:1646  */
     break;
 
   case 4:
-#line 78 "parser.y" /* yacc.c:1646  */
+#line 79 "parser.y" /* yacc.c:1646  */
     {(yyval.cv).value.number = (yyvsp[0].number); (yyval.cv).type = OCONFIG_TYPE_NUMBER;}
-#line 1277 "parser.c" /* yacc.c:1646  */
+#line 1278 "parser.c" /* yacc.c:1646  */
     break;
 
   case 5:
-#line 79 "parser.y" /* yacc.c:1646  */
+#line 80 "parser.y" /* yacc.c:1646  */
     {(yyval.cv).value.boolean = 1; (yyval.cv).type = OCONFIG_TYPE_BOOLEAN;}
-#line 1283 "parser.c" /* yacc.c:1646  */
+#line 1284 "parser.c" /* yacc.c:1646  */
     break;
 
   case 6:
-#line 80 "parser.y" /* yacc.c:1646  */
+#line 81 "parser.y" /* yacc.c:1646  */
     {(yyval.cv).value.boolean = 0; (yyval.cv).type = OCONFIG_TYPE_BOOLEAN;}
-#line 1289 "parser.c" /* yacc.c:1646  */
+#line 1290 "parser.c" /* yacc.c:1646  */
     break;
 
   case 7:
-#line 81 "parser.y" /* yacc.c:1646  */
+#line 82 "parser.y" /* yacc.c:1646  */
     {(yyval.cv).value.string = (yyvsp[0].string); (yyval.cv).type = OCONFIG_TYPE_STRING;}
-#line 1295 "parser.c" /* yacc.c:1646  */
+#line 1296 "parser.c" /* yacc.c:1646  */
     break;
 
   case 8:
-#line 86 "parser.y" /* yacc.c:1646  */
+#line 87 "parser.y" /* yacc.c:1646  */
     {
 	 (yyval.al) = (yyvsp[-1].al);
 	 (yyval.al).argument_num++;
 	 (yyval.al).argument = realloc ((yyval.al).argument, (yyval.al).argument_num * sizeof (oconfig_value_t));
 	 (yyval.al).argument[(yyval.al).argument_num-1] = (yyvsp[0].cv);
 	}
-#line 1306 "parser.c" /* yacc.c:1646  */
+#line 1307 "parser.c" /* yacc.c:1646  */
     break;
 
   case 9:
-#line 93 "parser.y" /* yacc.c:1646  */
+#line 94 "parser.y" /* yacc.c:1646  */
     {
 	 (yyval.al).argument = malloc (sizeof (oconfig_value_t));
 	 (yyval.al).argument[0] = (yyvsp[0].cv);
 	 (yyval.al).argument_num = 1;
 	}
-#line 1316 "parser.c" /* yacc.c:1646  */
+#line 1317 "parser.c" /* yacc.c:1646  */
     break;
 
   case 10:
-#line 101 "parser.y" /* yacc.c:1646  */
+#line 102 "parser.y" /* yacc.c:1646  */
     {(yyval.string) = strdup ((yyvsp[0].string));}
-#line 1322 "parser.c" /* yacc.c:1646  */
+#line 1323 "parser.c" /* yacc.c:1646  */
     break;
 
   case 11:
-#line 106 "parser.y" /* yacc.c:1646  */
+#line 107 "parser.y" /* yacc.c:1646  */
     {
 	 memset (&(yyval.ci), '\0', sizeof ((yyval.ci)));
 	 (yyval.ci).key = (yyvsp[-2].string);
 	 (yyval.ci).values = (yyvsp[-1].al).argument;
 	 (yyval.ci).values_num = (yyvsp[-1].al).argument_num;
 	}
-#line 1333 "parser.c" /* yacc.c:1646  */
+#line 1334 "parser.c" /* yacc.c:1646  */
     break;
 
   case 12:
-#line 116 "parser.y" /* yacc.c:1646  */
+#line 117 "parser.y" /* yacc.c:1646  */
     {
 	 memset (&(yyval.ci), '\0', sizeof ((yyval.ci)));
 	 (yyval.ci).key = (yyvsp[-2].string);
 	}
-#line 1342 "parser.c" /* yacc.c:1646  */
+#line 1343 "parser.c" /* yacc.c:1646  */
     break;
 
   case 13:
-#line 122 "parser.y" /* yacc.c:1646  */
+#line 123 "parser.y" /* yacc.c:1646  */
     {
 	 memset (&(yyval.ci), '\0', sizeof ((yyval.ci)));
 	 (yyval.ci).key = (yyvsp[-3].string);
 	 (yyval.ci).values = (yyvsp[-2].al).argument;
 	 (yyval.ci).values_num = (yyvsp[-2].al).argument_num;
 	}
-#line 1353 "parser.c" /* yacc.c:1646  */
+#line 1354 "parser.c" /* yacc.c:1646  */
     break;
 
   case 14:
-#line 132 "parser.y" /* yacc.c:1646  */
+#line 133 "parser.y" /* yacc.c:1646  */
     {
 	 (yyval.string) = (yyvsp[-2].string);
 	}
-#line 1361 "parser.c" /* yacc.c:1646  */
+#line 1362 "parser.c" /* yacc.c:1646  */
     break;
 
   case 15:
-#line 139 "parser.y" /* yacc.c:1646  */
+#line 140 "parser.y" /* yacc.c:1646  */
     {
 	 if (strcmp ((yyvsp[-2].ci).key, (yyvsp[0].string)) != 0)
 	 {
 		printf ("block_begin = %s; block_end = %s;\n", (yyvsp[-2].ci).key, (yyvsp[0].string));
 	 	yyerror ("Block not closed..\n");
 		exit (1);
 	 }
 	 free ((yyvsp[0].string)); (yyvsp[0].string) = NULL;
 	 (yyval.ci) = (yyvsp[-2].ci);
 	 (yyval.ci).children = (yyvsp[-1].sl).statement;
 	 (yyval.ci).children_num = (yyvsp[-1].sl).statement_num;
 	}
-#line 1378 "parser.c" /* yacc.c:1646  */
+#line 1379 "parser.c" /* yacc.c:1646  */
     break;
 
   case 16:
-#line 152 "parser.y" /* yacc.c:1646  */
+#line 153 "parser.y" /* yacc.c:1646  */
     {
 	 if (strcmp ((yyvsp[-1].ci).key, (yyvsp[0].string)) != 0)
 	 {
 		printf ("block_begin = %s; block_end = %s;\n", (yyvsp[-1].ci).key, (yyvsp[0].string));
 		yyerror ("Block not closed..\n");
 		exit (1);
 	 }
 	 free ((yyvsp[0].string)); (yyvsp[0].string) = NULL;
 	 (yyval.ci) = (yyvsp[-1].ci);
 	 (yyval.ci).children = NULL;
 	 (yyval.ci).children_num = 0;
 	}
-#line 1395 "parser.c" /* yacc.c:1646  */
+#line 1396 "parser.c" /* yacc.c:1646  */
     break;
 
   case 17:
-#line 167 "parser.y" /* yacc.c:1646  */
+#line 168 "parser.y" /* yacc.c:1646  */
     {(yyval.ci) = (yyvsp[0].ci);}
-#line 1401 "parser.c" /* yacc.c:1646  */
+#line 1402 "parser.c" /* yacc.c:1646  */
     break;
 
   case 18:
-#line 168 "parser.y" /* yacc.c:1646  */
+#line 169 "parser.y" /* yacc.c:1646  */
     {(yyval.ci) = (yyvsp[0].ci);}
-#line 1407 "parser.c" /* yacc.c:1646  */
+#line 1408 "parser.c" /* yacc.c:1646  */
     break;
 
   case 19:
-#line 169 "parser.y" /* yacc.c:1646  */
+#line 170 "parser.y" /* yacc.c:1646  */
     {(yyval.ci).values_num = 0;}
-#line 1413 "parser.c" /* yacc.c:1646  */
+#line 1414 "parser.c" /* yacc.c:1646  */
     break;
 
   case 20:
-#line 174 "parser.y" /* yacc.c:1646  */
+#line 175 "parser.y" /* yacc.c:1646  */
     {
 	 (yyval.sl) = (yyvsp[-1].sl);
 	 if (((yyvsp[0].ci).values_num > 0) || ((yyvsp[0].ci).children_num > 0))
 	 {
 		 (yyval.sl).statement_num++;
 		 (yyval.sl).statement = realloc ((yyval.sl).statement, (yyval.sl).statement_num * sizeof (oconfig_item_t));
 		 (yyval.sl).statement[(yyval.sl).statement_num-1] = (yyvsp[0].ci);
 	 }
 	}
-#line 1427 "parser.c" /* yacc.c:1646  */
+#line 1428 "parser.c" /* yacc.c:1646  */
     break;
 
   case 21:
-#line 184 "parser.y" /* yacc.c:1646  */
+#line 185 "parser.y" /* yacc.c:1646  */
     {
 	 if (((yyvsp[0].ci).values_num > 0) || ((yyvsp[0].ci).children_num > 0))
 	 {
 		 (yyval.sl).statement = malloc (sizeof (oconfig_item_t));
 		 (yyval.sl).statement[0] = (yyvsp[0].ci);
 		 (yyval.sl).statement_num = 1;
