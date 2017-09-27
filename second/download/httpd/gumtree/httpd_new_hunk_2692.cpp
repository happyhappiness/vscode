    apr_table_t *env = r->subprocess_env;

    if (!ctx->argc) {
        ap_log_rerror(APLOG_MARK,
                      (ctx->flags & SSI_FLAG_PRINTING)
                          ? APLOG_ERR : APLOG_WARNING,
                      0, r, APLOGNO(01347)
                      "missing argument for config element in %s",
                      r->filename);
    }

    if (!(ctx->flags & SSI_FLAG_PRINTING)) {
        return APR_SUCCESS;
    }
