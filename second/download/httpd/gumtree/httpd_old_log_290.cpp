ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_DEBUG, r->server,
	     MODNAME ": rsl_strdup() %d chars: %s", res_pos - 1, result);