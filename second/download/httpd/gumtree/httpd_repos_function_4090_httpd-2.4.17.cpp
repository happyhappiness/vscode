static int mpmt_os2_pre_config(apr_pool_t *pconf, apr_pool_t *plog, apr_pool_t *ptemp)
{
    one_process = ap_exists_config_define("ONE_PROCESS") ||
                  ap_exists_config_define("DEBUG");
    is_graceful = 0;
    ap_listen_pre_config();
    ap_daemons_to_start = DEFAULT_START_DAEMON;
    ap_thread_limit = HARD_THREAD_LIMIT;
    ap_extended_status = 0;
    ap_min_spare_threads = DEFAULT_MIN_SPARE_THREAD;
    ap_max_spare_threads = DEFAULT_MAX_SPARE_THREAD;
    ap_sys_privileges_handlers(1);

    return OK;
}