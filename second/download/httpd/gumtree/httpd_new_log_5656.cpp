ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01667)
                    "Authorization of user %s to access %s failed, reason: "
                    "user is not part of the 'require'ed group(s).",
                    r->user, r->uri);