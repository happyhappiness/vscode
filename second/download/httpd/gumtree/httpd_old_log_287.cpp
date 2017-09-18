ap_log_rerror(APLOG_MARK, APLOG_NOERRNO | APLOG_DEBUG, 0, r,
			MODNAME ": match: POINTER CLOBBERED! "
			"m=\"%c%c%c%c\"",
			(((unsigned long) m) >> 24) & 255,
			(((unsigned long) m) >> 16) & 255,
			(((unsigned long) m) >> 8) & 255,
			((unsigned long) m) & 255);