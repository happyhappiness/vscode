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
        h2_io *io = h2_io_set_pop_highest_prio(m->ready_ios);
        if (io) {
            stream = h2_stream_set_get(streams, io->id);
            if (stream) {
                if (io->rst_error) {
                    h2_stream_rst(stream, io->rst_error);
                }
                else {
                    AP_DEBUG_ASSERT(io->response);
                    H2_MPLX_IO_OUT(APLOG_TRACE2, m, io, "h2_mplx_next_submit_pre");
                    h2_stream_set_response(stream, io->response, io->bbout);
                    H2_MPLX_IO_OUT(APLOG_TRACE2, m, io, "h2_mplx_next_submit_post");
                }
                
            }
            else {
                /* We have the io ready, but the stream has gone away, maybe
                 * reset by the client. Should no longer happen since such
                 * streams should clear io's from the ready queue.
                 */
                ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, m->c, APLOGNO(02953) 
                              "h2_mplx(%ld): stream for response %d closed, "
                              "resetting io to close request processing",
                              m->id, io->id);
                io->orphaned = 1;
                if (io->task_done) {
                    io_destroy(m, io, 1);
                }
                else {
                    /* hang around until the h2_task is done, but
                     * shutdown input and send out any events (e.g. window
                     * updates) asap. */
                    h2_io_in_shutdown(io);
                    h2_io_rst(io, H2_ERR_STREAM_CLOSED);
                    io_process_events(m, io);
                }
            }
            
            if (io->output_drained) {
                apr_thread_cond_signal(io->output_drained);
            }
        }
        apr_thread_mutex_unlock(m->lock);
    }
    return stream;
}