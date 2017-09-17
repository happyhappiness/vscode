ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
			    "user %s not in DB group file %s: %s",
			    user, sec->auth_dbgrpfile, r->filename);