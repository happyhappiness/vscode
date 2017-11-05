static apr_status_t dummy_connection(ap_pod_t *pod)
{
    char *srequest;
    apr_status_t rv;
    apr_socket_t *sock;
    apr_pool_t *p;
    apr_size_t len;
    ap_listen_rec *lp;

    /* create a temporary pool for the socket.  pconf stays around too long */
    rv = apr_pool_create(&p, pod->p);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    /* If possible, find a listener which is configured for
     * plain-HTTP, not SSL; using an SSL port would either be
     * expensive to do correctly (performing a complete SSL handshake)
     * or cause log spam by doing incorrectly (simply sending EOF). */
    lp = ap_listeners;
    while (lp && lp->protocol && strcasecmp(lp->protocol, "http") != 0) {
        lp = lp->next;
    }
    if (!lp) {
        lp = ap_listeners;
    }

    rv = apr_socket_create(&sock, lp->bind_addr->family, SOCK_STREAM, 0, p);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, rv, ap_server_conf,
                     "get socket to connect to listener");
        apr_pool_destroy(p);
        return rv;
    }

    /* on some platforms (e.g., FreeBSD), the kernel won't accept many
     * queued connections before it starts blocking local connects...
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

    rv = apr_socket_connect(sock, lp->bind_addr);
    if (rv != APR_SUCCESS) {
        int log_level = APLOG_WARNING;

        if (APR_STATUS_IS_TIMEUP(rv)) {
            /* probably some server processes bailed out already and there
             * is nobody around to call accept and clear out the kernel
             * connection queue; usually this is not worth logging
             */
            log_level = APLOG_DEBUG;
        }

        ap_log_error(APLOG_MARK, log_level, rv, ap_server_conf,
                     "connect to listener on %pI", lp->bind_addr);
    }

    /* Create the request string. We include a User-Agent so that
     * adminstrators can track down the cause of the odd-looking
     * requests in their logs.
     */
    srequest = apr_pstrcat(p, "OPTIONS * HTTP/1.0\r\nUser-Agent: ",
                           ap_get_server_description(),
                           " (internal dummy connection)\r\n\r\n", NULL);

    /* Since some operating systems support buffering of data or entire
     * requests in the kernel, we send a simple request, to make sure
     * the server pops out of a blocking accept().
     */
    /* XXX: This is HTTP specific. We should look at the Protocol for each
     * listener, and send the correct type of request to trigger any Accept
     * Filters.
     */
    len = strlen(srequest);
    apr_socket_send(sock, srequest, &len);
    apr_socket_close(sock);
    apr_pool_destroy(p);

    return rv;
}