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

    case PARSE_ARG_PREVAL:
        *store = NULL;

        while (p < ep && apr_isspace(*p)) {
            ++p;
        }

        /* buffer doesn't consist of whitespaces only */
        if (p < ep) {
            ctx->state = PARSE_ARG_VAL;
            switch (*p) {
            case '"': case '\'': case '`':
                ctx->quote = *p++;
                break;
            default:
                ctx->quote = '\0';
                break;
            }

            return (p - data);
        }
        break;

    case PARSE_ARG_VAL_ESC:
        if (*p == ctx->quote) {
            ++p;
        }
        ctx->state = PARSE_ARG_VAL;
        /* continue with next state immediately */

    case PARSE_ARG_VAL:
        for (; p < ep; ++p) {
            if (ctx->quote && *p == '\\') {
                ++p;
                if (p == ep) {
                    ctx->state = PARSE_ARG_VAL_ESC;
                    break;
                }

                if (*p != ctx->quote) {
                    --p;
                }
            }
            else if (ctx->quote && *p == ctx->quote) {
                ++p;
                *store = &ctx->current_arg->value;
                *store_len = &ctx->current_arg->value_len;
                ctx->state = PARSE_ARG_POSTVAL;
                break;
            }
            else if (!ctx->quote && apr_isspace(*p)) {
                ++p;
                *store = &ctx->current_arg->value;
                *store_len = &ctx->current_arg->value_len;
                ctx->state = PARSE_ARG_POSTVAL;
                break;
            }
        }

        return (p - data);

    case PARSE_ARG_POSTVAL:
        /*
         * The value is still the raw input string. Finally clean it up.
         */
        --(ctx->current_arg->value_len);

        /* strip quote escaping \ from the string */
        if (ctx->quote) {
            apr_size_t shift = 0;
            char *sp;

            sp = ctx->current_arg->value;
            ep = ctx->current_arg->value + ctx->current_arg->value_len;
            while (sp < ep && *sp != '\\') {
                ++sp;
            }
            for (; sp < ep; ++sp) {
                if (*sp == '\\' && sp[1] == ctx->quote) {
                    ++sp;
                    ++shift;
                }
                if (shift) {
                    *(sp-shift) = *sp;
                }
            }

            ctx->current_arg->value_len -= shift;
        }

        ctx->current_arg->value[ctx->current_arg->value_len] = '\0';
        ctx->state = PARSE_PRE_ARG;

        return 0;

    default:
        /* get a rid of a gcc warning about unhandled enumerations */
        break;
    }

    return len; /* partial match of something */
}