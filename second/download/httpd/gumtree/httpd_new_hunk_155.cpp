/* shouldn't we implement telnet control options here? */

#ifdef CHARSET_EBCDIC
    ap_bsetflag(f, B_ASCII2EBCDIC|B_EBCDIC2ASCII, 1);
#endif /*CHARSET_EBCDIC*/

/* possible results: */
    /* 120 Service ready in nnn minutes. */
    /* 220 Service ready for new user. */
    /* 421 Service not available, closing control connection. */
    ap_hard_timeout("proxy ftp", r);
    i = ftp_getrc_msg(f, resp, sizeof resp);
    Explain1("FTP: returned status %d", i);
    if (i == -1) {
	ap_kill_timeout(r);
	return ap_proxyerror(r, /*HTTP_BAD_GATEWAY*/ "Error reading from remote server");
    }
#if 0
    if (i == 120) {
	ap_kill_timeout(r);
	/* RFC2068 states:
	 * 14.38 Retry-After
	 * 
	 *  The Retry-After response-header field can be used with a 503 (Service
	 *  Unavailable) response to indicate how long the service is expected to
	 *  be unavailable to the requesting client. The value of this field can
	 *  be either an HTTP-date or an integer number of seconds (in decimal)
	 *  after the time of the response.
	 *     Retry-After  = "Retry-After" ":" ( HTTP-date | delta-seconds )
	 */
	ap_set_header("Retry-After", ap_psprintf(p, "%u", 60*wait_mins);
	return ap_proxyerror(r, /*HTTP_SERVICE_UNAVAILABLE*/ resp);
    }
#endif
    if (i != 220) {
	ap_kill_timeout(r);
	return ap_proxyerror(r, /*HTTP_BAD_GATEWAY*/ resp);
    }

    Explain0("FTP: connected.");

    ap_bvputs(f, "USER ", user, CRLF, NULL);
    ap_bflush(f);			/* capture any errors */
    Explain1("FTP: USER %s", user);

/* possible results; 230, 331, 332, 421, 500, 501, 530 */
/* states: 1 - error, 2 - success; 3 - send password, 4,5 fail */
    /* 230 User logged in, proceed. */
    /* 331 User name okay, need password. */
    /* 332 Need account for login. */
    /* 421 Service not available, closing control connection. */
    /* 500 Syntax error, command unrecognized. */
    /*     (This may include errors such as command line too long.) */
    /* 501 Syntax error in parameters or arguments. */
    /* 530 Not logged in. */
    i = ftp_getrc(f);
    Explain1("FTP: returned status %d", i);
    if (i == -1) {
	ap_kill_timeout(r);
	return ap_proxyerror(r, /*HTTP_BAD_GATEWAY*/ "Error reading from remote server");
    }
    if (i == 530) {
	ap_kill_timeout(r);
	return ftp_unauthorized (r, 1);	/* log it: user name guessing attempt? */
    }
    if (i != 230 && i != 331) {
	ap_kill_timeout(r);
	return HTTP_BAD_GATEWAY;
    }

    if (i == 331) {		/* send password */
	if (password == NULL) {
	    return ftp_unauthorized (r, 0);
	}
	ap_bvputs(f, "PASS ", password, CRLF, NULL);
	ap_bflush(f);
	Explain1("FTP: PASS %s", password);
/* possible results 202, 230, 332, 421, 500, 501, 503, 530 */
    /* 230 User logged in, proceed. */
    /* 332 Need account for login. */
    /* 421 Service not available, closing control connection. */
    /* 500 Syntax error, command unrecognized. */
    /* 501 Syntax error in parameters or arguments. */
    /* 503 Bad sequence of commands. */
    /* 530 Not logged in. */
	i = ftp_getrc(f);
	Explain1("FTP: returned status %d", i);
	if (i == -1) {
	    ap_kill_timeout(r);
	    return ap_proxyerror(r, /*HTTP_BAD_GATEWAY*/ "Error reading from remote server");
	}
	if (i == 332) {
	    ap_kill_timeout(r);
	    return ap_proxyerror(r, /*HTTP_UNAUTHORIZED*/ "Need account for login");
	}
	/* @@@ questionable -- we might as well return a 403 Forbidden here */
	if (i == 530) {
	    ap_kill_timeout(r);
	    return ftp_unauthorized (r, 1); /* log it: passwd guessing attempt? */
	}
	if (i != 230 && i != 202) {
	    ap_kill_timeout(r);
	    return HTTP_BAD_GATEWAY;
	}
    }

/* set the directory (walk directory component by component):
 * this is what we must do if we don't know the OS type of the remote
 * machine
 */
    for (;;) {
	strp = strchr(path, '/');
	if (strp == NULL)
	    break;
	*strp = '\0';

	len = decodeenc(path);
	ap_bvputs(f, "CWD ", path, CRLF, NULL);
	ap_bflush(f);
	Explain1("FTP: CWD %s", path);
	*strp = '/';
/* responses: 250, 421, 500, 501, 502, 530, 550 */
    /* 250 Requested file action okay, completed. */
    /* 421 Service not available, closing control connection. */
    /* 500 Syntax error, command unrecognized. */
    /* 501 Syntax error in parameters or arguments. */
    /* 502 Command not implemented. */
    /* 530 Not logged in. */
    /* 550 Requested action not taken. */
	i = ftp_getrc(f);
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
