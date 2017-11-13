h2_stream *h2_mplx_next_submit(h2_mplx *m, h2_ihash_t *streams)
{
    apr_status_t status;
    h2_stream *stream = NULL;
    int acquired;

    AP_DEBUG_ASSERT(m);
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        h2_io *io = h2_io_set_shift(m->ready_ios);
        if (io && !m->aborted) {
            stream = h2_ihash_get(streams, io->id);
            if (stream) {
                io->submitted = 1;
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
                ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, m->c, APLOGNO(03347)
                              "h2_mplx(%ld): stream for response %d closed, "
                              "resetting io to close request processing",
                              m->id, io->id);
                h2_io_make_orphaned(io, H2_ERR_STREAM_CLOSED);
                if (!io->worker_started || io->worker_done) {
                    io_destroy(m, io, 1);
                }
                else {
                    /* hang around until the h2_task is done, but
                     * shutdown input and send out any events (e.g. window
                     * updates) asap. */
                    h2_io_in_shutdown(io);
                    io_in_consumed_signal(m, io);
                }
            }
            
            h2_io_signal(io, H2_IO_WRITE);
        }
        leave_mutex(m, acquired);
    }
    return stream;
}