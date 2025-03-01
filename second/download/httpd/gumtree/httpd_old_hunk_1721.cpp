                }
            }
        }

        connected    = 1;
    }
    if (PROXY_WORKER_IS_USABLE(worker)) {
        /*
         * Put the entire worker to error state if
         * the PROXY_WORKER_IGNORE_ERRORS flag is not set.
         * Although some connections may be alive
         * no further connections to the worker could be made
         */
        if (!connected) {
            if (!(worker->s->status & PROXY_WORKER_IGNORE_ERRORS)) {
                worker->s->error_time = apr_time_now();
                worker->s->status |= PROXY_WORKER_IN_ERROR;
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                    "ap_proxy_connect_backend disabling worker for (%s)",
                    worker->hostname);
            }
        }
        else {
            worker->s->error_time = 0;
            worker->s->retries = 0;
        }
        return connected ? OK : DECLINED;
    }
    else {
        /*
         * The worker is in error likely done by a different thread / process
         * e.g. for a timeout or bad status. We should respect this and should
         * not continue with a connection via this worker even if we got one.
         */
        if (connected) {
            socket_cleanup(conn);
        }
        return DECLINED;
    }
}

PROXY_DECLARE(int) ap_proxy_connection_create(const char *proxy_function,
                                              proxy_conn_rec *conn,
                                              conn_rec *c,
                                              server_rec *s)
