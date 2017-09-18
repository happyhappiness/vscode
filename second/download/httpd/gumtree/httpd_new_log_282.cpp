ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, serv,
		MODNAME ": parse line=%d m=%x next=%x cont=%d desc=%s",
		lineno, m, m->next, m->cont_level, m->desc);