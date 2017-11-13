ap_log_rerror(APLOG_MARK, APLOG_ERR, APR_SUCCESS, r,
                          "authorization failure (no authenticated user): %s",
                          r->uri);