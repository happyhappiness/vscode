ap_log_cerror(APLOG_MARK, APLOG_ERR, status, session->c,
                          APLOGNO(02970) "nghttp2_submit_window_update: %s", 
                          nghttp2_strerror(*rv));