ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, f->r,
                      "couldn't find definition of filter '%s'",
                      f->frec->name);