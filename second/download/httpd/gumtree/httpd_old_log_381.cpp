ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL,
	    "Warning: NetMask and IP-Addr disagree in %s/%ld\n",
		inet_ntoa(This->addr), bits);