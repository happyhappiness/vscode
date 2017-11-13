ap_log_cerror( APLOG_MARK, APLOG_TRACE3, status, c,
                                          "h2_session(%ld): idle(1 sec timeout) "
                                          "read failed", session->id);