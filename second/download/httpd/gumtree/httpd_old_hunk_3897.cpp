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
