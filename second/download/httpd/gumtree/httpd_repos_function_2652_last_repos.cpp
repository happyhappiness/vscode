static int skip_param(link_ctx *ctx)
{
    if (skip_ws(ctx) && read_chr(ctx, ';')) {
        if (skip_pname(ctx)) {
            skip_pvalue(ctx); /* value is optional */
            return 1;
        }
    }
    return 0;
}