    char *origs = s, *origp = p;
    char *pmax = p + plen - 1;
    register int c;
    register int val;

    while ((c = *s++) != '\0') {
	if (ap_isspace((unsigned char) c))
	    break;
	if (p >= pmax) {
	    ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_ERR, serv,
			MODNAME ": string too long: %s", origs);
	    break;
	}
