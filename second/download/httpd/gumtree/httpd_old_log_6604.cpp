ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c, 
                      "proxy_session(%s): pool cleanup, state=%d, streams=%d",
                      session->id, session->state, 
                      (int)h2_ihash_count(session->streams));