static apr_size_t find_arg_or_tail(include_ctx_t *ctx, const char *data,
                                   apr_size_t len)
{
    struct ssi_internal_ctx *intern = ctx->intern;
    const char *p = data;
    const char *ep = data + len;

    /* skip leading WS */
    while (p < ep && apr_isspace(*p)) {
        ++p;
    }

    /* buffer doesn't consist of whitespaces only */
    if (p < ep) {
        intern->state = (*p == *intern->end_seq) ? PARSE_TAIL : PARSE_ARG;
    }

    return (p - data);
}