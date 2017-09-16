	    parms[0] = '\0';

    }



/* try to set up PASV data connection first */

    dsock = ap_psocket(p, PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (dsock == -1) {

	ap_log_error(APLOG_MARK, APLOG_ERR, r->server,

		     "proxy: error creating PASV socket");

	ap_bclose(f);

	ap_kill_timeout(r);

	return HTTP_INTERNAL_SERVER_ERROR;

    }



    if (conf->recv_buffer_size) {

	if (setsockopt(dsock, SOL_SOCKET, SO_RCVBUF,

	       (const char *) &conf->recv_buffer_size, sizeof(int)) == -1) {

	    ap_log_error(APLOG_MARK, APLOG_ERR, r->server,

			 "setsockopt(SO_RCVBUF): Failed to set ProxyReceiveBufferSize, using default");

	}

    }



    ap_bputs("PASV" CRLF, f);

    ap_bflush(f);

    Explain0("FTP: PASV command issued");

/* possible results: 227, 421, 500, 501, 502, 530 */

    i = ap_bgets(pasv, sizeof(pasv), f);



    if (i == -1) {

	ap_log_error(APLOG_MARK, APLOG_ERR|APLOG_NOERRNO, r->server,

		     "PASV: control connection is toast");

	ap_pclosesocket(p, dsock);

	ap_bclose(f);

	ap_kill_timeout(r);

	return HTTP_INTERNAL_SERVER_ERROR;

    }

