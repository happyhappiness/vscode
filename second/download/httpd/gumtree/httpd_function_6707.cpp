apr_status_t ap_core_output_filter(ap_filter_t *f, apr_bucket_brigade *new_bb)
{
    conn_rec *c = f->c;
    core_net_rec *net = f->ctx;
    core_output_filter_ctx_t *ctx = net->out_ctx;
    apr_bucket_brigade *bb = NULL;
    apr_bucket *bucket, *next, *flush_upto = NULL;
    apr_size_t bytes_in_brigade, non_file_bytes_in_brigade;
    int eor_buckets_in_brigade, morphing_bucket_in_brigade;
    apr_status_t rv;

    /* Fail quickly if the connection has already been aborted. */
    if (c->aborted) {
        if (new_bb != NULL) {
            apr_brigade_cleanup(new_bb);
        }
        return APR_ECONNABORTED;
    }

    if (ctx == NULL) {
        ctx = apr_pcalloc(c->pool, sizeof(*ctx));
        net->out_ctx = (core_output_filter_ctx_t *)ctx;
        /*
         * Need to create tmp brigade with correct lifetime. Passing
         * NULL to apr_brigade_split_ex would result in a brigade
         * allocated from bb->pool which might be wrong.
         */
        ctx->tmp_flush_bb = apr_brigade_create(c->pool, c->bucket_alloc);
        /* same for buffered_bb and ap_save_brigade */
        ctx->buffered_bb = apr_brigade_create(c->pool, c->bucket_alloc);
    }

    if (new_bb != NULL)
        bb = new_bb;

    if ((ctx->buffered_bb != NULL) &&
        !APR_BRIGADE_EMPTY(ctx->buffered_bb)) {
        if (new_bb != NULL) {
            APR_BRIGADE_PREPEND(bb, ctx->buffered_bb);
        }
        else {
            bb = ctx->buffered_bb;
        }
        c->data_in_output_filters = 0;
    }
    else if (new_bb == NULL) {
        return APR_SUCCESS;
    }

    /* Scan through the brigade and decide whether to attempt a write,
     * and how much to write, based on the following rules:
     *
     *  1) The new_bb is null: Do a nonblocking write of as much as
     *     possible: do a nonblocking write of as much data as possible,
     *     then save the rest in ctx->buffered_bb.  (If new_bb == NULL,
     *     it probably means that the MPM is doing asynchronous write
     *     completion and has just determined that this connection
     *     is writable.)
     *
     *  2) Determine if and up to which bucket we need to do a blocking
     *     write:
     *
     *  a) The brigade contains a flush bucket: Do a blocking write
     *     of everything up that point.
     *
     *  b) The request is in CONN_STATE_HANDLER state, and the brigade
     *     contains at least THRESHOLD_MAX_BUFFER bytes in non-file
     *     buckets: Do blocking writes until the amount of data in the
     *     buffer is less than THRESHOLD_MAX_BUFFER.  (The point of this
     *     rule is to provide flow control, in case a handler is
     *     streaming out lots of data faster than the data can be
     *     sent to the client.)
     *
     *  c) The request is in CONN_STATE_HANDLER state, and the brigade
     *     contains at least MAX_REQUESTS_IN_PIPELINE EOR buckets:
     *     Do blocking writes until less than MAX_REQUESTS_IN_PIPELINE EOR
     *     buckets are left. (The point of this rule is to prevent too many
     *     FDs being kept open by pipelined requests, possibly allowing a
     *     DoS).
     *
     *  d) The brigade contains a morphing bucket: If there was no other
     *     reason to do a blocking write yet, try reading the bucket. If its
     *     contents fit into memory before THRESHOLD_MAX_BUFFER is reached,
     *     everything is fine. Otherwise we need to do a blocking write the
     *     up to and including the morphing bucket, because ap_save_brigade()
     *     would read the whole bucket into memory later on.
     *
     *  3) Actually do the blocking write up to the last bucket determined
     *     by rules 2a-d. The point of doing only one flush is to make as
     *     few calls to writev() as possible.
     *
     *  4) If the brigade contains at least THRESHOLD_MIN_WRITE
     *     bytes: Do a nonblocking write of as much data as possible,
     *     then save the rest in ctx->buffered_bb.
     */

    if (new_bb == NULL) {
        rv = send_brigade_nonblocking(net->client_socket, bb,
                                      &(ctx->bytes_written), c);
        if (APR_STATUS_IS_EAGAIN(rv)) {
            rv = APR_SUCCESS;
        }
        else if (rv != APR_SUCCESS) {
            /* The client has aborted the connection */
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, rv, c,
                          "core_output_filter: writing data to the network");
            c->aborted = 1;
        }
        setaside_remaining_output(f, ctx, bb, c);
        return rv;
    }

    bytes_in_brigade = 0;
    non_file_bytes_in_brigade = 0;
    eor_buckets_in_brigade = 0;
    morphing_bucket_in_brigade = 0;

    for (bucket = APR_BRIGADE_FIRST(bb); bucket != APR_BRIGADE_SENTINEL(bb);
         bucket = next) {
        next = APR_BUCKET_NEXT(bucket);

        if (!APR_BUCKET_IS_METADATA(bucket)) {
            if (bucket->length == (apr_size_t)-1) {
                /*
                 * A setaside of morphing buckets would read everything into
                 * memory. Instead, we will flush everything up to and
                 * including this bucket.
                 */
                morphing_bucket_in_brigade = 1;
            }
            else {
                bytes_in_brigade += bucket->length;
                if (!APR_BUCKET_IS_FILE(bucket))
                    non_file_bytes_in_brigade += bucket->length;
            }
        }
        else if (AP_BUCKET_IS_EOR(bucket)) {
            eor_buckets_in_brigade++;
        }

        if (APR_BUCKET_IS_FLUSH(bucket)
            || non_file_bytes_in_brigade >= THRESHOLD_MAX_BUFFER
            || morphing_bucket_in_brigade
            || eor_buckets_in_brigade > MAX_REQUESTS_IN_PIPELINE) {
            /* this segment of the brigade MUST be sent before returning. */

            if (APLOGctrace6(c)) {
                char *reason = APR_BUCKET_IS_FLUSH(bucket) ?
                               "FLUSH bucket" :
                               (non_file_bytes_in_brigade >= THRESHOLD_MAX_BUFFER) ?
                               "THRESHOLD_MAX_BUFFER" :
                               morphing_bucket_in_brigade ? "morphing bucket" :
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
            morphing_bucket_in_brigade = 0;
        }
    }

    if (flush_upto != NULL) {
        ctx->tmp_flush_bb = apr_brigade_split_ex(bb, flush_upto,
                                                 ctx->tmp_flush_bb);
        rv = send_brigade_blocking(net->client_socket, bb,
                                   &(ctx->bytes_written), c);
        if (rv != APR_SUCCESS) {
            /* The client has aborted the connection */
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, rv, c,
                          "core_output_filter: writing data to the network");
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
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, rv, c,
                          "core_output_filter: writing data to the network");
            c->aborted = 1;
            return rv;
        }
    }

    setaside_remaining_output(f, ctx, bb, c);
    return APR_SUCCESS;
}