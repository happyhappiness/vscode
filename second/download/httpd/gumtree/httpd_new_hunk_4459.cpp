                if ((err = PROXY_THREAD_LOCK(worker)) != APR_SUCCESS) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, err, r, APLOGNO(00945) "lock");
                    return HTTP_INTERNAL_SERVER_ERROR;
                }

                /*
                 * Worker can have the single constant backend address.
                 * The single DNS lookup is used once per worker.
                 * If dynamic change is needed then set the addr to NULL
                 * inside dynamic config to force the lookup.
                 */
                err = apr_sockaddr_info_get(&(worker->cp->addr),
                                            conn->hostname, APR_UNSPEC,
