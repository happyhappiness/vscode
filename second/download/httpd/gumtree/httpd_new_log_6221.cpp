ap_log_cerror(APLOG_MARK, APLOG_ERR, status, session->c,
                          H2_SSSN_LOG(APLOGNO(02970), session,
                          "nghttp2_submit_window_update: %s"), 
                          nghttp2_strerror(*rv));