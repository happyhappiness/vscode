ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c, 
                  H2_SSSN_LOG(APLOGNO(03201), session, 
                  "start, INITIAL_WINDOW_SIZE=%ld, MAX_CONCURRENT_STREAMS=%d"), 
                  (long)win_size, (int)session->max_stream_count);