		(conf->magic && conf->magic->next) ? "set" : "NULL",
		conf->last ? "set" : "NULL");
#endif

#if MIME_MAGIC_DEBUG
    for (m = conf->magic; m; m = m->next) {
	if (isprint((((unsigned long) m) >> 24) & 255) &&
	    isprint((((unsigned long) m) >> 16) & 255) &&
	    isprint((((unsigned long) m) >> 8) & 255) &&
	    isprint(((unsigned long) m) & 255)) {
	    ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_DEBUG, r->server,
			MODNAME ": match: POINTER CLOBBERED! "
			"m=\"%c%c%c%c\"",
			(((unsigned long) m) >> 24) & 255,
			(((unsigned long) m) >> 16) & 255,
			(((unsigned long) m) >> 8) & 255,
