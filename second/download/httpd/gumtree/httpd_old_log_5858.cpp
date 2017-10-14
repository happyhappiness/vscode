ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                  "h2_session(%ld): %d open streams",
                  session->id, (int)h2_stream_set_size(session->streams));