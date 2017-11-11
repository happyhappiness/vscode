static int mpmt_os2_pre_config(apr_pool_t *pconf, apr_pool_t *plog, apr_pool_t *ptemp)
{
    one_process = ap_exists_config_define("ONE_PROCESS") ||
                  ap_exists_config_define("DEBUG");
    is_graceful = 0;
    ap_listen_pre_config();
    ap_daemons_to_start = DEFAULT_START_DAEMON;
    ap_thread_limit = HARD_THREAD_LIMIT;
    ap_pid_fname = DEFAULT_PIDLOG;
    ap_max_requests_per_child = DEFAULT_MAX_REQUESTS_PER_CHILD;
    ap_extended_status = 0;
    ap_min_spare_threads = DEFAULT_MIN_SPARE_THREAD;
    ap_max_spare_threads = DEFAULT_MAX_SPARE_THREAD;
#ifdef AP_MPM_WANT_SET_MAX_MEM_FREE
        ap_max_mem_free = APR_ALLOCATOR_MAX_FREE_UNLIMITED;
#endif

    return OK;
}