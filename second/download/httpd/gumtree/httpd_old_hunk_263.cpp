        /* set no timeout */
        apr_setsocketopt(p_conn->sock, APR_SO_TIMEOUT, 0);
        socket_status = apr_recv(p_conn->sock, test_buffer, &buffer_len);
        /* put back old timeout */
        apr_setsocketopt(p_conn->sock, APR_SO_TIMEOUT, current_timeout);
        if ( APR_STATUS_IS_EOF(socket_status) ) {
            ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, NULL,
                         "proxy: HTTP: previous connection is closed");
            new = 1;
        }
    }
    if (new) {

