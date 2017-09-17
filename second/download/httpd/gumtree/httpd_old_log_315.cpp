ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_DEBUG, r->server,
			"%ld < %ld = %d", v, l, matched);