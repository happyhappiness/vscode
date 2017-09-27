ap_log_error(APLOG_MARK, APLOG_WARNING, rv, ap_server_conf, APLOGNO(02436)
                         "WARNING: ThreadStackSize of %" APR_SIZE_T_FMT " is "
                         "inappropriate, using default", 
                         ap_thread_stacksize);