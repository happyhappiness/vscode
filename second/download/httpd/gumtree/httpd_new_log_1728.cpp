ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Authorization of user %s to access %s failed, reason: "
                      "user doesn't appear in group file (%s).",
                      r->user, r->uri, conf->groupfile);