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