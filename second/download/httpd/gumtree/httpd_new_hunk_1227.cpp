    if (i != DECLINED) {

	ap_pclosesocket(p, dsock);

	ap_bclose(f);

	return i;

    }



    if (!pasvmode) {		/* wait for connection */

	ap_hard_timeout("proxy ftp data connect", r);

	clen = sizeof(struct sockaddr_in);

	do

	    csd = accept(dsock, (struct sockaddr *) &server, &clen);

	while (csd == -1 && errno == EINTR);

	if (csd == -1) {

	    ap_log_rerror(APLOG_MARK, APLOG_ERR, r,

			 "proxy: failed to accept data connection");

	    ap_pclosesocket(p, dsock);

	    ap_bclose(f);

	    ap_kill_timeout(r);

	    if (c != NULL)

		c = ap_proxy_cache_error(c);

	    return HTTP_BAD_GATEWAY;

	}

	ap_note_cleanups_for_socket(p, csd);

	data = ap_bcreate(p, B_RDWR | B_SOCKET);

	ap_bpushfd(data, csd, -1);

	ap_kill_timeout(r);

