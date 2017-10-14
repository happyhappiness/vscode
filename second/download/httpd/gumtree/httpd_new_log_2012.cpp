ap_log_rerror(APLOG_MARK, APLOG_TRACE3, rv, r,
                          "proxy: SSL cleanup brigade contained %"
                          APR_OFF_T_FMT " bytes of data.", len);