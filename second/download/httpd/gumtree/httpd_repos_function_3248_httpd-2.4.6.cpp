YYSTYPE * ap_expr_yyget_lval  (yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
    return yylval;
}