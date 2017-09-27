    }

    /* sigh, want this only the second time around */
    retained = ap_retained_data_get(userdata_key);
    if (!retained) {
        retained = ap_retained_data_create(userdata_key, sizeof(*retained));
        retained->max_daemons_limit = -1;
        retained->idle_spawn_rate = 1;
    }
    ++retained->module_loads;
    if (retained->module_loads == 2) {
        rv = apr_pollset_create(&event_pollset, 1, plog,
                                APR_POLLSET_THREADSAFE | APR_POLLSET_NOCOPY);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, rv, NULL, APLOGNO(00495)
                         "Couldn't create a Thread Safe Pollset. "
                         "Is it supported on your platform?"
                         "Also check system or user limits!");
            return HTTP_INTERNAL_SERVER_ERROR;
        }
        apr_pollset_destroy(event_pollset);

        if (!one_process && !foreground) {
            /* before we detach, setup crash handlers to log to errorlog */
            ap_fatal_signal_setup(ap_server_conf, pconf);
            rv = apr_proc_detach(no_detach ? APR_PROC_DETACH_FOREGROUND
                                 : APR_PROC_DETACH_DAEMONIZE);
            if (rv != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_CRIT, rv, NULL, APLOGNO(00496)
                             "apr_proc_detach failed");
                return HTTP_INTERNAL_SERVER_ERROR;
            }
        }
    }

    parent_pid = ap_my_pid = getpid();

    ap_listen_pre_config();
    ap_daemons_to_start = DEFAULT_START_DAEMON;
    min_spare_threads = DEFAULT_MIN_FREE_DAEMON * DEFAULT_THREADS_PER_CHILD;
    max_spare_threads = DEFAULT_MAX_FREE_DAEMON * DEFAULT_THREADS_PER_CHILD;
    server_limit = DEFAULT_SERVER_LIMIT;
    thread_limit = DEFAULT_THREAD_LIMIT;
    ap_daemons_limit = server_limit;
    threads_per_child = DEFAULT_THREADS_PER_CHILD;
    max_workers = ap_daemons_limit * threads_per_child;
    ap_extended_status = 0;

    return OK;
}

static int event_check_config(apr_pool_t *p, apr_pool_t *plog,
                              apr_pool_t *ptemp, server_rec *s)
