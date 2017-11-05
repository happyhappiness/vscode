static
apr_status_t ap_proxy_http_process_response(apr_pool_t * p, request_rec *r,
                                            proxy_http_conn_t *p_conn,
                                            conn_rec *origin,
                                            proxy_conn_rec *backend,
                                            proxy_server_conf *conf,
                                            apr_bucket_brigade *bb,
                                            char *server_portstr) {
    conn_rec *c = r->connection;
    char buffer[HUGE_STRING_LEN];
    char keepchar;
    request_rec *rp;
    apr_bucket *e;
    int len, backasswards;
    int received_continue = 1; /* flag to indicate if we should
                                * loop over response parsing logic
                                * in the case that the origin told us
                                * to HTTP_CONTINUE
                                */

    /* Get response from the remote server, and pass it up the
     * filter chain
     */

    rp = ap_proxy_make_fake_req(origin, r);
    /* In case anyone needs to know, this is a fake request that is really a
     * response.
     */
    rp->proxyreq = PROXYREQ_RESPONSE;

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
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "proxy: error reading status line from remote "
                          "server %s", p_conn->name);
            return ap_proxyerror(r, HTTP_BAD_GATEWAY,
                                 "Error reading from remote server");
        }

       /* Is it an HTTP/1 response?
        * This is buggy if we ever see an HTTP/1.10
        */
        if (apr_date_checkmask(buffer, "HTTP/#.# ###*")) {
            int major, minor;

            if (2 != sscanf(buffer, "HTTP/%u.%u", &major, &minor)) {
                major = 1;
                minor = 1;
            }
            /* If not an HTTP/1 message or
             * if the status line was > 8192 bytes
             */
            else if ((buffer[5] != '1') || (len >= sizeof(buffer)-1)) {
                apr_socket_close(p_conn->sock);
                backend->connection = NULL;
                return ap_proxyerror(r, HTTP_BAD_GATEWAY,
                apr_pstrcat(p, "Corrupt status line returned by remote "
                            "server: ", buffer, NULL));
            }
            backasswards = 0;

            keepchar = buffer[12];
            if (keepchar == '\0') {
                ap_log_error(APLOG_MARK, APLOG_WARNING, 0,
                             r->server, "proxy: bad HTTP/%d.%d status line "
                             "returned by %s (%s)", major, minor, r->uri,
                             r->method);
            }
            buffer[12] = '\0';
            r->status = atoi(&buffer[9]);

            buffer[12] = keepchar;
            r->status_line = apr_pstrdup(p, &buffer[9]);
            

            /* read the headers. */
            /* N.B. for HTTP/1.0 clients, we have to fold line-wrapped headers*/
            /* Also, take care with headers with multiple occurences. */

            r->headers_out = ap_proxy_read_headers(r, rp, buffer,
                                                   sizeof(buffer), origin);
            if (r->headers_out == NULL) {
                ap_log_error(APLOG_MARK, APLOG_WARNING, 0,
                             r->server, "proxy: bad HTTP/%d.%d header "
                             "returned by %s (%s)", major, minor, r->uri,
                             r->method);
                p_conn->close += 1;
                /*
                 * ap_send_error relies on a headers_out to be present. we
                 * are in a bad position here.. so force everything we send out
                 * to have nothing to do with the incoming packet
                 */
                r->headers_out = apr_table_make(r->pool,1);
                r->status = HTTP_BAD_GATEWAY;
                r->status_line = "bad gateway";
                return r->status;

            } else {
                /* strip connection listed hop-by-hop headers from response */
                const char *buf;
                p_conn->close += ap_proxy_liststr(apr_table_get(r->headers_out,
                                                                "Connection"),
                                                  "close");
                ap_proxy_clear_connection(p, r->headers_out);
                if ((buf = apr_table_get(r->headers_out, "Content-Type"))) {
                    ap_set_content_type(r, apr_pstrdup(p, buf));
                }            
                ap_proxy_pre_http_request(origin,rp);
            }

            /* handle Via header in response */
            if (conf->viaopt != via_off && conf->viaopt != via_block) {
                /* create a "Via:" response header entry and merge it */
                apr_table_mergen(r->headers_out, "Via",
                                 (conf->viaopt == via_full)
                                     ? apr_psprintf(p, "%d.%d %s%s (%s)",
                                           HTTP_VERSION_MAJOR(r->proto_num),
                                           HTTP_VERSION_MINOR(r->proto_num),
                                           ap_get_server_name(r),
                                           server_portstr,
                                           AP_SERVER_BASEVERSION)
                                     : apr_psprintf(p, "%d.%d %s%s",
                                           HTTP_VERSION_MAJOR(r->proto_num),
                                           HTTP_VERSION_MINOR(r->proto_num),
                                           ap_get_server_name(r),
                                           server_portstr)
                );
            }

            /* cancel keepalive if HTTP/1.0 or less */
            if ((major < 1) || (minor < 1)) {
                p_conn->close += 1;
                origin->keepalive = AP_CONN_CLOSE;
            }
        } else {
            /* an http/0.9 response */
            backasswards = 1;
            r->status = 200;
            r->status_line = "200 OK";
            p_conn->close += 1;
        }

        if ( r->status != HTTP_CONTINUE ) {
            received_continue = 0;
        } else {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, NULL,
                         "proxy: HTTP: received 100 CONTINUE");
        }

        /* we must accept 3 kinds of date, but generate only 1 kind of date */
        {
            const char *buf;
            if ((buf = apr_table_get(r->headers_out, "Date")) != NULL) {
                apr_table_set(r->headers_out, "Date",
                              ap_proxy_date_canon(p, buf));
            }
            if ((buf = apr_table_get(r->headers_out, "Expires")) != NULL) {
                apr_table_set(r->headers_out, "Expires",
                              ap_proxy_date_canon(p, buf));
            }
            if ((buf = apr_table_get(r->headers_out, "Last-Modified")) != NULL) {
                apr_table_set(r->headers_out, "Last-Modified",
                              ap_proxy_date_canon(p, buf));
            }
        }

        /* munge the Location and URI response headers according to
         * ProxyPassReverse
         */
        {
            const char *buf;
            if ((buf = apr_table_get(r->headers_out, "Location")) != NULL) {
                apr_table_set(r->headers_out, "Location",
                              ap_proxy_location_reverse_map(r, conf, buf));
            }
            if ((buf = apr_table_get(r->headers_out, "Content-Location")) != NULL) {
                apr_table_set(r->headers_out, "Content-Location",
                              ap_proxy_location_reverse_map(r, conf, buf));
            }
            if ((buf = apr_table_get(r->headers_out, "URI")) != NULL) {
                apr_table_set(r->headers_out, "URI",
                              ap_proxy_location_reverse_map(r, conf, buf));
            }
        }

        r->sent_bodyct = 1;
        /* Is it an HTTP/0.9 response? If so, send the extra data */
        if (backasswards) {
            apr_ssize_t cntr = len;
            e = apr_bucket_heap_create(buffer, cntr, NULL, c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, e);
        }

        /* send body - but only if a body is expected */
        if ((!r->header_only) &&                   /* not HEAD request */
            (r->status > 199) &&                   /* not any 1xx response */
            (r->status != HTTP_NO_CONTENT) &&      /* not 204 */
            (r->status != HTTP_RESET_CONTENT) &&   /* not 205 */
            (r->status != HTTP_NOT_MODIFIED)) {    /* not 304 */

            /* We need to copy the output headers and treat them as input
             * headers as well.  BUT, we need to do this before we remove
             * TE and C-L, so that they are preserved accordingly for
             * ap_http_filter to know where to end.
             */
            rp->headers_in = apr_table_copy(r->pool, r->headers_out);

            /* In order for ap_set_keepalive to work properly, we can NOT
             * have any length information stored in the output headers.
             */
            apr_table_unset(r->headers_out,"Transfer-Encoding");
            apr_table_unset(r->headers_out,"Content-Length");

            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "proxy: start body send");
             
            /*
             * if we are overriding the errors, we can't put the content
             * of the page into the brigade
             */
            if ( (conf->error_override ==0) || r->status < 400 ) {

                /* read the body, pass it to the output filters */
                int finish = FALSE;
                while (ap_get_brigade(rp->input_filters, 
                                      bb, 
                                      AP_MODE_READBYTES, 
                                      APR_BLOCK_READ, 
                                      conf->io_buffer_size) == APR_SUCCESS) {
#if DEBUGGING
                    {
                    apr_off_t readbytes;
                    apr_brigade_length(bb, 0, &readbytes);
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
                                 r->server, "proxy (PID %d): readbytes: %#x",
                                 getpid(), readbytes);
                    }
#endif
                    /* sanity check */
                    if (APR_BRIGADE_EMPTY(bb)) {
                        apr_brigade_cleanup(bb);
                        break;
                    }

                    /* found the last brigade? */
                    if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(bb))) {
                        /* if this is the last brigade, cleanup the
                         * backend connection first to prevent the
                         * backend server from hanging around waiting
                         * for a slow client to eat these bytes
                         */
                        ap_proxy_http_cleanup(r, p_conn, backend);
                        /* signal that we must leave */
                        finish = TRUE;
                    }

                    /* try send what we read */
                    if (ap_pass_brigade(r->output_filters, bb) != APR_SUCCESS) {
                        /* Ack! Phbtt! Die! User aborted! */
                        p_conn->close = 1;  /* this causes socket close below */
                        finish = TRUE;
                    }

                    /* make sure we always clean up after ourselves */
                    apr_brigade_cleanup(bb);

                    /* if we are done, leave */
                    if (TRUE == finish) {
                        break;
                    }
                }
            }
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "proxy: end body send");
        } else {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "proxy: header only");
        }
    }

    if ( conf->error_override ) {
        /* the code above this checks for 'OK' which is what the hook expects */
        if ( r->status == HTTP_OK )
            return OK;
        else  {
            /* clear r->status for override error, otherwise ErrorDocument
             * thinks that this is a recursive error, and doesn't find the
             * custom error page
             */
            int status = r->status;
            r->status = HTTP_OK;
            return status;
        }
    } else 
        return OK;
}