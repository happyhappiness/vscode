                                         NULL));
    }
    if (!uri->port) {
        uri->port = apr_uri_default_port_for_scheme(uri->scheme);
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r->server,
                 "proxy: HTTP connecting %s to %s:%d", *url, uri->hostname,
                 uri->port);

    /* do a DNS lookup for the destination host */
    /* see memory note above */
    err = apr_sockaddr_info_get(&uri_addr, apr_pstrdup(c->pool, uri->hostname),
