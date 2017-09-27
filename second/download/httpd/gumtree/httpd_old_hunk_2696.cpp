    int expr_ret, was_error;

    if (ctx->argc != 1) {
        ap_log_rerror(APLOG_MARK,
                      (ctx->flags & SSI_FLAG_PRINTING)
                          ? APLOG_ERR : APLOG_WARNING,
                      0, r, (ctx->argc)
                                ? "too many arguments for if element in %s"
                                : "missing expr argument for if element in %s",
                      r->filename);
    }

    if (!(ctx->flags & SSI_FLAG_PRINTING)) {
        ++(ctx->if_nesting_level);
        return APR_SUCCESS;
