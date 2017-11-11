static apr_status_t get_chunk_line(http_ctx_t *ctx, apr_bucket_brigade *b,
                                   int linelimit)
{
    apr_size_t len;
    int tmp_len;
    apr_status_t rv;

    tmp_len = sizeof(ctx->chunk_ln) - (ctx->pos - ctx->chunk_ln) - 1;
    /* Saveguard ourselves against underflows */
    if (tmp_len < 0) {
        len = 0;
    }
    else {
        len = (apr_size_t) tmp_len;
    }
    /*
     * Check if there is space left in ctx->chunk_ln. If not, then either
     * the chunk size is insane or we have chunk-extensions. Ignore both
     * by discarding the remaining part of the line via
     * get_remaining_chunk_line. Only bail out if the line is too long.
     */
    if (len > 0) {
        rv = apr_brigade_flatten(b, ctx->pos, &len);
        if (rv != APR_SUCCESS) {
            return rv;
        }
        ctx->pos += len;
        ctx->linesize += len;
        *(ctx->pos) = '\0';
        /*
         * Check if we really got a full line. If yes the
         * last char in the just read buffer must be LF.
         * If not advance the buffer and return APR_EAGAIN.
         * We do not start processing until we have the
         * full line.
         */
        if (ctx->pos[-1] != APR_ASCII_LF) {
            /* Check if the remaining data in the brigade has the LF */
            return get_remaining_chunk_line(ctx, b, linelimit);
        }
        /* Line is complete. So reset ctx->pos for next round. */
        ctx->pos = ctx->chunk_ln;
        return APR_SUCCESS;
    }
    return get_remaining_chunk_line(ctx, b, linelimit);
}