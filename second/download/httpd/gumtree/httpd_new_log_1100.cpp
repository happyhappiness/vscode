ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
			      "proxy: FTP: error setting reuseaddr option: apr_socket_opt_set(APR_SO_REUSEADDR)");