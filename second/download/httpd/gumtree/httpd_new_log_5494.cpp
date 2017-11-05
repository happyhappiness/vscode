ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                      "h2_session(%ld): destroy, %d streams open",
                      session->id, (int)h2_ihash_count(session->streams));