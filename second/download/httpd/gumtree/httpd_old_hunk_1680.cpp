     * responding server, whatever.
     *
     * For now we do nothing, ie we get DNS round robin.
     * XXX FIXME
     */
    failed = ap_proxy_connect_to_backend(&sock, "CONNECT", connect_addr,
                                         connectname, conf, r->server,
                                         r->pool);

    /* handle a permanent error from the above loop */
    if (failed) {
        if (proxyname) {
            return DECLINED;
        }
        else {
            return HTTP_SERVICE_UNAVAILABLE;
        }
    }

    /*
     * Step Three: Send the Request
     *
     * Send the HTTP/1.1 CONNECT request to the remote server
     */

    /* we are acting as a tunnel - the output filter stack should
     * be completely empty, because when we are done here we are done completely.
     * We add the NULL filter to the stack to do this...
     */
    r->output_filters = NULL;
    r->connection->output_filters = NULL;


    /* If we are connecting through a remote proxy, we need to pass
     * the CONNECT request on to it.
     */
    if (proxyport) {
    /* FIXME: Error checking ignored.
     */
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
             "proxy: CONNECT: sending the CONNECT request to the remote proxy");
        nbytes = apr_snprintf(buffer, sizeof(buffer),
                  "CONNECT %s HTTP/1.0" CRLF, r->uri);
        apr_socket_send(sock, buffer, &nbytes);
        nbytes = apr_snprintf(buffer, sizeof(buffer),
                  "Proxy-agent: %s" CRLF CRLF, ap_get_server_banner());
        apr_socket_send(sock, buffer, &nbytes);
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
             "proxy: CONNECT: Returning 200 OK Status");
        nbytes = apr_snprintf(buffer, sizeof(buffer),
                  "HTTP/1.0 200 Connection Established" CRLF);
        ap_xlate_proto_to_ascii(buffer, nbytes);
        apr_socket_send(client_socket, buffer, &nbytes);
        nbytes = apr_snprintf(buffer, sizeof(buffer),
                  "Proxy-agent: %s" CRLF CRLF, ap_get_server_banner());
        ap_xlate_proto_to_ascii(buffer, nbytes);
        apr_socket_send(client_socket, buffer, &nbytes);
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

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
         "proxy: CONNECT: setting up poll()");

    /*
     * Step Four: Handle Data Transfer
     *
     * Handle two way transfer of data over the socket (this is a tunnel).
     */

/*    r->sent_bodyct = 1;*/

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

    while (1) { /* Infinite loop until error (one side closes the connection) */
        if ((rv = apr_pollset_poll(pollset, -1, &pollcnt, &signalled)) != APR_SUCCESS) {
            if (APR_STATUS_IS_EINTR(rv)) { 
                continue;
            }
            apr_socket_close(sock);
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, "proxy: CONNECT: error apr_poll()");
            return HTTP_INTERNAL_SERVER_ERROR;
        }
#ifdef DEBUGGING
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: CONNECT: woke from select(), i=%d", pollcnt);
#endif

        for (pi = 0; pi < pollcnt; pi++) {
            const apr_pollfd_t *cur = &signalled[pi];

            if (cur->desc.s == sock) {
                pollevent = cur->rtnevents;
                if (pollevent & APR_POLLIN) {
#ifdef DEBUGGING
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                                 "proxy: CONNECT: sock was set");
#endif
                    nbytes = sizeof(buffer);
                    rv = apr_socket_recv(sock, buffer, &nbytes);
                    if (rv == APR_SUCCESS) {
                        o = 0;
                        i = nbytes;
                        while(i > 0)
                        {
                            nbytes = i;
    /* This is just plain wrong.  No module should ever write directly
     * to the client.  For now, this works, but this is high on my list of
     * things to fix.  The correct line is:
     * if ((nbytes = ap_rwrite(buffer + o, nbytes, r)) < 0)
     * rbb
     */
                            rv = apr_socket_send(client_socket, buffer + o, &nbytes);
                            if (rv != APR_SUCCESS)
                                break;
                            o += nbytes;
                            i -= nbytes;
                        }
                    }
                    else
                        break;
                }
                else if ((pollevent & APR_POLLERR) || (pollevent & APR_POLLHUP))
                    break;
            }
            else if (cur->desc.s == client_socket) {
                pollevent = cur->rtnevents;
                if (pollevent & APR_POLLIN) {
#ifdef DEBUGGING
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                                 "proxy: CONNECT: client was set");
#endif
                    nbytes = sizeof(buffer);
                    rv = apr_socket_recv(client_socket, buffer, &nbytes);
                    if (rv == APR_SUCCESS) {
                        o = 0;
                        i = nbytes;
#ifdef DEBUGGING
                        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                                     "proxy: CONNECT: read %d from client", i);
#endif
                        while(i > 0)
                        {
                            nbytes = i;
                            rv = apr_socket_send(sock, buffer + o, &nbytes);
                            if (rv != APR_SUCCESS)
                                break;
                            o += nbytes;
                            i -= nbytes;
                        }
                    }
                    else
                        break;
                }
                else if ((pollevent & APR_POLLERR) || (pollevent & APR_POLLHUP)) {
                    rv = APR_EOF;
                    break;
                }
            }
            else
                break;
        }
        if (rv != APR_SUCCESS) {
            break;
        }
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
         "proxy: CONNECT: finished with poll() - cleaning up");

    /*
     * Step Five: Clean Up
     *
     * Close the socket and clean up
     */

    apr_socket_close(sock);

    return OK;
}

static void ap_proxy_connect_register_hook(apr_pool_t *p)
{
    proxy_hook_scheme_handler(proxy_connect_handler, NULL, NULL, APR_HOOK_MIDDLE);
    proxy_hook_canon_handler(proxy_connect_canon, NULL, NULL, APR_HOOK_MIDDLE);
}

module AP_MODULE_DECLARE_DATA proxy_connect_module = {
    STANDARD20_MODULE_STUFF,
    NULL,       /* create per-directory config structure */
    NULL,       /* merge per-directory config structures */
    NULL,       /* create per-server config structure */
    NULL,       /* merge per-server config structures */
    NULL,       /* command apr_table_t */
    ap_proxy_connect_register_hook  /* register hooks */
};
