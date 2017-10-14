h2_stream *h2_mplx_next_submit(h2_mplx *m, h2_stream_set *streams)
{
    apr_status_t status;
    h2_stream *stream = NULL;
    AP_DEBUG_ASSERT(m);
    if (m->aborted) {
        return NULL;
    }
    status = apr_thread_mutex_lock(m->lock);
    if (APR_SUCCESS == status) {
        h2_io *io = h2_io_set_get_highest_prio(m->ready_ios);
        if (io) {
            h2_response *response = io->response;
            
            AP_DEBUG_ASSERT(response);
            h2_io_set_remove(m->ready_ios, io);
            
            stream = h2_stream_set_get(streams, response->stream_id);
            if (stream) {
                h2_stream_set_response(stream, response, io->bbout);
                if (io->output_drained) {
                    apr_thread_cond_signal(io->output_drained);
                }
            }
            else {
                ap_log_cerror(APLOG_MARK, APLOG_WARNING, APR_NOTFOUND, m->c,
                              APLOGNO(02953) "h2_mplx(%ld): stream for response %d",
                              m->id, response->stream_id);
            }
        }
        apr_thread_mutex_unlock(m->lock);
    }
    return stream;
}