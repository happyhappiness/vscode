    }

    for (i = 0; i < format->nelts; ++i) {
        len += strl[i] = strlen(strs[i]);
    }
    if (!log_writer) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                "log writer isn't correctly setup");
         return HTTP_INTERNAL_SERVER_ERROR;
    }
    rv = log_writer(r, cls->log_writer, strs, strl, format->nelts, len);
    if (rv != APR_SUCCESS)
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, rv, r, "Error writing to %s",
                      cls->fname);
    return OK;
}

static int multi_log_transaction(request_rec *r)
{
    multi_log_state *mls = ap_get_module_config(r->server->module_config,
                                                &log_config_module);
    config_log_state *clsarray;
    int i;

    /*
     * Initialize per request state
     */
    log_request_state *state = apr_pcalloc(r->pool, sizeof(log_request_state));
    ap_set_module_config(r->request_config, &log_config_module, state);

    /*
     * Log this transaction..
     */
    if (mls->config_logs->nelts) {
        clsarray = (config_log_state *) mls->config_logs->elts;
        for (i = 0; i < mls->config_logs->nelts; ++i) {
            config_log_state *cls = &clsarray[i];
