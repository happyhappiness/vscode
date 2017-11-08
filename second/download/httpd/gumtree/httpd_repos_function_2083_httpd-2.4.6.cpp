static apr_status_t dispatch(proxy_conn_rec *conn, proxy_dir_conf *conf,
                             request_rec *r, int request_id)
{
    apr_bucket_brigade *ib, *ob;
    int seen_end_of_headers = 0, done = 0;
    apr_status_t rv = APR_SUCCESS;
    int script_error_status = HTTP_OK;
    conn_rec *c = r->connection;
    struct iovec vec[2];
    fcgi_header header;
    unsigned char farray[FCGI_HEADER_LEN];
    apr_pollfd_t pfd;
    int header_state = HDR_STATE_READING_HEADERS;
    apr_pool_t *setaside_pool;

    apr_pool_create(&setaside_pool, r->pool);

    pfd.desc_type = APR_POLL_SOCKET;
    pfd.desc.s = conn->sock;
    pfd.p = r->pool;
    pfd.reqevents = APR_POLLIN | APR_POLLOUT;

    ib = apr_brigade_create(r->pool, c->bucket_alloc);
    ob = apr_brigade_create(r->pool, c->bucket_alloc);

    while (! done) {
        apr_interval_time_t timeout = conn->worker->s->timeout;
        apr_size_t len;
        int n;

        /* We need SOME kind of timeout here, or virtually anything will
         * cause timeout errors. */
        if (! conn->worker->s->timeout_set) {
            timeout = apr_time_from_sec(30);
        }

        rv = apr_poll(&pfd, 1, &n, timeout);
        if (rv != APR_SUCCESS) {
            if (APR_STATUS_IS_EINTR(rv)) {
                continue;
            }
            break;
        }

        if (pfd.rtnevents & APR_POLLOUT) {
            char writebuf[AP_IOBUFSIZE];
            apr_size_t writebuflen;
            int last_stdin = 0;
            int nvec = 0;

            rv = ap_get_brigade(r->input_filters, ib,
                                AP_MODE_READBYTES, APR_BLOCK_READ,
                                sizeof(writebuf));
            if (rv != APR_SUCCESS) {
                break;
            }

            if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(ib))) {
                last_stdin = 1;
            }

            writebuflen = sizeof(writebuf);

            rv = apr_brigade_flatten(ib, writebuf, &writebuflen);

            apr_brigade_cleanup(ib);

            if (rv != APR_SUCCESS) {
                break;
            }

            fill_in_header(&header, FCGI_STDIN, request_id,
                           (apr_uint16_t) writebuflen, 0);
            fcgi_header_to_array(&header, farray);

            vec[nvec].iov_base = (void *)farray;
            vec[nvec].iov_len = sizeof(farray);
            ++nvec;
            if (writebuflen) {
                vec[nvec].iov_base = writebuf;
                vec[nvec].iov_len = writebuflen;
                ++nvec;
            }

            rv = send_data(conn, vec, nvec, &len, 0);
            if (rv != APR_SUCCESS) {
                break;
            }

            if (last_stdin) {
                pfd.reqevents = APR_POLLIN; /* Done with input data */

                if (writebuflen) { /* empty FCGI_STDIN not already sent? */
                    fill_in_header(&header, FCGI_STDIN, request_id, 0, 0);
                    fcgi_header_to_array(&header, farray);

                    vec[0].iov_base = (void *)farray;
                    vec[0].iov_len = sizeof(farray);

                    rv = send_data(conn, vec, 1, &len, 1);
                }
            }
        }

        if (pfd.rtnevents & APR_POLLIN) {
            /* readbuf has one byte on the end that is always 0, so it's
             * able to work with a strstr when we search for the end of
             * the headers, even if we fill the entire length in the recv. */
            char readbuf[AP_IOBUFSIZE + 1];
            apr_size_t readbuflen;
            apr_size_t clen;
            int rid, type;
            apr_bucket *b;
            char plen;

            memset(readbuf, 0, sizeof(readbuf));
            memset(farray, 0, sizeof(farray));

            /* First, we grab the header... */
            readbuflen = FCGI_HEADER_LEN;

            rv = get_data(conn, (char *) farray, &readbuflen);
            if (rv != APR_SUCCESS) {
                break;
            }

            dump_header_to_log(r, farray, readbuflen);

            if (readbuflen != FCGI_HEADER_LEN) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01067)
                              "Failed to read entire header "
                              "got %" APR_SIZE_T_FMT " wanted %d",
                              readbuflen, FCGI_HEADER_LEN);
                rv = APR_EINVAL;
                break;
            }

            fcgi_header_from_array(&header, farray);

            if (header.version != FCGI_VERSION) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01068)
                              "Got bogus version %d", (int) header.version);
                rv = APR_EINVAL;
                break;
            }

            type = header.type;

            rid = header.requestIdB1 << 8;
            rid |= header.requestIdB0;

            if (rid != request_id) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01069)
                              "Got bogus rid %d, expected %d",
                              rid, request_id);
                rv = APR_EINVAL;
                break;
            }

            clen = header.contentLengthB1 << 8;
            clen |= header.contentLengthB0;

            plen = header.paddingLength;

recv_again:
            if (clen > sizeof(readbuf) - 1) {
                readbuflen = sizeof(readbuf) - 1;
            } else {
                readbuflen = clen;
            }

            /* Now get the actual data.  Yes it sucks to do this in a second
             * recv call, this will eventually change when we move to real
             * nonblocking recv calls. */
            if (readbuflen != 0) {
                rv = get_data(conn, readbuf, &readbuflen);
                if (rv != APR_SUCCESS) {
                    break;
                }
                readbuf[readbuflen] = 0;
            }

            switch (type) {
            case FCGI_STDOUT:
                if (clen != 0) {
                    b = apr_bucket_transient_create(readbuf,
                                                    readbuflen,
                                                    c->bucket_alloc);

                    APR_BRIGADE_INSERT_TAIL(ob, b);

                    if (! seen_end_of_headers) {
                        int st = handle_headers(r, &header_state, readbuf);

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
                                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01070)
                                              "Error parsing script headers");
                                rv = APR_EINVAL;
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

                            if (script_error_status == HTTP_OK) {
                                rv = ap_pass_brigade(r->output_filters, ob);
                                if (rv != APR_SUCCESS) {
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
                        if (script_error_status == HTTP_OK) {
                            rv = ap_pass_brigade(r->output_filters, ob);
                            if (rv != APR_SUCCESS) {
                                break;
                            }
                        }
                        apr_brigade_cleanup(ob);
                    }

                    /* If we didn't read all the data go back and get the
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
                            break;
                        }
                    }

                    /* XXX Why don't we cleanup here?  (logic from AJP) */
                }
                break;

            case FCGI_STDERR:
                /* TODO: Should probably clean up this logging a bit... */
                if (clen) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01071)
                                  "Got error '%s'", readbuf);
                }

                if (clen > readbuflen) {
                    clen -= readbuflen;
                    goto recv_again;
                }
                break;

            case FCGI_END_REQUEST:
                done = 1;
                break;

            default:
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01072)
                              "Got bogus record %d", type);
                break;
            }

            if (plen) {
                readbuflen = plen;

                rv = get_data(conn, readbuf, &readbuflen);
                if (rv != APR_SUCCESS) {
                    break;
                }
            }
        }
    }

    apr_brigade_destroy(ib);
    apr_brigade_destroy(ob);

    if (script_error_status != HTTP_OK) {
        ap_die(script_error_status, r); /* send ErrorDocument */
    }

    return rv;
}