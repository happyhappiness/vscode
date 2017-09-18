        return DECLINED;
    }

    /*
     * Log information about incoming HTTPS requests
     */
    if (SSLConnLogApplies(sslconn, SSL_LOG_INFO) && ap_is_initial_req(r)) {
        ssl_log(r->server, SSL_LOG_INFO,
                "%s HTTPS request received for child %d (server %s)",
                (r->connection->keepalives <= 0 ?
                 "Initial (No.1)" :
                 apr_psprintf(r->pool, "Subsequent (No.%d)",
                              r->connection->keepalives+1)),
                r->connection->id,
                ssl_util_vhostid(r->pool, r->server));
    }

    /* SetEnvIf ssl-*-shutdown flags can only be per-server,
     * so they won't change across keepalive requests
     */
    if (sslconn->shutdown_type == SSL_SHUTDOWN_TYPE_UNSET) {
