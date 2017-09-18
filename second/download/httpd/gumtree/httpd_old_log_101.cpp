ap_log_rerror(APLOG_MARK, APLOG_ERR | APLOG_NOERRNO, 0, r,
                      "Depth must be 0 or \"infinity\" for LOCK.");