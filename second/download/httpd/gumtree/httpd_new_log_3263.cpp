ap_log_rerror(APLOG_MARK,
                      (ctx->flags & SSI_FLAG_PRINTING)
                          ? APLOG_ERR : APLOG_WARNING,
                      0, r,
                      (ctx->argc)
                      ? APLOGNO(01352) "too many arguments for if element in %s"
                      : APLOGNO(01353) "missing expr argument for if element in %s",
                      r->filename);