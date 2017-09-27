ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "brigade: [%d] %s", i, e->type->name);