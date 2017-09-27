    backend->close = 1;
    if (worker->s->disablereuse_set && !worker->s->disablereuse) { 
        backend->close = 0;
    }

    /* Step Two: Make the Connection */
    if (ap_proxy_connect_backend(FCGI_SCHEME, backend, worker, r->server)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01079)
                      "failed to make connection to backend: %s",
                      backend->hostname);
        status = HTTP_SERVICE_UNAVAILABLE;
        goto cleanup;
    }
