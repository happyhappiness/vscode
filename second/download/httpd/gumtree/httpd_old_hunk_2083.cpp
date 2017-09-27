            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                         "apr_socket_opt_set(SO_RCVBUF): Failed to set "
                         "ProxyReceiveBufferSize, using default");
        }
#endif

        /* Set a timeout on the socket */
        if (worker->timeout_set == 1) {
            apr_socket_timeout_set(newsock, worker->timeout);
        }
        else {
             apr_socket_timeout_set(newsock, s->timeout);
        }
        /* Set a keepalive option */
        if (worker->keepalive) {
            if ((rv = apr_socket_opt_set(newsock,
