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

#line 483 "getdate.y"





/* Include this file down here because bison inserts code above which

