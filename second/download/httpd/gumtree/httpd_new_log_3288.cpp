ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01671)
                  "Authorization of user %s to access %s failed, reason: "
                  "user is not part of the 'require'ed file group.",
                  r->user, r->uri);