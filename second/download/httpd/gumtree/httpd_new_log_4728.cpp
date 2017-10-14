ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02018)
                          "request body exceeds maximum size (%" APR_SIZE_T_FMT
                          ") for SSL buffer", maxlen);