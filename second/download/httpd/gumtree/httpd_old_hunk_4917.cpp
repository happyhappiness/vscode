}

static int winnt_check_config(apr_pool_t *pconf, apr_pool_t *plog,
                              apr_pool_t *ptemp, server_rec* s)
{
    int is_parent;
    static int restart_num = 0;
    int startup = 0;

    /* We want this only in the parent and only the first time around */
    is_parent = (parent_pid == my_pid);
    if (is_parent && restart_num++ == 0) {
        startup = 1;
    }

    if (thread_limit > MAX_THREAD_LIMIT) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00439)
