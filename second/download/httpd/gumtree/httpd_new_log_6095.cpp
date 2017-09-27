ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, wd_server_conf->s,
                 APLOGNO(02973) "%sWatchdog (%s) stopping",
                 w->singleton ? "Singleton " : "", w->name);