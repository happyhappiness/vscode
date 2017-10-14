ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                         "proxy: %s: worker for (%s) has been marked for retry",
                         proxy_function, worker->hostname);