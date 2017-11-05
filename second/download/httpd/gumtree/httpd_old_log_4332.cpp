ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, c,
                      "could not resolve address of OCSP responder %s", 
                      uri->hostinfo);