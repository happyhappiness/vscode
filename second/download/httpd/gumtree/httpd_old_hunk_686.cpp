    /* get a socket - either a keepalive one, or a new one */
    new = 1;
    if ((backend->connection) && (backend->connection->id == c->id)) {
        apr_size_t buffer_len = 1;
        char test_buffer[1]; 
        apr_status_t socket_status;
        apr_short_interval_time_t current_timeout;

        /* use previous keepalive socket */
        *origin = backend->connection;
        p_conn->sock = client_socket;
        new = 0;

        /* save timeout */
        apr_getsocketopt(p_conn->sock, APR_SO_TIMEOUT, &current_timeout);
        /* set no timeout */
        apr_setsocketopt(p_conn->sock, APR_SO_TIMEOUT, 0);
        socket_status = apr_recv(p_conn->sock, test_buffer, &buffer_len);
        /* put back old timeout */
        apr_setsocketopt(p_conn->sock, APR_SO_TIMEOUT, current_timeout);
        if ( APR_STATUS_IS_EOF(socket_status) ) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
                         "proxy: HTTP: previous connection is closed");
            new = 1;
        }
    }
