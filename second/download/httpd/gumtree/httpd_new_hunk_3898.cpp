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
            mem->mem_user_data = session;
            mem->malloc    = session_malloc;
            mem->free      = session_free;
            mem->calloc    = session_calloc;
            mem->realloc   = session_realloc;
            
            rv = nghttp2_session_server_new3(&session->ngh2, callbacks,
                                             session, options, mem);
        }
        else {
            rv = nghttp2_session_server_new2(&session->ngh2, callbacks,
                                             session, options);
        }
        nghttp2_session_callbacks_del(callbacks);
        nghttp2_option_del(options);
        
        if (rv != 0) {
            ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_EGENERAL, c,
                          APLOGNO(02929) "nghttp2_session_server_new: %s",
