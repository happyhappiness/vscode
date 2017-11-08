static apr_size_t find_tail(include_ctx_t *ctx, const char *data,
                            apr_size_t len)
{
    struct ssi_internal_ctx *intern = ctx->intern;
    const char *p = data;
    const char *ep = data + len;
    apr_size_t pos = intern->parse_pos;

    if (PARSE_TAIL == intern->state) {
        intern->state = PARSE_TAIL_SEQ;
        pos = intern->parse_pos = 0;
    }

    while (p < ep && pos < intern->end_seq_len && *p == intern->end_seq[pos]) {
        ++p;
        ++pos;
    }

    /* bingo, full match */
    if (pos == intern->end_seq_len) {
        intern->state = PARSE_EXECUTE;
        return (p - data);
    }

    /* partial match, the buffer is too small to match fully */
    if (p == ep) {
        intern->parse_pos = pos;
        return (p - data);
    }

    /* no match. It must be an argument string then
     * The caller should cleanup and rewind to the reparse point
     */
    intern->state = PARSE_ARG;
    return 0;
}