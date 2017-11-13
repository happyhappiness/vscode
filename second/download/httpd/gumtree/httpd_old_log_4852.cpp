ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, c,
                          "failed to send request to OCSP responder '%s'",
                          uri->hostinfo);