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