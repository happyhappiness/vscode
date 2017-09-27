ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      MODNAME ": unexpected state %d; could be caused by bad "
                      "data in magic file",
                      state);