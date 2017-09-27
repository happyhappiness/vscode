                                           server_portstr,
                                           sizeof(server_portstr));
    if (status != OK) {
        goto cleanup;
    }

    /* This scheme handler does not reuse connections by default, to
     * avoid tieing up a fastcgi that isn't expecting to work on 
     * parallel requests.  But if the user went out of their way to
     * type the default value of disablereuse=off, we'll allow it.
     */  
    backend->close = 1;
    if (worker->s->disablereuse_set && !worker->s->disablereuse) { 
        backend->close = 0;
    }

    /* Step Two: Make the Connection */
    if (ap_proxy_connect_backend(FCGI_SCHEME, backend, worker, r->server)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01079)
                      "failed to make connection to backend: %s",
                      backend->hostname);
