{
    register unsigned long l = m->value.l;
    register unsigned long v;
    int matched;

    if ((m->value.s[0] == 'x') && (m->value.s[1] == '\0')) {
	ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_ERR, r->server,
		    MODNAME ": BOINK");
	return 1;
    }

    switch (m->type) {
    case BYTE:
