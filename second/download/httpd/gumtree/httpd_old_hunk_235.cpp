    /* we break the URL into host, port, uri */
    if (APR_SUCCESS != apr_uri_parse_hostinfo(p, url, &uri)) {
	return ap_proxyerror(r, HTTP_BAD_REQUEST,
			     apr_pstrcat(p, "URI cannot be parsed: ", url, NULL));
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r->server,
		 "proxy: CONNECT: connecting %s to %s:%d", url, uri.hostname, uri.port);

    /* do a DNS lookup for the destination host */
    err = apr_sockaddr_info_get(&uri_addr, uri.hostname, APR_UNSPEC, uri.port, 0, p);

    /* are we connecting directly, or via a proxy? */
