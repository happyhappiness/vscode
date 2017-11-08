static apr_size_t find_start_sequence(ssi_ctx_t *ctx, const char *data,
                                      apr_size_t len)
{
    apr_size_t slen = ctx->ctx->start_seq_len;
    apr_size_t index;
    const char *p, *ep;

    if (len < slen) {
        p = data; /* try partial match at the end of the buffer (below) */
    }
    else {
        /* try fast bndm search over the buffer
         * (hopefully the whole start sequence can be found in this buffer)
         */
        index = bndm(ctx->ctx->start_seq, ctx->ctx->start_seq_len, data, len,
                     ctx->ctx->start_seq_pat);

        /* wow, found it. ready. */
        if (index < len) {
            ctx->state = PARSE_DIRECTIVE;
            return index;
        }
        else {
            /* ok, the pattern can't be found as whole in the buffer,
             * check the end for a partial match
             */
            p = data + len - slen + 1;
        }
    }

    ep = data + len;
    do {
        while (p < ep && *p != *ctx->ctx->start_seq) {
            ++p;
        }

        index = p - data;

        /* found a possible start_seq start */
        if (p < ep) {
            apr_size_t pos = 1;

            ++p;
            while (p < ep && *p == ctx->ctx->start_seq[pos]) {
                ++p;
                ++pos;
            }

            /* partial match found. Store the info for the next round */
            if (p == ep) {
                ctx->state = PARSE_HEAD;
                ctx->ctx->parse_pos = pos;
                return index;
            }
        }

        /* we must try all combinations; consider (e.g.) SSIStartTag "--->"
         * and a string data of "--.-" and the end of the buffer
         */
        p = data + index + 1;
    } while (p < ep);

    /* no match */
    return len;
}