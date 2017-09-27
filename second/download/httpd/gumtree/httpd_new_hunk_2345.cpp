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
