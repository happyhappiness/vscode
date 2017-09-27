
PROXY_DECLARE(int) ap_proxy_post_request(proxy_worker *worker,
                                         proxy_balancer *balancer,
                                         request_rec *r,
                                         proxy_server_conf *conf)
{
    int access_status = OK;
    if (balancer) {
        access_status = proxy_run_post_request(worker, balancer, r, conf);
        if (access_status == DECLINED) {
            access_status = OK; /* no post_request handler available */
            /* TODO: recycle direct worker */
        }
    }

    return access_status;
}

/* DEPRECATED */
PROXY_DECLARE(int) ap_proxy_connect_to_backend(apr_socket_t **newsock,
                                               const char *proxy_function,
                                               apr_sockaddr_t *backend_addr,
                                               const char *backend_name,
                                               proxy_server_conf *conf,
                                               request_rec *r)
{
    apr_status_t rv;
    int connected = 0;
    int loglevel;

    while (backend_addr && !connected) {
        if ((rv = apr_socket_create(newsock, backend_addr->family,
                                    SOCK_STREAM, 0, r->pool)) != APR_SUCCESS) {
            loglevel = backend_addr->next ? APLOG_DEBUG : APLOG_ERR;
            ap_log_rerror(APLOG_MARK, loglevel, rv, r,
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

        if (conf->recv_buffer_size > 0 &&
            (rv = apr_socket_opt_set(*newsock, APR_SO_RCVBUF,
                                     conf->recv_buffer_size))) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "apr_socket_opt_set(SO_RCVBUF): Failed to set "
                          "ProxyReceiveBufferSize, using default");
        }

        rv = apr_socket_opt_set(*newsock, APR_TCP_NODELAY, 1);
        if (rv != APR_SUCCESS && rv != APR_ENOTIMPL) {
             ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                           "apr_socket_opt_set(APR_TCP_NODELAY): "
                           "Failed to set");
        }

        /* Set a timeout on the socket */
        if (conf->timeout_set == 1) {
            apr_socket_timeout_set(*newsock, conf->timeout);
        }
        else {
             apr_socket_timeout_set(*newsock, r->server->timeout);
        }

        ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                      "proxy: %s: fam %d socket created to connect to %s",
                      proxy_function, backend_addr->family, backend_name);

        /* make the connection out of the socket */
        rv = apr_socket_connect(*newsock, backend_addr);

        /* if an error occurred, loop round and try again */
        if (rv != APR_SUCCESS) {
            apr_socket_close(*newsock);
            loglevel = backend_addr->next ? APLOG_DEBUG : APLOG_ERR;
            ap_log_rerror(APLOG_MARK, loglevel, rv, r,
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

static apr_status_t connection_cleanup(void *theconn)
{
    proxy_conn_rec *conn = (proxy_conn_rec *)theconn;
    proxy_worker *worker = conn->worker;

    /*
