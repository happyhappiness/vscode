            ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_EGENERAL, c,
                          APLOGNO(02928) "nghttp2_option_new: %s", 
                          nghttp2_strerror(rv));
            h2_session_destroy(session);
            return NULL;
        }
        nghttp2_option_set_peer_max_concurrent_streams(options, 
                                                       (uint32_t)session->max_stream_count);
        /* We need to handle window updates ourself, otherwise we
         * get flooded by nghttp2. */
        nghttp2_option_set_no_auto_window_update(options, 1);
        
        if (APLOGctrace6(c)) {
            mem = apr_pcalloc(session->pool, sizeof(nghttp2_mem));
