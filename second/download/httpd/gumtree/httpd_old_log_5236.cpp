ap_log_error(APLOG_MARK, APLOG_ERR, APR_FROM_OS_ERROR(rc), ap_server_conf,
                     "unable to create shutdown semaphore, exiting");