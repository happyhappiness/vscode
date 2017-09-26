    return (p - data);
}

/*
 * find out whether the next token is (a possible) end_seq or an argument
 */
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

/*
 * test the stream for end_seq. If it doesn't match at all, it must be an
 * argument
 */
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

/*
 * extract name=value from the buffer
 * A pcre-pattern could look (similar to):
 * name\s*(?:=\s*(["'`]?)value\1(?>\s*))?
 */
static apr_size_t find_argument(ssi_ctx_t *ctx, const char *data,
                                apr_size_t len, char ***store,
                                apr_size_t **store_len)
{
    const char *p = data;
    const char *ep = data + len;

    switch (ctx->state) {
    case PARSE_ARG:
        /*
         * create argument structure and append it to the current list
         */
        ctx->current_arg = apr_palloc(ctx->dpool,
                                      sizeof(*ctx->current_arg));
        ctx->current_arg->next = NULL;

        ++(ctx->argc);
        if (!ctx->argv) {
            ctx->argv = ctx->current_arg;
        }
        else {
            ssi_arg_item_t *newarg = ctx->argv;

            while (newarg->next) {
                newarg = newarg->next;
            }
            newarg->next = ctx->current_arg;
        }

        /* check whether it's a valid one. If it begins with a quote, we
         * can safely assume, someone forgot the name of the argument
         */
        switch (*p) {
        case '"': case '\'': case '`':
            *store = NULL;

            ctx->state = PARSE_ARG_VAL;
            ctx->quote = *p++;
            ctx->current_arg->name = NULL;
            ctx->current_arg->name_len = 0;
            ctx->error = 1;

            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r, "missing argument "
                          "name for value to tag %s in %s",
                          apr_pstrmemdup(ctx->r->pool, ctx->directive,
                                         ctx->ctx->directive_length),
                                         ctx->r->filename);

            return (p - data);

        default:
            ctx->state = PARSE_ARG_NAME;
        }
        /* continue immediately with next state */

    case PARSE_ARG_NAME:
        while (p < ep && !apr_isspace(*p) && *p != '=') {
            ++p;
        }

        if (p < ep) {
            ctx->state = PARSE_ARG_POSTNAME;
            *store = &ctx->current_arg->name;
            *store_len = &ctx->current_arg->name_len;
            return (p - data);
        }
        break;

    case PARSE_ARG_POSTNAME:
        ctx->current_arg->name = apr_pstrmemdup(ctx->dpool,
                                                ctx->current_arg->name,
                                                ctx->current_arg->name_len);
        if (!ctx->current_arg->name_len) {
            ctx->error = 1;
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r, "missing argument "
                          "name for value to tag %s in %s",
                          apr_pstrmemdup(ctx->r->pool, ctx->directive,
                                         ctx->ctx->directive_length),
                                         ctx->r->filename);
        }
        else {
            char *sp = ctx->current_arg->name;

            /* normalize the name */
            while (*sp) {
                *sp = apr_tolower(*sp);
                ++sp;
            }
        }

        ctx->state = PARSE_ARG_EQ;
        /* continue with next state immediately */

    case PARSE_ARG_EQ:
        *store = NULL;

        while (p < ep && apr_isspace(*p)) {
            ++p;
        }

        if (p < ep) {
            if (*p == '=') {
                ctx->state = PARSE_ARG_PREVAL;
                ++p;
            }
            else { /* no value */
                ctx->current_arg->value = NULL;
                ctx->state = PARSE_PRE_ARG;
            }

            return (p - data);
        }
        break;

