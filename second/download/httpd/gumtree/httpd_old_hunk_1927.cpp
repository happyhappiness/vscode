	/* TM - Added \015\012 to the end of TYPE I, otherwise it hangs the

	   connection */

	ap_bputs("TYPE I" CRLF, f);

	ap_bflush(f);

	Explain0("FTP: TYPE I");

/* responses: 200, 421, 500, 501, 504, 530 */

	i = ftp_getrc(f);

	Explain1("FTP: returned status %d", i);

	if (i == -1) {

	    ap_kill_timeout(r);

	    return ap_proxyerror(r, "Error sending to remote server");

	}

	if (i != 200 && i != 504) {

	    ap_kill_timeout(r);

	    return HTTP_BAD_GATEWAY;

	}

/* Allow not implemented */

