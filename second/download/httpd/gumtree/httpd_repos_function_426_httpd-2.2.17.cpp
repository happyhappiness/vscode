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

            config_log_transaction(r, cls, mls->default_format);
        }
    }
    else if (mls->server_config_logs) {
        clsarray = (config_log_state *) mls->server_config_logs->elts;
        for (i = 0; i < mls->server_config_logs->nelts; ++i) {
            config_log_state *cls = &clsarray[i];

            config_log_transaction(r, cls, mls->default_format);
        }
    }

    return OK;
}