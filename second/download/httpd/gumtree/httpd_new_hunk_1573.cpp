                     "proxy: AJP: failed to make connection to backend: %s",
                     backend->hostname);
        status = HTTP_SERVICE_UNAVAILABLE;
        goto cleanup;
    }

    /* Handle CPING/CPONG */
    if (worker->ping_timeout_set) {
        status = ajp_handle_cping_cpong(backend->sock, r,
                                        worker->ping_timeout);
        if (status != APR_SUCCESS) {
            backend->close++;
            ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                         "proxy: AJP: cping/cpong failed to %pI (%s)",
                         worker->cp->addr,
                         worker->hostname);
            status = HTTP_SERVICE_UNAVAILABLE;
            goto cleanup;
        }
    }
    /* Step Three: Process the Request */
    status = ap_proxy_ajp_request(p, r, backend, origin, dconf, uri, url,
                                  server_portstr);

cleanup:
    /* Do not close the socket */
