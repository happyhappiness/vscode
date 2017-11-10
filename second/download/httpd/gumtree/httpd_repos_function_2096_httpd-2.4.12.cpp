static apr_status_t dispatch(proxy_conn_rec *conn, proxy_dir_conf *conf,
                             request_rec *r, apr_pool_t *setaside_pool,
                             apr_uint16_t request_id,
                             const char **err)
{
    apr_bucket_brigade *ib, *ob;
    int seen_end_of_headers = 0, done = 0, ignore_body = 0;
    apr_status_t rv = APR_SUCCESS;
    int script_error_status = HTTP_OK;
    conn_rec *c = r->connection;
    struct iovec vec[2];
    ap_fcgi_header header;
    unsigned char farray[AP_FCGI_HEADER_LEN];
    apr_pollfd_t pfd;
    int header_state = HDR_STATE_READING_HEADERS;
    char stack_iobuf[AP_IOBUFSIZE];
    apr_size_t iobuf_size = AP_IOBUFSIZE;
    char *iobuf = stack_iobuf;

    *err = NULL;
    if (conn->worker->s->io_buffer_size_set) {
        iobuf_size = conn->worker->s->io_buffer_size;
        iobuf = apr_palloc(r->pool, iobuf_size);
    }

    pfd.desc_type = APR_POLL_SOCKET;
    pfd.desc.s = conn->sock;
    pfd.p = r->pool;
    pfd.reqevents = APR_POLLIN | APR_POLLOUT;

    ib = apr_brigade_create(r->pool, c->bucket_alloc);
    ob = apr_brigade_create(r->pool, c->bucket_alloc);

    while (! done) {
        apr_interval_time_t timeout;
        apr_size_t len;
        int n;

        /* We need SOME kind of timeout here, or virtually anything will
         * cause timeout errors. */
        apr_socket_timeout_get(conn->sock, &timeout);

        rv = apr_poll(&pfd, 1, &n, timeout);
        if (rv != APR_SUCCESS) {
            if (APR_STATUS_IS_EINTR(rv)) {
                continue;
            }
            *err = "polling";
            break;
        }

        if (pfd.rtnevents & APR_POLLOUT) {
            apr_size_t to_send, writebuflen;
            int last_stdin = 0;
            char *iobuf_cursor;

            rv = ap_get_brigade(r->input_filters, ib,
                                AP_MODE_READBYTES, APR_BLOCK_READ,
                                iobuf_size);
            if (rv != APR_SUCCESS) {
                *err = "reading input brigade";
                break;
            }

            if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(ib))) {
                last_stdin = 1;
            }

            writebuflen = iobuf_size;

            rv = apr_brigade_flatten(ib, iobuf, &writebuflen);

            apr_brigade_cleanup(ib);

            if (rv != APR_SUCCESS) {
                *err = "flattening brigade";
                break;
            }

            to_send = writebuflen;
            iobuf_cursor = iobuf;
            while (to_send > 0) {
                int nvec = 0;
                apr_size_t write_this_time;

                write_this_time =
                    to_send < AP_FCGI_MAX_CONTENT_LEN ? to_send : AP_FCGI_MAX_CONTENT_LEN;

                ap_fcgi_fill_in_header(&header, AP_FCGI_STDIN, request_id,
                                       (apr_uint16_t)write_this_time, 0);
                ap_fcgi_header_to_array(&header, farray);

                vec[nvec].iov_base = (void *)farray;
                vec[nvec].iov_len = sizeof(farray);
                ++nvec;
                if (writebuflen) {
                    vec[nvec].iov_base = iobuf_cursor;
                    vec[nvec].iov_len = write_this_time;
                    ++nvec;
                }

                rv = send_data(conn, vec, nvec, &len);
                if (rv != APR_SUCCESS) {
                    *err = "sending stdin";
                    break;
                }

                to_send -= write_this_time;
                iobuf_cursor += write_this_time;
            }
            if (rv != APR_SUCCESS) {
                break;
            }

            if (last_stdin) {
                pfd.reqevents = APR_POLLIN; /* Done with input data */

                /* signal EOF (empty FCGI_STDIN) */
                ap_fcgi_fill_in_header(&header, AP_FCGI_STDIN, request_id,
                                       0, 0);
                ap_fcgi_header_to_array(&header, farray);

                vec[0].iov_base = (void *)farray;
                vec[0].iov_len = sizeof(farray);

                rv = send_data(conn, vec, 1, &len);
                if (rv != APR_SUCCESS) {
                    *err = "sending empty stdin";
                    break;
                }
            }
        }

        if (pfd.rtnevents & APR_POLLIN) {
            apr_size_t readbuflen;
            apr_uint16_t clen, rid;
            apr_bucket *b;
            unsigned char plen;
            unsigned char type, version;

            /* First, we grab the header... */
            rv = get_data_full(conn, (char *) farray, AP_FCGI_HEADER_LEN);
            if (rv != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01067)
                              "Failed to read FastCGI header");
                break;
            }

