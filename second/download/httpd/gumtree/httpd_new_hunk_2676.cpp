#if MIME_MAGIC_DEBUG

    for (m = conf->magic; m; m = m->next) {

	if (ap_isprint((((unsigned long) m) >> 24) & 255) &&

	    ap_isprint((((unsigned long) m) >> 16) & 255) &&

	    ap_isprint((((unsigned long) m) >> 8) & 255) &&

	    ap_isprint(((unsigned long) m) & 255)) {

	    ap_log_rerror(APLOG_MARK, APLOG_NOERRNO | APLOG_DEBUG, r,

			MODNAME ": match: POINTER CLOBBERED! "

			"m=\"%c%c%c%c\"",

			(((unsigned long) m) >> 24) & 255,

			(((unsigned long) m) >> 16) & 255,

			(((unsigned long) m) >> 8) & 255,

			((unsigned long) m) & 255);

