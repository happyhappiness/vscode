ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
		    "DB user %s: password mismatch: %s", c->user, r->uri);