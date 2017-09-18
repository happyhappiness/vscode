    if (APR_SUCCESS != err) {
        return ap_proxyerror(r, HTTP_BAD_GATEWAY, apr_pstrcat(p,
                                                 "DNS lookup failure for: ",
                                                        connectname, NULL));
    }


    if ((rv = apr_socket_create(&sock, APR_INET, SOCK_STREAM, r->pool)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "proxy: FTP: error creating socket");
        return HTTP_INTERNAL_SERVER_ERROR;
    }

#if !defined(TPF) && !defined(BEOS)
    if (conf->recv_buffer_size > 0
        && (rv = apr_setsocketopt(sock, APR_SO_RCVBUF,
                                  conf->recv_buffer_size))) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "setsockopt(SO_RCVBUF): Failed to set ProxyReceiveBufferSize, using default");
    }
#endif

    if (APR_SUCCESS != (rv = apr_setsocketopt(sock, APR_SO_REUSEADDR, one))) {
#ifndef _OSD_POSIX              /* BS2000 has this option "always on" */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "proxy: FTP: error setting reuseaddr option: setsockopt(SO_REUSEADDR)");
        return HTTP_INTERNAL_SERVER_ERROR;
#endif                          /* _OSD_POSIX */
    }

    /* Set a timeout on the socket */
    if (conf->timeout_set == 1) {
        apr_setsocketopt(sock, APR_SO_TIMEOUT, (int)conf->timeout);
    }
    else {
        apr_setsocketopt(sock, 
                         APR_SO_TIMEOUT, (int)r->server->timeout);
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "proxy: FTP: socket has been created");


    /*
     * At this point we have a list of one or more IP addresses of the
     * machine to connect to. If configured, reorder this list so that the
     * "best candidate" is first try. "best candidate" could mean the least
     * loaded server, the fastest responding server, whatever.
     *
