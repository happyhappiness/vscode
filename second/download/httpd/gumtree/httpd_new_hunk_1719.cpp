             */
            backend_addr = backend_addr->next;
            continue;
        }
        conn->connection = NULL;

        if (worker->recv_buffer_size > 0 &&
            (rv = apr_socket_opt_set(newsock, APR_SO_RCVBUF,
                                     worker->recv_buffer_size))) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                         "apr_socket_opt_set(SO_RCVBUF): Failed to set "
                         "ProxyReceiveBufferSize, using default");
        }

        rv = apr_socket_opt_set(newsock, APR_TCP_NODELAY, 1);
        if (rv != APR_SUCCESS && rv != APR_ENOTIMPL) {
             ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                          "apr_socket_opt_set(APR_TCP_NODELAY): "
                          "Failed to set");
