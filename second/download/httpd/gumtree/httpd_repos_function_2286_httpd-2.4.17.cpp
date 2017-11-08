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