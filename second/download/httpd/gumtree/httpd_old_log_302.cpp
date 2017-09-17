ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_DEBUG, r->server,
			MODNAME ": match line=%d cont=%d type=%d %s",
			m->lineno, m->cont_level, m->type,
			(m->type == STRING) ? m->value.s : "");