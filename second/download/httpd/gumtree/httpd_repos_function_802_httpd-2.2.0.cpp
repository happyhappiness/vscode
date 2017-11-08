static int ssl_expr_yygrowstack()
{
    int newsize, i;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = ssl_expr_yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;
    i = ssl_expr_yyssp - ssl_expr_yyss;
    newss = ssl_expr_yyss ? (short *)realloc(ssl_expr_yyss, newsize * sizeof *newss) :
      (short *)malloc(newsize * sizeof *newss);
    if (newss == NULL)
        return -1;
    ssl_expr_yyss = newss;
    ssl_expr_yyssp = newss + i;
    newvs = ssl_expr_yyvs ? (YYSTYPE *)realloc(ssl_expr_yyvs, newsize * sizeof *newvs) :
      (YYSTYPE *)malloc(newsize * sizeof *newvs);
    if (newvs == NULL)
        return -1;
    ssl_expr_yyvs = newvs;
    ssl_expr_yyvsp = newvs + i;
    ssl_expr_yystacksize = newsize;
    ssl_expr_yysslim = ssl_expr_yyss + newsize - 1;
    return 0;
}