ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_netos_error(),
                         ap_server_conf, APLOGNO(02323)
                         "winnt_accept: failed to retrieve GetAcceptExSockaddrs, try 'AcceptFilter none'");