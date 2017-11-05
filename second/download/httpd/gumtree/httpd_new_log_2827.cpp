ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(01638)
                      "Authorization of user %s to access %s failed, reason: %s",
                      r->user, r->uri, reason ? reason : "unknown");