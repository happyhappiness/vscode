static apr_status_t xlate_brigade(charset_filter_ctx_t *ctx,
                                  apr_bucket_brigade *bb,
                                  char *buffer, 
                                  apr_size_t *buffer_avail,
                                  int *hit_eos)
{
    apr_bucket *b = NULL; /* set to NULL only to quiet some gcc */
    apr_bucket *consumed_bucket;
    const char *bucket;
    apr_size_t bytes_in_bucket; /* total bytes read from current bucket */
    apr_size_t bucket_avail;    /* bytes left in current bucket */
    apr_status_t rv = APR_SUCCESS;

    *hit_eos = 0;
    bucket_avail = 0;
    consumed_bucket = NULL;
    while (1) {
        if (!bucket_avail) { /* no bytes left to process in the current bucket... */
            if (consumed_bucket) {
                apr_bucket_delete(consumed_bucket);
                consumed_bucket = NULL;
            }
            b = APR_BRIGADE_FIRST(bb);
            if (b == APR_BRIGADE_SENTINEL(bb) ||
                APR_BUCKET_IS_EOS(b)) {
                break;
            }
            rv = apr_bucket_read(b, &bucket, &bytes_in_bucket, APR_BLOCK_READ);
            if (rv != APR_SUCCESS) {
                ctx->ees = EES_BUCKET_READ;
                break;
            }
            bucket_avail = bytes_in_bucket;
            consumed_bucket = b;   /* for axing when we're done reading it */
        }
        if (bucket_avail) {
            /* We've got data, so translate it. */
            if (ctx->saved) {
                /* Rats... we need to finish a partial character from the previous
                 * bucket.
                 *
                 * Strangely, finish_partial_char() increments the input buffer
                 * pointer but does not increment the output buffer pointer.
                 */
                apr_size_t old_buffer_avail = *buffer_avail;
                rv = finish_partial_char(ctx,
                                         &bucket, &bucket_avail,
                                         &buffer, buffer_avail);
                buffer += old_buffer_avail - *buffer_avail;
            }
            else {
                apr_size_t old_buffer_avail = *buffer_avail;
                apr_size_t old_bucket_avail = bucket_avail;
                rv = apr_xlate_conv_buffer(ctx->xlate,
                                           bucket, &bucket_avail,
                                           buffer,
                                           buffer_avail);
                buffer  += old_buffer_avail - *buffer_avail;
                bucket  += old_bucket_avail - bucket_avail;
                
                if (rv == APR_INCOMPLETE) { /* partial character at end of input */
                    /* We need to save the final byte(s) for next time; we can't
                     * convert it until we look at the next bucket.
                     */
                    rv = set_aside_partial_char(ctx, bucket, bucket_avail);
                    bucket_avail = 0;
                }
            }
            if (rv != APR_SUCCESS) {
                /* bad input byte or partial char too big to store */
                break;
            }
            if (*buffer_avail < XLATE_MIN_BUFF_LEFT) {
                /* if any data remains in the current bucket, split there */
                if (bucket_avail) {
                    apr_bucket_split(b, bytes_in_bucket - bucket_avail);
                }
                apr_bucket_delete(b);
                break;
            }
        }
    }

    if (!APR_BRIGADE_EMPTY(bb)) {
        b = APR_BRIGADE_FIRST(bb);
        if (APR_BUCKET_IS_EOS(b)) {
            /* Leave the eos bucket in the brigade for reporting to
             * subsequent filters.
             */
            *hit_eos = 1;
            if (ctx->saved) {
                /* Oops... we have a partial char from the previous bucket
                 * that won't be completed because there's no more data.
                 */
                rv = APR_INCOMPLETE;
                ctx->ees = EES_INCOMPLETE_CHAR;
            }
        }
    }

    return rv;
}