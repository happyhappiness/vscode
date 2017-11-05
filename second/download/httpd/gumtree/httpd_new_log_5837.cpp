ap_log_cerror( APLOG_MARK, APLOG_TRACE3, status, c,
                                      "h2_session(%ld): sync idle, stutter 1-sec, "
                                      "%d streams open", session->id,
                                      session->open_streams);