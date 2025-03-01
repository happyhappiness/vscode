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
