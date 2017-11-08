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