ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_NOTICE, 0,
                         ap_server_conf, "caught SIGTERM, shutting down");