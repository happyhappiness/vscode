ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
                      "Authorization of user %s to access %s failed, reason: %s",
                      r->user, r->uri, reason ? reason : "unknown");