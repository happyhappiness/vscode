                                                sizeof(ctx->server_portstr))) != OK) {
        goto cleanup;
    }
    
    /* If we are not already hosting an engine, try to push the request 
     * to an already existing engine or host a new engine here. */
    if (!ctx->engine) {
        ctx = push_request_somewhere(ctx);
        if (ctx->r_status == SUSPENDED) {
            /* request was pushed to another engine */
            goto cleanup;
        }
    }
    
    /* Step Two: Make the Connection (or check that an already existing
     * socket is still usable). On success, we have a socket connected to
     * backend->hostname. */
    if (ap_proxy_connect_backend(ctx->proxy_func, ctx->p_conn, ctx->worker, 
                                 ctx->server)) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, ctx->owner, APLOGNO(03352)
                      "H2: failed to make connection to backend: %s",
                      ctx->p_conn->hostname);
        goto cleanup;
    }
    
    /* Step Three: Create conn_rec for the socket we have open now. */
    if (!ctx->p_conn->connection) {
        if ((status = ap_proxy_connection_create(ctx->proxy_func, ctx->p_conn,
                                                 ctx->owner, 
                                                 ctx->server)) != OK) {
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, ctx->owner, APLOGNO(03353)
                          "setup new connection: is_ssl=%d %s %s %s", 
                          ctx->p_conn->is_ssl, ctx->p_conn->ssl_hostname, 
                          locurl, ctx->p_conn->hostname);
            goto cleanup;
        }
        
        if (!ctx->p_conn->data) {
            /* New conection: set a note on the connection what CN is
             * requested and what protocol we want */
            if (ctx->p_conn->ssl_hostname) {
                apr_table_setn(ctx->p_conn->connection->notes,
                               "proxy-request-hostname", ctx->p_conn->ssl_hostname);
            }
            if (ctx->is_ssl) {
                apr_table_setn(ctx->p_conn->connection->notes,
                               "proxy-request-alpn-protos", "h2");
