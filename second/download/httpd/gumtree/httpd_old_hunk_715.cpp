
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "proxy: %s: fam %d socket created to connect to %s",
                     proxy_function, backend_addr->family, backend_name);

        /* make the connection out of the socket */
        rv = apr_connect(*newsock, backend_addr);

        /* if an error occurred, loop round and try again */
        if (rv != APR_SUCCESS) {
            apr_socket_close(*newsock);
            loglevel = backend_addr->next ? APLOG_DEBUG : APLOG_ERR;
            ap_log_error(APLOG_MARK, loglevel, rv, s,
