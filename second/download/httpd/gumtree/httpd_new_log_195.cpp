ap_log_rerror(APLOG_MARK, APLOG_ERR, r,
		     "proxy connect to %s port %d failed",
		     inet_ntoa(addr->sin_addr), ntohs(addr->sin_port));