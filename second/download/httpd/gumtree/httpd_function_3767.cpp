static int reflector_handler(request_rec * r)
{
    apr_bucket_brigade *bbin, *bbout;
    reflector_cfg *conf;
    apr_status_t status;

    if (strcmp(r->handler, "reflector")) {
        return DECLINED;
    }

    conf = (reflector_cfg *) ap_get_module_config(r->per_dir_config,
                                                  &reflector_module);

    ap_allow_methods(r, 1, "POST", "OPTIONS", NULL);

    if (r->method_number == M_OPTIONS) {
        return ap_send_http_options(r);
    }

    else if (r->method_number == M_POST) {
        const char *content_length, *content_type;
        int seen_eos;

        /*
         * Sometimes we'll get in a state where the input handling has
         * detected an error where we want to drop the connection, so if
         * that's the case, don't read the data as that is what we're trying
         * to avoid.
         *
         * This function is also a no-op on a subrequest.
         */
        if (r->main || r->connection->keepalive == AP_CONN_CLOSE ||
            ap_status_drops_connection(r->status)) {
            return OK;
        }

        /* copy headers from in to out if configured */
        apr_table_do(header_do, r, conf->headers, NULL);

        /* last modified defaults to now, unless otherwise set on the way in */
        if (!apr_table_get(r->headers_out, "Last-Modified")) {
            ap_update_mtime(r, apr_time_now());
            ap_set_last_modified(r);
        }
        apr_table_setn(r->headers_out, "Accept-Ranges", "bytes");

        /* reflect the content length, if present */
        if ((content_length = apr_table_get(r->headers_in, "Content-Length"))) {
            apr_off_t offset;

            apr_strtoff(&offset, content_length, NULL, 10);
            ap_set_content_length(r, offset);

        }

        /* reflect the content type, if present */
        if ((content_type = apr_table_get(r->headers_in, "Content-Type"))) {

            ap_set_content_type(r, content_type);

        }

        bbin = apr_brigade_create(r->pool, r->connection->bucket_alloc);
        bbout = apr_brigade_create(r->pool, r->connection->bucket_alloc);

        seen_eos = 0;
        do {
            apr_bucket *bucket;

            status = ap_get_brigade(r->input_filters, bbin, AP_MODE_READBYTES,
                                    APR_BLOCK_READ, HUGE_STRING_LEN);

            if (status != APR_SUCCESS) {
                if (status == AP_FILTER_ERROR) {
                    apr_brigade_destroy(bbin);
                    return status;
                }
                else {
                    apr_brigade_destroy(bbin);
                    return HTTP_BAD_REQUEST;
                }
            }

            for (bucket = APR_BRIGADE_FIRST(bbin);
                 bucket != APR_BRIGADE_SENTINEL(bbin);
                 bucket = APR_BUCKET_NEXT(bucket)) {
                const char *data;
                apr_size_t len;

                if (APR_BUCKET_IS_EOS(bucket)) {
                    seen_eos = 1;
                    break;
                }

                /* These are metadata buckets. */
                if (bucket->length == 0) {
                    continue;
                }

                /*
                 * We MUST read because in case we have an unknown-length
                 * bucket or one that morphs, we want to exhaust it.
                 */
                status = apr_bucket_read(bucket, &data, &len, APR_BLOCK_READ);
                if (status != APR_SUCCESS) {
                    apr_brigade_destroy(bbin);
                    return HTTP_BAD_REQUEST;
                }

                apr_brigade_write(bbout, NULL, NULL, data, len);

                status = ap_pass_brigade(r->output_filters, bbout);
                if (status != APR_SUCCESS) {
                    /* no way to know what type of error occurred */
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, r,
                             "reflector_handler: ap_pass_brigade returned %i",
                                  status);
                    return HTTP_INTERNAL_SERVER_ERROR;
                }

            }

            apr_brigade_cleanup(bbin);

        } while (!seen_eos);

        return OK;

    }

    else {
        return HTTP_METHOD_NOT_ALLOWED;
    }

}