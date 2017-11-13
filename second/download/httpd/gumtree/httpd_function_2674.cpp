static
apr_status_t ap_proxy_http_process_response(apr_pool_t * p, request_rec *r,
                                            proxy_conn_rec *backend,
                                            conn_rec *origin,
                                            proxy_server_conf *conf,
                                            char *server_portstr) {
    conn_rec *c = r->connection;
    char buffer[HUGE_STRING_LEN];
    const char *buf;
    char keepchar;
    request_rec *rp;
    apr_bucket *e;
    apr_bucket_brigade *bb;
    int len, backasswards;
    int interim_response; /* non-zero whilst interim 1xx responses
                           * are being read. */
    int pread_len = 0;
    apr_table_t *save_table;
    int backend_broke = 0;

    bb = apr_brigade_create(p, c->bucket_alloc);

    /* Get response from the remote server, and pass it up the
     * filter chain
     */

    rp = ap_proxy_make_fake_req(origin, r);
    /* In case anyone needs to know, this is a fake request that is really a
     * response.
     */
    rp->proxyreq = PROXYREQ_RESPONSE;
    do {
        apr_brigade_cleanup(bb);

        len = ap_getline(buffer, sizeof(buffer), rp, 0);
        if (len == 0) {
            /* handle one potential stray CRLF */
            len = ap_getline(buffer, sizeof(buffer), rp, 0);
        }
        if (len <= 0) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "proxy: error reading status line from remote "
                          "server %s", backend->hostname);
            return ap_proxyerror(r, HTTP_BAD_GATEWAY,
                                 "Error reading from remote server");
        }
        /* XXX: Is this a real headers length send from remote? */
        backend->worker->s->read += len;

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
                return ap_proxyerror(r, HTTP_BAD_GATEWAY,
                apr_pstrcat(p, "Corrupt status line returned by remote "
                            "server: ", buffer, NULL));
            }
            backasswards = 0;

            keepchar = buffer[12];
            buffer[12] = '\0';
            r->status = atoi(&buffer[9]);

            if (keepchar != '\0') {
                buffer[12] = keepchar;
            } else {
                /* 2616 requires the space in Status-Line; the origin
                 * server may have sent one but ap_rgetline_core will
                 * have stripped it. */
                buffer[12] = ' ';
                buffer[13] = '\0';
            }
            r->status_line = apr_pstrdup(p, &buffer[9]);


            /* read the headers. */
            /* N.B. for HTTP/1.0 clients, we have to fold line-wrapped headers*/
            /* Also, take care with headers with multiple occurences. */

            /* First, tuck away all already existing cookies */
            save_table = apr_table_make(r->pool, 2);
            apr_table_do(addit_dammit, save_table, r->headers_out,
                         "Set-Cookie", NULL);

            /* shove the headers direct into r->headers_out */
            ap_proxy_read_headers(r, rp, buffer, sizeof(buffer), origin,
                                  &pread_len);

            if (r->headers_out == NULL) {
                ap_log_error(APLOG_MARK, APLOG_WARNING, 0,
                             r->server, "proxy: bad HTTP/%d.%d header "
                             "returned by %s (%s)", major, minor, r->uri,
                             r->method);
                backend->close += 1;
                /*
                 * ap_send_error relies on a headers_out to be present. we
                 * are in a bad position here.. so force everything we send out
                 * to have nothing to do with the incoming packet
                 */
                r->headers_out = apr_table_make(r->pool,1);
                r->status = HTTP_BAD_GATEWAY;
                r->status_line = "bad gateway";
                return r->status;
            }

            /* Now, add in the just read cookies */
            apr_table_do(addit_dammit, save_table, r->headers_out,
                         "Set-Cookie", NULL);

            /* and now load 'em all in */
            if (!apr_is_empty_table(save_table)) {
                apr_table_unset(r->headers_out, "Set-Cookie");
                r->headers_out = apr_table_overlay(r->pool,
                                                   r->headers_out,
                                                   save_table);
            }

            /* can't have both Content-Length and Transfer-Encoding */
            if (apr_table_get(r->headers_out, "Transfer-Encoding")
                    && apr_table_get(r->headers_out, "Content-Length")) {
                /*
                 * 2616 section 4.4, point 3: "if both Transfer-Encoding
                 * and Content-Length are received, the latter MUST be
                 * ignored";
                 *
                 * To help mitigate HTTP Splitting, unset Content-Length
                 * and shut down the backend server connection
                 * XXX: We aught to treat such a response as uncachable
                 */
                apr_table_unset(r->headers_out, "Content-Length");
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                             "proxy: server %s returned Transfer-Encoding"
                             " and Content-Length", backend->hostname);
                backend->close += 1;
            }

            /* strip connection listed hop-by-hop headers from response */
            backend->close += ap_proxy_liststr(apr_table_get(r->headers_out,
                                                             "Connection"),
                                              "close");
            ap_proxy_clear_connection(p, r->headers_out);
            if ((buf = apr_table_get(r->headers_out, "Content-Type"))) {
                ap_set_content_type(r, apr_pstrdup(p, buf));
            }
            ap_proxy_pre_http_request(origin,rp);

            /* handle Via header in response */
            if (conf->viaopt != via_off && conf->viaopt != via_block) {
                const char *server_name = ap_get_server_name(r);
                /* If USE_CANONICAL_NAME_OFF was configured for the proxy virtual host,
                 * then the server name returned by ap_get_server_name() is the
                 * origin server name (which does make too much sense with Via: headers)
                 * so we use the proxy vhost's name instead.
                 */
                if (server_name == r->hostname)
                    server_name = r->server->server_hostname;
                /* create a "Via:" response header entry and merge it */
                apr_table_mergen(r->headers_out, "Via",
                                 (conf->viaopt == via_full)
                                     ? apr_psprintf(p, "%d.%d %s%s (%s)",
                                           HTTP_VERSION_MAJOR(r->proto_num),
                                           HTTP_VERSION_MINOR(r->proto_num),
                                           server_name,
                                           server_portstr,
                                           AP_SERVER_BASEVERSION)
                                     : apr_psprintf(p, "%d.%d %s%s",
                                           HTTP_VERSION_MAJOR(r->proto_num),
                                           HTTP_VERSION_MINOR(r->proto_num),
                                           server_name,
                                           server_portstr)
                );
            }

            /* cancel keepalive if HTTP/1.0 or less */
            if ((major < 1) || (minor < 1)) {
                backend->close += 1;
                origin->keepalive = AP_CONN_CLOSE;
            }
        } else {
            /* an http/0.9 response */
            backasswards = 1;
            r->status = 200;
            r->status_line = "200 OK";
            backend->close += 1;
        }

        interim_response = ap_is_HTTP_INFO(r->status);
        if (interim_response) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, NULL,
                         "proxy: HTTP: received interim %d response",
                         r->status);
        }
        /* Moved the fixups of Date headers and those affected by
         * ProxyPassReverse/etc from here to ap_proxy_read_headers
         */

        if ((r->status == 401) && (conf->error_override)) {
            const char *buf;
            const char *wa = "WWW-Authenticate";
            if ((buf = apr_table_get(r->headers_out, wa))) {
                apr_table_set(r->err_headers_out, wa, buf);
            } else {
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                             "proxy: origin server sent 401 without WWW-Authenticate header");
            }
        }

        r->sent_bodyct = 1;
        /*
         * Is it an HTTP/0.9 response or did we maybe preread the 1st line of
         * the response? If so, load the extra data. These are 2 mutually
         * exclusive possibilities, that just happen to require very
         * similar behavior.
         */
        if (backasswards || pread_len) {
            apr_ssize_t cntr = (apr_ssize_t)pread_len;
            if (backasswards) {
                /*@@@FIXME:
                 * At this point in response processing of a 0.9 response,
                 * we don't know yet whether data is binary or not.
                 * mod_charset_lite will get control later on, so it cannot
                 * decide on the conversion of this buffer full of data.
                 * However, chances are that we are not really talking to an
                 * HTTP/0.9 server, but to some different protocol, therefore
                 * the best guess IMHO is to always treat the buffer as "text/x":
                 */
                ap_xlate_proto_to_ascii(buffer, len);
                cntr = (apr_ssize_t)len;
            }
            e = apr_bucket_heap_create(buffer, cntr, NULL, c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, e);
        }

        /* send body - but only if a body is expected */
        if ((!r->header_only) &&                   /* not HEAD request */
            !interim_response &&                   /* not any 1xx response */
            (r->status != HTTP_NO_CONTENT) &&      /* not 204 */
            (r->status != HTTP_NOT_MODIFIED)) {    /* not 304 */

            /* We need to copy the output headers and treat them as input
             * headers as well.  BUT, we need to do this before we remove
             * TE, so that they are preserved accordingly for
             * ap_http_filter to know where to end.
             */
            rp->headers_in = apr_table_copy(r->pool, r->headers_out);

            apr_table_unset(r->headers_out,"Transfer-Encoding");

            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "proxy: start body send");

            /*
             * if we are overriding the errors, we can't put the content
             * of the page into the brigade
             */
            if (!conf->error_override || ap_is_HTTP_SUCCESS(r->status)) {
                /* read the body, pass it to the output filters */
                apr_read_type_e mode = APR_NONBLOCK_READ;
                int finish = FALSE;

                do {
                    apr_off_t readbytes;
                    apr_status_t rv;

                    rv = ap_get_brigade(rp->input_filters, bb,
                                        AP_MODE_READBYTES, mode,
                                        conf->io_buffer_size);

                    /* ap_get_brigade will return success with an empty brigade
                     * for a non-blocking read which would block: */
                    if (APR_STATUS_IS_EAGAIN(rv)
                        || (rv == APR_SUCCESS && APR_BRIGADE_EMPTY(bb))) {
                        /* flush to the client and switch to blocking mode */
                        e = apr_bucket_flush_create(c->bucket_alloc);
                        APR_BRIGADE_INSERT_TAIL(bb, e);
                        if (ap_pass_brigade(r->output_filters, bb)
                            || c->aborted) {
                            backend->close = 1;
                            break;
                        }
                        apr_brigade_cleanup(bb);
                        mode = APR_BLOCK_READ;
                        continue;
                    }
                    else if (rv == APR_EOF) {
                        break;
                    }
                    else if (rv != APR_SUCCESS) {
                        /* In this case, we are in real trouble because
                         * our backend bailed on us. Pass along a 502 error
                         * error bucket
                         */
                        ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, c,
                                      "proxy: error reading response");
                        ap_proxy_backend_broke(r, bb);
                        ap_pass_brigade(r->output_filters, bb);
                        backend_broke = 1;
                        backend->close = 1;
                        break;
                    }
                    /* next time try a non-blocking read */
                    mode = APR_NONBLOCK_READ;

                    apr_brigade_length(bb, 0, &readbytes);
                    backend->worker->s->read += readbytes;
#if DEBUGGING
                    {
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
                        /* signal that we must leave */
                        finish = TRUE;
                    }

                    /* try send what we read */
                    if (ap_pass_brigade(r->output_filters, bb) != APR_SUCCESS
                        || c->aborted) {
                        /* Ack! Phbtt! Die! User aborted! */
                        backend->close = 1;  /* this causes socket close below */
                        finish = TRUE;
                    }

                    /* make sure we always clean up after ourselves */
                    apr_brigade_cleanup(bb);

                } while (!finish);
            }
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "proxy: end body send");
        }
        else if (!interim_response) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "proxy: header only");

            /* Pass EOS bucket down the filter chain. */
            e = apr_bucket_eos_create(c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, e);
            if (ap_pass_brigade(r->output_filters, bb) != APR_SUCCESS
                || c->aborted) {
                /* Ack! Phbtt! Die! User aborted! */
                backend->close = 1;  /* this causes socket close below */
            }

            apr_brigade_cleanup(bb);
        }
    } while (interim_response);

    /* If our connection with the client is to be aborted, return DONE. */
    if (c->aborted || backend_broke) {
        return DONE;
    }

    if (conf->error_override) {
        /* the code above this checks for 'OK' which is what the hook expects */
        if (ap_is_HTTP_SUCCESS(r->status))
            return OK;
        else {
            /* clear r->status for override error, otherwise ErrorDocument
             * thinks that this is a recursive error, and doesn't find the
             * custom error page
             */
            int status = r->status;
            r->status = HTTP_OK;
            /* Discard body, if one is expected */
            if ((status != HTTP_NO_CONTENT) && /* not 204 */
                (status != HTTP_NOT_MODIFIED)) { /* not 304 */
               ap_discard_request_body(rp);
           }
            return status;
        }
    } else
        return OK;
}