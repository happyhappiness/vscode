     */
    if ((r->proxyreq == PROXYREQ_REVERSE) && (!c->keepalives)
        && (apr_table_get(r->subprocess_env, "proxy-initial-not-pooled"))) {
        backend->close = 1;
    }

    /* Step One: Determine Who To Connect To */
    if ((status = ap_proxy_determine_connection(p, r, conf, worker, backend,
                                                uri, &url, proxyname,
                                                proxyport, server_portstr,
                                                sizeof(server_portstr))) != OK)
        goto cleanup;

    /* Step Two: Make the Connection */
    if (ap_proxy_connect_backend(proxy_function, backend, worker, r->server)) {
        status = HTTP_SERVICE_UNAVAILABLE;
        goto cleanup;
    }

    /* Step Three: Create conn_rec */
    if (!backend->connection) {
        if ((status = ap_proxy_connection_create(proxy_function, backend,
                                                 c, r->server)) != OK)
            goto cleanup;
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

    /* Step Four: Send the Request */
    if ((status = ap_proxy_http_request(p, r, backend, backend->connection,
                                        conf, uri, url, server_portstr)) != OK)
        goto cleanup;

    /* Step Five: Receive the Response */
    if ((status = ap_proxy_http_process_response(p, r, backend,
                                                 backend->connection,
                                                 conf, server_portstr)) != OK)
        goto cleanup;

    /* Step Six: Clean Up */

cleanup:
    if (backend) {
        if (status != OK)
            backend->close = 1;
        ap_proxy_http_cleanup(proxy_function, r, backend);
    }
