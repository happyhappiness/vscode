static int worker_check_config(apr_pool_t *p, apr_pool_t *plog,
                               apr_pool_t *ptemp, server_rec *s)
{
    int startup = 0;

    /* the reverse of pre_config, we want this only the first time around */
    if (retained->mpm->module_loads == 1) {
        startup = 1;
    }

    if (server_limit > MAX_SERVER_LIMIT) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00300)
