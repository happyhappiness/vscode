
	if (bind(dsock, (struct sockaddr *) &server,
		 sizeof(struct sockaddr_in)) == -1) {
	    char buff[22];

	    ap_snprintf(buff, sizeof(buff), "%s:%d", inet_ntoa(server.sin_addr), server.sin_port);
	    ap_log_rerror(APLOG_MARK, APLOG_ERR, r,
			 "proxy: error binding to ftp data socket %s", buff);
	    ap_bclose(f);
	    ap_pclosesocket(p, dsock);
	    return HTTP_INTERNAL_SERVER_ERROR;
	}
	listen(dsock, 2);	/* only need a short queue */
    }

/* set request; "path" holds last path component */
    len = decodeenc(path);

    /* TM - if len == 0 then it must be a directory (you can't RETR nothing) */

    if (len == 0) {
	parms = "d";
    }
    else {
	ap_bvputs(f, "SIZE ", path, CRLF, NULL);
	ap_bflush(f);
	Explain1("FTP: SIZE %s", path);
	i = ftp_getrc_msg(f, resp, sizeof resp);
	Explain2("FTP: returned status %d with response %s", i, resp);
	if (i != 500) {		/* Size command not recognized */
	    if (i == 550) {	/* Not a regular file */
		Explain0("FTP: SIZE shows this is a directory");
		parms = "d";
		ap_bvputs(f, "CWD ", path, CRLF, NULL);
		ap_bflush(f);
		Explain1("FTP: CWD %s", path);
		i = ftp_getrc(f);
		/* possible results: 250, 421, 500, 501, 502, 530, 550 */
		/* 250 Requested file action okay, completed. */
		/* 421 Service not available, closing control connection. */
		/* 500 Syntax error, command unrecognized. */
		/* 501 Syntax error in parameters or arguments. */
		/* 502 Command not implemented. */
		/* 530 Not logged in. */
		/* 550 Requested action not taken. */
		Explain1("FTP: returned status %d", i);
		if (i == -1) {
		    ap_kill_timeout(r);
		    return ap_proxyerror(r, /*HTTP_BAD_GATEWAY*/ "Error reading from remote server");
		}
		if (i == 550) {
		    ap_kill_timeout(r);
		    return HTTP_NOT_FOUND;
		}
		if (i != 250) {
