static apr_size_t find_argument(include_ctx_t *ctx, const char *data,
                                apr_size_t len, char ***store,
                                apr_size_t **store_len)
{
    struct ssi_internal_ctx *intern = ctx->intern;
    const char *p = data;
    const char *ep = data + len;

    switch (intern->state) {
    case PARSE_ARG:
        /*
         * create argument structure and append it to the current list
         */
        intern->current_arg = apr_palloc(ctx->dpool,
                                         sizeof(*intern->current_arg));
        intern->current_arg->next = NULL;

        ++(ctx->argc);
        if (!intern->argv) {
            intern->argv = intern->current_arg;
        }
        else {
            arg_item_t *newarg = intern->argv;

            while (newarg->next) {
                newarg = newarg->next;
            }
            newarg->next = intern->current_arg;
        }

        /* check whether it's a valid one. If it begins with a quote, we
         * can safely assume, someone forgot the name of the argument
         */
        switch (*p) {
        case '"': case '\'': case '`':
            *store = NULL;

            intern->state = PARSE_ARG_VAL;
            intern->quote = *p++;
            intern->current_arg->name = NULL;
            intern->current_arg->name_len = 0;
            intern->error = 1;

            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, intern->r, "missing "
                          "argument name for value to tag %s in %s",
                          apr_pstrmemdup(intern->r->pool, intern->directive,
                                         intern->directive_len),
                                         intern->r->filename);

            return (p - data);

        default:
            intern->state = PARSE_ARG_NAME;
        }
        /* continue immediately with next state */

    case PARSE_ARG_NAME:
        while (p < ep && !apr_isspace(*p) && *p != '=') {
            ++p;
        }

        if (p < ep) {
            intern->state = PARSE_ARG_POSTNAME;
            *store = &intern->current_arg->name;
            *store_len = &intern->current_arg->name_len;
            return (p - data);
        }
        break;

    case PARSE_ARG_POSTNAME:
        intern->current_arg->name = apr_pstrmemdup(ctx->dpool,
                                                 intern->current_arg->name,
                                                 intern->current_arg->name_len);
        if (!intern->current_arg->name_len) {
            intern->error = 1;
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, intern->r, "missing "
                          "argument name for value to tag %s in %s",
                          apr_pstrmemdup(intern->r->pool, intern->directive,
                                         intern->directive_len),
                                         intern->r->filename);
        }
        else {
            char *sp = intern->current_arg->name;

            /* normalize the name */
            while (*sp) {
                *sp = apr_tolower(*sp);
                ++sp;
            }
        }

        intern->state = PARSE_ARG_EQ;
        /* continue with next state immediately */

    case PARSE_ARG_EQ:
        *store = NULL;

        while (p < ep && apr_isspace(*p)) {
            ++p;
        }

        if (p < ep) {
            if (*p == '=') {
                intern->state = PARSE_ARG_PREVAL;
                ++p;
            }
            else { /* no value */
                intern->current_arg->value = NULL;
                intern->state = PARSE_PRE_ARG;
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
            intern->state = PARSE_ARG_VAL;
            switch (*p) {
            case '"': case '\'': case '`':
                intern->quote = *p++;
                break;
            default:
                intern->quote = '\0';
                break;
            }

            return (p - data);
        }
        break;

    case PARSE_ARG_VAL_ESC:
        if (*p == intern->quote) {
            ++p;
        }
        intern->state = PARSE_ARG_VAL;
        /* continue with next state immediately */

    case PARSE_ARG_VAL:
        for (; p < ep; ++p) {
            if (intern->quote && *p == '\\') {
                ++p;
                if (p == ep) {
                    intern->state = PARSE_ARG_VAL_ESC;
                    break;
                }

                if (*p != intern->quote) {
                    --p;
                }
            }
            else if (intern->quote && *p == intern->quote) {
                ++p;
                *store = &intern->current_arg->value;
                *store_len = &intern->current_arg->value_len;
                intern->state = PARSE_ARG_POSTVAL;
                break;
            }
            else if (!intern->quote && apr_isspace(*p)) {
                ++p;
                *store = &intern->current_arg->value;
                *store_len = &intern->current_arg->value_len;
                intern->state = PARSE_ARG_POSTVAL;
                break;
            }
        }

        return (p - data);

    case PARSE_ARG_POSTVAL:
        /*
         * The value is still the raw input string. Finally clean it up.
         */
        --(intern->current_arg->value_len);

        /* strip quote escaping \ from the string */
        if (intern->quote) {
            apr_size_t shift = 0;
            char *sp;

            sp = intern->current_arg->value;
            ep = intern->current_arg->value + intern->current_arg->value_len;
            while (sp < ep && *sp != '\\') {
                ++sp;
            }
            for (; sp < ep; ++sp) {
                if (*sp == '\\' && sp[1] == intern->quote) {
                    ++sp;
                    ++shift;
                }
                if (shift) {
                    *(sp-shift) = *sp;
                }
            }

            intern->current_arg->value_len -= shift;
        }

        intern->current_arg->value[intern->current_arg->value_len] = '\0';
        intern->state = PARSE_PRE_ARG;

        return 0;

    default:
        /* get a rid of a gcc warning about unhandled enumerations */
        break;
    }

    return len; /* partial match of something */
}