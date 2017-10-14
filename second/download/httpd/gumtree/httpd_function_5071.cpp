static int event_pre_config(apr_pool_t * pconf, apr_pool_t * plog,
                            apr_pool_t * ptemp)
{
    int no_detach, debug, foreground;
    apr_status_t rv;
    const char *userdata_key = "mpm_event_module";

    mpm_state = AP_MPMQ_STARTING;

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
    retained = ap_retained_data_get(userdata_key);
    if (!retained) {
        retained = ap_retained_data_create(userdata_key, sizeof(*retained));
    }
    ++retained->module_loads;
    if (retained->module_loads == 2) {
        is_graceful = 0;
        rv = apr_pollset_create(&event_pollset, 1, plog,
                                APR_POLLSET_THREADSAFE | APR_POLLSET_NOCOPY);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, rv, NULL,
                         "Couldn't create a Thread Safe Pollset. "
                         "Is it supported on your platform?"
                         "Also check system or user limits!");
            return HTTP_INTERNAL_SERVER_ERROR;
        }
        apr_pollset_destroy(event_pollset);

        if (!one_process && !foreground) {
            rv = apr_proc_detach(no_detach ? APR_PROC_DETACH_FOREGROUND
                                 : APR_PROC_DETACH_DAEMONIZE);
            if (rv != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_CRIT, rv, NULL,
                             "apr_proc_detach failed");
                return HTTP_INTERNAL_SERVER_ERROR;
            }
        }
        parent_pid = ap_my_pid = getpid();
    }

    ap_listen_pre_config();
    ap_daemons_to_start = DEFAULT_START_DAEMON;
    min_spare_threads = DEFAULT_MIN_FREE_DAEMON * DEFAULT_THREADS_PER_CHILD;
    max_spare_threads = DEFAULT_MAX_FREE_DAEMON * DEFAULT_THREADS_PER_CHILD;
    server_limit = DEFAULT_SERVER_LIMIT;
    thread_limit = DEFAULT_THREAD_LIMIT;
    ap_daemons_limit = server_limit;
    threads_per_child = DEFAULT_THREADS_PER_CHILD;
    max_clients = ap_daemons_limit * threads_per_child;
    ap_pid_fname = DEFAULT_PIDLOG;
    ap_max_requests_per_child = DEFAULT_MAX_REQUESTS_PER_CHILD;
    ap_extended_status = 0;
    ap_max_mem_free = APR_ALLOCATOR_MAX_FREE_UNLIMITED;

    apr_cpystrn(ap_coredump_dir, ap_server_root, sizeof(ap_coredump_dir));

    return OK;
}