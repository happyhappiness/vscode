ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
			     "getpwuid: invalid userid %ld",
			     (long) r->server->server_uid);