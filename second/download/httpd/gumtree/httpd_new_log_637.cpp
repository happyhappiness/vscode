ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "Missing '}' on "
                                  "variable \"%s\" in %s", p, r->filename);