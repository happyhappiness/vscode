

	if (bind(dsock, (struct sockaddr *) &server,

		 sizeof(struct sockaddr_in)) == -1) {

	    char buff[22];



	    ap_snprintf(buff, sizeof(buff), "%s:%d", inet_ntoa(server.sin_addr), server.sin_port);

	    ap_log_error(APLOG_MARK, APLOG_ERR, r->server,

			 "proxy: error binding to ftp data socket %s", buff);

	    ap_bclose(f);

	    ap_pclosesocket(p, dsock);

	    return HTTP_INTERNAL_SERVER_ERROR;

	}

	listen(dsock, 2);	/* only need a short queue */

    }



/* set request */

    len = decodeenc(path);



    /* TM - if len == 0 then it must be a directory (you can't RETR nothing) */



    if (len == 0) {

	parms = "d";

    }

    else {

	ap_bputs("SIZE ", f);

	ap_bwrite(f, path, len);

	ap_bputs(CRLF, f);

	ap_bflush(f);

	Explain1("FTP: SIZE %s", path);

	i = ftp_getrc_msg(f, resp, resplen);

	Explain2("FTP: returned status %d with response %s", i, resp);

	if (i != 500) {		/* Size command not recognized */

	    if (i == 550) {	/* Not a regular file */

		Explain0("FTP: SIZE shows this is a directory");

		parms = "d";

		ap_bputs("CWD ", f);

		ap_bwrite(f, path, len);

		ap_bputs(CRLF, f);

		ap_bflush(f);

		Explain1("FTP: CWD %s", path);

		i = ftp_getrc(f);

		Explain1("FTP: returned status %d", i);

		if (i == -1) {

		    ap_kill_timeout(r);

		    return ap_proxyerror(r, "Error sending to remote server");

		}

		if (i == 550) {

		    ap_kill_timeout(r);

		    return HTTP_NOT_FOUND;

		}

		if (i != 250) {

