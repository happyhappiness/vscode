
static APR_INLINE int re_check(include_ctx_t *ctx, const char *string,
                               const char *rexp)
{
    ap_regex_t *compiled;
    backref_t *re = ctx->intern->re;

    compiled = ap_pregcomp(ctx->dpool, rexp, AP_REG_EXTENDED);
    if (!compiled) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->intern->r, "unable to "
                      "compile pattern \"%s\"", rexp);
        return -1;
