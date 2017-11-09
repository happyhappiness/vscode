apr_status_t h2_mplx_pop_task(h2_mplx *m, h2_task **ptask)
{
    apr_status_t rv = APR_EOF;
    
    *ptask = NULL;
    if (APR_SUCCESS != (rv = apr_thread_mutex_lock(m->lock))) {
        return rv;
    }
    
    if (m->aborted) {
        rv = APR_EOF;
    }
    else {
        *ptask = next_stream_task(m);
        rv = (*ptask != NULL && !h2_iq_empty(m->q))? APR_EAGAIN : APR_SUCCESS;
    }
    if (APR_EAGAIN != rv) {
        m->is_registered = 0; /* h2_workers will discard this mplx */
    }
    H2_MPLX_LEAVE(m);
    return rv;
}