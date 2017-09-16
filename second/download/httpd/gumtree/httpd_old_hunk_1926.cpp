/* shouldn't we implement telnet control options here? */



#ifdef CHARSET_EBCDIC

    ap_bsetflag(f, B_ASCII2EBCDIC|B_EBCDIC2ASCII, 1);

#endif /*CHARSET_EBCDIC*/



/* possible results: 120, 220, 421 */

    ap_hard_timeout("proxy ftp", r);

    i = ftp_getrc(f);

    Explain1("FTP: returned status %d", i);

    if (i == -1) {

	ap_kill_timeout(r);

	return ap_proxyerror(r, "Error reading from remote server");

    }

    if (i != 220) {

	ap_kill_timeout(r);

	return HTTP_BAD_GATEWAY;

    }



    Explain0("FTP: connected.");



    ap_bputs("USER ", f);

    ap_bwrite(f, user, userlen);

    ap_bputs(CRLF, f);

    ap_bflush(f);			/* capture any errors */

    Explain1("FTP: USER %s", user);



/* possible results; 230, 331, 332, 421, 500, 501, 530 */

/* states: 1 - error, 2 - success; 3 - send password, 4,5 fail */

    i = ftp_getrc(f);

    Explain1("FTP: returned status %d", i);

    if (i == -1) {

	ap_kill_timeout(r);

	return ap_proxyerror(r, "Error sending to remote server");

    }

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

	i = ftp_getrc(f);

	Explain1("FTP: returned status %d", i);

	if (i == -1) {

	    ap_kill_timeout(r);

	    return ap_proxyerror(r, "Error sending to remote server");

	}

	if (i == 332) {

	    ap_kill_timeout(r);

	    return ap_proxyerror(r, "Need account for login");

	}

	if (i == 530) {

	    ap_kill_timeout(r);

	    return ap_proxyerror(r, "Not logged in");

	}

	if (i != 230 && i != 202) {

	    ap_kill_timeout(r);

	    return HTTP_BAD_GATEWAY;

	}

    }



/* set the directory */

/* this is what we must do if we don't know the OS type of the remote

 * machine

 */

    for (;;) {

	strp = strchr(path, '/');

	if (strp == NULL)

	    break;

	*strp = '\0';



	len = decodeenc(path);

	ap_bputs("CWD ", f);

	ap_bwrite(f, path, len);

	ap_bputs(CRLF, f);

	ap_bflush(f);

	Explain1("FTP: CWD %s", path);

/* responses: 250, 421, 500, 501, 502, 530, 550 */

/* 1,3 error, 2 success, 4,5 failure */

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

