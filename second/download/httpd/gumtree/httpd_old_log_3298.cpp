ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "mod_asis: failed to find end-of-headers position "
                          "for %s", r->filename);