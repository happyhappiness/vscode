	clen = sizeof(struct sockaddr_in);
	if (getsockname(sock, (struct sockaddr *) &server, &clen) < 0) {
	    ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
			 "proxy: error getting socket address");
	    ap_bclose(f);
	    ap_kill_timeout(r);
	    return HTTP_INTERNAL_SERVER_ERROR;
	}

	dsock = ap_psocket(p, PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (dsock == -1) {
	    ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
			 "proxy: error creating socket");
	    ap_bclose(f);
	    ap_kill_timeout(r);
	    return HTTP_INTERNAL_SERVER_ERROR;
	}

	if (setsockopt(dsock, SOL_SOCKET, SO_REUSEADDR, (void *) &one,
		       sizeof(one)) == -1) {
#ifndef _OSD_POSIX /* BS2000 has this option "always on" */
	    ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
			 "proxy: error setting reuseaddr option");
	    ap_pclosesocket(p, dsock);
	    ap_bclose(f);
	    ap_kill_timeout(r);
	    return HTTP_INTERNAL_SERVER_ERROR;
#endif /*_OSD_POSIX*/
	}

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
