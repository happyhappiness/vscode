    if (win_size != H2_INITIAL_WINDOW_SIZE) {
        settings[slen].settings_id = NGHTTP2_SETTINGS_INITIAL_WINDOW_SIZE;
        settings[slen].value = win_size;
        ++slen;
    }
    
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c, APLOGNO(03201)
                  "h2_session(%ld): start, INITIAL_WINDOW_SIZE=%ld, "
                  "MAX_CONCURRENT_STREAMS=%d", 
                  session->id, (long)win_size, (int)session->max_stream_count);
    *rv = nghttp2_submit_settings(session->ngh2, NGHTTP2_FLAG_NONE,
                                  settings, slen);
    if (*rv != 0) {
        status = APR_EGENERAL;
        ap_log_cerror(APLOG_MARK, APLOG_ERR, status, session->c,
                      APLOGNO(02935) "nghttp2_submit_settings: %s", 
                      nghttp2_strerror(*rv));
    }
    else {
        /* use maximum possible value for connection window size. We are only
         * interested in per stream flow control. which have the initial window
         * size configured above.
         * Therefore, for our use, the connection window can only get in the
