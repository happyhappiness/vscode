int h2_mplx_in_has_eos_for(h2_mplx *m, int stream_id)
{
    int has_eos = 0;
    apr_status_t status;
    AP_DEBUG_ASSERT(m);
    if (m->aborted) {
        return 0;
    }
    status = apr_thread_mutex_lock(m->lock);
    if (APR_SUCCESS == status) {
        h2_io *io = h2_io_set_get(m->stream_ios, stream_id);
        if (io) {
            has_eos = h2_io_in_has_eos_for(io);
        }
        apr_thread_mutex_unlock(m->lock);
    }
    return has_eos;
}