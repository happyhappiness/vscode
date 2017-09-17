ap_log_rerror(APLOG_MARK, APLOG_ERR, r,
			     "getgrgid: invalid groupid %ld",
			     (long) r->server->server_gid);