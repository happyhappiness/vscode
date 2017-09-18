
    /* Get response from the remote server, and pass it up the
     * filter chain
     */

    rp = ap_proxy_make_fake_req(origin, r);

    while (received_continue) {
        apr_brigade_cleanup(bb);

        len = ap_getline(buffer, sizeof(buffer), rp, 0);
        if (len == 0) {
            /* handle one potential stray CRLF */
            len = ap_getline(buffer, sizeof(buffer), rp, 0);
        }
        if (len <= 0) {
            apr_socket_close(p_conn->sock);
            backend->connection = NULL;
            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                          "proxy: error reading status line from remote "
                          "server %s", p_conn->name);
            return ap_proxyerror(r, HTTP_BAD_GATEWAY,
                                 "Error reading from remote server");
        }

