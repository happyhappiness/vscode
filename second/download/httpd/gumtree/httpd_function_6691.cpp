static int proxy_http2_handler(request_rec *r, 
                               proxy_worker *worker,
                               proxy_server_conf *conf,
                               char *url, 
                               const char *proxyname,
                               apr_port_t proxyport)
{
    const char *proxy_func;
    char *locurl = url, *u;
    apr_size_t slen;
    int is_ssl = 0;
    apr_status_t status;
    h2_proxy_ctx *ctx;
    apr_uri_t uri;
    int reconnected = 0;
    
    /* find the scheme */
    if ((url[0] != 'h' && url[0] != 'H') || url[1] != '2') {
       return DECLINED;
    }
    u = strchr(url, ':');
    if (u == NULL || u[1] != '/' || u[2] != '/' || u[3] == '\0') {
       return DECLINED;
    }
    slen = (u - url);
    switch(slen) {
        case 2:
            proxy_func = "H2";
            is_ssl = 1;
            break;
        case 3:
            if (url[2] != 'c' && url[2] != 'C') {
                return DECLINED;
            }
            proxy_func = "H2C";
            break;
        default:
            return DECLINED;
    }
    ctx = apr_pcalloc(r->pool, sizeof(*ctx));
    ctx->owner      = r->connection;
    ctx->pool       = r->pool;
    ctx->rbase      = r;
    ctx->server     = r->server;
    ctx->proxy_func = proxy_func;
    ctx->is_ssl     = is_ssl;
    ctx->worker     = worker;
    ctx->conf       = conf;
    ctx->flushall   = apr_table_get(r->subprocess_env, "proxy-flushall")? 1 : 0;
    ctx->r_status   = HTTP_SERVICE_UNAVAILABLE;
    ctx->next       = r;
    r = NULL;
    ap_set_module_config(ctx->owner->conn_config, &proxy_http2_module, ctx);

    /* scheme says, this is for us. */
    apr_table_setn(ctx->rbase->notes, H2_PROXY_REQ_URL_NOTE, url);
    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, ctx->rbase, 
                  "H2: serving URL %s", url);
    
run_connect:    
    /* Get a proxy_conn_rec from the worker, might be a new one, might
     * be one still open from another request, or it might fail if the
     * worker is stopped or in error. */
    if ((status = ap_proxy_acquire_connection(ctx->proxy_func, &ctx->p_conn,
                                              ctx->worker, ctx->server)) != OK) {
        goto cleanup;
    }

    ctx->p_conn->is_ssl = ctx->is_ssl;
    if (ctx->is_ssl && ctx->p_conn->connection) {
        /* If there are some metadata on the connection (e.g. TLS alert),
         * let mod_ssl detect them, and create a new connection below.
         */ 
        apr_bucket_brigade *tmp_bb;
        tmp_bb = apr_brigade_create(ctx->rbase->pool, 
                                    ctx->rbase->connection->bucket_alloc);
        status = ap_get_brigade(ctx->p_conn->connection->input_filters, tmp_bb,
                                AP_MODE_SPECULATIVE, APR_NONBLOCK_READ, 1);
        if (status != APR_SUCCESS && !APR_STATUS_IS_EAGAIN(status)) {
            ctx->p_conn->close = 1;
        }
        apr_brigade_cleanup(tmp_bb);
    }   

    /* Step One: Determine the URL to connect to (might be a proxy),
     * initialize the backend accordingly and determine the server 
     * port string we can expect in responses. */
    if ((status = ap_proxy_determine_connection(ctx->pool, ctx->rbase, conf, worker, 
                                                ctx->p_conn, &uri, &locurl, 
                                                proxyname, proxyport, 
                                                ctx->server_portstr,
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
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, ctx->owner, APLOGNO(03352)
                      "H2: failed to make connection to backend: %s",
                      ctx->p_conn->hostname);
        goto cleanup;
    }
    
    /* Step Three: Create conn_rec for the socket we have open now. */
    if (!ctx->p_conn->connection) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, ctx->owner, APLOGNO(03353)
                      "setup new connection: is_ssl=%d %s %s %s", 
                      ctx->p_conn->is_ssl, ctx->p_conn->ssl_hostname, 
                      locurl, ctx->p_conn->hostname);
        if ((status = ap_proxy_connection_create(ctx->proxy_func, ctx->p_conn,
                                                 ctx->owner, 
                                                 ctx->server)) != OK) {
            goto cleanup;
        }
        
        /*
         * On SSL connections set a note on the connection what CN is
         * requested, such that mod_ssl can check if it is requested to do
         * so.
         */
        if (ctx->p_conn->ssl_hostname) {
            apr_table_setn(ctx->p_conn->connection->notes,
                           "proxy-request-hostname", ctx->p_conn->ssl_hostname);
        }
        
        if (ctx->is_ssl) {
            apr_table_setn(ctx->p_conn->connection->notes,
                           "proxy-request-alpn-protos", "h2");
        }
    }

run_session:
    status = proxy_engine_run(ctx);
    if (status == APR_SUCCESS) {
        /* session and connection still ok */
        if (next_request(ctx, 1) == APR_SUCCESS) {
            /* more requests, run again */
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, ctx->owner, APLOGNO(03376)
                          "run_session, again");
            goto run_session;
        }
        /* done */
        ctx->engine = NULL;
    }

cleanup:
    if (!reconnected && ctx->engine && next_request(ctx, 1) == APR_SUCCESS) {
        /* Still more to do, tear down old conn and start over */
        if (ctx->p_conn) {
            ctx->p_conn->close = 1;
            /*only in trunk so far */
            /*proxy_run_detach_backend(r, ctx->p_conn);*/
            ap_proxy_release_connection(ctx->proxy_func, ctx->p_conn, ctx->server);
            ctx->p_conn = NULL;
        }
        reconnected = 1; /* we do this only once, then fail */
        goto run_connect;
    }
    
    if (ctx->p_conn) {
        if (status != APR_SUCCESS) {
            /* close socket when errors happened or session shut down (EOF) */
            ctx->p_conn->close = 1;
        }
        /*only in trunk so far */
        /*proxy_run_detach_backend(ctx->rbase, ctx->p_conn);*/
        ap_proxy_release_connection(ctx->proxy_func, ctx->p_conn, ctx->server);
        ctx->p_conn = NULL;
    }

    ap_set_module_config(ctx->owner->conn_config, &proxy_http2_module, NULL);
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, ctx->owner, 
                  APLOGNO(03377) "leaving handler");
    return ctx->r_status;
}