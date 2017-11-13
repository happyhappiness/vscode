ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, LOG_PREFIX
        "internal redirect requested but one or all of method, mimetype or "
                      "body are NULL: %s", r->uri);