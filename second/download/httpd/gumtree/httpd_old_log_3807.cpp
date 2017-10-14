ap_log_error(APLOG_MARK, APLOG_ERR, errno,
                             (server_rec *)data,
                             "Error accepting on cgid socket");