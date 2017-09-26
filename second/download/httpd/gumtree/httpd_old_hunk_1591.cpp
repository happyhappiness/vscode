         */
        err = apr_sockaddr_info_get(&(worker->cp->addr),
                                    conn->hostname, APR_UNSPEC,
                                    conn->port, 0,
                                    worker->cp->pool);
        conn->addr = worker->cp->addr;
        PROXY_THREAD_UNLOCK(worker);
    }
    else
        conn->addr = worker->cp->addr;

    if (err != APR_SUCCESS) {
        return ap_proxyerror(r, HTTP_BAD_GATEWAY,
