 *   Since HTTP/2 connections can be expected to live longer than
 *   their HTTP/1 cousins, the separate allocator seems to work better
 *   than protecting a shared h2_session one with an own lock.
 */
h2_mplx *h2_mplx_create(conn_rec *c, apr_pool_t *parent, 
                        const h2_config *conf, 
                        h2_workers *workers)
{
    apr_status_t status = APR_SUCCESS;
    apr_allocator_t *allocator;
    apr_thread_mutex_t *mutex;
    h2_mplx *m;
    h2_ctx *ctx = h2_ctx_get(c, 0);
    ap_assert(conf);
    
    m = apr_pcalloc(parent, sizeof(h2_mplx));
    if (m) {
        m->id = c->id;
        m->c = c;
        m->s = (ctx? h2_ctx_server_get(ctx) : NULL);
        if (!m->s) {
            m->s = c->base_server;
        }
        
        /* We create a pool with its own allocator to be used for
         * processing slave connections. This is the only way to have the
         * processing independant of its parent pool in the sense that it
         * can work in another thread. Also, the new allocator needs its own
         * mutex to synchronize sub-pools.
         */
        status = apr_allocator_create(&allocator);
        if (status != APR_SUCCESS) {
            return NULL;
        }
        apr_allocator_max_free_set(allocator, ap_max_mem_free);
        apr_pool_create_ex(&m->pool, parent, NULL, allocator);
        if (!m->pool) {
            apr_allocator_destroy(allocator);
            return NULL;
        }
        apr_pool_tag(m->pool, "h2_mplx");
        apr_allocator_owner_set(allocator, m->pool);
        status = apr_thread_mutex_create(&mutex, APR_THREAD_MUTEX_DEFAULT,
                                         m->pool);
        if (status != APR_SUCCESS) {
            apr_pool_destroy(m->pool);
            return NULL;
        }
        apr_allocator_mutex_set(allocator, mutex);

        status = apr_thread_mutex_create(&m->lock, APR_THREAD_MUTEX_DEFAULT,
                                         m->pool);
        if (status != APR_SUCCESS) {
            apr_pool_destroy(m->pool);
            return NULL;
        }
        
        status = apr_thread_cond_create(&m->task_thawed, m->pool);
        if (status != APR_SUCCESS) {
            apr_pool_destroy(m->pool);
            return NULL;
        }
    
        m->max_streams = h2_config_geti(conf, H2_CONF_MAX_STREAMS);
        m->stream_max_mem = h2_config_geti(conf, H2_CONF_STREAM_MAX_MEM);

        m->streams = h2_ihash_create(m->pool, offsetof(h2_stream,id));
        m->sredo = h2_ihash_create(m->pool, offsetof(h2_stream,id));
        m->shold = h2_ihash_create(m->pool, offsetof(h2_stream,id));
        m->spurge = h2_ihash_create(m->pool, offsetof(h2_stream,id));
        m->q = h2_iq_create(m->pool, m->max_streams);

        status = h2_fifo_set_create(&m->readyq, m->pool, m->max_streams);
        if (status != APR_SUCCESS) {
            apr_pool_destroy(m->pool);
            return NULL;
        }

        m->workers = workers;
        m->max_active = workers->max_workers;
        m->limit_active = 6; /* the original h1 max parallel connections */
        m->last_limit_change = m->last_idle_block = apr_time_now();
        m->limit_change_interval = apr_time_from_msec(100);
        
        m->spare_slaves = apr_array_make(m->pool, 10, sizeof(conn_rec*));
        
        m->ngn_shed = h2_ngn_shed_create(m->pool, m->c, m->max_streams, 
                                         m->stream_max_mem);
        h2_ngn_shed_set_ctx(m->ngn_shed , m);
    }
    return m;
}

int h2_mplx_shutdown(h2_mplx *m)
{
    int max_stream_started = 0;
    
    H2_MPLX_ENTER(m);

    max_stream_started = m->max_stream_started;
    /* Clear schedule queue, disabling existing streams from starting */ 
    h2_iq_clear(m->q);

    H2_MPLX_LEAVE(m);
    return max_stream_started;
}

static int input_consumed_signal(h2_mplx *m, h2_stream *stream)
{
    if (stream->input) {
        return h2_beam_report_consumption(stream->input);
    }
    return 0;
}

static int report_consumption_iter(void *ctx, void *val)
{
    h2_stream *stream = val;
    h2_mplx *m = ctx;
    
    input_consumed_signal(m, stream);
    if (stream->state == H2_SS_CLOSED_L
        && (!stream->task || stream->task->worker_done)) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, m->c, 
                      H2_STRM_LOG(APLOGNO(10026), stream, "remote close missing")); 
        nghttp2_submit_rst_stream(stream->session->ngh2, NGHTTP2_FLAG_NONE, 
                                  stream->id, NGHTTP2_NO_ERROR);
    }
    return 1;
}

static int output_consumed_signal(h2_mplx *m, h2_task *task)
{
    if (task->output.beam) {
        return h2_beam_report_consumption(task->output.beam);
    }
    return 0;
}

static void task_destroy(h2_mplx *m, h2_task *task)
{
    conn_rec *slave = NULL;
    int reuse_slave = 0;
    
    slave = task->c;

    if (m->s->keep_alive_max == 0 || slave->keepalives < m->s->keep_alive_max) {
        reuse_slave = ((m->spare_slaves->nelts < (m->limit_active * 3 / 2))
                       && !task->rst_error);
    }
    
    if (slave) {
        if (reuse_slave && slave->keepalive == AP_CONN_KEEPALIVE) {
            h2_beam_log(task->output.beam, m->c, APLOG_DEBUG, 
                        APLOGNO(03385) "h2_task_destroy, reuse slave");    
            h2_task_destroy(task);
            APR_ARRAY_PUSH(m->spare_slaves, conn_rec*) = slave;
        }
        else {
            h2_beam_log(task->output.beam, m->c, APLOG_TRACE1, 
                        "h2_task_destroy, destroy slave");    
            slave->sbh = NULL;
            h2_slave_destroy(slave);
        }
    }
}

static int stream_destroy_iter(void *ctx, void *val) 
{   
    h2_mplx *m = ctx;
    h2_stream *stream = val;

    h2_ihash_remove(m->spurge, stream->id);
    ap_assert(stream->state == H2_SS_CLEANUP);
    
    if (stream->input) {
        /* Process outstanding events before destruction */
        input_consumed_signal(m, stream);    
        h2_beam_log(stream->input, m->c, APLOG_TRACE2, "stream_destroy");
        h2_beam_destroy(stream->input);
        stream->input = NULL;
    }

    if (stream->task) {
        task_destroy(m, stream->task);
        stream->task = NULL;
    }
    h2_stream_destroy(stream);
    return 0;
}

static void purge_streams(h2_mplx *m, int lock)
{
    if (!h2_ihash_empty(m->spurge)) {
        H2_MPLX_ENTER_MAYBE(m, lock);
        while (!h2_ihash_iter(m->spurge, stream_destroy_iter, m)) {
            /* repeat until empty */
        }
        H2_MPLX_LEAVE_MAYBE(m, lock);
    }
}

typedef struct {
    h2_mplx_stream_cb *cb;
    void *ctx;
} stream_iter_ctx_t;
