                                           server_portstr,
                                           sizeof(server_portstr));
    if (status != OK) {
        goto cleanup;
    }

    /* XXX Setting close to 0 is a great way to end up with
     *     timeouts at this point, since we lack good ways to manage the
     *     back end fastcgi processes.  This should be revisited when we
     *     have a better story on that part of things. */
    backend->close = 1;

    /* Step Two: Make the Connection */
    if (ap_proxy_connect_backend(FCGI_SCHEME, backend, worker, r->server)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01079)
                      "failed to make connection to backend: %s",
                      backend->hostname);
