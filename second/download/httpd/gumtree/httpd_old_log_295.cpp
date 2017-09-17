ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_ERR, r->server,
		    MODNAME ": broken symlink (%s)", fn);