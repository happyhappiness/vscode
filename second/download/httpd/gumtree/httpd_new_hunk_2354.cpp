            }
            bytes_in_brigade += bucket->length;
            if (!APR_BUCKET_IS_FILE(bucket)) {
                non_file_bytes_in_brigade += bucket->length;
            }
        }
        else if (AP_BUCKET_IS_EOR(bucket)) {
            eor_buckets_in_brigade++;
        }

        if (APR_BUCKET_IS_FLUSH(bucket)                         ||
            (non_file_bytes_in_brigade >= THRESHOLD_MAX_BUFFER) ||
            (eor_buckets_in_brigade > MAX_REQUESTS_IN_PIPELINE) )
        {
            if (APLOGctrace6(c)) {
                char *reason = APR_BUCKET_IS_FLUSH(bucket) ?
                               "FLUSH bucket" :
                               (non_file_bytes_in_brigade >= THRESHOLD_MAX_BUFFER) ?
                               "THRESHOLD_MAX_BUFFER" :
                               "MAX_REQUESTS_IN_PIPELINE";
                ap_log_cerror(APLOG_MARK, APLOG_TRACE6, 0, c,
                              "core_output_filter: flushing because of %s",
                              reason);
            }
            /*
             * Defer the actual blocking write to avoid doing many writes.
             */
            flush_upto = next;

            bytes_in_brigade = 0;
            non_file_bytes_in_brigade = 0;
            eor_buckets_in_brigade = 0;
        }
    }

    if (flush_upto != NULL) {
        ctx->tmp_flush_bb = apr_brigade_split_ex(bb, flush_upto,
                                                 ctx->tmp_flush_bb);
        rv = send_brigade_blocking(net->client_socket, bb,
                                   &(ctx->bytes_written), c);
        if (rv != APR_SUCCESS) {
            /* The client has aborted the connection */
            c->aborted = 1;
            return rv;
        }
        APR_BRIGADE_CONCAT(bb, ctx->tmp_flush_bb);
    }

    if (bytes_in_brigade >= THRESHOLD_MIN_WRITE) {
        rv = send_brigade_nonblocking(net->client_socket, bb,
                                      &(ctx->bytes_written), c);
        if ((rv != APR_SUCCESS) && (!APR_STATUS_IS_EAGAIN(rv))) {
            /* The client has aborted the connection */
            c->aborted = 1;
            return rv;
