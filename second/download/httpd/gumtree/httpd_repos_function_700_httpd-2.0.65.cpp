int ssl_expr_exec(request_rec *r, ssl_expr *expr)
{
    BOOL rc;

    rc = ssl_expr_eval(r, expr);
    if (ssl_expr_error != NULL)
        return (-1);
    else
        return (rc ? 1 : 0);
}