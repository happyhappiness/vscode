static apr_size_t find_tail(ssi_ctx_t *ctx, const char *data,
                            apr_size_t len)
{
    const char *p = data;
    const char *ep = data + len;
    apr_size_t pos = ctx->ctx->parse_pos;

    if (PARSE_TAIL == ctx->state) {
        ctx->state = PARSE_TAIL_SEQ;
        pos = ctx->ctx->parse_pos = 0;
    }

    while (p < ep && pos < ctx->end_seq_len && *p == ctx->ctx->end_seq[pos]) {
        ++p;
        ++pos;
    }

    /* bingo, full match */
    if (pos == ctx->end_seq_len) {
        ctx->state = PARSE_EXECUTE;
        return (p - data);
    }

    /* partial match, the buffer is too small to match fully */
    if (p == ep) {
        ctx->ctx->parse_pos = pos;
        return (p - data);
    }

    /* no match. It must be an argument string then */
    ctx->state = PARSE_ARG;
    return 0;
}