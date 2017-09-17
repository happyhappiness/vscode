ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
			    "user %s not in DB group file %s: %s",
			    user, sec->auth_dbgrpfile, r->filename);