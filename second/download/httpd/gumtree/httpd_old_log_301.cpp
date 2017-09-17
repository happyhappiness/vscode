r(APLOG_MARK, APLOG_NOERRNO | APLOG_DEBUG, r->server,
		    MODNAME ": rule matched, line=%d type=%d %s",
		    m->lineno, m->type,
		    (m->type == STRING) ? m->value.s : "");