ap_log_error(APLOG_MARK, APLOG_CRIT, errno, server_conf,
            "make_secure_socket: failed to get a socket for %s", addr);