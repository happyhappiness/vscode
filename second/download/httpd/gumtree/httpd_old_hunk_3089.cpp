                                            server_rec *s)
{
    apr_status_t rv;
    int connected = 0;
    int loglevel;
    apr_sockaddr_t *backend_addr = conn->addr;
    apr_socket_t *newsock;
    void *sconf = s->module_config;
    proxy_server_conf *conf =
        (proxy_server_conf *) ap_get_module_config(sconf, &proxy_module);

    if (conn->sock) {
        if (!(connected = is_socket_connected(conn->sock))) {
            socket_cleanup(conn);
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                         "proxy: %s: backend socket is disconnected.",
                         proxy_function);
        }
    }
    while (backend_addr && !connected) {
        if ((rv = apr_socket_create(&newsock, backend_addr->family,
                                SOCK_STREAM, APR_PROTO_TCP,
                                conn->scpool)) != APR_SUCCESS) {
            loglevel = backend_addr->next ? APLOG_DEBUG : APLOG_ERR;
            ap_log_error(APLOG_MARK, loglevel, rv, s,
                         "proxy: %s: error creating fam %d socket for target %s",
                         proxy_function,
                         backend_addr->family,
                         worker->hostname);
            /*
             * this could be an IPv6 address from the DNS but the
             * local machine won't give us an IPv6 socket; hopefully the
             * DNS returned an additional address to try
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
        }

        /* Set a timeout for connecting to the backend on the socket */
        if (worker->conn_timeout_set) {
            apr_socket_timeout_set(newsock, worker->conn_timeout);
        }
        else if (worker->timeout_set == 1) {
            apr_socket_timeout_set(newsock, worker->timeout);
        }
        else if (conf->timeout_set == 1) {
            apr_socket_timeout_set(newsock, conf->timeout);
        }
        else {
             apr_socket_timeout_set(newsock, s->timeout);
        }
        /* Set a keepalive option */
        if (worker->keepalive) {
            if ((rv = apr_socket_opt_set(newsock,
                            APR_SO_KEEPALIVE, 1)) != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                             "apr_socket_opt_set(SO_KEEPALIVE): Failed to set"
                             " Keepalive");
            }
        }
        ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, s,
                     "proxy: %s: fam %d socket created to connect to %s",
                     proxy_function, backend_addr->family, worker->hostname);

        /* make the connection out of the socket */
        rv = apr_socket_connect(newsock, backend_addr);

        /* if an error occurred, loop round and try again */
        if (rv != APR_SUCCESS) {
            apr_socket_close(newsock);
            loglevel = backend_addr->next ? APLOG_DEBUG : APLOG_ERR;
            ap_log_error(APLOG_MARK, loglevel, rv, s,
                         "proxy: %s: attempt to connect to %pI (%s) failed",
                         proxy_function,
                         backend_addr,
                         worker->hostname);
            backend_addr = backend_addr->next;
            continue;
        }

        /* Set a timeout on the socket */
        if (worker->timeout_set == 1) {
            apr_socket_timeout_set(newsock, worker->timeout);
        }
        else if (conf->timeout_set == 1) {
            apr_socket_timeout_set(newsock, conf->timeout);
        }
        else {
             apr_socket_timeout_set(newsock, s->timeout);
        }

