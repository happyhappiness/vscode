static int read_param(link_ctx *ctx)
{
    if (skip_ws(ctx) && read_chr(ctx, ';')) {
        char *name, *value = "";
        if (read_pname(ctx, &name)) {
            read_pvalue(ctx, &value); /* value is optional */
            apr_table_setn(ctx->params, name, value);
            return 1;
        }
    }
    return 0;
}