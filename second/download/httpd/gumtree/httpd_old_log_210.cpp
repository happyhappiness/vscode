ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
		    "DB user %s not found: %s", c->user, r->filename);