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

        server_pid = getpid();
    }

    beosd_pre_config();
