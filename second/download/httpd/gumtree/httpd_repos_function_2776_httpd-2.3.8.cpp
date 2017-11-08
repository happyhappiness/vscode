static APR_INLINE int re_check(request_rec *r, const char *string,
                               const char *rexp, backref_t **reptr)
{
    ap_regex_t *compiled;
    backref_t *re = reptr ? *reptr : NULL;

    compiled = ap_pregcomp(r->pool, rexp, AP_REG_EXTENDED);
    if (!compiled) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "unable to "
                      "compile pattern \"%s\"", rexp);
        return -1;
    }

    if (!re) {
        re = apr_palloc(r->pool, sizeof(*re));
        if (reptr) {
            *reptr = re;
        }
    }

    re->source = apr_pstrdup(r->pool, string);
    re->rexp = apr_pstrdup(r->pool, rexp);
    re->nsub = compiled->re_nsub;
    re->have_match = !ap_regexec(compiled, string, AP_MAX_REG_MATCH,
                                 re->match, 0);

    ap_pregfree(r->pool, compiled);
    return re->have_match;
}