    *pw = t;

    return OK;
}

struct content_length_ctx {
    int data_sent;  /* true if the C-L filter has already sent at
                     * least one bucket on to the next output filter
                     * for this request
                     */
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
    apr_bucket *e;
    int eos = 0;
    apr_read_type_e eblock = APR_NONBLOCK_READ;

    int can_send_content_length;

    /* We can only set a C-L in the response header if we
     * haven't already sent any buckets on to the next
     * output filter for this request.
     */
    ctx = f->ctx;
    if (!ctx) {
        f->ctx = ctx = apr_palloc(r->pool, sizeof(struct content_length_ctx));
        ctx->data_sent = 0;
        can_send_content_length = 1;
    }
    else {
        can_send_content_length = (ctx->data_sent == 0);
    }

    /* Loop through this set of buckets to compute their length
     */
    e = APR_BRIGADE_FIRST(b);
    while (e != APR_BRIGADE_SENTINEL(b)) {
        if (APR_BUCKET_IS_EOS(e)) {
            eos = 1;
            break;
        }
        if (e->length == -1) {
            apr_size_t len;
            const char *ignored;
            apr_status_t rv;

            /* This is probably a pipe bucket.  Send everything
             * prior to this, and then read the data for this bucket.
             */
            rv = apr_bucket_read(e, &ignored, &len, eblock);
            if (rv == APR_SUCCESS) {
                /* Attempt a nonblocking read next time through */
                eblock = APR_NONBLOCK_READ;
                r->bytes_sent += len;
            }
            else if (APR_STATUS_IS_EAGAIN(rv)) {
                /* Output everything prior to this bucket, and
                 * do a blocking read
                 */
                if (e != APR_BRIGADE_FIRST(b)) {
                    apr_bucket_brigade *split = apr_brigade_split(b, e);
                    rv = ap_pass_brigade(f->next, b);
                    if (rv != APR_SUCCESS) {
                        apr_brigade_destroy(split);
                        return rv;
                    }
                    b = split;
                    e = APR_BRIGADE_FIRST(b);
                    can_send_content_length = 0;
                    ctx->data_sent = 1;
                }
                eblock = APR_BLOCK_READ;
                continue;
            }
            else {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                              "ap_content_length_filter: "
                              "apr_bucket_read() failed");
                return rv;
            }
        }
        else {
            r->bytes_sent += e->length;
        }
        e = APR_BUCKET_NEXT(e);
    }

    /* If we've now seen the entire response and it's otherwise
     * okay to set the C-L in the response header, do so now:
         */
    if (can_send_content_length && eos) {
        ap_set_content_length(r, r->bytes_sent);
    }

    ctx->data_sent = 1;
    return ap_pass_brigade(f->next, b);
}

/*
 * Send the body of a response to the client.
 */
