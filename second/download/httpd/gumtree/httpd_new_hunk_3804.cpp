            }
            ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, s,
                         "%s: fam %d socket created to connect to %s",
                         proxy_function, backend_addr->family, worker->s->hostname);

            if (conf->source_address_set) {
                local_addr = apr_pmemdup(conn->scpool, conf->source_address,
                                         sizeof(apr_sockaddr_t));
                local_addr->pool = conn->scpool;
                rv = apr_socket_bind(newsock, local_addr);
                if (rv != APR_SUCCESS) {
                    ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(00956)
                                 "%s: failed to bind socket to local address",
                                 proxy_function);
                }
