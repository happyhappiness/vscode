static apr_size_t find_partial_start_sequence(include_ctx_t *ctx,
                                              const char *data,
                                              apr_size_t len,
                                              apr_size_t *release)
{
    struct ssi_internal_ctx *intern = ctx->intern;
    apr_size_t pos, spos = 0;
    apr_size_t slen = intern->start_seq_pat->pattern_len;
    const char *p, *ep;

    pos = intern->parse_pos;
    ep = data + len;
    *release = 0;

    do {
        p = data;

        while (p < ep && pos < slen && *p == intern->start_seq[pos]) {
            ++p;
            ++pos;
        }

        /* full match */
        if (pos == slen) {
            intern->state = PARSE_DIRECTIVE;
            return (p - data);
        }

        /* the whole buffer is a partial match */
        if (p == ep) {
            intern->parse_pos = pos;
            return (p - data);
        }

        /* No match so far, but again:
         * We must try all combinations, since the start_seq is a random
         * user supplied string
         *
         * So: look if the first char of start_seq appears somewhere within
         * the current partial match. If it does, try to start a match that
         * begins with this offset. (This can happen, if a strange
         * start_seq like "---->" spans buffers)
         */
        if (spos < intern->parse_pos) {
            do {
                ++spos;
                ++*release;
                p = intern->start_seq + spos;
                pos = intern->parse_pos - spos;

                while (pos && *p != *intern->start_seq) {
                    ++p;
                    ++spos;
                    ++*release;
                    --pos;
                }

                /* if a matching beginning char was found, try to match the
                 * remainder of the old buffer.
                 */
                if (pos > 1) {
                    apr_size_t t = 1;

                    ++p;
                    while (t < pos && *p == intern->start_seq[t]) {
                        ++p;
                        ++t;
                    }

                    if (t == pos) {
                        /* yeah, another partial match found in the *old*
                         * buffer, now test the *current* buffer for
                         * continuing match
                         */
                        break;
                    }
                }
            } while (pos > 1);

            if (pos) {
                continue;
            }
        }

        break;
    } while (1); /* work hard to find a match ;-) */

    /* no match at all, release all (wrongly) matched chars so far */
    *release = intern->parse_pos;
    intern->state = PARSE_PRE_HEAD;
    return 0;
}