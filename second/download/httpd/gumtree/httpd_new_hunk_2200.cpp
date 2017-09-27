                                              conn_rec *c,
                                              server_rec *s)
{
    apr_sockaddr_t *backend_addr = conn->addr;
    int rc;
    apr_interval_time_t current_timeout;
    apr_bucket_alloc_t *bucket_alloc;

    if (conn->connection) {
        return OK;
    }

    /*
     * We need to flush the buckets before we return the connection to the
     * connection pool. See comment in connection_cleanup for why this is
     * needed.
     */
    conn->need_flush = 1;
    bucket_alloc = apr_bucket_alloc_create(conn->scpool);
    /*
     * The socket is now open, create a new backend server connection
     */
    conn->connection = ap_run_create_connection(conn->scpool, s, conn->sock,
                                                0, NULL,
                                                bucket_alloc);

    if (!conn->connection) {
        /*
         * the peer reset the connection already; ap_run_create_connection()
         * closed the socket
         */
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
                     s, "proxy: %s: an error occurred creating a "
                     "new connection to %pI (%s)", proxy_function,
                     backend_addr, conn->hostname);
        /* XXX: Will be closed when proxy_conn is closed */
        socket_cleanup(conn);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    /* For ssl connection to backend */
    if (conn->is_ssl) {
        if (!ap_proxy_ssl_enable(conn->connection)) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                         s, "proxy: %s: failed to enable ssl support "
