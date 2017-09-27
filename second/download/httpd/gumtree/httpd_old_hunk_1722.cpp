
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "proxy: %s: connection complete to %pI (%s)",
                 proxy_function, backend_addr, conn->hostname);

    /*
     * save the timout of the socket because core_pre_connection
     * will set it to base_server->timeout
     * (core TimeOut directive).
     */
    apr_socket_timeout_get(conn->sock, &current_timeout);
    /* set up the connection filters */
    rc = ap_run_pre_connection(conn->connection, conn->sock);
