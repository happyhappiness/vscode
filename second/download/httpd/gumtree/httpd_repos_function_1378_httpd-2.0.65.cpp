static apr_size_t find_arg_or_tail(ssi_ctx_t *ctx, const char *data,
                                   apr_size_t len)
{
    const char *p = data;
    const char *ep = data + len;

    /* skip leading WS */
    while (p < ep && apr_isspace(*p)) {
        ++p;
    }

    /* buffer doesn't consist of whitespaces only */
    if (p < ep) {
        ctx->state = (*p == *ctx->ctx->end_seq) ? PARSE_TAIL : PARSE_ARG;
    }

    return (p - data);
}