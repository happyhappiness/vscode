ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                          "Content-Type condition for '%s' did not match: "
                          "no Content-Type", provider->frec->name);