static int perchild_pre_config(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp)
{
    static int restart_num = 0;
    int no_detach, debug, foreground;
    ap_directive_t *pdir;
    int i;
    int tmp_server_limit = DEFAULT_SERVER_LIMIT;
    int tmp_thread_limit = DEFAULT_THREAD_LIMIT;
    apr_status_t rv;

    debug = ap_exists_config_define("DEBUG");

    if (debug) {
        foreground = one_process = 1;
        no_detach = 0;
    }
    else {
        one_process = ap_exists_config_define("ONE_PROCESS");
        no_detach = ap_exists_config_define("NO_DETACH");
        foreground = ap_exists_config_define("FOREGROUND");
    }

    /* sigh, want this only the second time around */
    if (restart_num++ == 1) {
        is_graceful = 0;

        if (!one_process && !foreground) {
            rv = apr_proc_detach(no_detach ? APR_PROC_DETACH_FOREGROUND
                                           : APR_PROC_DETACH_DAEMONIZE);
            if (rv != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_CRIT, rv, NULL,
                             "apr_proc_detach failed");
                return HTTP_INTERNAL_SERVER_ERROR;
            }                  
        }

        my_pid = getpid();
    }

    unixd_pre_config(ptemp);
    ap_listen_pre_config();
    num_daemons = DEFAULT_NUM_DAEMON;
    threads_to_start = DEFAULT_START_THREAD;
    min_spare_threads = DEFAULT_MIN_SPARE_THREAD;
    max_spare_threads = DEFAULT_MAX_SPARE_THREAD;
    max_threads = thread_limit;
    ap_pid_fname = DEFAULT_PIDLOG;
    ap_lock_fname = DEFAULT_LOCKFILE;
    ap_max_requests_per_child = DEFAULT_MAX_REQUESTS_PER_CHILD;
    curr_child_num = 0;
#ifdef AP_MPM_WANT_SET_MAX_MEM_FREE
	ap_max_mem_free = APR_ALLOCATOR_MAX_FREE_UNLIMITED;
#endif

    apr_cpystrn(ap_coredump_dir, ap_server_root, sizeof(ap_coredump_dir));

    /* we need to know ServerLimit and ThreadLimit before we start processing
     * the tree because we need to already have allocated child_info_table
     */
    for (pdir = ap_conftree; pdir != NULL; pdir = pdir->next) {
        if (!strcasecmp(pdir->directive, "ServerLimit")) {
            if (atoi(pdir->args) > tmp_server_limit) {
                tmp_server_limit = atoi(pdir->args);
                if (tmp_server_limit > MAX_SERVER_LIMIT) {
                    tmp_server_limit = MAX_SERVER_LIMIT;
                }
            }
        }
        else if (!strcasecmp(pdir->directive, "ThreadLimit")) {
            if (atoi(pdir->args) > tmp_thread_limit) {
                tmp_thread_limit = atoi(pdir->args);
                if (tmp_thread_limit > MAX_THREAD_LIMIT) {
                    tmp_thread_limit = MAX_THREAD_LIMIT;
                }
            }
        }
    }

    child_info_table = (child_info_t *)apr_pcalloc(p, tmp_server_limit * sizeof(child_info_t));
    for (i = 0; i < tmp_server_limit; i++) {
        child_info_table[i].uid = -1;
        child_info_table[i].gid = -1;
        child_info_table[i].input = -1;
        child_info_table[i].output = -1;
    }

    return OK;
}