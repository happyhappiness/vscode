ap_log_rerror(APLOG_MARK, APLOG_ERR, r,
			     "getpwuid: invalid userid %ld",
			     (long) r->server->server_uid);