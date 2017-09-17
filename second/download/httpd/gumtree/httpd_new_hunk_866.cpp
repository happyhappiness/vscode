    if (i == 530) {
	ap_kill_timeout(r);
	return ap_proxyerror(r, "Not logged in");
    }
    if (i != 230 && i != 331) {
	ap_kill_timeout(r);
	return HTTP_BAD_GATEWAY;
    }

    if (i == 331) {		/* send password */
	if (password == NULL)
	    return HTTP_FORBIDDEN;
	ap_bputs("PASS ", f);
	ap_bwrite(f, password, passlen);
	ap_bputs(CRLF, f);
	ap_bflush(f);
	Explain1("FTP: PASS %s", password);
/* possible results 202, 230, 332, 421, 500, 501, 503, 530 */
