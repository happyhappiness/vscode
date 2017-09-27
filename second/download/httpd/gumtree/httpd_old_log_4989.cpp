ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "OCSP stapling response too big (%u bytes)", resp_derlen);