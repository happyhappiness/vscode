ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                          "h2_session(%ld): unknown event %d", 
                          session->id, ev);