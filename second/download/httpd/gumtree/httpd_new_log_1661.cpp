ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                    "ap_proxy_connect_backend disabling worker for (%s)",
                    worker->hostname);