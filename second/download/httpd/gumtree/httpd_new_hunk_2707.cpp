    case PARSE_ARG_POSTNAME:
        intern->current_arg->name = apr_pstrmemdup(ctx->dpool,
                                                 intern->current_arg->name,
                                                 intern->current_arg->name_len);
        if (!intern->current_arg->name_len) {
            intern->error = 1;
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r, APLOGNO(01370) "missing "
                          "argument name for value to tag %s in %s",
                          apr_pstrmemdup(ctx->r->pool, intern->directive,
                                         intern->directive_len),
                                         ctx->r->filename);
        }
        else {
            ap_str_tolower(intern->current_arg->name);
        }

        intern->state = PARSE_ARG_EQ;
        /* continue with next state immediately */

    case PARSE_ARG_EQ:
