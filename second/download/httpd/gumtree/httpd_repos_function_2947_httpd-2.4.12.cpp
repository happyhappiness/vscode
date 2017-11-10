static apr_status_t handle_response(const fcgi_provider_conf *conf,
                                    request_rec *r, apr_socket_t *s,
                                    apr_pool_t *temp_pool,
                                    apr_uint16_t request_id,
                                    char *rspbuf,
                                    apr_size_t *rspbuflen)
{
    apr_bucket *b;
    apr_bucket_brigade *ob;
    apr_size_t orspbuflen = 0;
    apr_status_t rv = APR_SUCCESS;
    const char *fn = "handle_response";
    int header_state = HDR_STATE_READING_HEADERS;
    int seen_end_of_headers = 0, done = 0;

    if (rspbuflen) {
        orspbuflen = *rspbuflen;
        *rspbuflen = 0; /* unless we actually read something */
    }

    ob = apr_brigade_create(r->pool, r->connection->bucket_alloc);

    while (!done && rv == APR_SUCCESS) { /* Keep reading FastCGI records until
                                          * we get AP_FCGI_END_REQUEST (done)
                                          * or an error occurs.
                                          */
        apr_size_t readbuflen;
        apr_uint16_t clen;
        apr_uint16_t rid;
        char readbuf[AP_IOBUFSIZE + 1];
        unsigned char farray[AP_FCGI_HEADER_LEN];
        unsigned char plen;
        unsigned char type;
        unsigned char version;

        rv = recv_data_full(conf, r, s, (char *)farray, AP_FCGI_HEADER_LEN);
        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          APLOGNO(02501) "%s: Error occurred before reading "
                          "entire header", fn);
            break;
        }

        ap_fcgi_header_fields_from_array(&version, &type, &rid, &clen, &plen,
                                         farray);

        if (version != AP_FCGI_VERSION_1) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          APLOGNO(02502) "%s: Got bogus FastCGI header "
                          "version %d", fn, (int)version);
            rv = APR_EINVAL;
            break;
        }

        if (rid != request_id) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          APLOGNO(02503) "%s: Got bogus FastCGI header "
                          "request id %d, expected %d",
                          fn, rid, request_id);
            rv = APR_EINVAL;
            break;
        }

    recv_again: /* if we need to keep reading more of a record's content */

        if (clen > sizeof(readbuf) - 1) {
            readbuflen = sizeof(readbuf) - 1;
        } else {
            readbuflen = clen;
        }

        /*
         * Now get the actual content of the record.
         */
        if (readbuflen != 0) {
            rv = recv_data(conf, r, s, readbuf, &readbuflen);
            if (rv != APR_SUCCESS) {
                break;
            }
            readbuf[readbuflen] = '\0';
        }

        switch (type) {
        case AP_FCGI_STDOUT: /* Response headers and optional body */
            if (clen != 0) {
                b = apr_bucket_transient_create(readbuf,
                                                readbuflen,
                                                r->connection->bucket_alloc);

                APR_BRIGADE_INSERT_TAIL(ob, b);

                if (!seen_end_of_headers) {
                    int st = handle_headers(r, &header_state,
                                            readbuf, readbuflen);

                    if (st == 1) {
                        int status;

                        seen_end_of_headers = 1;

                        status =
                            ap_scan_script_header_err_brigade_ex(r, ob,
                                                                 NULL, 
                                                                 APLOG_MODULE_INDEX);
                        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                      APLOGNO(02504) "%s: script header "
                                      "parsing -> %d/%d",
                                      fn, status, 