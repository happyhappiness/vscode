    /* on some platforms (e.g., FreeBSD), the kernel won't accept many
     * queued connections before it starts blocking local connects...
     * we need to keep from blocking too long and instead return an error,
     * because the MPM won't want to hold up a graceful restart for a
     * long time
     */
    rv = apr_setsocketopt(sock, APR_SO_TIMEOUT, 3 * APR_USEC_PER_SEC);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, rv, ap_server_conf,
                     "set timeout on socket to connect to listener");
        apr_socket_close(sock);
        return rv;
    }
