        }
    }

    backend->is_ssl = 0;
    backend->close_on_recycle = 0;

    /* Step One: Determine Who To Connect To */
    status = ap_proxy_determine_connection(p, r, conf, worker, backend,
                                           uri, &url, proxyname, proxyport,
                                           server_portstr,
                                           sizeof(server_portstr));

    if (status != OK)
        goto cleanup;

    /* Step Two: Make the Connection */
    if (ap_proxy_connect_backend(scheme, backend, worker, r->server)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
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
    ap_proxy_release_connection(scheme, backend, r->server);
    return status;
}

static void ap_proxy_http_register_hook(apr_pool_t *p)
