		return;

#if MIME_MAGIC_DEBUG

	    prevm = 0;

	    ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_DEBUG, s,

			MODNAME ": magic_init 1 test");

	    for (m = conf->magic; m; m = m->next) {

		if (isprint((((unsigned long) m) >> 24) & 255) &&

		    isprint((((unsigned long) m) >> 16) & 255) &&

		    isprint((((unsigned long) m) >> 8) & 255) &&

		    isprint(((unsigned long) m) & 255)) {

		    ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_DEBUG, s,

				MODNAME ": magic_init 1: POINTER CLOBBERED! "

				"m=\"%c%c%c%c\" line=%d",

				(((unsigned long) m) >> 24) & 255,

				(((unsigned long) m) >> 16) & 255,

				(((unsigned long) m) >> 8) & 255,

-- apache_1.3.0/src/modules/standard/mod_negotiation.c	1998-05-31 03:15:38.000000000 +0800

