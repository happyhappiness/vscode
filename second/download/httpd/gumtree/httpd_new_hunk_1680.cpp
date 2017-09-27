     * responding server, whatever.
     *
     * For now we do nothing, ie we get DNS round robin.
     * XXX FIXME
     */
    failed = ap_proxy_connect_to_backend(&sock, "CONNECT", connect_addr,
                                         connectname, conf, r);

    /* handle a permanent error from the above loop */
    if (failed) {
        if (proxyname) {
            return DECLINED;
        }
        else {
            return HTTP_SERVICE_UNAVAILABLE;
        }
    }

    /* setup polling for connection */
    ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                  "proxy: CONNECT: setting up poll()");

    if ((rv = apr_pollset_create(&pollset, 2, r->pool, 0)) != APR_SUCCESS) {
        apr_socket_close(sock);
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "proxy: CONNECT: error apr_pollset_create()");
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    /* Add client side to the poll */
    pollfd.p = r->pool;
    pollfd.desc_type = APR_POLL_SOCKET;
    pollfd.reqevents = APR_POLLIN;
    pollfd.desc.s = client_socket;
    pollfd.client_data = NULL;
    apr_pollset_add(pollset, &pollfd);

    /* Add the server side to the poll */
    pollfd.desc.s = sock;
    apr_pollset_add(pollset, &pollfd);

    /*
     * Step Three: Send the Request
     *
     * Send the HTTP/1.1 CONNECT request to the remote server
     */

    backconn = ap_run_create_connection(c->pool, r->server, sock,
                                        c->id, c->sbh, c->bucket_alloc);
    if (!backconn) {
        /* peer reset */
        ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                      "proxy: an error occurred creating a new connection "
                      "to %pI (%s)", connect_addr, connectname);
        apr_socket_close(sock);
        return HTTP_INTERNAL_SERVER_ERROR;
    }
    ap_proxy_ssl_disable(backconn);
    rc = ap_run_pre_connection(backconn, sock);
    if (rc != OK && rc != DONE) {
        backconn->aborted = 1;
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "proxy: CONNECT: pre_connection setup failed (%d)", rc);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    ap_log_rerror(APLOG_MARK, APLOG_TRACE3, 0, r,
                  "proxy: CONNECT: connection complete to %pI (%s)",
                  connect_addr, connectname);


    /* If we are connecting through a remote proxy, we need to pass
     * the CONNECT request on to it.
     */
    if (proxyport) {
    /* FIXME: Error checking ignored.
     */
        ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, r->server,
                     "proxy: CONNECT: sending the CONNECT request"
                     " to the remote proxy");
        ap_fprintf(backconn->output_filters, bb,
                   "CONNECT %s HTTP/1.0" CRLF, r->uri);
        ap_fprintf(backconn->output_filters, bb,
                   "Proxy-agent: %s" CRLF CRLF, ap_get_server_banner());
        ap_fflush(backconn->output_filters, bb);
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, r->server,
                     "proxy: CONNECT: Returning 200 OK Status");
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
#if 0
        /* This is safer code, but it doesn't work yet.  I'm leaving it
         * here so that I can fix it later.
         */
        r->status = HTTP_OK;
        r->header_only = 1;
        apr_table_set(r->headers_out, "Proxy-agent: %s", ap_get_server_banner());
        ap_rflush(r);
#endif
    }

    ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, r->server,
                 "proxy: CONNECT: setting up poll()");

    /*
     * Step Four: Handle Data Transfer
     *
     * Handle two way transfer of data over the socket (this is a tunnel).
     */

    /* we are now acting as a tunnel - the input/output filter stacks should
     * not contain any non-connection filters.
     */
    r->output_filters = c->output_filters;
    r->proto_output_filters = c->output_filters;
    r->input_filters = c->input_filters;
    r->proto_input_filters = c->input_filters;
/*    r->sent_bodyct = 1;*/

    while (1) { /* Infinite loop until error (one side closes the connection) */
        if ((rv = apr_pollset_poll(pollset, -1, &pollcnt, &signalled))
            != APR_SUCCESS) {
            apr_socket_close(sock);
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, "proxy: CONNECT: error apr_poll()");
            return HTTP_INTERNAL_SERVER_ERROR;
        }
#ifdef DEBUGGING
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: CONNECT: woke from poll(), i=%d", pollcnt);
#endif

        for (pi = 0; pi < pollcnt; pi++) {
            const apr_pollfd_t *cur = &signalled[pi];

            if (cur->desc.s == sock) {
                pollevent = cur->rtnevents;
                if (pollevent & APR_POLLIN) {
#ifdef DEBUGGING
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                  "proxy: CONNECT: sock was readable");
#endif
                    rv = proxy_connect_transfer(r, backconn, c, bb, "sock");
                    }
                else if ((pollevent & APR_POLLERR)
                         || (pollevent & APR_POLLHUP)) {
                         rv = APR_EPIPE;
                         ap_log_rerror(APLOG_MARK, APLOG_NOTICE, 0, r,
                                       "proxy: CONNECT: err/hup on backconn");
                }
                if (rv != APR_SUCCESS)
                    client_error = 1;
            }
            else if (cur->desc.s == client_socket) {
                pollevent = cur->rtnevents;
                if (pollevent & APR_POLLIN) {
#ifdef DEBUGGING
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                  "proxy: CONNECT: client was readable");
#endif
                    rv = proxy_connect_transfer(r, c, backconn, bb, "client");
                }
            }
            else {
                rv = APR_EBADF;
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                              "proxy: CONNECT: unknown socket in pollset");
            }

        }
        if (rv != APR_SUCCESS) {
            break;
        }
    }

    ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, r->server,
                 "proxy: CONNECT: finished with poll() - cleaning up");

    /*
     * Step Five: Clean Up
     *
     * Close the socket and clean up
     */

    if (client_error)
        apr_socket_close(sock);
    else
        ap_lingering_close(backconn);

    c->aborted = 1;

    return OK;
}

static void ap_proxy_connect_register_hook(apr_pool_t *p)
{
    proxy_hook_scheme_handler(proxy_connect_handler, NULL, NULL, APR_HOOK_MIDDLE);
    proxy_hook_canon_handler(proxy_connect_canon, NULL, NULL, APR_HOOK_MIDDLE);
}

static const command_rec cmds[] =
{
    AP_INIT_ITERATE("AllowCONNECT", set_allowed_ports, NULL, RSRC_CONF,
     "A list of ports or port ranges which CONNECT may connect to"),
    {NULL}
};

AP_DECLARE_MODULE(proxy_connect) = {
    STANDARD20_MODULE_STUFF,
    NULL,       /* create per-directory config structure */
    NULL,       /* merge per-directory config structures */
    create_config,       /* create per-server config structure */
    merge_config,       /* merge per-server config structures */
    cmds,       /* command apr_table_t */
    ap_proxy_connect_register_hook  /* register hooks */
};
