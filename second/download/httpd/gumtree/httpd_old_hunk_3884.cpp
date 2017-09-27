}

static void workers_unregister(h2_mplx *m) {
    h2_workers_unregister(m->workers, m);
}

apr_status_t h2_mplx_release_and_join(h2_mplx *m, apr_thread_cond_t *wait)
{
    apr_status_t status;
    workers_unregister(m);

    status = apr_thread_mutex_lock(m->lock);
    if (APR_SUCCESS == status) {
        int attempts = 0;
        
        release(m);
        while (apr_atomic_read32(&m->refs) > 0) {
            m->join_wait = wait;
            ap_log_cerror(APLOG_MARK, (attempts? APLOG_INFO : APLOG_DEBUG), 
                          0, m->c,
                          "h2_mplx(%ld): release_join, refs=%d, waiting...", 
                          m->id, m->refs);
            apr_thread_cond_timedwait(wait, m->lock, apr_time_from_sec(10));
            if (++attempts >= 6) {
                ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, m->c,
                              APLOGNO(02952) 
                              "h2_mplx(%ld): join attempts exhausted, refs=%d", 
                              m->id, m->refs);
                break;
            }
        }
        if (m->join_wait) {
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, m->c,
                          "h2_mplx(%ld): release_join -> destroy", m->id);
        }
        m->join_wait = NULL;
        apr_thread_mutex_unlock(m->lock);
        h2_mplx_destroy(m);
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
        h2_io_set_destroy_all(m->stream_ios);
        apr_thread_mutex_unlock(m->lock);
    }
    workers_unregister(m);
}


h2_stream *h2_mplx_open_io(h2_mplx *m, int stream_id)
{
    h2_stream *stream = NULL;
    apr_status_t status; 
    h2_io *io;

    if (m->aborted) {
        return NULL;
    }
    status = apr_thread_mutex_lock(m->lock);
    if (APR_SUCCESS == status) {
        apr_pool_t *stream_pool = m->spare_pool;
        
        if (!stream_pool) {
            apr_pool_create(&stream_pool, m->pool);
        }
        else {
            m->spare_pool = NULL;
        }
        
        stream = h2_stream_create(stream_id, stream_pool, m);
        stream->state = H2_STREAM_ST_OPEN;
        
        io = h2_io_set_get(m->stream_ios, stream_id);
        if (!io) {
            io = h2_io_create(stream_id, stream_pool, m->bucket_alloc);
            h2_io_set_add(m->stream_ios, io);
        }
        status = io? APR_SUCCESS : APR_ENOMEM;
        apr_thread_mutex_unlock(m->lock);
    }
    return stream;
}

static void stream_destroy(h2_mplx *m, h2_stream *stream, h2_io *io)
{
    apr_pool_t *pool = h2_stream_detach_pool(stream);
    if (pool) {
        apr_pool_clear(pool);
        if (m->spare_pool) {
            apr_pool_destroy(m->spare_pool);
        }
        m->spare_pool = pool;
    }
    h2_stream_destroy(stream);
    if (io) {
        /* The pool is cleared/destroyed which also closes all
         * allocated file handles. Give this count back to our
         * file handle pool. */
        m->file_handles_allowed += io->files_handles_owned;
        h2_io_set_remove(m->stream_ios, io);
        h2_io_set_remove(m->ready_ios, io);
        h2_io_destroy(io);
    }
}

apr_status_t h2_mplx_cleanup_stream(h2_mplx *m, h2_stream *stream)
{
    apr_status_t status;
    AP_DEBUG_ASSERT(m);
    status = apr_thread_mutex_lock(m->lock);
    if (APR_SUCCESS == status) {
        h2_io *io = h2_io_set_get(m->stream_ios, stream->id);
        if (!io || io->task_done) {
            /* No more io or task already done -> cleanup immediately */
            stream_destroy(m, stream, io);
        }
        else {
            /* Add stream to closed set for cleanup when task is done */
            h2_stream_set_add(m->closed, stream);
        }
        apr_thread_mutex_unlock(m->lock);
    }
    return status;
}

void h2_mplx_task_done(h2_mplx *m, int stream_id)
{
    apr_status_t status = apr_thread_mutex_lock(m->lock);
    if (APR_SUCCESS == status) {
        h2_stream *stream = h2_stream_set_get(m->closed, stream_id);
        h2_io *io = h2_io_set_get(m->stream_ios, stream_id);
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c,
                      "h2_mplx(%ld): task(%d) done", m->id, stream_id);
        if (stream) {
            /* stream was already closed by main connection and is in 
             * zombie state. Now that the task is done with it, we
             * can free its resources. */
            h2_stream_set_remove(m->closed, stream);
            stream_destroy(m, stream, io);
        }
        else if (io) {
            /* main connection has not finished stream. Mark task as done
             * so that eventual cleanup can start immediately. */
            io->task_done = 1;
        }
        apr_thread_mutex_unlock(m->lock);
    }
}

apr_status_t h2_mplx_in_read(h2_mplx *m, apr_read_type_e block,
