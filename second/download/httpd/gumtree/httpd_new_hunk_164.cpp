	return ap_proxyerror(r, err);	/* give up */



    sock = ap_psocket(r->pool, PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sock == -1) {

	ap_log_error(APLOG_MARK, APLOG_ERR, r->server,

		    "proxy: error creating socket");

	return HTTP_INTERNAL_SERVER_ERROR;

    }



#ifndef WIN32

    if (sock >= FD_SETSIZE) {

	ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_WARNING, NULL,

	    "proxy_connect_handler: filedescriptor (%u) "

	    "larger than FD_SETSIZE (%u) "

	    "found, you probably need to rebuild Apache with a "

	    "larger FD_SETSIZE", sock, FD_SETSIZE);

	ap_pclosesocket(r->pool, sock);

	return HTTP_INTERNAL_SERVER_ERROR;

    }

#endif



    j = 0;

    while (server_hp.h_addr_list[j] != NULL) {

	memcpy(&server.sin_addr, server_hp.h_addr_list[j],

++ apache_1.3.1/src/modules/proxy/proxy_ftp.c	1998-07-10 03:45:56.000000000 +0800

