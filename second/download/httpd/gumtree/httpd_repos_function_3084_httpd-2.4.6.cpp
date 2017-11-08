static const char *ap_expr_eval_re_backref(ap_expr_eval_ctx_t *ctx, unsigned int n)
{
    int len;

    if (!ctx->re_pmatch || !ctx->re_source || *ctx->re_source == '\0' ||
        ctx->re_nmatch < n + 1)
        return "";

    len = ctx->re_pmatch[n].rm_eo - ctx->re_pmatch[n].rm_so;
    if (len == 0)
        return "";

    return apr_pstrndup(ctx->p, *ctx->re_source + ctx->re_pmatch[n].rm_so, len);
}