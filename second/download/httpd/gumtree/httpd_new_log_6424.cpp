ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                          "h2_session(%ld): NO_IO event, %d streams open", 
                          session->id, session->open_streams);