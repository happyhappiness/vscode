static int skip_pvalue(link_ctx *ctx)
{
    if (skip_ws(ctx) && read_chr(ctx, '=')) {
        if (skip_qstring(ctx) || skip_ptoken(ctx)) {
            return 1;
        }
    }
    return 0;
}