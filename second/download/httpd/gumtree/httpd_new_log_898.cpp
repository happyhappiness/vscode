ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ap_server_conf,
                             "Server ran out of threads to serve requests. Consider "
                             "raising the ThreadsPerChild setting");