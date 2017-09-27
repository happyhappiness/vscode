    }
    else {
        rv = APR_ENOSOCKET;
    }

    if (rv == APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, server,
                     "%s: reusing backend connection %pI<>%pI",
                     scheme, conn->connection->local_addr,
                     conn->connection->client_addr);
    }
    else if (conn->sock) {
        /* This clears conn->scpool (and associated data), so backup and
         * restore any ssl_hostname for this connection set earlier by
         * ap_proxy_determine_connection().
         */
