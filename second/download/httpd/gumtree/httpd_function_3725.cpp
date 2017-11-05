static int proxy_ajp_handler(request_rec *r, proxy_worker *worker,
                             proxy_server_conf *conf,
                             char *url, const char *proxyname,
                             apr_port_t proxyport)
{
    int status;
    char server_portstr[32];
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
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: AJP: declining URL %s", url);
        return DECLINED;
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "proxy: AJP: serving URL %s", url);

    /* create space for state information */
    status = ap_proxy_acquire_connection(scheme, &backend, worker,
                                         r->server);
    if (status != OK) {
        if (backend) {
            backend->close = 1;
            ap_proxy_release_connection(scheme, backend, r->server);
        }
        return status;
    }

    backend->is_ssl = 0;
    backend->close = 0;

    retry = 0;
    while (retry < 2) {
        char *locurl = url;
        /* Step One: Determine Who To Connect To */
        status = ap_proxy_determine_connection(p, r, conf, worker, backend,
                                               uri, &locurl, proxyname, proxyport,
                                               server_portstr,
                                               sizeof(server_portstr));

        if (status != OK)
            break;

        /* Step Two: Make the Connection */
        if (ap_proxy_connect_backend(scheme, backend, worker, r->server)) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                         "proxy: AJP: failed to make connection to backend: %s",
                         backend->hostname);
            status = HTTP_SERVICE_UNAVAILABLE;
            break;
        }

        /* Handle CPING/CPONG */
        if (worker->ping_timeout_set) {
            status = ajp_handle_cping_cpong(backend->sock, r,
                                            worker->ping_timeout);
            /*
             * In case the CPING / CPONG failed for the first time we might be
             * just out of luck and got a faulty backend connection, but the
             * backend might be healthy nevertheless. So ensure that the backend
             * TCP connection gets closed and try it once again.
             */
            if (status != APR_SUCCESS) {
                backend->close++;
                ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                             "proxy: AJP: cping/cpong failed to %pI (%s)",
                             worker->cp->addr,
                             worker->hostname);
                status = HTTP_SERVICE_UNAVAILABLE;
                retry++;
                continue;
            }
        }
        /* Step Three: Process the Request */
        status = ap_proxy_ajp_request(p, r, backend, origin, dconf, uri, locurl,
                                      server_portstr);
        break;
    }

    /* Do not close the socket */
    ap_proxy_release_connection(scheme, backend, r->server);
    return status;
}