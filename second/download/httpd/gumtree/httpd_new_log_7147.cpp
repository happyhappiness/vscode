ap_log_rerror(APLOG_MARK, APLOG_TRACE4, 0, r,
                              "fix_cgivars: override %s from '%s' to '%s'",
                              entry->envname, oldval, val);