}

static void workers_unregister(h2_mplx *m) {
    h2_workers_unregister(m->workers, m);
}

static int io_process_events(h2_mplx *m, h2_io *io) {
    if (io->input_consumed && m->input_consumed) {
        m->input_consumed(m->input_consumed_ctx, 
                          io->id, io->input_consumed);
        io->input_consumed = 0;
        return 1;
    }
    return 0;
}


static void io_destroy(h2_mplx *m, h2_io *io, int events)
{
    apr_pool_t *pool = io->pool;
    
    /* cleanup any buffered input */
    h2_io_in_shutdown(io);
    if (events) {
        /* Process outstanding events before destruction */
        io_process_events(m, io);
    }
    
    io->pool = NULL;    
    /* The pool is cleared/destroyed which also closes all
     * allocated file handles. Give this count back to our
     * file handle pool. */
    m->file_handles_allowed += io->files_handles_owned;
    h2_io_set_remove(m->stream_ios, io);
    h2_io_set_remove(m->ready_ios, io);
    h2_io_destroy(io);
    
    if (pool) {
        apr_pool_clear(pool);
        if (m->spare_pool) {
            apr_pool_destroy(m->spare_pool);
        }
        m->spare_pool = pool;
    }
}

static int io_stream_done(h2_mplx *m, h2_io *io, int rst_error) 
{
    /* Remove io from ready set, we will never submit it */
    h2_io_set_remove(m->ready_ios, io);
    if (io->task_done || h2_tq_remove(m->q, io->id)) {
        /* already finished or not even started yet */
        io_destroy(m, io, 1);
        return 0;
    }
    else {
        /* cleanup once task is done */
        io->orphaned = 1;
        if (rst_error) {
            h2_io_rst(io, rst_error);
        }
        return 1;
    }
}

static int stream_done_iter(void *ctx, h2_io *io) {
    return io_stream_done((h2_mplx*)ctx, io, 0);
}

apr_status_t h2_mplx_release_and_join(h2_mplx *m, apr_thread_cond_t *wait)
{
    apr_status_t status;
    
    workers_unregister(m);
    status = apr_thread_mutex_lock(m->lock);
    if (APR_SUCCESS == status) {
        while (!h2_io_set_iter(m->stream_ios, stream_done_iter, m)) {
            /* iterator until all h2_io have been orphaned or destroyed */
        }
    
        release(m, 0);
        while (m->refs > 0) {
            m->join_wait = wait;
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, m->c,
                          "h2_mplx(%ld): release_join, refs=%d, waiting...", 
                          m->id, m->refs);
            apr_thread_cond_wait(wait, m->lock);
        }
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, m->c,
                      "h2_mplx(%ld): release_join -> destroy, (#ios=%ld)", 
                      m->id, (long)h2_io_set_size(m->stream_ios));
        h2_mplx_destroy(m);
        /* all gone */
        /*apr_thread_mutex_unlock(m->lock);*/
    }
    return status;
}

void h2_mplx_abort(h2_mplx *m)
{
    apr_status_t status;
    AP_DEBUG_ASSERT(m);
    status = apr_thread_mutex_lock(m->lock);
    if (APR_SUCCESS == status) {
        m->aborted = 1;
        apr_thread_mutex_unlock(m->lock);
    }
}

apr_status_t h2_mplx_stream_done(h2_mplx *m, int stream_id, int rst_error)
{
    apr_status_t status;
    
    AP_DEBUG_ASSERT(m);
    status = apr_thread_mutex_lock(m->lock);
    if (APR_SUCCESS == status) {
        h2_io *io = h2_io_set_get(m->stream_ios, stream_id);

        /* there should be an h2_io, once the stream has been scheduled
         * for processing, e.g. when we received all HEADERs. But when
         * a stream is cancelled very early, it will not exist. */
        if (io) {
            io_stream_done(m, io, rst_error);
        }
        
        apr_thread_mutex_unlock(m->lock);
    }
    return status;
}

void h2_mplx_task_done(h2_mplx *m, int stream_id)
{
    apr_status_t status = apr_thread_mutex_lock(m->lock);
    if (APR_SUCCESS == status) {
        h2_io *io = h2_io_set_get(m->stream_ios, stream_id);
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c,
                      "h2_mplx(%ld): task(%d) done", m->id, stream_id);
        if (io) {
            io->task_done = 1;
            if (io->orphaned) {
                io_destroy(m, io, 0);
            }
            else {
                /* hang around until the stream deregisteres */
            }
        }
        apr_thread_mutex_unlock(m->lock);
    }
}

apr_status_t h2_mplx_in_read(h2_mplx *m, apr_read_type_e block,
