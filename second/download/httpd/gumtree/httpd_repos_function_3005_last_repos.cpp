static const char *interpolate_vars(request_rec *r, const char *str)
{
    const char *start;
    const char *end;
    const char *delim;
    const char *before;
    const char *after;
    const char *replacement;
    const char *var;
    for (;;) {
        start = str;
        if (start = ap_strstr_c(start, "${"), start == NULL)
            break;

        if (end = ap_strchr_c(start+2, '}'), end == NULL)
            break;

        delim = ap_strchr_c(start, '|');
        before = apr_pstrndup(r->pool, str, start-str);
        after = end+1;
        if (delim) {
            var = apr_pstrndup(r->pool, start+2, delim-start-2);
        }
        else {
            var = apr_pstrndup(r->pool, start+2, end-start-2);
        }
        replacement = apr_table_get(r->subprocess_env, var);
        if (!replacement) {
            if (delim)
                replacement = apr_pstrndup(r->pool, delim+1, end-delim-1);
            else
                replacement = "";
        }
        str = apr_pstrcat(r->pool, before, replacement, after, NULL);
        ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r,
                      "Interpolating %s  =>  %s", var, replacement);
    }
    return str;
}