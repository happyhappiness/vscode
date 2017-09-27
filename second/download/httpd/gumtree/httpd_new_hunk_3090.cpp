                rv = send_http_connect(conn, s);
                /* If an error occurred, loop round and try again */
                if (rv != APR_SUCCESS) {
                    conn->sock = NULL;
                    apr_socket_close(newsock);
                    loglevel = backend_addr->next ? APLOG_DEBUG : APLOG_ERR;
                    ap_log_error(APLOG_MARK, loglevel, rv, s, APLOGNO(00958)
                                 "%s: attempt to connect to %s:%d "
                                 "via http CONNECT through %pI (%s) failed",
                                 proxy_function,
                                 forward->target_host, forward->target_port,
                                 backend_addr, worker->s->hostname);
                    backend_addr = backend_addr->next;
                    continue;
                }
            }
        }

