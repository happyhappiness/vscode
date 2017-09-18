ap_log_error(APLOG_MARK, APLOG_DEBUG, lasterror, ap_server_conf,
                       "winnt_accept: AcceptEx failed due to early client "
                       "disconnect. Reallocate the accept socket and try again.");