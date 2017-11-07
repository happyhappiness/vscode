ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c, APLOGNO(03201)
                  "h2_session(%ld): start, INITIAL_WINDOW_SIZE=%ld, "
                  "MAX_CONCURRENT_STREAMS=%d", 
                  session->id, (long)win_size, (int)session->max_stream_count);