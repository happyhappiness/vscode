     * TODO: Handle this much better... 
     *
     * XXX: If generic workers are ever address-reusable, we need 
     *      to check host and port on the conn and be careful about
     *      spilling the cached addr from the worker.
     */
    if (!conn->hostname || !worker->s->is_address_reusable ||
        worker->s->disablereuse || *worker->s->uds_path) {
        if (proxyname) {
            conn->hostname = apr_pstrdup(conn->pool, proxyname);
            conn->port = proxyport;
            /*
             * If we have a forward proxy and the protocol is HTTPS,
             * then we need to prepend a HTTP CONNECT request before
             * sending our actual HTTPS requests.
             * Save our real backend data for using it later during HTTP CONNECT.
             */
            if (conn->is_ssl) {
                const char *proxy_auth;

                forward_info *forward = apr_pcalloc(conn->pool, sizeof(forward_info));
                conn->forward = forward;
                forward->use_http_connect = 1;
                forward->target_host = apr_pstrdup(conn->pool, uri->hostname);
                forward->target_port = uri->port;
                /* Do we want to pass Proxy-Authorization along?
                 * If we haven't used it, then YES
                 * If we have used it then MAYBE: RFC2616 says we MAY propagate it.
                 * So let's make it configurable by env.
                 * The logic here is the same used in mod_proxy_http.
                 */
                proxy_auth = apr_table_get(r->headers_in, "Proxy-Authorization");
                if (proxy_auth != NULL &&
                    proxy_auth[0] != '\0' &&
                    r->user == NULL && /* we haven't yet authenticated */
                    apr_table_get(r->subprocess_env, "Proxy-Chain-Auth")) {
                    forward->proxy_auth = apr_pstrdup(conn->pool, proxy_auth);
                }
            }
        }
        else {
            conn->hostname = apr_pstrdup(conn->pool, uri->hostname);
            conn->port = uri->port;
        }
        socket_cleanup(conn);
        if (!(*worker->s->uds_path) &&
            (!worker->s->is_address_reusable || worker->s->disablereuse)) {
            /*
             * Only do a lookup if we should not reuse the backend address.
             * Otherwise we will look it up once for the worker.
             */
            err = apr_sockaddr_info_get(&(conn->addr),
                                        conn->hostname, APR_UNSPEC,
                                        conn->port, 0,
                                        conn->pool);
        }
    }
    if (!(*worker->s->uds_path) && worker->s->is_address_reusable && !worker->s->disablereuse) {
        /*
         * Looking up the backend address for the worker only makes sense if
         * we can reuse the address.
         */
        if (!worker->cp->addr) {
            if ((err = PROXY_THREAD_LOCK(worker)) != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, err, r, APLOGNO(00945) "lock");
                return HTTP_INTERNAL_SERVER_ERROR;
            }

            /*
             * Worker can have the single constant backend adress.
             * The single DNS lookup is used once per worker.
             * If dynamic change is needed then set the addr to NULL
             * inside dynamic config to force the lookup.
             */
            err = apr_sockaddr_info_get(&(worker->cp->addr),
                                        conn->hostname, APR_UNSPEC,
                                        conn->port, 0,
                                        worker->cp->pool);
            conn->addr = worker->cp->addr;
            if ((uerr = PROXY_THREAD_UNLOCK(worker)) != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, uerr, r, APLOGNO(00946) "unlock");
            }
        }
        else {
            conn->addr = worker->cp->addr;
        }
    }
    /* Close a possible existing socket if we are told to do so */
    if (conn->close) {
        socket_cleanup(conn);
        conn->close = 0;
