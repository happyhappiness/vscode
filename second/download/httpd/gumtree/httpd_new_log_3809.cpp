ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                          "Expression condition for '%s' %s",
                          provider->frec->name,
                          match ? "matched" : "did not match");