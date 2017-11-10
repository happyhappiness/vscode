static apr_size_t find_directive(include_ctx_t *ctx, const char *data,
                                 apr_size_t len, char ***store,
                                 apr_size_t **store_len)
{
    struct ssi_internal_ctx *intern = ctx->intern;
    const char *p = data;
    const char *ep = data + len;
    apr_size_t pos;

    switch (intern->state) {
    case PARSE_DIRECTIVE:
        while (p < ep && !apr_isspace(*p)) {
            /* we have to consider the case of missing space between directive
             * and end_seq (be somewhat lenient), e.g. <!--#printenv-->
             */
            if (*p == *intern->end_seq) {
                intern->state = PARSE_DIRECTIVE_TAIL;
                intern->parse_pos = 1;
                ++p;
                return (p - data);
            }
            ++p;
        }

        if (p < ep) { /* found delimiter whitespace */
            intern->state = PARSE_DIRECTIVE_POSTNAME;
            *store = &intern->directive;
            *store_len = &intern->directive_len;
        }

        break;

    case PARSE_DIRECTIVE_TAIL:
        pos = intern->parse_pos;

        while (p < ep && pos < intern->end_seq_len &&
               *p == intern->end_seq[pos]) {
            ++p;
            ++pos;
        }

        /* full match, we're done */
        if (pos == intern->end_seq_len) {
            intern->state = PARSE_DIRECTIVE_POSTTAIL;
            *store = &intern->directive;
            *store_len = &intern->directive_len;
            break;
        }

        /* partial match, the buffer is too small to match fully */
        if (p == ep) {
            intern->parse_pos = pos;
            break;
        }

        /* no match. continue normal parsing */
        intern->state = PARSE_DIRECTIVE;
        return 0;

    case PARSE_DIRECTIVE_POSTTAIL:
        intern->state = PARSE_EXECUTE;
        intern->directive_len -= intern->end_seq_len;
        /* continue immediately with the next state */

    case PARSE_DIRECTIVE_POSTNAME:
        if (PARSE_DIRECTIVE_POSTNAME == intern->state) {
            intern->state = PARSE_PRE_ARG;
        }
        ctx->argc = 0;
        intern->argv = NULL;

        if (!intern->directive_len) {
            intern->error = 1;
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, intern->r, "missing "
                          "directive name in parsed document %s",
                          intern->r->filename);
        }
        else {
            char *sp = intern->directive;
            char *sep = intern->directive + intern->directive_len;

            /* normalize directive name */
            for (; sp < sep; ++sp) {
                *sp = apr_tolower(*sp);
            }
        }

        return 0;

    default:
        /* get a rid of a gcc warning about unhandled enumerations */
        break;
    }

    return (p - data);
}