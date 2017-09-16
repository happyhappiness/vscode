	else

	    return ap_proxyerror(r, /*HTTP_BAD_GATEWAY*/ ap_pstrcat(r->pool,

				"Could not connect to remote machine: ",

				strerror(errno), NULL));

    }



    clear_connection(r->pool, r->headers_in);	/* Strip connection-based headers */



    f = ap_bcreate(p, B_RDWR | B_SOCKET);

    ap_bpushfd(f, sock, sock);



    ap_hard_timeout("proxy send", r);

    ap_bvputs(f, r->method, " ", proxyhost ? url : urlptr, " HTTP/1.0" CRLF,

