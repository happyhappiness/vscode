ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
			 "setrlimit(RLIMIT_DATA): failed to set memory "
			 "usage limit");