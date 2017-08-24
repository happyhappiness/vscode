                    context->yyMeridian = MER24;
                  }
              }
          }
    break;

  case 50:
#line 487 "getdate.y"
    {
            yyval.Meridian = MER24;
          }
    break;

  case 51:
#line 491 "getdate.y"
    {
            yyval.Meridian = yyvsp[0].Meridian;
          }
    break;


    }

/* Line 999 of yacc.c.  */
#line 1688 "y.tab.c"

  yyvsp -= yylen;
  yyssp -= yylen;


  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
        {
          YYSIZE_T yysize = 0;
          int yytype = YYTRANSLATE (yychar);
          char *yymsg;
          int yyx, yycount;

          yycount = 0;
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  */
          for (yyx = yyn < 0 ? -yyn : 0;
               yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
              yysize += yystrlen (yytname[yyx]) + 15, yycount++;
          yysize += yystrlen ("syntax error, unexpected ") + 1;
          yysize += yystrlen (yytname[yytype]);
          yymsg = (char *) YYSTACK_ALLOC (yysize);
          if (yymsg != 0)
            {
              char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
              yyp = yystpcpy (yyp, yytname[yytype]);

              if (yycount < 5)
                {
                  yycount = 0;
                  for (yyx = yyn < 0 ? -yyn : 0;
                       yyx < (int) (sizeof (yytname) / sizeof (char *));
                       yyx++)
                    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
                      {
                        const char *yyq = ! yycount ? ", expecting " : " or ";
                        yyp = yystpcpy (yyp, yyq);
                        yyp = yystpcpy (yyp, yytname[yyx]);
                        yycount++;
                      }
                }
              yyerror (yymsg);
              YYSTACK_FREE (yymsg);
            }
          else
            yyerror ("syntax error; also virtual memory exhausted");
        }
      else
#endif /* YYERROR_VERBOSE */
        yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        {
          /* Pop the error token.  */
          YYPOPSTACK;
          /* Pop the rest of the stack.  */
          while (yyss < yyssp)
            {
              YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
              yydestruct (yystos[*yyssp], yyvsp);
              YYPOPSTACK;
            }
          YYABORT;
        }

      YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
      yydestruct (yytoken, &yylval);
      yychar = YYEMPTY;

    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      yyvsp--;
      yystate = *--yyssp;

      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 496 "getdate.y"


/* Include this file down here because bison inserts code above which
