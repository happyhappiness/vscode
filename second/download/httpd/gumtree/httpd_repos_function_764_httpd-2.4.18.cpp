static apr_status_t ssl_io_filter_output(ap_filter_t *f,
                                         apr_bucket_brigade *bb)
{
    apr_status_t status = APR_SUCCESS;
    ssl_filter_ctx_t *filter_ctx = f->ctx;
    bio_filter_in_ctx_t *inctx;
    bio_filter_out_ctx_t *outctx;
    apr_read_type_e rblock = APR_NONBLOCK_READ;

    if (f->c->aborted) {
        apr_brigade_cleanup(bb);
        return APR_ECONNABORTED;
    }

    if (!filter_ctx->pssl) {
        /* ssl_filter_io_shutdown was called */
        return ap_pass_brigade(f->next, bb);
    }

    inctx = (bio_filter_in_ctx_t *)filter_ctx->pbioRead->ptr;
    outctx = (bio_filter_out_ctx_t *)filter_ctx->pbioWrite->ptr;

    /* When we are the writer, we must initialize the inctx
     * mode so that we block for any required ssl input, because
     * output filtering is always nonblocking.
     */
    inctx->mode = AP_MODE_READBYTES;
    inctx->block = APR_BLOCK_READ;

    if ((status = ssl_io_filter_handshake(filter_ctx)) != APR_SUCCESS) {
        return ssl_io_filter_error(f, bb, status, 0);
    }

    while (!APR_BRIGADE_EMPTY(bb) && status == APR_SUCCESS) {
        apr_bucket *bucket = APR_BRIGADE_FIRST(bb);

        if (APR_BUCKET_IS_METADATA(bucket)) {
            /* Pass through metadata buckets untouched.  EOC is
             * special; terminate the SSL layer first. */
            if (AP_BUCKET_IS_EOC(bucket)) {
                ssl_filter_io_shutdown(filter_ctx, f->c, 0);
            }
            AP_DEBUG_ASSERT(APR_BRIGADE_EMPTY(outctx->bb));

            /* Metadata buckets are passed one per brigade; it might
             * be more efficient (but also more complex) to use
             * outctx->bb as a true buffer and interleave these with
             * data buckets. */
            APR_BUCKET_REMOVE(bucket);
            APR_BRIGADE_INSERT_HEAD(outctx->bb, bucket);
            status = ap_pass_brigade(f->next, outctx->bb);
            if (status == APR_SUCCESS && f->c->aborted)
                status = APR_ECONNRESET;
            apr_brigade_cleanup(outctx->bb);
        }
        else {
            /* Filter a data bucket. */
            const char *data;
            apr_size_t len;

            status = apr_bucket_read(bucket, &data, &len, rblock);

            if (APR_STATUS_IS_EAGAIN(status)) {
                /* No data available: flush... */
                if (bio_filter_out_flush(filter_ctx->pbioWrite) < 0) {
                    status = outctx->rc;
                    break;
                }
                rblock = APR_BLOCK_READ;
                /* and try again with a blocking read. */
                status = APR_SUCCESS;
                continue;
            }

            rblock = APR_NONBLOCK_READ;

            if (!APR_STATUS_IS_EOF(status) && (status != APR_SUCCESS)) {
                break;
            }

            status = ssl_filter_write(f, data, len);
            apr_bucket_delete(bucket);
        }

    }

    return status;
}