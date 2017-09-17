		    return HTTP_BAD_GATEWAY;
		}
		path = "";
		len = 0;
	    }
	    else if (i == 213) { /* Size command ok */
		for (j = 0; j < sizeof resp && ap_isdigit(resp[j]); j++)
			;
		resp[j] = '\0';
		if (resp[0] != '\0')
		    size = ap_pstrdup(p, resp);
	    }
	}
    }

#ifdef AUTODETECT_PWD
    ap_bvputs(f, "PWD", CRLF, NULL);
    ap_bflush(f);
    Explain0("FTP: PWD");
/* responses: 257, 500, 501, 502, 421, 550 */
    /* 257 "<directory-name>" <commentary> */
    /* 421 Service not available, closing control connection. */
    /* 500 Syntax error, command unrecognized. */
    /* 501 Syntax error in parameters or arguments. */
    /* 502 Command not implemented. */
    /* 550 Requested action not taken. */
    i = ftp_getrc_msg(f, resp, sizeof resp);
    Explain1("FTP: PWD returned status %d", i);
    if (i == -1 || i == 421) {
	ap_kill_timeout(r);
	return ap_proxyerror(r, /*HTTP_BAD_GATEWAY*/ "Error reading from remote server");
    }
    if (i == 550) {
	ap_kill_timeout(r);
	return HTTP_NOT_FOUND;
    }
    if (i == 257) {
	const char *dirp = resp;
	cwd = ap_getword_conf(r->pool, &dirp);
    }
#endif /*AUTODETECT_PWD*/

    if (parms[0] == 'd') {
	if (len != 0)
	    ap_bvputs(f, "LIST ", path, CRLF, NULL);
	else
	    ap_bputs("LIST -lag" CRLF, f);
	Explain1("FTP: LIST %s", (len == 0 ? "" : path));
    }
    else {
	ap_bvputs(f, "RETR ", path, CRLF, NULL);
	Explain1("FTP: RETR %s", path);
    }
    ap_bflush(f);
/* RETR: 110, 125, 150, 226, 250, 421, 425, 426, 450, 451, 500, 501, 530, 550
   NLST: 125, 150, 226, 250, 421, 425, 426, 450, 451, 500, 501, 502, 530 */
    /* 110 Restart marker reply. */
    /* 125 Data connection already open; transfer starting. */
    /* 150 File status okay; about to open data connection. */
    /* 226 Closing data connection. */
    /* 250 Requested file action okay, completed. */
    /* 421 Service not available, closing control connection. */
    /* 425 Can't open data connection. */
    /* 426 Connection closed; transfer aborted. */
    /* 450 Requested file action not taken. */
    /* 451 Requested action aborted. Local error in processing. */
    /* 500 Syntax error, command unrecognized. */
    /* 501 Syntax error in parameters or arguments. */
    /* 530 Not logged in. */
    /* 550 Requested action not taken. */
    rc = ftp_getrc(f);
    Explain1("FTP: returned status %d", rc);
    if (rc == -1) {
	ap_kill_timeout(r);
	return ap_proxyerror(r, /*HTTP_BAD_GATEWAY*/ "Error reading from remote server");
    }
    if (rc == 550) {
	Explain0("FTP: RETR failed, trying LIST instead");
	parms = "d";
	ap_bvputs(f, "CWD ", path, CRLF, NULL);
	ap_bflush(f);
	Explain1("FTP: CWD %s", path);
	/* possible results: 250, 421, 500, 501, 502, 530, 550 */
	/* 250 Requested file action okay, completed. */
	/* 421 Service not available, closing control connection. */
	/* 500 Syntax error, command unrecognized. */
	/* 501 Syntax error in parameters or arguments. */
	/* 502 Command not implemented. */
	/* 530 Not logged in. */
	/* 550 Requested action not taken. */
	rc = ftp_getrc(f);
	Explain1("FTP: returned status %d", rc);
	if (rc == -1) {
	    ap_kill_timeout(r);
	    return ap_proxyerror(r, /*HTTP_BAD_GATEWAY*/ "Error reading from remote server");
	}
	if (rc == 550) {
	    ap_kill_timeout(r);
	    return HTTP_NOT_FOUND;
	}
	if (rc != 250) {
	    ap_kill_timeout(r);
	    return HTTP_BAD_GATEWAY;
	}

#ifdef AUTODETECT_PWD
	ap_bvputs(f, "PWD", CRLF, NULL);
	ap_bflush(f);
	Explain0("FTP: PWD");
/* responses: 257, 500, 501, 502, 421, 550 */
	/* 257 "<directory-name>" <commentary> */
	/* 421 Service not available, closing control connection. */
	/* 500 Syntax error, command unrecognized. */
	/* 501 Syntax error in parameters or arguments. */
	/* 502 Command not implemented. */
	/* 550 Requested action not taken. */
	i = ftp_getrc_msg(f, resp, sizeof resp);
	Explain1("FTP: PWD returned status %d", i);
	if (i == -1 || i == 421) {
	    ap_kill_timeout(r);
	    return ap_proxyerror(r, /*HTTP_BAD_GATEWAY*/ "Error reading from remote server");
	}
	if (i == 550) {
	    ap_kill_timeout(r);
	    return HTTP_NOT_FOUND;
	}
	if (i == 257) {
	    const char *dirp = resp;
	    cwd = ap_getword_conf(r->pool, &dirp);
	}
#endif /*AUTODETECT_PWD*/

	ap_bputs("LIST -lag" CRLF, f);
	ap_bflush(f);
	Explain0("FTP: LIST -lag");
	rc = ftp_getrc(f);
	Explain1("FTP: returned status %d", rc);
	if (rc == -1)
	    return ap_proxyerror(r, /*HTTP_BAD_GATEWAY*/ "Error reading from remote server");
    }
    ap_kill_timeout(r);
    if (rc != 125 && rc != 150 && rc != 226 && rc != 250)
	return HTTP_BAD_GATEWAY;

    r->status = HTTP_OK;
    r->status_line = "200 OK";

    resp_hdrs = ap_make_table(p, 2);
    c->hdrs = resp_hdrs;

    if (parms[0] == 'd')
	ap_table_set(resp_hdrs, "Content-Type", "text/html");
    else {
	if (r->content_type != NULL) {
	    ap_table_set(resp_hdrs, "Content-Type", r->content_type);
	    Explain1("FTP: Content-Type set to %s", r->content_type);
	}
	else {
	    ap_table_set(resp_hdrs, "Content-Type", "text/plain");
	}
	if (parms[0] != 'a' && size != NULL) {
	    /* We "trust" the ftp server to really serve (size) bytes... */
	    ap_table_set(resp_hdrs, "Content-Length", size);
	    Explain1("FTP: Content-Length set to %s", size);
	}
    }

/* check if NoCache directive on this host */
    for (i = 0; i < conf->nocaches->nelts; i++) {
