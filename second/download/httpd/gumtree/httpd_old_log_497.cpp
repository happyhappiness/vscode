ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
	      "Warning: NetMask not supplied with IP-Addr; guessing: %s/%ld\n",
		 inet_ntoa(This->addr), bits);