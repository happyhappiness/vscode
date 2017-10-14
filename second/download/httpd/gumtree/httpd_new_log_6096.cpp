ap_log_cerror( APLOG_MARK, APLOG_TRACE1, status, c,
                                  "h2_session(%ld): async idle, nonblock read", session->id);