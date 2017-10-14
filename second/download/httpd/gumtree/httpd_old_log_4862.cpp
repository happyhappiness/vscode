ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, c,
                          "OCSP response size exceeds %u byte limit",
                          MAX_CONTENT);