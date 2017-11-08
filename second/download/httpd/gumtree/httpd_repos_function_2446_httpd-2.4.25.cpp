static int read_pvalue(link_ctx *ctx, const char **pvalue)
{
    if (skip_ws(ctx) && read_chr(ctx, '=')) {
        if (read_qstring(ctx, pvalue) || read_ptoken(ctx, pvalue)) {
            return 1;
        }
    }
    return 0;
}