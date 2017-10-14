ap_log_rerror(APLOG_MARK,
                      (ctx->flags & SSI_FLAG_PRINTING)
                          ? APLOG_ERR : APLOG_WARNING,
                      0, r, APLOGNO(01350)
                      "missing argument for fsize element in %s",
                      r->filename);