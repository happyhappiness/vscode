
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

            ap_fcgi_fill_in_header(&header, AP_FCGI_STDIN, request_id,
                                   (apr_uint16_t) writebuflen, 0);
            ap_fcgi_header_to_array(&header, farray);

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

                if (writebuflen) { /* empty AP_FCGI_STDIN not already sent? */
                    ap_fcgi_fill_in_header(&header, AP_FCGI_STDIN, request_id,
                                           0, 0);
                    ap_fcgi_header_to_array(&header, farray);

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
            apr_uint16_t clen, rid;
            apr_bucket *b;
            unsigned char plen;
            unsigned char type, version;

            memset(readbuf, 0, sizeof(readbuf));
            memset(farray, 0, sizeof(farray));

            /* First, we grab the header... */
            rv = get_data_full(conn, (char *) farray, AP_FCGI_HEADER_LEN);
            if (rv != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01067)
                              "Failed to read FastCGI header");
                break;
