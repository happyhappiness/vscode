static int read_ptoken(link_ctx *ctx, const char **ps)
{
    if (skip_ws(ctx)) {
        size_t i;
        for (i = ctx->i; i < ctx->slen && ptoken_char(ctx->s[i]); ++i) {
            /* nop */
        }
        if (i > ctx->i) {
            *ps = mk_str(ctx, i);
            ctx->i = i;
            return 1;
        }
    }
    return 0;
}