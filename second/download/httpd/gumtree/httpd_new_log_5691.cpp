ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, APLOGNO(00201)
                         "caught %s, shutting down",
                         (rc == DONE) ? "SIGTERM" : "error");