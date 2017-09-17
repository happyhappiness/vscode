ap_log_rerror(APLOG_MARK, APLOG_NOERRNO | APLOG_DEBUG, r,
		    "((%lx & %lx) != %lx) = %d", v, l, l, matched);