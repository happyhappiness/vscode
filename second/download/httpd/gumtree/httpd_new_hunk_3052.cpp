    int i;
    const char *te = NULL;
    int original_status = r->status;
    int proxy_status = OK;
    const char *original_status_line = r->status_line;
    const char *proxy_status_line = NULL;
    proxy_conn_rec *backend = *backend_ptr;
    conn_rec *origin = backend->connection;
    apr_interval_time_t old_timeout = 0;
    proxy_dir_conf *dconf;
    int do_100_continue;

    dconf = ap_get_module_config(r->per_dir_config, &proxy_module);

    do_100_continue = (worker->s->ping_timeout_set
                       && ap_request_has_body(r)
                       && (PROXYREQ_REVERSE == r->proxyreq)
                       && !(apr_table_get(r->subprocess_env, "force-proxy-request-1.0")));

    bb = apr_brigade_create(p, c->bucket_alloc);
    pass_bb = apr_brigade_create(p, c->bucket_alloc);

    /* Setup for 100-Continue timeout if appropriate */
    if (do_100_continue) {
        apr_socket_timeout_get(backend->sock, &old_timeout);
        if (worker->s->ping_timeout != old_timeout) {
            apr_status_t rc;
            rc = apr_socket_timeout_set(backend->sock, worker->s->ping_timeout);
            if (rc != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, rc, r, APLOGNO(01101)
                              "could not set 100-Continue timeout");
            }
        }
    }

    /* Get response from the remote server, and pass it up the
     * filter chain
     */

    backend->r = make_fake_req(origin, r);
    /* In case anyone needs to know, this is a fake request that is really a
     * response.
     */
    backend->r->proxyreq = PROXYREQ_RESPONSE;
    apr_table_setn(r->notes, "proxy-source-port", apr_psprintf(r->pool, "%hu",
                   origin->local_addr->port));
    tmp_bb = apr_brigade_create(p, c->bucket_alloc);
    do {
        apr_status_t rc;

        apr_brigade_cleanup(bb);

        rc = ap_proxygetline(tmp_bb, buffer, sizeof(buffer), backend->r, 0, &len);
        if (len == 0) {
            /* handle one potential stray CRLF */
            rc = ap_proxygetline(tmp_bb, buffer, sizeof(buffer), backend->r, 0, &len);
        }
        if (len <= 0) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rc, r, APLOGNO(01102)
                          "error reading status line from remote "
                          "server %s:%d", backend->hostname, backend->port);
            if (APR_STATUS_IS_TIMEUP(rc)) {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01103) "read timeout");
                if (do_100_continue) {
                    return ap_proxyerror(r, HTTP_SERVICE_UNAVAILABLE, "Timeout on 100-Continue");
                }
            }
            /*
             * If we are a reverse proxy request shutdown the connection
