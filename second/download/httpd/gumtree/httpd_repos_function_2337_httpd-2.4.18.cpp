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