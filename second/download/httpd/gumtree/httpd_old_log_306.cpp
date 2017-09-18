ap_log_rerror(APLOG_MARK, APLOG_NOERRNO | APLOG_DEBUG, 0, r,
		    "((%lx & %lx) != %lx) = %d", v, l, l, matched);