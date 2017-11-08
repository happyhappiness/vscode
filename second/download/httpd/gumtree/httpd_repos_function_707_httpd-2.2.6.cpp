char *ssl_expr_get_error(void)
{
    if (ssl_expr_error == NULL)
        return "";
    return ssl_expr_error;
}