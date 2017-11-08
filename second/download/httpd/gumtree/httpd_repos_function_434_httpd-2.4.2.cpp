static int config_log_transaction(request_rec *r, config_log_state *cls,
                                  apr_array_header_t *default_format)
{
    log_format_item *items;
    const char **strs;
    int *strl;
    request_rec *orig;
    int i;
    apr_size_t len = 0;
    apr_array_header_t *format;
    char *envar;
    apr_status_t rv;

    if (cls->fname == NULL) {
        return DECLINED;
    }

    /*
     * See if we've got any conditional envariable-controlled logging decisions
     * to make.
     */
    if (cls->condition_var != NULL) {
        envar = cls->condition_var;
        if (*envar != '!') {
            if (apr_table_get(r->subprocess_env, envar) == NULL) {
                return DECLINED;
            }
        }
        else {
            if (apr_table_get(r->subprocess_env, &envar[1]) != NULL) {
                return DECLINED;
            }
        }
    }
    else if (cls->condition_expr != NULL) {
        const char *err;
        int rc = ap_expr_exec(r, cls->condition_expr, &err);
        if (rc < 0)
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(00644)
                           "Error evaluating log condition: %s", err);
        if (rc <= 0)
            return DECLINED;
    }

    format = cls->format ? cls->format : default_format;

    strs = apr_palloc(r->pool, sizeof(char *) * (format->nelts));
    strl = apr_palloc(r->pool, sizeof(int) * (format->nelts));
    items = (log_format_item *) format->elts;

    orig = r;
    while (orig->prev) {
        orig = orig->prev;
    }
    while (r->next) {
        r = r->next;
    }

    for (i = 0; i < format->nelts; ++i) {
        strs[i] = process_item(r, orig, &items[i]);
    }

    for (i = 0; i < format->nelts; ++i) {
        len += strl[i] = strlen(strs[i]);
    }
    if (!log_writer) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00645)
                "log writer isn't correctly setup");
         return HTTP_INTERNAL_SERVER_ERROR;
    }
    rv = log_writer(r, cls->log_writer, strs, strl, format->nelts, len);
    if (rv != APR_SUCCESS)
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, rv, r, APLOGNO(00646) "Error writing to %s",
                      cls->fname);
    return OK;
}