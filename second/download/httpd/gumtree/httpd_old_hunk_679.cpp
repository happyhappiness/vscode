
    /* try each IP address until we connect successfully */
    {
        int failed = 1;
        while (connect_addr) {

            /* FIXME: @@@: We created an APR_INET socket. Now there may be
             * IPv6 (AF_INET6) DNS addresses in the list... IMO the socket
             * should be created with the correct family in the first place.
             * (either do it in this loop, or make at least two attempts
             * with the AF_INET and AF_INET6 elements in the list)
             */
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "proxy: FTP: trying to connect to %pI (%s)...", connect_addr, connectname);

            /* make the connection out of the socket */
            rv = apr_connect(sock, connect_addr);

            /* if an error occurred, loop round and try again */
            if (rv != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
                             "proxy: FTP: attempt to connect to %pI (%s) failed", connect_addr, connectname);
                connect_addr = connect_addr->next;
                continue;
            }

