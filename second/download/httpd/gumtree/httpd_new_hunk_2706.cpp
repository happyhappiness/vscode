            intern->state = PARSE_ARG_VAL;
            intern->quote = *p++;
            intern->current_arg->name = NULL;
            intern->current_arg->name_len = 0;
            intern->error = 1;

            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r, APLOGNO(01369) "missing "
                          "argument name for value to tag %s in %s",
                          apr_pstrmemdup(ctx->r->pool, intern->directive,
                                         intern->directive_len),
                                         ctx->r->filename);

            return (p - data);

        default:
            intern->state = PARSE_ARG_NAME;
        }
