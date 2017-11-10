static apr_status_t connect_to_peer(apr_socket_t **newsock,
                                    request_rec *r,
                                    apr_sockaddr_t *backend_addrs,
                                    const char *backend_name,
                                    apr_interval_time_t timeout)
{
    apr_status_t rv = APR_EINVAL; /* returned if no backend addr was provided
                                   */
    int connected = 0;
    apr_sockaddr_t *addr = backend_addrs;

    while (addr && !connected) {
        int loglevel = addr->next ? APLOG_DEBUG : APLOG_ERR;
        rv = apr_socket_create(newsock, addr->family,
                               SOCK_STREAM, 0, r->pool);
        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, loglevel, rv, r,
                          APLOGNO(02494) "error creating family %d socket "
                          "for target %s",
                          addr->family, backend_name);
            addr = addr->next;
            continue;
        }

        apr_socket_opt_set(*newsock, APR_TCP_NODELAY, 1);
        apr_socket_timeout_set(*newsock,
                               timeout ? timeout : r->server->timeout);

        rv = apr_socket_connect(*newsock, addr);
        if (rv != APR_SUCCESS) {
            apr_socket_close(*newsock);
            ap_log_rerror(APLOG_MARK, loglevel, rv, r,
                          APLOGNO(02495) "attempt to connect to %pI (%s) "
                          "failed", addr, backend_name);
            addr = addr->next;
            continue;
        }

        connected = 1;
    }

    return rv;
#undef FN_LOG_MARK
}