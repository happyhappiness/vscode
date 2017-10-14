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

    if ((status = ssl_io_filter_connect(filter_ctx)) != APR_SUCCESS) {
        return ssl_io_filter_error(inctx, bb, status);
    }

    while (!APR_BRIGADE_EMPTY(bb)) {
        apr_bucket *bucket = APR_BRIGADE_FIRST(bb);

        /* If it is a flush or EOS, we need to pass this down.
         * These types do not require translation by OpenSSL.
         */
        if (APR_BUCKET_IS_EOS(bucket) || APR_BUCKET_IS_FLUSH(bucket)) {
            if (bio_filter_out_flush(filter_ctx->pbioWrite) < 0) {
                status = outctx->rc;
                break;
            }

            if (APR_BUCKET_IS_EOS(bucket)) {
                /*
                 * By definition, nothing can come after EOS.
                 * which also means we can pass the rest of this brigade
                 * without creating a new one since it only contains the
                 * EOS bucket.
                 */

                if ((status = ap_pass_brigade(f->next, bb)) != APR_SUCCESS) {
                    return status;
                }
                break;
            }
            else {
                /* bio_filter_out_flush() already passed down a flush bucket
                 * if there was any data to be flushed.
                 */
                apr_bucket_delete(bucket);
            }
        }
        else if (AP_BUCKET_IS_EOC(bucket)) {
            /* The special "EOC" bucket means a shutdown is needed;
             * - turn off buffering in bio_filter_out_write
             * - issue the SSL_shutdown
             */
            filter_ctx->nobuffer = 1;
            status = ssl_filter_io_shutdown(filter_ctx, f->c, 0);
            if (status != APR_SUCCESS) {
                ap_log_cerror(APLOG_MARK, APLOG_INFO, status, f->c,
                              "SSL filter error shutting down I/O");
            }
            if ((status = ap_pass_brigade(f->next, bb)) != APR_SUCCESS) {
                return status;
            }
            break;
        }
        else {
            /* filter output */
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
                continue; /* and try again with a blocking read. */
            }

            rblock = APR_NONBLOCK_READ;

            if (!APR_STATUS_IS_EOF(status) && (status != APR_SUCCESS)) {
                break;
            }

            status = ssl_filter_write(f, data, len);
            apr_bucket_delete(bucket);

            if (status != APR_SUCCESS) {
                break;
            }
        }
    }

    return status;
}