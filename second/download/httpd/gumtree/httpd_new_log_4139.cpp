ap_log_error(APLOG_MARK, APLOG_CRIT, rv, srv, APLOGNO(01493)
                     "rfc1413: apr_sockaddr_info_get(%s) failed",
                     conn->client_ip);