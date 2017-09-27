            lr = apr_pcalloc(s->process->pool, sizeof(ap_listen_rec));

            if (lr) {
                lr->sd = sd;
                if ((status = apr_sockaddr_info_get(&lr->bind_addr, sl->addr, APR_UNSPEC, sl->port, 0,
                                              s->process->pool)) != APR_SUCCESS) {
                    ap_log_perror(APLOG_MARK, APLOG_CRIT, status, pconf, APLOGNO(02129)
                                 "alloc_listener: failed to set up sockaddr for %s:%d", sl->addr, sl->port);
                    return HTTP_INTERNAL_SERVER_ERROR;
                }
                lr->next = ap_listeners;
                ap_listeners = lr;
                apr_pool_cleanup_register(s->process->pool, lr, nwssl_socket_cleanup, apr_pool_cleanup_null);
