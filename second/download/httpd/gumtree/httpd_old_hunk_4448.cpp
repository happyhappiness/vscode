                                               sizeof(server_portstr));

        if (status != OK)
            break;

        /* Step Two: Make the Connection */
        if (ap_proxy_connect_backend(scheme, backend, worker, r->server)) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00896)
                          "failed to make connection to backend: %s",
                          backend->hostname);
            status = HTTP_SERVICE_UNAVAILABLE;
            break;
        }
