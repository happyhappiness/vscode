static int proxy_http_handler(request_rec *r, proxy_worker *worker,
                              proxy_server_conf *conf,
                              char *url, const char *proxyname,
                              apr_port_t proxyport)
{
    int status;
    char server_portstr[32];
    char *scheme;
    const char *proxy_function;
    const char *u;
    proxy_conn_rec *backend = NULL;
    int is_ssl = 0;
    conn_rec *c = r->connection;
    int retry = 0;
    /*
     * Use a shorter-lived pool to reduce memory usage
     * and avoid a memory leak
     */
    apr_pool_t *p = r->pool;
    apr_uri_t *uri = apr_palloc(p, sizeof(*uri));

    /* find the scheme */
    u = strchr(url, ':');
    if (u == NULL || u[1] != '/' || u[2] != '/' || u[3] == '\0')
       return DECLINED;
    if ((u - url) > 14)
        return HTTP_BAD_REQUEST;
    scheme = apr_pstrndup(p, url, u - url);
    /* scheme is lowercase */
    ap_str_tolower(scheme);
    /* is it for us? */
    if (strcmp(scheme, "https") == 0) {
        if (!ap_proxy_ssl_enable(NULL)) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "proxy: HTTPS: declining URL %s"
                         " (mod_ssl not configured?)", url);
            return DECLINED;
        }
        is_ssl = 1;
        proxy_function = "HTTPS";
    }
    else if (!(strcmp(scheme, "http") == 0 || (strcmp(scheme, "ftp") == 0 && proxyname))) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: HTTP: declining URL %s", url);
        return DECLINED; /* only interested in HTTP, or FTP via proxy */
    }
    else {
        if (*scheme == 'h')
            proxy_function = "HTTP";
        else
            proxy_function = "FTP";
    }
    ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, r->server,
                 "proxy: HTTP: serving URL %s", url);


    /* create space for state information */
    if ((status = ap_proxy_acquire_connection(proxy_function, &backend,
                                              worker, r->server)) != OK)
        goto cleanup;


    backend->is_ssl = is_ssl;

    if (is_ssl) {
        ap_proxy_ssl_connection_cleanup(backend, r);
    }

    /*
     * In the case that we are handling a reverse proxy connection and this
     * is not a request that is coming over an already kept alive connection
     * with the client, do NOT reuse the connection to the backend, because
     * we cannot forward a failure to the client in this case as the client
     * does NOT expect this in this situation.
     * Yes, this creates a performance penalty.
     */
    if ((r->proxyreq == PROXYREQ_REVERSE) && (!c->keepalives)
        && (apr_table_get(r->subprocess_env, "proxy-initial-not-pooled"))) {
        backend->close = 1;
    }

    while (retry < 2) {
        char *locurl = url;

        /* Step One: Determine Who To Connect To */
        if ((status = ap_proxy_determine_connection(p, r, conf, worker, backend,
                                                uri, &locurl, proxyname,
                                                proxyport, server_portstr,
                                                sizeof(server_portstr))) != OK)
            break;

        /* Step Two: Make the Connection */
        if (ap_proxy_connect_backend(proxy_function, backend, worker, r->server)) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                         "proxy: HTTP: failed to make connection to backend: %s",
                         backend->hostname);
            status = HTTP_SERVICE_UNAVAILABLE;
            break;
        }

        /* Step Three: Create conn_rec */
        if (!backend->connection) {
            if ((status = ap_proxy_connection_create(proxy_function, backend,
                                                     c, r->server)) != OK)
                break;
            /*
             * On SSL connections set a note on the connection what CN is
             * requested, such that mod_ssl can check if it is requested to do
             * so.
             */
            if (is_ssl) {
                apr_table_set(backend->connection->notes, "proxy-request-hostname",
                              uri->hostname);
            }
        }

        /* Step Four: Send the Request
         * On the off-chance that we forced a 100-Continue as a
         * kinda HTTP ping test, allow for retries
         */
        if ((status = ap_proxy_http_request(p, r, backend, worker,
                                        conf, uri, locurl, server_portstr)) != OK) {
            if ((status == HTTP_SERVICE_UNAVAILABLE) && worker->ping_timeout_set) {
                backend->close = 1;
                ap_log_error(APLOG_MARK, APLOG_INFO, status, r->server,
                             "proxy: HTTP: 100-Continue failed to %pI (%s)",
                             worker->cp->addr, worker->hostname);
                retry++;
                continue;
            } else {
                break;
            }

        }

        /* Step Five: Receive the Response... Fall thru to cleanup */
        status = ap_proxy_http_process_response(p, r, backend, worker,
                                                conf, server_portstr);

        break;
    }

    /* Step Six: Clean Up */
cleanup:
    if (backend) {
        if (status != OK)
            backend->close = 1;
        ap_proxy_http_cleanup(proxy_function, r, backend);
    }
    return status;
}