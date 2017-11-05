static APR_INLINE int re_check(include_ctx_t *ctx, const char *string,
                               const char *rexp)
{
    ap_regex_t *compiled;
    backref_t *re = ctx->intern->re;

    compiled = ap_pregcomp(ctx->dpool, rexp, AP_REG_EXTENDED);
    if (!compiled) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r, "unable to "
                      "compile pattern \"%s\"", rexp);
        return -1;
    }

    if (!re) {
        re = ctx->intern->re = apr_palloc(ctx->pool, sizeof(*re));
    }

    re->source = apr_pstrdup(ctx->pool, string);
    re->rexp = apr_pstrdup(ctx->pool, rexp);
    re->nsub = compiled->re_nsub;
    re->have_match = !ap_regexec(compiled, string, AP_MAX_REG_MATCH,
                                 re->match, 0);

    ap_pregfree(ctx->dpool, compiled);
    return re->have_match;
}