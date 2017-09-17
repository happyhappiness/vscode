	/* TM - Added \015\012 to the end of TYPE I, otherwise it hangs the
	   connection */
	ap_bputs("TYPE I" CRLF, f);
	ap_bflush(f);
	Explain0("FTP: TYPE I");
/* responses: 200, 421, 500, 501, 504, 530 */
    /* 200 Command okay. */
    /* 421 Service not available, closing control connection. */
    /* 500 Syntax error, command unrecognized. */
    /* 501 Syntax error in parameters or arguments. */
    /* 504 Command not implemented for that parameter. */
    /* 530 Not logged in. */
	i = ftp_getrc(f);
	Explain1("FTP: returned status %d", i);
	if (i == -1) {
	    ap_kill_timeout(r);
	    return ap_proxyerror(r, /*HTTP_BAD_GATEWAY*/ "Error reading from remote server");
	}
	if (i != 200 && i != 504) {
	    ap_kill_timeout(r);
	    return HTTP_BAD_GATEWAY;
	}
/* Allow not implemented */
