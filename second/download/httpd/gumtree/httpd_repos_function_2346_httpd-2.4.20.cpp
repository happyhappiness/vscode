h2_mplx *h2_mplx_create(conn_rec *c, apr_pool_t *parent, 
                        const h2_config *conf, 
                        apr_interval_time_t stream_timeout,
                        h2_workers *workers)
{
    apr_status_t status = APR_SUCCESS;
    apr_allocator_t *allocator = NULL;
    h2_mplx *m;
    AP_DEBUG_ASSERT(conf);
    
    status = apr_allocator_create(&allocator);
    if (status != APR_SUCCESS) {
        return NULL;
    }

    m = apr_pcalloc(parent, sizeof(h2_mplx));
    if (m) {
        m->id = c->id;
        APR_RING_ELEM_INIT(m, link);
        m->c = c;
        apr_pool_create_ex(&m->pool, parent, NULL, allocator);
        if (!m->pool) {
            return NULL;
        }
        apr_pool_tag(m->pool, "h2_mplx");
        apr_allocator_owner_set(allocator, m->pool);
        
        status = apr_thread_mutex_create(&m->lock, APR_THREAD_MUTEX_DEFAULT,
                                         m->pool);
        if (status != APR_SUCCESS) {
            h2_mplx_destroy(m);
            return NULL;
        }
        
        status = apr_thread_cond_create(&m->task_thawed, m->pool);
        if (status != APR_SUCCESS) {
            h2_mplx_destroy(m);
            return NULL;
        }
    
        m->bucket_alloc = apr_bucket_alloc_create(m->pool);
        m->max_streams = h2_config_geti(conf, H2_CONF_MAX_STREAMS);
        m->stream_max_mem = h2_config_geti(conf, H2_CONF_STREAM_MAX_MEM);
        m->q = h2_iq_create(m->pool, m->max_streams);
        m->stream_ios = h2_io_set_create(m->pool);
        m->ready_ios = h2_io_set_create(m->pool);
        m->stream_timeout = stream_timeout;
        m->workers = workers;
        m->workers_max = workers->max_workers;
        m->workers_def_limit = 4;
        m->workers_limit = m->workers_def_limit;
        m->last_limit_change = m->last_idle_block = apr_time_now();
        m->limit_change_interval = apr_time_from_msec(200);
        
        m->tx_handles_reserved = 0;
        m->tx_chunk_size = 4;
        
        m->spare_slaves = apr_array_make(m->pool, 10, sizeof(conn_rec*));
        
        m->ngn_shed = h2_ngn_shed_create(m->pool, m->c, m->max_streams, 
                                         m->stream_max_mem);
        h2_ngn_shed_set_ctx(m->ngn_shed , m);
    }
    return m;
}