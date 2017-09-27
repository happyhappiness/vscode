ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00674)
                              "cannot redirect '%s' to '%s'; "
                              "target is not a valid absoluteURI or abs_path",
                              r->uri, ret);