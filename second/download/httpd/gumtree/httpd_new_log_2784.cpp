ap_log_rerror(APLOG_MARK, APLOG_ERR, APR_SUCCESS, r, APLOGNO(01629)
                          "authorization failure (no authenticated user): %s",
                          r->uri);