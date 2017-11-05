ap_log_rerror(APLOG_MARK,
                      (!(ctx->if_nesting_level)) ? APLOG_ERR : APLOG_WARNING,
                      0, r, APLOGNO(01361)
                      "endif directive does not take tags in %s",
                      r->filename);