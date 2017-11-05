ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01088)
                              "Request body is larger than the configured "
                              "limit of %" APR_OFF_T_FMT, limit);