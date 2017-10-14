ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01800)
                          "Authorization of user %s to access %s failed, reason: "
                          "user doesn't appear in DBM group file (%s).",
                          r->user, r->uri, conf->grpfile);