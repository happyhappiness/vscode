	if (err != NULL)

	    return ap_proxyerror(r, err);	/* give up */

    }



    sock = ap_psocket(p, PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sock == -1) {

	ap_log_error(APLOG_MARK, APLOG_ERR, r->server,

		    "proxy: error creating socket");

	return HTTP_INTERNAL_SERVER_ERROR;

    }



    if (conf->recv_buffer_size) {

	if (setsockopt(sock, SOL_SOCKET, SO_RCVBUF,

		       (const char *) &conf->recv_buffer_size, sizeof(int))

	    == -1) {

	    ap_log_error(APLOG_MARK, APLOG_ERR, r->server,

			 "setsockopt(SO_RCVBUF): Failed to set ProxyReceiveBufferSize, using default");

	}

    }



#ifdef SINIX_D_RESOLVER_BUG

    {

