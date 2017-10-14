ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, wd_server_conf->s,
                     "%sWatchdog (%s) running (%" APR_PID_T_FMT ")",
                     w->singleton ? "Singleton" : "",
                     w->name, getpid());