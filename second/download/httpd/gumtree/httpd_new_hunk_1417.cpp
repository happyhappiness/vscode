    }
    /* check if ProxyBlock directive on this host */
    if (OK != ap_proxy_checkproxyblock(r, conf, conn->addr)) {
        return ap_proxyerror(r, HTTP_FORBIDDEN,
                             "Connect to remote machine blocked");
    }
    /*
     * When SSL is configured, determine the hostname (SNI) for the request
     * and save it in conn->ssl_hostname. Close any reused connection whose
     * SNI differs.
     */
    if (conn->is_ssl) {
        const char *ssl_hostname;
        /*
         * In the case of ProxyPreserveHost on use the hostname of
         * the request if present otherwise use the one from the
         * backend request URI.
         */
        if (conf->preserve_host) {
            ssl_hostname = r->hostname;
        }
        else {
            ssl_hostname = conn->hostname;
        }
        /*
         * Close if a SNI is in use but this request requires no or
         * a different one, or no SNI is in use but one is required.
         */
        if ((conn->ssl_hostname && (!ssl_hostname ||
                                    strcasecmp(conn->ssl_hostname,
                                               ssl_hostname) != 0)) ||
                (!conn->ssl_hostname && ssl_hostname && conn->sock)) {
            socket_cleanup(conn);
        }
        if (conn->ssl_hostname == NULL) {
            conn->ssl_hostname = apr_pstrdup(conn->scpool, ssl_hostname);
        }
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "proxy: connected %s to %s:%d", *url, conn->hostname,
                 conn->port);
    return OK;
}

