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
