

    if (err != NULL)

	return ap_proxyerror(r, err);	/* give up */



    sock = ap_psocket(r->pool, PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sock == -1) {

	ap_log_error(APLOG_MARK, APLOG_ERR, r->server,

		    "proxy: error creating socket");

	return HTTP_INTERNAL_SERVER_ERROR;

    }



#ifndef WIN32

    if (sock >= FD_SETSIZE) {

-- apache_1.3.1/src/modules/proxy/proxy_ftp.c	1998-07-10 03:45:56.000000000 +0800

