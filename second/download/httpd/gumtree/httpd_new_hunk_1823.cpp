        }
    }

    backend->is_ssl = 0;
    backend->close_on_recycle = 0;

    retry = 0;
    while (retry < 2) {
        /* Step One: Determine Who To Connect To */
        status = ap_proxy_determine_connection(p, r, conf, worker, backend,
                                               uri, &url, proxyname, proxyport,
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
        status = ap_proxy_ajp_request(p, r, backend, origin, dconf, uri, url,
                                      server_portstr);
        break;
    }

    /* Do not close the socket */
    ap_proxy_release_connection(scheme, backend, r->server);
    return status;
}

static void ap_proxy_http_register_hook(apr_pool_t *p)
