ap_log_rerror(APLOG_MARK, APLOG_NOERRNO | APLOG_DEBUG, 0, r,
	     MODNAME ": rsl_strdup() %d chars: %s", res_pos - 1, result);