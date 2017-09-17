ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
		    "DB user %s not found: %s", c->user, r->filename);