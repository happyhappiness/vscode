ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
	    "Warning: NetMask and IP-Addr disagree in %s/%ld",
		inet_ntoa(This->addr), bits);