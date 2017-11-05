ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                                  "access to %s failed; stat of '%s' failed.",
                                  r->uri, r->filename);