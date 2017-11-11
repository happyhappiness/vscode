int ssl_expr_yyerror(char *s)
{
    ssl_expr_error = s;
    return 2;
}