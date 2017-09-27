        APR_BRIGADE_INSERT_TAIL(bb, bucket);
    }

    return APR_SUCCESS;
}


/* ssl_io_filter_output() produces one SSL/TLS message per bucket
 * passed down the output filter stack.  This results in a high
 * overhead (network packets) for any output comprising many small
 * buckets.  SSI page applied through the HTTP chunk filter, for
 * example, may produce many brigades containing small buckets -
 * [chunk-size CRLF] [chunk-data] [CRLF].
 *
 * The coalescing filter merges many small buckets into larger buckets
 * where possible, allowing the SSL I/O output filter to handle them
 * more efficiently. */

#define COALESCE_BYTES (2048)

struct coalesce_ctx {
    char buffer[COALESCE_BYTES];
    apr_size_t bytes; /* number of bytes of buffer used. */
};

static apr_status_t ssl_io_filter_coalesce(ap_filter_t *f,
                                           apr_bucket_brigade *bb)
{
    apr_bucket *e, *last = NULL;
    apr_size_t bytes = 0;
    struct coalesce_ctx *ctx = f->ctx;
    unsigned count = 0;

    /* The brigade consists of zero-or-more small data buckets which
     * can be coalesced (the prefix), followed by the remainder of the
     * brigade.
     *
     * Find the last bucket - if any - of that prefix.  count gives
     * the number of buckets in the prefix.  The "prefix" must contain
     * only data buckets with known length, and must be of a total
     * size which fits into the buffer.
     *
     * N.B.: The process here could be repeated throughout the brigade
     * (coalesce any run of consecutive data buckets) but this would
     * add significant complexity, particularly to memory
     * management. */
    for (e = APR_BRIGADE_FIRST(bb);
         e != APR_BRIGADE_SENTINEL(bb)
             && !APR_BUCKET_IS_METADATA(e)
             && e->length != (apr_size_t)-1
             && e->length < COALESCE_BYTES
             && (bytes + e->length) < COALESCE_BYTES
             && (ctx == NULL
                 || bytes + ctx->bytes + e->length < COALESCE_BYTES);
         e = APR_BUCKET_NEXT(e)) {
        last = e;
        if (e->length) count++; /* don't count zero-length buckets */
        bytes += e->length;
    }

    /* Coalesce the prefix, if:
     * a) more than one bucket is found to coalesce, or
     * b) the brigade contains only a single data bucket, or
     * c)
     */
    if (bytes > 0
        && (count > 1
            || (count == 1 && APR_BUCKET_NEXT(last) == APR_BRIGADE_SENTINEL(bb)))) {
        /* If coalescing some bytes, ensure a context has been
         * created. */
        if (!ctx) {
            f->ctx = ctx = apr_palloc(f->c->pool, sizeof *ctx);
            ctx->bytes = 0;
        }

        ap_log_cerror(APLOG_MARK, APLOG_TRACE4, 0, f->c,
                      "coalesce: have %" APR_SIZE_T_FMT " bytes, "
                      "adding %" APR_SIZE_T_FMT " more", ctx->bytes, bytes);

        /* Iterate through the prefix segment.  For non-fatal errors
         * in this loop it is safe to break out and fall back to the
         * normal path of sending the buffer + remaining buckets in
         * brigade.  */
        e = APR_BRIGADE_FIRST(bb);
        while (e != last) {
            apr_size_t len;
            const char *data;
            apr_bucket *next;

            if (APR_BUCKET_IS_METADATA(e)
                || e->length == (apr_size_t)-1) {
                ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, f->c, APLOGNO(02012)
                              "unexpected bucket type during coalesce");
                break; /* non-fatal error; break out */
            }

            if (e->length) {
                apr_status_t rv;

                /* A blocking read should be fine here for a
                 * known-length data bucket, rather than the usual
                 * non-block/flush/block.  */
                rv = apr_bucket_read(e, &data, &len, APR_BLOCK_READ);
                if (rv) {
                    ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, f->c, APLOGNO(02013)
                                  "coalesce failed to read from data bucket");
                    return AP_FILTER_ERROR;
                }

                /* Be paranoid. */
                if (len > sizeof ctx->buffer
                    || (len + ctx->bytes > sizeof ctx->buffer)) {
                    ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, f->c, APLOGNO(02014)
                                  "unexpected coalesced bucket data length");
                    break; /* non-fatal error; break out */
                }

                memcpy(ctx->buffer + ctx->bytes, data, len);
                ctx->bytes += len;
            }

            next = APR_BUCKET_NEXT(e);
            apr_bucket_delete(e);
            e = next;
        }
    }

    if (APR_BRIGADE_EMPTY(bb)) {
        /* If the brigade is now empty, our work here is done. */
        return APR_SUCCESS;
    }

    /* If anything remains in the brigade, it must now be passed down
     * the filter stack, first prepending anything that has been
     * coalesced. */
    if (ctx && ctx->bytes) {
        apr_bucket *e;

        ap_log_cerror(APLOG_MARK, APLOG_TRACE4, 0, f->c,
                      "coalesce: passing on %" APR_SIZE_T_FMT " bytes", ctx->bytes);

        e = apr_bucket_transient_create(ctx->buffer, ctx->bytes, bb->bucket_alloc);
        APR_BRIGADE_INSERT_HEAD(bb, e);
        ctx->bytes = 0; /* buffer now emptied. */
    }

    return ap_pass_brigade(f->next, bb);
}

static apr_status_t ssl_io_filter_output(ap_filter_t *f,
                                         apr_bucket_brigade *bb)
{
    apr_status_t status = APR_SUCCESS;
    ssl_filter_ctx_t *filter_ctx = f->ctx;
    bio_filter_in_ctx_t *inctx;
