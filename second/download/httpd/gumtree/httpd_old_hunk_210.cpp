    register int val;

    while ((c = *s++) != '\0') {
	if (apr_isspace((unsigned char) c))
	    break;
	if (p >= pmax) {
	    ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_ERR, 0, serv,
			MODNAME ": string too long: %s", origs);
	    break;
	}
	if (c == '\\') {
	    switch (c = *s++) {

