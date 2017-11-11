static h2_session *h2_session_create_int(conn_rec *c,
                                         request_rec *r,
                                         h2_config *config, 
                                         h2_workers *workers)
{
    nghttp2_session_callbacks *callbacks = NULL;
    nghttp2_option *options = NULL;

    apr_pool_t *pool = NULL;
    apr_status_t status = apr_pool_create(&pool, r? r->pool : c->pool);
    h2_session *session;
    if (status != APR_SUCCESS) {
        return NULL;
    }

    session = apr_pcalloc(pool, sizeof(h2_session));
    if (session) {
        int rv;
        session->id = c->id;
        session->c = c;
        session->r = r;
        
        session->max_stream_count = h2_config_geti(config, H2_CONF_MAX_STREAMS);
        session->max_stream_mem = h2_config_geti(config, H2_CONF_STREAM_MAX_MEM);

        session->pool = pool;
        
        status = apr_thread_cond_create(&session->iowait, session->pool);
        if (status != APR_SUCCESS) {
            return NULL;
        }
        
        session->streams = h2_stream_set_create(session->pool);
        
        session->workers = workers;
        session->mplx = h2_mplx_create(c, session->pool, workers);
        
        h2_conn_io_init(&session->io, c);
        session->bbtmp = apr_brigade_create(session->pool, c->bucket_alloc);
        
        status = init_callbacks(c, &callbacks);
        if (status != APR_SUCCESS) {
            ap_log_cerror(APLOG_MARK, APLOG_ERR, status, c, APLOGNO(02927) 
                          "nghttp2: error in init_callbacks");
            h2_session_destroy(session);
            return NULL;
        }
        
        rv = nghttp2_option_new(&options);
        if (rv != 0) {
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
        
        rv = nghttp2_session_server_new2(&session->ngh2, callbacks,
                                         session, options);
        nghttp2_session_callbacks_del(callbacks);
        nghttp2_option_del(options);
        
        if (rv != 0) {
            ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_EGENERAL, c,
                          APLOGNO(02929) "nghttp2_session_server_new: %s",
                          nghttp2_strerror(rv));
            h2_session_destroy(session);
            return NULL;
        }
        
    }
    return session;
}