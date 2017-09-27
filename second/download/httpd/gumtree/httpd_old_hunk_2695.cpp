    request_rec *r = f->r;

    if (!ctx->argc) {
        ap_log_rerror(APLOG_MARK,
                      (ctx->flags & SSI_FLAG_PRINTING)
                          ? APLOG_ERR : APLOG_WARNING,
                      0, r, "missing argument for flastmod element in %s",
                      r->filename);
    }

    if (!(ctx->flags & SSI_FLAG_PRINTING)) {
        return APR_SUCCESS;
    }
