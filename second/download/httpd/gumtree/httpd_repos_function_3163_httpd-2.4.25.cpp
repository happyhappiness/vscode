static apr_status_t finish_partial_char(charset_filter_ctx_t *ctx,
                                        /* input buffer: */
                                        const char **cur_str,
                                        apr_size_t *cur_len,
                                        /* output buffer: */
                                        char **out_str,
                                        apr_size_t *out_len)
{
    apr_status_t rv;
    apr_size_t tmp_input_len;

    /* Keep adding bytes from the input string to the saved string until we
     *    1) finish the input char
     *    2) get an error
     * or 3) run out of bytes to add
     */

    do {
        ctx->buf[ctx->saved] = **cur_str;
        ++ctx->saved;
        ++*cur_str;
        --*cur_len;
        tmp_input_len = ctx->saved;
        rv = apr_xlate_conv_buffer(ctx->xlate,
                                   ctx->buf,
                                   &tmp_input_len,
                                   *out_str,
                                   out_len);
    } while (rv == APR_INCOMPLETE && *cur_len);

    if (rv == APR_SUCCESS) {
        ctx->saved = 0;
    }
    else {
        ctx->ees = EES_LIMIT; /* code isn't smart enough to handle chars
                               * straddling more than two buckets
                               */
    }

    return rv;
}