ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "proxy: %s: found worker %s for %s",
                           (*worker)->scheme, (*worker)->name, *url);