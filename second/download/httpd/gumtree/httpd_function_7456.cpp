static int stream_reqbody_chunked(apr_pool_t *p,
                                           request_rec *r,
                                           proxy_conn_rec *p_conn,
                                           conn_rec *origin,
                                           apr_bucket_brigade *header_brigade,
                                           apr_bucket_brigade *input_brigade)
{
    int seen_eos = 0, rv = OK;
    apr_size_t hdr_len;
    apr_off_t bytes;
    apr_status_t status;
    apr_bucket_alloc_t *bucket_alloc = r->connection->bucket_alloc;
    apr_bucket_brigade *bb;
    apr_bucket *e;

    add_te_chunked(p, bucket_alloc, header_brigade);
    terminate_headers(bucket_alloc, header_brigade);

    while (!APR_BUCKET_IS_EOS(APR_BRIGADE_FIRST(input_brigade)))
    {
        char chunk_hdr[20];  /* must be here due to transient bucket. */

        /* If this brigade contains EOS, either stop or remove it. */
        if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(input_brigade))) {
            seen_eos = 1;

            /* We can't pass this EOS to the output_filters. */
            e = APR_BRIGADE_LAST(input_brigade);
            apr_bucket_delete(e);
        }

        apr_brigade_length(input_brigade, 1, &bytes);

        hdr_len = apr_snprintf(chunk_hdr, sizeof(chunk_hdr),
                               "%" APR_UINT64_T_HEX_FMT CRLF,
                               (apr_uint64_t)bytes);

        ap_xlate_proto_to_ascii(chunk_hdr, hdr_len);
        e = apr_bucket_transient_create(chunk_hdr, hdr_len,
                                        bucket_alloc);
        APR_BRIGADE_INSERT_HEAD(input_brigade, e);

        /*
         * Append the end-of-chunk CRLF
         */
        e = apr_bucket_immortal_create(ASCII_CRLF, 2, bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(input_brigade, e);

        if (header_brigade) {
            /* we never sent the header brigade, so go ahead and
             * take care of that now
             */
            bb = header_brigade;

            /*
             * Save input_brigade in bb brigade. (At least) in the SSL case
             * input_brigade contains transient buckets whose data would get
             * overwritten during the next call of ap_get_brigade in the loop.
             * ap_save_brigade ensures these buckets to be set aside.
             * Calling ap_save_brigade with NULL as filter is OK, because
             * bb brigade already has been created and does not need to get
             * created by ap_save_brigade.
             */
            status = ap_save_brigade(NULL, &bb, &input_brigade, p);
            if (status != APR_SUCCESS) {
                return HTTP_INTERNAL_SERVER_ERROR;
            }

            header_brigade = NULL;
        }
        else {
            bb = input_brigade;
        }

        /* The request is flushed below this loop with chunk EOS header */
        rv = ap_proxy_pass_brigade(bucket_alloc, r, p_conn, origin, bb, 0);
        if (rv != OK) {
            return rv;
        }

        if (seen_eos) {
            break;
        }

        status = ap_get_brigade(r->input_filters, input_brigade,
                                AP_MODE_READBYTES, APR_BLOCK_READ,
                                HUGE_STRING_LEN);

        if (status != APR_SUCCESS) {
            conn_rec *c = r->connection;
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(02608)
                          "read request body failed to %pI (%s)"
                          " from %s (%s)", p_conn->addr,
                          p_conn->hostname ? p_conn->hostname: "",
                          c->client_ip, c->remote_host ? c->remote_host: "");
            return HTTP_BAD_REQUEST;
        }
    }

    if (header_brigade) {
        /* we never sent the header brigade because there was no request body;
         * send it now
         */
        bb = header_brigade;
    }
    else {
        if (!APR_BRIGADE_EMPTY(input_brigade)) {
            /* input brigade still has an EOS which we can't pass to the output_filters. */
            e = APR_BRIGADE_LAST(input_brigade);
            AP_DEBUG_ASSERT(APR_BUCKET_IS_EOS(e));
            apr_bucket_delete(e);
        }
        bb = input_brigade;
    }

    e = apr_bucket_immortal_create(ASCII_ZERO ASCII_CRLF
                                   /* <trailers> */
                                   ASCII_CRLF,
                                   5, bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(bb, e);

    if (apr_table_get(r->subprocess_env, "proxy-sendextracrlf")) {
        e = apr_bucket_immortal_create(ASCII_CRLF, 2, bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, e);
    }

    /* Now we have headers-only, or the chunk EOS mark; flush it */
    rv = ap_proxy_pass_brigade(bucket_alloc, r, p_conn, origin, bb, 1);
    return rv;
}