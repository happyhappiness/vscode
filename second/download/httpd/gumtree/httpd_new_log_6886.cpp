ap_log_cerror(APLOG_MARK, APLOG_TRACE3, status, c,
                                          H2_SSSN_MSG(session, 
                                          "keepalive, %f sec left"),
                                          (session->idle_until - now) / 1000000.0f);