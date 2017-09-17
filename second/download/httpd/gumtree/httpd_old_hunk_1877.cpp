    if (i == -1) {
	ap_log_error(APLOG_MARK, APLOG_ERR|APLOG_NOERRNO, r->server,
		     "PASV: control connection is toast");
	ap_pclosesocket(p, dsock);
	ap_bclose(f);
	ap_kill_timeout(r);
	return SERVER_ERROR;
    }
    else {
	pasv[i - 1] = '\0';
	pstr = strtok(pasv, " ");	/* separate result code */
	if (pstr != NULL) {
	    presult = atoi(pstr);
