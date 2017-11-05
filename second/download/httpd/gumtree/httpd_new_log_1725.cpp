ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                              "proxy: CONNECT: error on %s - ap_pass_brigade",
                              name);