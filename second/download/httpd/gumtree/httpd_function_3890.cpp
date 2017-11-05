static apr_status_t dispatch(proxy_conn_rec *conn, request_rec *r,
                             int request_id)
{
    apr_bucket_brigade *ib, *ob;
    int seen_end_of_headers = 0, done = 0;
    apr_status_t rv = APR_SUCCESS;
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
        apr_interval_time_t timeout = conn->worker->timeout;
        apr_size_t len;
        int n;

        /* We need SOME kind of timeout here, or virtually anything will
         * cause timeout errors. */
        if (! conn->worker->timeout_set) {
            timeout = apr_time_from_sec(30);
        }

        rv = apr_poll(&pfd, 1, &n, timeout);
        if (rv != APR_SUCCESS) {
            break;
        }

        if (pfd.rtnevents & APR_POLLOUT) {
            char writebuf[AP_IOBUFSIZE];
            apr_size_t writebuflen;
            int last_stdin = 0;

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

            vec[0].iov_base = farray;
            vec[0].iov_len = sizeof(farray);
            vec[1].iov_base = writebuf;
            vec[1].iov_len = writebuflen;

            rv = send_data(conn, vec, 2, &len, 0);
            if (rv != APR_SUCCESS) {
                break;
            }

            if (last_stdin) {
                pfd.reqevents = APR_POLLIN; /* Done with input data */

                fill_in_header(&header, FCGI_STDIN, request_id, 0, 0);
                fcgi_header_to_array(&header, farray);

                vec[0].iov_base = farray;
                vec[0].iov_len = sizeof(farray);

                rv = send_data(conn, vec, 1, &len, 1);
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
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                             "proxy: FCGI: Failed to read entire header "
                             "got %" APR_SIZE_T_FMT " wanted %d", 
                             readbuflen, FCGI_HEADER_LEN);
                rv = APR_EINVAL;
                break;
            }

            fcgi_header_from_array(&header, farray);

            if (header.version != FCGI_VERSION) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                             "proxy: FCGI: Got bogus version %d",
                             (int) header.version);
                rv = APR_EINVAL;
                break;
            }

            type = header.type;

            rid = header.requestIdB1 << 8;
            rid |= header.requestIdB0;

            if (rid != request_id) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                             "proxy: FCGI: Got bogus rid %d, expected %d",
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
                        int st = handle_headers(r, &header_state, readbuf, ob);

                        if (st == 1) {
                            seen_end_of_headers = 1;

                            rv = ap_pass_brigade(r->output_filters, ob);
                            if (rv != APR_SUCCESS) {
                                break;
                            }

                            apr_brigade_cleanup(ob);

                            apr_pool_clear(setaside_pool);
                        }
                        else if (st == -1) {
                            rv = APR_EINVAL;
                            break;
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
                        rv = ap_pass_brigade(r->output_filters, ob);
                        if (rv != APR_SUCCESS) {
                            break;
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

                    b = apr_bucket_eos_create(c->bucket_alloc);

                    APR_BRIGADE_INSERT_TAIL(ob, b);

                    rv = ap_pass_brigade(r->output_filters, ob);
                    if (rv != APR_SUCCESS) {
                        break;
                    }

                    /* XXX Why don't we cleanup here?  (logic from AJP) */
                }
                break;

            case FCGI_STDERR:
                /* TODO: Should probably clean up this logging a bit... */
                if (clen) {
                    ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                                 "proxy: FCGI: Got error '%s'", readbuf);
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
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                             "proxy: FCGI: Got bogus record %d", type);
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

    return rv;
}