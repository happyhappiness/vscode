ap_log_cerror(APLOG_MARK, APLOG_TRACE3, status, c,
                                      H2_SSSN_MSG(session, 
                                      "nonblock read, %d streams open"), 
                                      session->open_streams);