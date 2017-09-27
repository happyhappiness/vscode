     */

    backconn = ap_run_create_connection(c->pool, r->server, sock,
                                        c->id, c->sbh, c->bucket_alloc);
    if (!backconn) {
        /* peer reset */
        ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(01021)
                      "an error occurred creating a new connection "
                      "to %pI (%s)", connect_addr, connectname);
        apr_socket_close(sock);
        return HTTP_INTERNAL_SERVER_ERROR;
    }
    ap_proxy_ssl_disable(backconn);
    rc = ap_run_pre_connection(backconn, sock);
    if (rc != OK && rc != DONE) {
        backconn->aborted = 1;
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01022)
                      "pre_connection setup failed (%d)", rc);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    ap_log_rerror(APLOG_MARK, APLOG_TRACE3, 0, r,
                  "connection complete to %pI (%s)",
                  connect_addr, connectname);
    apr_table_setn(r->notes, "proxy-source-port", apr_psprintf(r->pool, "%hu",
                   backconn->local_addr->port));

    /* If we are connecting through a remote proxy, we need to pass
     * the CONNECT request on to it.
     */
    if (proxyport) {
    /* FIXME: Error checking ignored.
     */
        ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                      "sending the CONNECT request to the remote proxy");
        ap_fprintf(backconn->output_filters, bb,
                   "CONNECT %s HTTP/1.0" CRLF, r->uri);
        ap_fprintf(backconn->output_filters, bb,
                   "Proxy-agent: %s" CRLF CRLF, ap_get_server_banner());
        ap_fflush(backconn->output_filters, bb);
    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, "Returning 200 OK");
        nbytes = apr_snprintf(buffer, sizeof(buffer),
                              "HTTP/1.0 200 Connection Established" CRLF);
        ap_xlate_proto_to_ascii(buffer, nbytes);
        ap_fwrite(c->output_filters, bb, buffer, nbytes);
        nbytes = apr_snprintf(buffer, sizeof(buffer),
                              "Proxy-agent: %s" CRLF CRLF,
                              ap_get_server_banner());
        ap_xlate_proto_to_ascii(buffer, nbytes);
        ap_fwrite(c->output_filters, bb, buffer, nbytes);
        ap_fflush(c->output_filters, bb);
