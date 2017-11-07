ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                          "h2_session(%ld): conn error -> shutdown", session->id);