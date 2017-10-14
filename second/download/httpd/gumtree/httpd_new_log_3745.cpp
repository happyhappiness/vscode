ap_log_rerror(APLOG_MARK,
                      (!(ctx->if_nesting_level)) ? APLOG_ERR : APLOG_WARNING,
                      0, r,
                      (ctx->argc)
                      ? APLOGNO(01356) "too many arguments for if element in %s"
                      : APLOGNO(01357) "missing expr argument for if element in %s",
                      r->filename);