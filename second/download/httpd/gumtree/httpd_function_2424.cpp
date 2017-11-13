static apr_status_t dummy_connection(ap_pod_t *pod)
{
    const char *data;
    apr_status_t rv;
    apr_socket_t *sock;
    apr_pool_t *p;
    apr_size_t len;

    /* create a temporary pool for the socket.  pconf stays around too long */
    rv = apr_pool_create(&p, pod->p);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    rv = apr_socket_create(&sock, ap_listeners->bind_addr->family,
                           SOCK_STREAM, 0, p);
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

    rv = apr_socket_connect(sock, ap_listeners->bind_addr);
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
                     "connect to listener on %pI", ap_listeners->bind_addr);
        apr_pool_destroy(p);
        return rv;
    }

    if (ap_listeners->protocol && strcasecmp(ap_listeners->protocol, "https") == 0) {
        /* Send a TLS 1.0 close_notify alert.  This is perhaps the
         * "least wrong" way to open and cleanly terminate an SSL
         * connection.  It should "work" without noisy error logs if
         * the server actually expects SSLv3/TLSv1.  With
         * SSLv23_server_method() OpenSSL's SSL_accept() fails
         * ungracefully on receipt of this message, since it requires
         * an 11-byte ClientHello message and this is too short. */
        static const unsigned char tls10_close_notify[7] = {
            '\x15',         /* TLSPlainText.type = Alert (21) */
            '\x03', '\x01', /* TLSPlainText.version = {3, 1} */
            '\x00', '\x02', /* TLSPlainText.length = 2 */
            '\x01',         /* Alert.level = warning (1) */
            '\x00'          /* Alert.description = close_notify (0) */
        };
        data = (const char *)tls10_close_notify;
        len = sizeof(tls10_close_notify);
    }
    else /* ... XXX other request types here? */ {
        /* Create an HTTP request string.  We include a User-Agent so
         * that adminstrators can track down the cause of the
         * odd-looking requests in their logs.  A complete request is
         * used since kernel-level filtering may require that much
         * data before returning from accept(). */
        data = apr_pstrcat(p, "OPTIONS * HTTP/1.0\r\nUser-Agent: ",
                           ap_get_server_banner(),
                           " (internal dummy connection)\r\n\r\n", NULL);
        len = strlen(data);
    }

    apr_socket_send(sock, data, &len);
    apr_socket_close(sock);
    apr_pool_destroy(p);

    return rv;
}