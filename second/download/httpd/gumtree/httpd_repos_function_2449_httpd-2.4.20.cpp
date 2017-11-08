static int read_pname(link_ctx *ctx, char **pname)
{
    if (skip_ws(ctx)) {
        size_t i;
        for (i = ctx->i; i < ctx->slen && attr_char(ctx->s[i]); ++i) {
            /* nop */
        }
        if (i > ctx->i) {
            *pname = mk_str(ctx, i);
            ctx->i = i;
            return 1;
        }
    }
    return 0;
}