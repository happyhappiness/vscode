     * we need to keep from blocking too long and instead return an error,
     * because the MPM won't want to hold up a graceful restart for a
     * long time
     */
    rv = apr_socket_timeout_set(sock, apr_time_from_sec(3));
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, rv, ap_server_conf,
                     "set timeout on socket to connect to listener");
        apr_socket_close(sock);
        apr_pool_destroy(p);
        return rv;
    }

