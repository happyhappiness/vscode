ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
			      "apr_socket_opt_set(APR_SO_RCVBUF): Failed to set ProxyReceiveBufferSize, using default");