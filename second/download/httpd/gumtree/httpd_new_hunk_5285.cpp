
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
