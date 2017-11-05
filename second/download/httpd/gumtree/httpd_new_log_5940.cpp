ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r, APLOGNO(02430)
                      "Response header '%s' value of '%s' contains invalid "
                      "characters, aborting request",
                      name, val);