ap_log_cerror(APLOG_MARK, APLOG_TRACE3, status, c,
                                      H2_SSSN_MSG(session, 
                                      "sync, stutter 1-sec, %d streams open"), 
                                      session->open_streams);