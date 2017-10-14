ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
                      "OCSP response: got %" APR_SIZE_T_FMT 
                      " bytes, %" APR_SIZE_T_FMT " total", len, count);