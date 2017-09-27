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
