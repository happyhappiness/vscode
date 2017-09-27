    AP_DEBUG_ASSERT(m);
    if (m->added_output) {
        apr_thread_cond_signal(m->added_output);
    }
}

apr_status_t h2_mplx_do_task(h2_mplx *m, struct h2_task *task)
{
    apr_status_t status;
    AP_DEBUG_ASSERT(m);
    if (m->aborted) {
        return APR_ECONNABORTED;
    }
    status = apr_thread_mutex_lock(m->lock);
    if (APR_SUCCESS == status) {
        /* TODO: needs to sort queue by priority */
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                      "h2_mplx: do task(%s)", task->id);
        h2_tq_append(m->q, task);
        apr_thread_mutex_unlock(m->lock);
    }
    workers_register(m);
    return status;
}

h2_task *h2_mplx_pop_task(h2_mplx *m, int *has_more)
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
        task = h2_tq_pop_first(m->q);
        if (task) {
            h2_task_set_started(task);
        }
        *has_more = !h2_tq_empty(m->q);
        apr_thread_mutex_unlock(m->lock);
    }
    return task;
}

apr_status_t h2_mplx_create_task(h2_mplx *m, struct h2_stream *stream)
{
    apr_status_t status;
    AP_DEBUG_ASSERT(m);
    if (m->aborted) {
        return APR_ECONNABORTED;
    }
    status = apr_thread_mutex_lock(m->lock);
    if (APR_SUCCESS == status) {
        conn_rec *c = h2_conn_create(m->c, stream->pool);
        stream->task = h2_task_create(m->id, stream->id, 
                                      stream->pool, m, c);
        
        apr_thread_mutex_unlock(m->lock);
    }
    return status;
}

