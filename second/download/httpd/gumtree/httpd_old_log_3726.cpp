ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "The request body must be present and must be a "
                      "DAV:merge element.");