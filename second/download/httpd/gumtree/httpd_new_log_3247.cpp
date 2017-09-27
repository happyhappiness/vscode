ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01813)
        "internal redirect requested but one or all of method, mimetype or "
                      "body are NULL: %s", r->uri);