             * Transfer-Encoding overrides the Content-Length. ... A sender
             * MUST remove the received Content-Length field".
             */
            apr_table_unset(r->headers_in, "Content-Length");
        }
    }

    apr_brigade_destroy(tmp_bb);

    /* update what we think the virtual host is based on the headers we've
     * now read. may update status.
     */
    ap_update_vhost_from_headers(r);
    access_status = r->status;

    /* Toggle to the Host:-based vhost's timeout mode to fetch the
     * request body and send the response body, if needed.
     */
    if (cur_timeout != r->server->timeout) {
        apr_socket_timeout_set(csd, r->server->timeout);
