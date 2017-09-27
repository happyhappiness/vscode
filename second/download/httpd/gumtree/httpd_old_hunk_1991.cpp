                     "proxy: AJP: failed to make connection to backend: %s",
                     backend->hostname);
        status = HTTP_SERVICE_UNAVAILABLE;
        goto cleanup;
    }

    /* Step Three: Process the Request */
    status = ap_proxy_ajp_request(p, r, backend, origin, dconf, uri, url,
                                  server_portstr);

cleanup:
    /* Do not close the socket */
