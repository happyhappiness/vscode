ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, c,
                      "could not connect to OCSP responder '%s'",
                      uri->hostinfo);