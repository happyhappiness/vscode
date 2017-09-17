ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
		     "proxy connect to %s port %d failed",
		     inet_ntoa(addr->sin_addr), ntohs(addr->sin_port));