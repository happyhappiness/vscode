ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_DEBUG, r->server,
		    "((%lx & %lx) == %lx) = %d", v, l, l, matched);