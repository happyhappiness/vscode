static apr_status_t ssl_io_filter_Output(ap_filter_t *f,
                                         apr_bucket_brigade *bb)
{
    apr_status_t status = APR_SUCCESS;
    SSLFilterRec *ctx = f->ctx;

    if (!ctx->pssl) {
        /* ssl_abort() has been called */
        return ap_pass_brigade(f->next, bb);
    }

    if ((status = ssl_hook_process_connection(ctx)) != APR_SUCCESS) {
        return status;
    }

    while (!APR_BRIGADE_EMPTY(bb)) {
        apr_bucket *bucket = APR_BRIGADE_FIRST(bb);

        /* If it is a flush or EOS, we need to pass this down. 
         * These types do not require translation by OpenSSL.  
         */
        if (APR_BUCKET_IS_EOS(bucket) || APR_BUCKET_IS_FLUSH(bucket)) {
            if ((status = BIO_bucket_flush(ctx->pbioWrite)) != APR_SUCCESS) {
                return status;
            }

            if (APR_BUCKET_IS_EOS(bucket)) {
                /* By definition, nothing can come after EOS.
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
                /* BIO_bucket_flush() already passed down a flush bucket
                 * if there was any data to be flushed.
                 */
                apr_bucket_delete(bucket);
            }
        }
        else {
            /* read filter */
            const char *data;
            apr_size_t len;

            apr_bucket_read(bucket, &data, &len, APR_BLOCK_READ);
            status = ssl_filter_write(f, data, len);
            apr_bucket_delete(bucket);

            if (status != APR_SUCCESS) {
                break;
            }
        }
    }

    return status;
}