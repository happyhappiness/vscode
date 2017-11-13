ap_log_rerror(APLOG_MARK,
                      (ctx->flags & SSI_FLAG_PRINTING)
                          ? APLOG_ERR : APLOG_WARNING,
                      0, r,
                      APLOGNO(01367) "printenv directive does not take tags in %s",
                      r->filename);