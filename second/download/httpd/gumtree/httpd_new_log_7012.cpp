ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, c,
                      H2_SSSN_LOG(APLOGNO(03199), session, 
                      "connection disappeared without proper "
                      "goodbye, clients will be confused, should not happen"));