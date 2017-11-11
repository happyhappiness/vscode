static void *make_config_log_state(apr_pool_t *p, server_rec *s)
{
    multi_log_state *mls;

    mls = (multi_log_state *) apr_palloc(p, sizeof(multi_log_state));
    mls->config_logs = apr_array_make(p, 1, sizeof(config_log_state));
    mls->default_format_string = NULL;
    mls->default_format = NULL;
    mls->server_config_logs = NULL;
    mls->formats = apr_table_make(p, 4);
    apr_table_setn(mls->formats, "CLF", DEFAULT_LOG_FORMAT);

    return mls;
}