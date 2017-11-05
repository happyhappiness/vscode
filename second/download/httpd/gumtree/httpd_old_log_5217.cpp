ap_log_error(APLOG_MARK, APLOG_EMERG, status, ap_server_conf, APLOGNO(00155)
                     "Couldn't initialize cross-process lock in child "
                     "(%s) (%s)",
                     lockfile ? lockfile : "none",
                     apr_proc_mutex_name(accept_mutex));