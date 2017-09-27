    return APR_SUCCESS;
#else
    return APR_ENOTIMPL;
#endif
}

PROXY_DECLARE(apr_status_t) ap_proxy_check_connection(const char *scheme,
                                                      proxy_conn_rec *conn,
                                                      server_rec *server,
                                                      unsigned max_blank_lines,
                                                      int flags)
{
    apr_status_t rv = APR_SUCCESS;
    proxy_worker *worker = conn->worker;

    if (!PROXY_WORKER_IS_USABLE(worker)) {
        /*
         * The worker is in error likely done by a different thread / process
         * e.g. for a timeout or bad status. We should respect this and should
         * not continue with a connection via this worker even if we got one.
         */
        rv = APR_EINVAL;
    }
    else if (conn->connection) {
        /* We have a conn_rec, check the full filter stack for things like
         * SSL alert/shutdown, filters aside data...
         */
        rv = ap_check_pipeline(conn->connection, conn->tmp_bb,
                               max_blank_lines);
        apr_brigade_cleanup(conn->tmp_bb);
        if (rv == APR_SUCCESS) {
            /* Some data available, the caller might not want them. */
            if (flags & PROXY_CHECK_CONN_EMPTY) {
                rv = APR_ENOTEMPTY;
            }
        }
        else if (APR_STATUS_IS_EAGAIN(rv)) {
            /* Filter chain is OK and empty, yet we can't determine from
             * ap_check_pipeline (actually ap_core_input_filter) whether
             * an empty non-blocking read is EAGAIN or EOF on the socket
             * side (it's always SUCCESS), so check it explicitely here.
             */
            if (ap_proxy_is_socket_connected(conn->sock)) {
                rv = APR_SUCCESS;
            }
            else {
                rv = APR_EPIPE;
            }
        }
    }
    else if (conn->sock) {
        /* For modules working with sockets directly, check it. */
        if (!ap_proxy_is_socket_connected(conn->sock)) {
            rv = APR_EPIPE;
        }
    }
    else {
        rv = APR_ENOSOCKET;
    }

    if (rv == APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, server,
                     "%s: reusing backend connection %pI<>%pI",
                     scheme, conn->connection->local_addr,
                     conn->connection->client_addr);
    }
    else if (conn->sock) {
        /* This clears conn->scpool (and associated data), so backup and
         * restore any ssl_hostname for this connection set earlier by
         * ap_proxy_determine_connection().
         */
        char ssl_hostname[PROXY_WORKER_RFC1035_NAME_SIZE];
        if (rv == APR_EINVAL
                || !conn->ssl_hostname
                || PROXY_STRNCPY(ssl_hostname, conn->ssl_hostname)) {
            ssl_hostname[0] = '\0';
        }

        socket_cleanup(conn);
        if (rv != APR_ENOTEMPTY) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, server, APLOGNO(00951)
                         "%s: backend socket is disconnected.", scheme);
        }
        else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, server, APLOGNO(03408)
                         "%s: reusable backend connection is not empty: "
                         "forcibly closed", scheme);
        }

        if (ssl_hostname[0]) {
            conn->ssl_hostname = apr_pstrdup(conn->scpool, ssl_hostname);
        }
    }

    return rv;
}

PROXY_DECLARE(int) ap_proxy_connect_backend(const char *proxy_function,
                                            proxy_conn_rec *conn,
                                            proxy_worker *worker,
                                            server_rec *s)
{
    apr_status_t rv;
    int loglevel;
    apr_sockaddr_t *backend_addr = conn->addr;
    /* the local address to use for the outgoing connection */
    apr_sockaddr_t *local_addr;
    apr_socket_t *newsock;
    void *sconf = s->module_config;
    proxy_server_conf *conf =
        (proxy_server_conf *) ap_get_module_config(sconf, &proxy_module);

    rv = ap_proxy_check_connection(proxy_function, conn, s, 0, 0);
    if (rv == APR_EINVAL) {
        return DECLINED;
    }

    while (rv != APR_SUCCESS && (backend_addr || conn->uds_path)) {
#if APR_HAVE_SYS_UN_H
        if (conn->uds_path)
        {
            rv = apr_socket_create(&newsock, AF_UNIX, SOCK_STREAM, 0,
                                   conn->scpool);
            if (rv != APR_SUCCESS) {
