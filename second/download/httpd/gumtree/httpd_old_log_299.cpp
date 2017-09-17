ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_DEBUG, r->server,
		    MODNAME ": line=%d desc=%s", m->lineno, m->desc);