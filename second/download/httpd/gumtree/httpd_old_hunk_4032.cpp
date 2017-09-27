                  session->id, (long)size);
    return realloc(p, size);
}

static h2_session *h2_session_create_int(conn_rec *c,
                                         request_rec *r,
                                         const h2_config *config, 
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
        nghttp2_mem *mem;
        
        session->id = c->id;
        session->c = c;
        session->r = r;
        session->config = config;
        
        session->pool = pool;
        apr_pool_pre_cleanup_register(pool, session, session_pool_cleanup);
        
        session->max_stream_count = h2_config_geti(config, H2_CONF_MAX_STREAMS);
        session->max_stream_mem = h2_config_geti(config, H2_CONF_STREAM_MAX_MEM);

        status = apr_thread_cond_create(&session->iowait, session->pool);
        if (status != APR_SUCCESS) {
            return NULL;
        }
        
        session->streams = h2_stream_set_create(session->pool, session->max_stream_count);
        
        session->workers = workers;
        session->mplx = h2_mplx_create(c, session->pool, config, workers);
        
        h2_mplx_set_consumed_cb(session->mplx, update_window, session);
        
        h2_conn_io_init(&session->io, c, config, session->pool);
        session->bbtmp = apr_brigade_create(session->pool, c->bucket_alloc);
        
        status = init_callbacks(c, &callbacks);
        if (status != APR_SUCCESS) {
            ap_log_cerror(APLOG_MARK, APLOG_ERR, status, c, APLOGNO(02927) 
                          "nghttp2: error in init_callbacks");
