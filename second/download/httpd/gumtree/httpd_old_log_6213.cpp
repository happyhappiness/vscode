ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                          "h2_session(%ld): destroy, %d streams open",
                          session->id, (int)h2_stream_set_size(session->streams));