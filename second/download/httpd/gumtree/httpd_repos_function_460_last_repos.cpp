static int log_check_config(apr_pool_t *pconf, apr_pool_t *plog, apr_pool_t *ptemp, server_rec *s)
{
    int rv = OK;
    while (s) {
        multi_log_state *mls = ap_get_module_config(s->module_config,
                                                    &log_config_module);
        /*
         * We don't need to check mls->server_config_logs because it just
         * points to the parent server's mls->config_logs.
         */
        apr_array_header_t *log_list = mls->config_logs;
        config_log_state *clsarray = (config_log_state *) log_list->elts;
        int i;
        for (i = 0; i < log_list->nelts; ++i) {
            if (check_log_dir(ptemp, s, &clsarray[i]) != OK)
                rv = !OK;
        }

        s = s->next;
    }
    return rv;
}