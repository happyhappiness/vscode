ap_log_rerror(APLOG_MARK, APLOG_NOERRNO | APLOG_DEBUG, r,
		    MODNAME ": line=%d desc=%s", m->lineno, m->desc);