#ifdef FCGI_DUMP_HEADERS
            ap_log_rdata(APLOG_MARK, APLOG_DEBUG, r, "FastCGI header",
                         farray, AP_FCGI_HEADER_LEN, 0);
#endif

            ap_fcgi_header_fields_from_array(&version, &type, &rid,
                                             &clen, &plen, farray);

            if (version != AP_FCGI_VERSION_1) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01068)
                              "Got bogus version %d", (int)version);
                rv = APR_EINVAL;
                break;
            }

            if (rid != request_id) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01069)
                              "Got bogus rid %d, expected %d",
                              rid, request_id);
                rv = APR_EINVAL;
                break;
            }

recv_again:
            if (clen > iobuf_size) {
                readbuflen = iobuf_size;
            } else {
                readbuflen = clen;
            }

            /* Now get the actual data.  Yes it sucks to do this in a second
             * recv call, this will eventually change when we move to real
             * nonblocking recv calls. */
            if (readbuflen != 0) {
                rv = get_data(conn, iobuf, &readbuflen);
                if (rv != APR_SUCCESS) {
                    *err = "reading response body";
                    break;
                }
            }

            switch (type) {
            case AP_FCGI_STDOUT:
                if (clen != 0) {
                    b = apr_bucket_transient_create(iobuf,
                                                    readbuflen,
                                                    c->bucket_alloc);

                    APR_BRIGADE_INSERT_TAIL(ob, b);

                    if (! seen_end_of_headers) {
                        int st = handle_headers(r, &header_state,
                                                iobuf, readbuflen);

                        if (st == 1) {
                            int status;
                            seen_end_of_headers = 1;

                            status = ap_scan_script_header_err_brigade_ex(r, ob,
                                NULL, APLOG_MODULE_INDEX);
                            /* suck in all the rest */
                            if (status != OK) {
                                apr_bucket *tmp_b;
                                apr_brigade_cleanup(ob);
                                tmp_b = apr_bucket_eos_create(c->bucket_alloc);
                                APR_BRIGADE_INSERT_TAIL(ob, tmp_b);
                                r->status = status;
                                ap_pass_brigade(r->output_filters, ob);
                                if (status == HTTP_NOT_MODIFIED) {
                                    /* The 304 response MUST NOT contain
                                     * a message-body, ignore it. */
                                    ignore_body = 1;
                                }
                                else {
                                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01070)
                                                    "Error parsing script headers");
                                    rv = APR_EINVAL;
                                }
                                break;
                            }

                            if (conf->error_override &&
                                ap_is_HTTP_ERROR(r->status)) {
                                /*
                                 * set script_error_status to discard
                                 * everything after the headers
                                 */
                                script_error_status = r->status;
                                /*
                                 * prevent ap_die() from treating this as a
                                 * recursive error, initially:
                                 */
                                r->status = HTTP_OK;
                            }

                            if (script_error_status == HTTP_OK
                                && !APR_BRIGADE_EMPTY(ob) && !ignore_body) {
                                /* Send the part of the body that we read while
                                 * reading the headers.
                                 */
                                rv = ap_pass_brigade(r->output_filters, ob);
                                if (rv != APR_SUCCESS) {
                                    *err = "passing brigade to output filters";
                                    break;
                                }
                            }
                            apr_brigade_cleanup(ob);

                            apr_pool_clear(setaside_pool);
                        }
                        else {
                            /* We're still looking for the end of the
                             * headers, so this part of the data will need
                             * to persist. */
                            apr_bucket_setaside(b, setaside_pool);
                        }
                    } else {
                        /* we've already passed along the headers, so now pass
                         * through the content.  we could simply continue to
                         * setaside the content and not pass until we see the
                         * 0 content-length (below, where we append the EOS),
                         * but that could be a huge amount of data; so we pass
                         * along smaller chunks
                         */
                        if (script_error_status == HTTP_OK && !ignore_body) {
                            rv = ap_pass_brigade(r->output_filters, ob);
                            if (rv != APR_SUCCESS) {
                                *err = "passing brigade to output filters";
                                break;
                            }
                        }
                        apr_brigade_cleanup(ob);
                    }

                    /* If we didn't read all the data, go back and get the
                     * rest of it. */
                    if (clen > readbuflen) {
                        clen -= readbuflen;
                        goto recv_again;
                    }
                } else {
                    /* XXX what if we haven't seen end of the headers yet? */

                    if (script_error_status == HTTP_OK) {
                        b = apr_bucket_eos_create(c->bucket_alloc);
                        APR_BRIGADE_INSERT_TAIL(ob, b);
                        rv = ap_pass_brigade(r->output_filters, ob);
                        if (rv != APR_SUCCESS) {
                            *err = "passing brigade to output filters";
                            break;
                        }
                    }

                    /* XXX Why don't we cleanup here?  (logic from AJP) */
                }
                break;

            case AP_FCGI_STDERR:
                /* TODO: Should probably clean up this logging a bit... */
                if (clen) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01071)
                                  "Got error '%.*s'", (int)readbuflen, iobuf);
                }

                if (clen > readbuflen) {
                    clen -= readbufle