ap_log_rerror(APLOG_MARK, APLOG_NOERRNO | APLOG_ERR, 0, r,
				MODNAME ": bad state %d (ns)", state);