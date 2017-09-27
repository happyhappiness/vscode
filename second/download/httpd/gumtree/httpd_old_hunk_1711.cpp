
PROXY_DECLARE(int) ap_proxy_post_request(proxy_worker *worker,
                                         proxy_balancer *balancer,
                                         request_rec *r,
                                         proxy_server_conf *conf)
{
    int access_status;
    if (balancer) {
        access_status = proxy_run_post_request(worker, balancer, r, conf);
    }
    else {
        access_status = OK;
    }

    return access_status;
}

/* DEPRECATED */
PROXY_DECLARE(int) ap_proxy_connect_to_backend(apr_socket_t **newsock,
                                               const char *proxy_function,
                                               apr_sockaddr_t *backend_addr,
                                               const char *backend_name,
                                               proxy_server_conf *conf,
                                               server_rec *s,
                                               apr_pool_t *p)
{
    apr_status_t rv;
    int connected = 0;
    int loglevel;

    while (backend_addr && !connected) {
        if ((rv = apr_socket_create(newsock, backend_addr->family,
                                    SOCK_STREAM, 0, p)) != APR_SUCCESS) {
            loglevel = backend_addr->next ? APLOG_DEBUG : APLOG_ERR;
            ap_log_error(APLOG_MARK, loglevel, rv, s,
                         "proxy: %s: error creating fam %d socket for target %s",
                         proxy_function,
                         backend_addr->family,
                         backend_name);
            /*
             * this could be an IPv6 address from the DNS but the
             * local machine won't give us an IPv6 socket; hopefully the
             * DNS returned an additional address to try
             */
            backend_addr = backend_addr->next;
            continue;
        }

#if !defined(TPF) && !defined(BEOS)
        if (conf->recv_buffer_size > 0 &&
            (rv = apr_socket_opt_set(*newsock, APR_SO_RCVBUF,
                                     conf->recv_buffer_size))) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                         "apr_socket_opt_set(SO_RCVBUF): Failed to set "
                         "ProxyReceiveBufferSize, using default");
        }
#endif

        rv = apr_socket_opt_set(*newsock, APR_TCP_NODELAY, 1);
        if (rv != APR_SUCCESS && rv != APR_ENOTIMPL) {
             ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                          "apr_socket_opt_set(APR_TCP_NODELAY): "
                          "Failed to set");
        }

        /* Set a timeout on the socket */
        if (conf->timeout_set == 1) {
            apr_socket_timeout_set(*newsock, conf->timeout);
        }
        else {
             apr_socket_timeout_set(*newsock, s->timeout);
        }

        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "proxy: %s: fam %d socket created to connect to %s",
                     proxy_function, backend_addr->family, backend_name);

        /* make the connection out of the socket */
        rv = apr_socket_connect(*newsock, backend_addr);

        /* if an error occurred, loop round and try again */
        if (rv != APR_SUCCESS) {
            apr_socket_close(*newsock);
            loglevel = backend_addr->next ? APLOG_DEBUG : APLOG_ERR;
            ap_log_error(APLOG_MARK, loglevel, rv, s,
                         "proxy: %s: attempt to connect to %pI (%s) failed",
                         proxy_function,
                         backend_addr,
                         backend_name);
            backend_addr = backend_addr->next;
            continue;
        }
        connected = 1;
    }
    return connected ? 0 : 1;
}

PROXY_DECLARE(int) ap_proxy_connection_reusable(proxy_conn_rec *conn)
{
    proxy_worker *worker = conn->worker;

    return ! (conn->close || conn->close_on_recycle
              || !worker->is_address_reusable || worker->disablereuse);
}

static apr_status_t connection_cleanup(void *theconn)
{
    proxy_conn_rec *conn = (proxy_conn_rec *)theconn;
    proxy_worker *worker = conn->worker;

    /*
