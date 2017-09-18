    *pw = t;

    return OK;
}

struct content_length_ctx {
    apr_bucket_brigade *saved;
    int compute_len;
    apr_size_t curr_len;
};

/* This filter computes the content length, but it also computes the number
 * of bytes sent to the client.  This means that this filter will always run
 * through all of the buckets in all brigades
 */
AP_CORE_DECLARE_NONSTD(apr_status_t) ap_content_length_filter(ap_filter_t *f,
                                         apr_bucket_brigade *b)
{
    request_rec *r = f->r;
    struct content_length_ctx *ctx;
    apr_status_t rv;
    apr_bucket *e;
    int eos = 0, flush = 0, partial_send_okay = 0;
    apr_bucket_brigade *more, *split;
    apr_read_type_e eblock = APR_NONBLOCK_READ;

    ctx = f->ctx;
    if (!ctx) { /* first time through */
        f->ctx = ctx = apr_pcalloc(r->pool, sizeof(struct content_length_ctx));
        ctx->compute_len = 1;   /* Assume we will compute the length */
        ctx->saved = apr_brigade_create(r->pool, f->c->bucket_alloc);
    }

    /* Humm, is this check the best it can be?
     * - protocol >= HTTP/1.1 implies support for chunking
     * - non-keepalive implies the end of byte stream will be signaled
     *    by a connection close
     * In both cases, we can send bytes to the client w/o needing to
     * compute content-length.
     * Todo:
     * We should be able to force connection close from this filter
     * when we see we are buffering too much.
     */
    if ((r->proto_num >= HTTP_VERSION(1, 1)) ||
        (r->connection->keepalive == AP_CONN_CLOSE)) {
        partial_send_okay = 1;
    }

    more = b;
    while (more) {
        b = more;
        more = NULL;
        split = NULL;
        flush = 0;

        e = APR_BRIGADE_FIRST(b);
        while (e != APR_BRIGADE_SENTINEL(b)) {
            const char *ignored;
            apr_size_t len;
            len = 0;
            if (APR_BUCKET_IS_EOS(e)) {
                eos = 1;
                break;
            }
            else if (APR_BUCKET_IS_FLUSH(e)) {
                if (partial_send_okay) {
                    split = b;
                    more = apr_brigade_split(b, APR_BUCKET_NEXT(e));
                    break;
                }
            }
            else if ((ctx->curr_len > 4 * AP_MIN_BYTES_TO_WRITE)) {
                /* If we've accumulated more than 4xAP_MIN_BYTES_TO_WRITE and
                 * the client supports chunked encoding, send what we have
                 * and come back for more.
                 */
                if (partial_send_okay) {
                    split = b;
                    more = apr_brigade_split(b, e);
                    break;
                }
            }
            if (e->length == -1) { /* if length unknown */
                rv = apr_bucket_read(e, &ignored, &len, eblock);
                if (rv == APR_SUCCESS) {
                    /* Attempt a nonblocking read next time through */
                    eblock = APR_NONBLOCK_READ;
                }
                else if (APR_STATUS_IS_EAGAIN(rv)) {
                    /* Make the next read blocking.  If the client supports
                     * chunked encoding, flush the filter stack to the network.
                     */
                    eblock = APR_BLOCK_READ;
                    if (partial_send_okay) {
                        split = b;
                        more = apr_brigade_split(b, e);
                        flush = 1;
                        break;
                    }
                    continue;
                }
                else if (rv != APR_EOF) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                                  "ap_content_length_filter: "
                                  "apr_bucket_read() failed");
                    return rv;
                }
            }
            else {
                len = e->length;
            }

            ctx->curr_len += len;
            r->bytes_sent += len;
            e = APR_BUCKET_NEXT(e);
        }

        if (split) {
            ctx->compute_len = 0;  /* Ooops, can't compute the length now */
            ctx->curr_len = 0;

            APR_BRIGADE_PREPEND(split, ctx->saved);

            if (flush) {
                rv = ap_fflush(f->next, split);
            }
            else {
                rv = ap_pass_brigade(f->next, split);
            }

            if (rv != APR_SUCCESS)
                return rv;
        }
    }

    if ((ctx->curr_len < AP_MIN_BYTES_TO_WRITE) && !eos) {
        return ap_save_brigade(f, &ctx->saved, &b,
                               (r->main) ? r->main->pool : r->pool);
    }

    if (ctx->compute_len) {
        /* save the brigade; we can't pass any data to the next
         * filter until we have the entire content length
         */
        if (!eos) {
            return ap_save_brigade(f, &ctx->saved, &b, r->pool);
        }

        ap_set_content_length(r, r->bytes_sent);
    }

    APR_BRIGADE_PREPEND(b, ctx->saved);

    ctx->curr_len = 0;
    return ap_pass_brigade(f->next, b);
}

/*
 * Send the body of a response to the client.
 */
