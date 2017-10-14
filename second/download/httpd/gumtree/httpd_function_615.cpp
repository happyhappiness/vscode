static int re_check(request_rec *r, include_ctx_t *ctx, 
                    char *string, char *rexp)
{
    regex_t *compiled;
    const apr_size_t nres = sizeof(*ctx->re_result) / sizeof(regmatch_t);
    int regex_error;

    compiled = ap_pregcomp(r->pool, rexp, REG_EXTENDED | REG_NOSUB);
    if (compiled == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "unable to compile pattern \"%s\"", rexp);
        return -1;
    }
    if (!ctx->re_result) {
        ctx->re_result = apr_pcalloc(r->pool, sizeof(*ctx->re_result));
    }
    ctx->re_string = string;
    regex_error = ap_regexec(compiled, string, nres, *ctx->re_result, 0);
    ap_pregfree(r->pool, compiled);
    return (!regex_error);
}