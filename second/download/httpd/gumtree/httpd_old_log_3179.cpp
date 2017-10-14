ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "Cached authn credentials for %s in %s",
                      user, dcfg->context);