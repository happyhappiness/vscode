    if (acquired) {
        apr_threadkey_private_set(NULL, thread_lock);
        apr_thread_mutex_unlock(m->lock);
    }
}

static void beam_leave(void *ctx, apr_thread_mutex_t *lock)
{
    leave_mutex(ctx, 1);
}

static apr_status_t beam_enter(void *ctx, h2_beam_lock *pbl)
{
    h2_mplx *m = ctx;
    int acquired;
    apr_status_t status;
    
    status = enter_mutex(m, &acquired);
    if (status == APR_SUCCESS) {
        pbl->mutex = m->lock;
        pbl->leave = acquired? beam_leave : NULL;
        pbl->leave_ctx = m;
    }
    return status;
}

static void stream_output_consumed(void *ctx, 
                                   h2_bucket_beam *beam, apr_off_t length)
{
    h2_task *task = ctx;
    if (length > 0 && task && task->assigned) {
        h2_req_engine_out_consumed(task->assigned, task->c, length); 
    }
}

static void stream_input_consumed(void *ctx, 
                                  h2_bucket_beam *beam, apr_off_t length)
{
    h2_mplx *m = ctx;
    if (m->input_consumed && length) {
        m->input_consumed(m->input_consumed_ctx, beam->id, length);
    }
}

static int can_beam_file(void *ctx, h2_bucket_beam *beam,  apr_file_t *file)
{
    h2_mplx *m = ctx;
    if (m->tx_handles_reserved > 0) {
        --m->tx_handles_reserved;
        ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, m->c,
                      "h2_mplx(%ld-%d): beaming file %s, tx_avail %d", 
                      m->id, beam->id, beam->tag, m->tx_handles_reserved);
        return 1;
    }
    ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, m->c,
                  "h2_mplx(%ld-%d): can_beam_file denied on %s", 
                  m->id, beam->id, beam->tag);
    return 0;
}

static void have_out_data_for(h2_mplx *m, int stream_id);
static void task_destroy(h2_mplx *m, h2_task *task, int called_from_master);

static void check_tx_reservation(h2_mplx *m) 
{
    if (m->tx_handles_reserved <= 0) {
        m->tx_handles_reserved += h2_workers_tx_reserve(m->workers, 
            H2MIN(m->tx_chunk_size, h2_ihash_count(m->tasks)));
    }
}

static void check_tx_free(h2_mplx *m) 
{
    if (m->tx_handles_reserved > m->tx_chunk_size) {
        apr_size_t count = m->tx_handles_reserved - m->tx_chunk_size;
        m->tx_handles_reserved = m->tx_chunk_size;
        h2_workers_tx_free(m->workers, count);
    }
    else if (m->tx_handles_reserved && h2_ihash_empty(m->tasks)) {
        h2_workers_tx_free(m->workers, m->tx_handles_reserved);
        m->tx_handles_reserved = 0;
    }
}

static int purge_stream(void *ctx, void *val) 
{
    h2_mplx *m = ctx;
    h2_stream *stream = val;
    h2_task *task = h2_ihash_get(m->tasks, stream->id);
    h2_ihash_remove(m->spurge, stream->id);
    h2_stream_destroy(stream);
    if (task) {
        task_destroy(m, task, 1);
    }
    return 0;
}

static void purge_streams(h2_mplx *m)
{
    if (!h2_ihash_empty(m->spurge)) {
        while(!h2_ihash_iter(m->spurge, purge_stream, m)) {
            /* repeat until empty */
        }
        h2_ihash_clear(m->spurge);
    }
}

static void h2_mplx_destroy(h2_mplx *m)
{
    AP_DEBUG_ASSERT(m);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                  "h2_mplx(%ld): destroy, tasks=%d", 
                  m->id, (int)h2_ihash_count(m->tasks));
    check_tx_free(m);
    if (m->pool) {
        apr_pool_destroy(m->pool);
    }
}

