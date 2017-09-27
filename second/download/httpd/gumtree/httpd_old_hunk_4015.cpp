    }
}

apr_status_t h2_mplx_reprioritize(h2_mplx *m, h2_stream_pri_cmp *cmp, void *ctx)
{
    apr_status_t status;
    
    AP_DEBUG_ASSERT(m);
    if (m->aborted) {
        return APR_ECONNABORTED;
    }
    status = apr_thread_mutex_lock(m->lock);
    if (APR_SUCCESS == status) {
        h2_tq_sort(m->q, cmp, ctx);
        
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                      "h2_mplx(%ld): reprioritize tasks", m->id);
        apr_thread_mutex_unlock(m->lock);
    }
    workers_register(m);
    return status;
}

static h2_io *open_io(h2_mplx *m, int stream_id)
{
    apr_pool_t *io_pool = m->spare_pool;
    h2_io *io;
    
    if (!io_pool) {
        apr_pool_create(&io_pool, m->pool);
    }
    else {
        m->spare_pool = NULL;
    }
    
    io = h2_io_create(stream_id, io_pool, m->bucket_alloc);
    h2_io_set_add(m->stream_ios, io);
    
    return io;
}


apr_status_t h2_mplx_process(h2_mplx *m, int stream_id,
                             const h2_request *req, int eos, 
                             h2_stream_pri_cmp *cmp, void *ctx)
{
    apr_status_t status;
    
    AP_DEBUG_ASSERT(m);
    if (m->aborted) {
        return APR_ECONNABORTED;
    }
    status = apr_thread_mutex_lock(m->lock);
    if (APR_SUCCESS == status) {
        h2_io *io = open_io(m, stream_id);
        io->request = req;
        io->request_body = !eos;

        if (eos) {
            status = h2_io_in_close(io);
        }
        
        h2_tq_add(m->q, io->id, cmp, ctx);

        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, m->c,
                      "h2_mplx(%ld-%d): process", m->c->id, stream_id);
        H2_MPLX_IO_IN(APLOG_TRACE2, m, io, "h2_mplx_process");
        apr_thread_mutex_unlock(m->lock);
    }
    
    if (status == APR_SUCCESS) {
        workers_register(m);
    }
    return status;
}

h2_task *h2_mplx_pop_task(h2_mplx *m, h2_worker *w, int *has_more)
{
    h2_task *task = NULL;
    apr_status_t status;
    
    AP_DEBUG_ASSERT(m);
    if (m->aborted) {
        *has_more = 0;
        return NULL;
    }
    status = apr_thread_mutex_lock(m->lock);
    if (APR_SUCCESS == status) {
        int sid;
        while (!task && (sid = h2_tq_shift(m->q)) > 0) {
            /* Anything not already setup correctly in the task
             * needs to be so now, as task will be executed right about 
             * when this method returns. */
            h2_io *io = h2_io_set_get(m->stream_ios, sid);
            if (io) {
                task = h2_worker_create_task(w, m, io->request, !io->request_body);
            }
        }
        *has_more = !h2_tq_empty(m->q);
        apr_thread_mutex_unlock(m->lock);
    }
    return task;
}

