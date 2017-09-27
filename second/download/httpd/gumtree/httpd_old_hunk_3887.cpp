            apr_thread_mutex_unlock(m->lock);
        }
    }
    return status;
}

apr_status_t h2_mplx_out_close(h2_mplx *m, int stream_id)
{
    apr_status_t status;
    AP_DEBUG_ASSERT(m);
    if (m->aborted) {
        return APR_ECONNABORTED;
    }
    status = apr_thread_mutex_lock(m->lock);
    if (APR_SUCCESS == status) {
        if (!m->aborted) {
            h2_io *io = h2_io_set_get(m->stream_ios, stream_id);
            if (io) {
                if (!io->response || !io->response->ngheader) {
                    /* In case a close comes before a response was created,
                     * insert an error one so that our streams can properly
                     * reset.
                     */
                    h2_response *r = h2_response_create(stream_id, 
                                                        "500", NULL, m->pool);
                    status = out_open(m, stream_id, r, NULL, NULL, NULL);
                }
                status = h2_io_out_close(io);
                have_out_data_for(m, stream_id);
                if (m->aborted) {
                    /* if we were the last output, the whole session might
                     * have gone down in the meantime.
                     */
                    return APR_SUCCESS;
