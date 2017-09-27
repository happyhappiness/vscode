    if (status != OK) {
        goto cleanup;
    }

    /* Step Two: Make the Connection */
    if (ap_proxy_connect_backend(PROXY_FUNCTION, backend, worker, r->server)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "proxy: " PROXY_FUNCTION ": failed to make connection "
                     "to backend: %s:%u", backend->hostname, backend->port);
        status = HTTP_SERVICE_UNAVAILABLE;
        goto cleanup;
    }

    /* Step Three: Process the Request */
    if (   ((status = ap_setup_client_block(r, REQUEST_CHUNKED_ERROR)) != OK)
