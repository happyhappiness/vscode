	else if (conf->magicfile) {
	    result = apprentice(s, p);
	    if (result == -1)
		return OK;
#if MIME_MAGIC_DEBUG
	    prevm = 0;
	    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
			MODNAME ": magic_init 1 test");
	    for (m = conf->magic; m; m = m->next) {
		if (apr_isprint((((unsigned long) m) >> 24) & 255) &&
		    apr_isprint((((unsigned long) m) >> 16) & 255) &&
		    apr_isprint((((unsigned long) m) >> 8) & 255) &&
		    apr_isprint(((unsigned long) m) & 255)) {
		    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
				MODNAME ": magic_init 1: POINTER CLOBBERED! "
				"m=\"%c%c%c%c\" line=%d",
				(((unsigned long) m) >> 24) & 255,
				(((unsigned long) m) >> 16) & 255,
				(((unsigned long) m) >> 8) & 255,
				((unsigned long) m) & 255,
