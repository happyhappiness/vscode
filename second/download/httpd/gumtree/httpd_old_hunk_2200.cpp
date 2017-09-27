                                              conn_rec *c,
                                              server_rec *s)
{
    apr_sockaddr_t *backend_addr = conn->addr;
    int rc;
    apr_interval_time_t current_timeout;

    /*
     * The socket is now open, create a new backend server connection
     */
    conn->connection = ap_run_create_connection(c->pool, s, conn->sock,
                                                c->id, c->sbh,
                                                c->bucket_alloc);

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
        apr_socket_close(conn->sock);
        conn->sock = NULL;
        return HTTP_INTERNAL_SERVER_ERROR;
    }
    /*
     * register the connection cleanup to client connection
     * so that the connection can be closed or reused
     */
    apr_pool_cleanup_register(c->pool, (void *)conn,
                              connection_cleanup,
                              apr_pool_cleanup_null);

    /* For ssl connection to backend */
    if (conn->is_ssl) {
        if (!ap_proxy_ssl_enable(conn->connection)) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                         s, "proxy: %s: failed to enable ssl support "
