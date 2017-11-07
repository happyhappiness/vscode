ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, c,
                      H2_SSSN_LOG(APLOGNO(10020), session, 
                      "session cleanup triggered by pool cleanup. "
                      "this should have happened earlier already."));