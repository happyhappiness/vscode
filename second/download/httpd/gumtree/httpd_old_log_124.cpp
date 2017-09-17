ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
			     "getgrgid: invalid groupid %ld",
			     (long) r->server->server_gid);