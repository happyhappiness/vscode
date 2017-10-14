ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Error looking up %s:%s in database", user, realm);