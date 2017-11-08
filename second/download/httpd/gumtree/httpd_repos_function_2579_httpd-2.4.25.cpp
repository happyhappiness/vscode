static int skip_ptoken(link_ctx *ctx)
{
    if (skip_ws(ctx)) {
        int i;
        for (i = ctx->i; i < ctx->slen && ptoken_char(ctx->s[i]); ++i) {
            /* nop */
        }
        if (i > ctx->i) {
            ctx->i = i;
            return 1;
        }
    }
    return 0;
}