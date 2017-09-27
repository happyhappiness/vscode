ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01805)
                  "Authorization of user %s to access %s failed, reason: "
                  "user is not part of the 'require'ed group(s).",
                  r->user, r->uri);