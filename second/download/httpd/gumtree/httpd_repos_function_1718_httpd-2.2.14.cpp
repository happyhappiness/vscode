static apr_status_t set_aside_partial_char(charset_filter_ctx_t *ctx,
                                           const char *partial,
                                           apr_size_t partial_len)
{
    apr_status_t rv;

    if (sizeof(ctx->buf) > partial_len) {
        ctx->saved = partial_len;
        memcpy(ctx->buf, partial, partial_len);
        rv = APR_SUCCESS;
    }
    else {
        rv = APR_INCOMPLETE;
        ctx->ees = EES_LIMIT; /* we don't handle chars this wide which straddle
                               * buckets
                               */
    }
    return rv;
}