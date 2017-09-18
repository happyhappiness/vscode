ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_DEBUG, 0, s,
		MODNAME ": apprentice conf=%x file=%s m=%s m->next=%s last=%s",
		conf,
		conf->magicfile ? conf->magicfile : "NULL",
		conf->magic ? "set" : "NULL",
		(conf->magic && conf->magic->next) ? "set" : "NULL",
		conf->last ? "set" : "NULL");