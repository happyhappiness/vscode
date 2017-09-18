ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_NOERRNO, 0,
                             ap_server_conf, "Could not pass request to proper "
                             "child, request will not be honored.");