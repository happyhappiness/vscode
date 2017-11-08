ssl_expr *ssl_expr_comp(apr_pool_t *p, char *expr)
{
    ssl_expr_info.pool       = p;
    ssl_expr_info.inputbuf   = expr;
    ssl_expr_info.inputlen   = strlen(expr);
    ssl_expr_info.inputptr   = ssl_expr_info.inputbuf;
    ssl_expr_info.expr       = FALSE;

    ssl_expr_error = NULL;
    if (ssl_expr_yyparse())
        return NULL;
    return ssl_expr_info.expr;
}