ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_DEBUG, r->server,
			"%lu < %lu = %d", v, l, matched);