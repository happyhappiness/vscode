     * and any initial read will fail.
     */
    rv = apr_socket_timeout_set(csd, c->base_server->timeout);
    if (rv != APR_SUCCESS) {
        /* expected cause is that the client disconnected already */
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, rv, c,
                     "apr_socket_timeout_set");
    }

    net->c = c;
    net->in_ctx = NULL;
    net->out_ctx = NULL;
    net->client_socket = csd;
