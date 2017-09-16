    err = ap_proxy_host2addr(host, &server_hp);

    if (err != NULL)

	return ap_proxyerror(r, err);	/* give up */



    sock = ap_psocket(p, PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sock == -1) {

	ap_log_rerror(APLOG_MARK, APLOG_ERR, r,

		     "proxy: error creating socket");

	return HTTP_INTERNAL_SERVER_ERROR;

    }



    if (conf->recv_buffer_size > 0

	&& setsockopt(sock, SOL_SOCKET, SO_RCVBUF,

		       (const char *) &conf->recv_buffer_size, sizeof(int))

	    == -1) {

	    ap_log_rerror(APLOG_MARK, APLOG_ERR, r,

			 "setsockopt(SO_RCVBUF): Failed to set ProxyReceiveBufferSize, using default");

    }



    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (void *) &one,

		   sizeof(one)) == -1) {

#ifndef _OSD_POSIX /* BS2000 has this option "always on" */

	ap_log_rerror(APLOG_MARK, APLOG_ERR, r,

		     "proxy: error setting reuseaddr option: setsockopt(SO_REUSEADDR)");

	ap_pclosesocket(p, sock);

	return HTTP_INTERNAL_SERVER_ERROR;

#endif /*_OSD_POSIX*/

    }



