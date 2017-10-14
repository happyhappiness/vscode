ap_log_cerror( APLOG_MARK, APLOG_DEBUG, status, c,
                                      "h2_session(%ld): idle, no data, error", 
                                      session->id);