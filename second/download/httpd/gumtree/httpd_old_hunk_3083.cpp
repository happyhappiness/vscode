                                         NULL));
    }
    if (!uri->port) {
        uri->port = apr_uri_port_of_scheme(uri->scheme);
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "proxy: connecting %s to %s:%d", *url, uri->hostname,
                 uri->port);

    /*
     * allocate these out of the specified connection pool
     * The scheme handler decides if this is permanent or
     * short living pool.
     */
