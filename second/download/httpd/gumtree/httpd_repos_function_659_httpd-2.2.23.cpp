int yyinput(char *buf, int max_size)
{
    int n;

    if ((n = MIN(max_size, ssl_expr_info.inputbuf
                         + ssl_expr_info.inputlen
                         - ssl_expr_info.inputptr)) <= 0)
        return YY_NULL;
    memcpy(buf, ssl_expr_info.inputptr, n);
    ssl_expr_info.inputptr += n;
    return n;
}