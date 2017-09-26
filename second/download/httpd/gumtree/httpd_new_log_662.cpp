ap_log_rerror(APLOG_MARK,
                      (!(ctx->if_nesting_level)) ? APLOG_ERR : APLOG_WARNING,
                      0, r, "endif directive does not take tags in %s",
                      r->filename);