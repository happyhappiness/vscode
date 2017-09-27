    }

    for (i = 0; i < format->nelts; ++i) {
        len += strl[i] = strlen(strs[i]);
    }
    if (!log_writer) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, APR_EGENERAL, r,
                "log writer isn't correctly setup");
         return HTTP_INTERNAL_SERVER_ERROR;
    }
    rv = log_writer(r, cls->log_writer, strs, strl, format->nelts, len);
    /* xxx: do we return an error on log_writer? */
    return OK;
}

static int multi_log_transaction(request_rec *r)
{
    multi_log_state *mls = ap_get_module_config(r->server->module_config,
                                                &log_config_module);
    config_log_state *clsarray;
    int i;

    /*
     * Log this transaction..
     */
    if (mls->config_logs->nelts) {
        clsarray = (config_log_state *) mls->config_logs->elts;
        for (i = 0; i < mls->config_logs->nelts; ++i) {
            config_log_state *cls = &clsarray[i];
