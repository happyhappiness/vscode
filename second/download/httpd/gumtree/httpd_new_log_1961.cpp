ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r,
                          "proxy: CONNECT: error on %s - ap_get_brigade",
                          name);