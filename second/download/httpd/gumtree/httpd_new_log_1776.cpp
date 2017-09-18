ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, 
                      "total of %" APR_OFF_T_FMT " bytes in buffer, eos=%d",
                      total, eos);