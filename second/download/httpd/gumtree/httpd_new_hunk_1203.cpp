        /* set no timeout */
        apr_socket_timeout_set(p_conn->sock, 0);
        socket_status = apr_recv(p_conn->sock, test_buffer, &buffer_len);
        /* put back old timeout */
        apr_socket_timeout_set(p_conn->sock, current_timeout);
        if ( APR_STATUS_IS_EOF(socket_status) ) {
            ap_log_error(APLOG_MARK, APLOG_INFO, 0, NULL,
                         "proxy: previous connection is closed, creating a new connection.");
            new = 1;
        }
    }
    if (new) {

        /* create a new socket */
