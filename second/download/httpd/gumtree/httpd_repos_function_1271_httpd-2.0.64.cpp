static
apr_status_t ap_proxy_http_create_connection(apr_pool_t *p, request_rec *r,
                                             proxy_http_conn_t *p_conn,
                                             conn_rec *c, conn_rec **origin,
                                             proxy_conn_rec *backend,
                                             proxy_server_conf *conf,
                                             const char *proxyname) {
    int failed=0, new=0;
    apr_socket_t *client_socket = NULL;

    /* We have determined who to connect to. Now make the connection, supporting
     * a KeepAlive connection.
     */

    /* get all the possible IP addresses for the destname and loop through them
     * until we get a successful connection
     */

    /* if a keepalive socket is already open, check whether it must stay
     * open, or whether it should be closed and a new socket created.
     */
    /* see memory note above */
    if (backend->connection) {
        client_socket = ap_get_module_config(backend->connection->conn_config, &core_module);
        if ((backend->connection->id == c->id) &&
            (backend->port == p_conn->port) &&
            (backend->hostname) &&
            (!apr_strnatcasecmp(backend->hostname, p_conn->name))) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "proxy: keepalive address match (keep original socket)");
        } else {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "proxy: keepalive address mismatch / connection has"
                         " changed (close old socket (%s/%s, %d/%d))", 
                         p_conn->name, backend->hostname, p_conn->port,
                         backend->port);
            apr_socket_close(client_socket);
            backend->connection = NULL;
        }
    }

    /* get a socket - either a keepalive one, or a new one */
    new = 1;
    if ((backend->connection) && (backend->connection->id == c->id)) {
        apr_size_t buffer_len = 1;
        char test_buffer[1]; 
        apr_status_t socket_status;
        apr_interval_time_t current_timeout;

        /* use previous keepalive socket */
        *origin = backend->connection;
        p_conn->sock = client_socket;
        new = 0;

        /* save timeout */
        apr_socket_timeout_get(p_conn->sock, &current_timeout);
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
        int rc;

        /* create a new socket */
        backend->connection = NULL;

        /*
         * At this point we have a list of one or more IP addresses of
         * the machine to connect to. If configured, reorder this
         * list so that the "best candidate" is first try. "best
         * candidate" could mean the least loaded server, the fastest
         * responding server, whatever.
         *
         * For now we do nothing, ie we get DNS round robin.
         * XXX FIXME
         */
        failed = ap_proxy_connect_to_backend(&p_conn->sock, "HTTP",
                                             p_conn->addr, p_conn->name,
                                             conf, r->server, c->pool);

        /* handle a permanent error on the connect */
        if (failed) {
            if (proxyname) {
                return DECLINED;
            } else {
                return HTTP_BAD_GATEWAY;
            }
        }

        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: socket is connected");

        /* the socket is now open, create a new backend server connection */
        *origin = ap_run_create_connection(c->pool, r->serve