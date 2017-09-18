ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                         "setsockopt(SO_RCVBUF): Failed to set "
                         "ProxyReceiveBufferSize, using default");