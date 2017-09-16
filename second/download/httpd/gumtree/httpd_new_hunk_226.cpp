

    if (i != DECLINED) {

	ap_pclosesocket(p, dsock);

	ap_bclose(f);

	return i;

    }



    cache = c->fp;



    c->hdrs = resp_hdrs;



    if (!pasvmode) {		/* wait for connection */

	ap_hard_timeout("proxy ftp data connect", r);

	clen = sizeof(struct sockaddr_in);

	do

	    csd = accept(dsock, (struct sockaddr *) &server, &clen);

	while (csd == -1 && errno == EINTR);

