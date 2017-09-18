    regex_t *compiled;
    const apr_size_t nres = sizeof(*ctx->re_result) / sizeof(regmatch_t);
    int regex_error;

    compiled = ap_pregcomp(r->pool, rexp, REG_EXTENDED | REG_NOSUB);
    if (compiled == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                      "unable to compile pattern \"%s\"", rexp);
        return -1;
    }
    if (!ctx->re_result) {
        ctx->re_result = apr_pcalloc(r->pool, sizeof(*ctx->re_result));
    }
