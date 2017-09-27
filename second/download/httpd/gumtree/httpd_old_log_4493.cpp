ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "proxy: FCGI: sending env var '%s' value '%s'",
                      elts[i].key, elts[i].val);