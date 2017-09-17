ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
		    "DBM user %s not found: %s", c->user, r->filename);