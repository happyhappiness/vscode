ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "Failed to cache authn credentials for %s in %s",
                      module, dcfg->context);