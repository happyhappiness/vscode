static apr_status_t get_remaining_chunk_line(http_ctx_t *ctx,
                                             apr_bucket_brigade *b,
                                             int linelimit)
{
    apr_status_t rv;
    apr_off_t brigade_length;
    apr_bucket *e;
    const char *lineend;
    apr_size_t len;

    /*
     * As the brigade b should have been requested in mode AP_MODE_GETLINE
     * all buckets in this brigade are already some type of memory
     * buckets (due to the needed scanning for LF in mode AP_MODE_GETLINE)
     * or META buckets.
     */
    rv = apr_brigade_length(b, 0, &brigade_length);
    if (rv != APR_SUCCESS) {
        return rv;
    }
    /* Sanity check. Should never happen. See above. */
    if (brigade_length == -1) {
        return APR_EGENERAL;
    }
    if (!brigade_length) {
        return APR_EAGAIN;
    }
    ctx->linesize += brigade_length;
    if (ctx->linesize > linelimit) {
        return APR_ENOSPC;
    }
    /*
     * As all buckets are already some type of memory buckets or META buckets
     * (see above), we only need to check the last byte in the last data bucket.
     */
    for (e = APR_BRIGADE_LAST(b);
         e != APR_BRIGADE_SENTINEL(b);
         e = APR_BUCKET_PREV(e)) {

        if (APR_BUCKET_IS_METADATA(e)) {
            continue;
        }
        rv = apr_bucket_read(e, &lineend, &len, APR_BLOCK_READ);
        if (rv != APR_SUCCESS) {
            return rv;
        }
        if (len > 0) {
            break;  /* we got the data we want */
        }
        /* If we got a zero-length data bucket, we try the next one */
    }
    /* We had no data in this brigade */
    if (!len || e == APR_BRIGADE_SENTINEL(b)) {
        return APR_EAGAIN;
    }
    if (lineend[len - 1] != APR_ASCII_LF) {
        return APR_EAGAIN;
    }
    /* Line is complete. So reset ctx->linesize for next round. */
    ctx->linesize = 0;
    return APR_SUCCESS;
}