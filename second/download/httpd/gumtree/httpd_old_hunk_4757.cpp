    conn_rec *origin = NULL;
    proxy_conn_rec *backend = NULL;
    const char *scheme = "AJP";
    int retry;
    proxy_dir_conf *dconf = ap_get_module_config(r->per_dir_config,
                                                 &proxy_module);

    /*
     * Note: Memory pool allocation.
     * A downstream keepalive connection is always connected to the existence
     * (or not) of an upstream keepalive connection. If this is not done then
     * load balancing against multiple backend servers breaks (one backend
     * server ends up taking 100% of the load), and the risk is run of
     * downstream keepalive connections being kept open unnecessarily. This
     * keeps webservers busy and ties up resources.
     *
     * As a result, we allocate all sockets out of the upstream connection
     * pool, and when we want to reuse a socket, we check first whether the
     * connection ID of the current upstream connection is the same as that
     * of the connection when the socket was opened.
     */
    apr_pool_t *p = r->connection->pool;
    apr_uri_t *uri = apr_palloc(r->connection->pool, sizeof(*uri));


    if (strncasecmp(url, "ajp:", 4) != 0) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00894) "declining URL %s", url);
        return DECLINED;
    }
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00895) "serving URL %s", url);

    /* create space for state information */
    status = ap_proxy_acquire_connection(scheme, &backend, worker,
                                         r->server);
    if (status != OK) {
