	    ap_pclosesocket(p, dsock);	/* and try the regular way */

    }



    if (!pasvmode) {		/* set up data connection */

	clen = sizeof(struct sockaddr_in);

	if (getsockname(sock, (struct sockaddr *) &server, &clen) < 0) {

	    ap_log_rerror(APLOG_MARK, APLOG_ERR, r,

			 "proxy: error getting socket address");

	    ap_bclose(f);

	    ap_kill_timeout(r);

	    return HTTP_INTERNAL_SERVER_ERROR;

	}



	dsock = ap_psocket(p, PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (dsock == -1) {

	    ap_log_rerror(APLOG_MARK, APLOG_ERR, r,

			 "proxy: error creating socket");

	    ap_bclose(f);

	    ap_kill_timeout(r);

	    return HTTP_INTERNAL_SERVER_ERROR;

	}



	if (setsockopt(dsock, SOL_SOCKET, SO_REUSEADDR, (void *) &one,

		       sizeof(one)) == -1) {

#ifndef _OSD_POSIX /* BS2000 has this option "always on" */

	    ap_log_rerror(APLOG_MARK, APLOG_ERR, r,

			 "proxy: error setting reuseaddr option");

	    ap_pclosesocket(p, dsock);

	    ap_bclose(f);

	    ap_kill_timeout(r);

	    return HTTP_INTERNAL_SERVER_ERROR;

#endif /*_OSD_POSIX*/

