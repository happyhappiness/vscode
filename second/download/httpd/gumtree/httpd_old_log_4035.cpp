ap_log_error(APLOG_MARK, APLOG_CRIT, rv, srv,
                     "rfc1413: apr_sockaddr_info_get(%s) failed",
                     conn->local_ip);