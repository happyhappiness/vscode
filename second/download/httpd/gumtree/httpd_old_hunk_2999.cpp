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
