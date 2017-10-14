ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                  "Authorization of user %s to access %s failed, reason: %s",
                  r->user, r->uri,
                  reason ? reason : "user is not part of the "
                                    "'require'ed group(s).");