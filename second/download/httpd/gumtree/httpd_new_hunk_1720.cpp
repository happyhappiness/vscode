	    parms[0] = '\0';

    }



/* try to set up PASV data connection first */

    dsock = ap_psocket(p, PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (dsock == -1) {

	ap_log_rerror(APLOG_MARK, APLOG_ERR, r,

		     "proxy: error creating PASV socket");

	ap_bclose(f);

	ap_kill_timeout(r);

	return HTTP_INTERNAL_SERVER_ERROR;

    }



    if (conf->recv_buffer_size) {

	if (setsockopt(dsock, SOL_SOCKET, SO_RCVBUF,

	       (const char *) &conf->recv_buffer_size, sizeof(int)) == -1) {

	    ap_log_rerror(APLOG_MARK, APLOG_ERR, r,

			 "setsockopt(SO_RCVBUF): Failed to set ProxyReceiveBufferSize, using default");

	}

    }



    ap_bputs("PASV" CRLF, f);

    ap_bflush(f);

    Explain0("FTP: PASV command issued");

/* possible results: 227, 421, 500, 501, 502, 530 */

    /* 227 Entering Passive Mode (h1,h2,h3,h4,p1,p2). */

    /* 421 Service not available, closing control connection. */

    /* 500 Syntax error, command unrecognized. */

    /* 501 Syntax error in parameters or arguments. */

    /* 502 Command not implemented. */

    /* 530 Not logged in. */

    i = ap_bgets(pasv, sizeof(pasv), f);

    if (i == -1) {

	ap_log_rerror(APLOG_MARK, APLOG_ERR|APLOG_NOERRNO, r,

		     "PASV: control connection is toast");

	ap_pclosesocket(p, dsock);

	ap_bclose(f);

	ap_kill_timeout(r);

	return HTTP_INTERNAL_SERVER_ERROR;

    }

