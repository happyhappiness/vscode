ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "Digest: user %s: password mismatch: %s", r->user,
                          r->uri);