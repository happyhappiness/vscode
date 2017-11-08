void h2_mplx_task_done(h2_mplx *m, int stream_id)
{
    apr_status_t status = apr_thread_mutex_lock(m->lock);
    if (APR_SUCCESS == status) {
        h2_stream *stream = h2_stream_set_get(m->closed, stream_id);
        h2_io *io = h2_io_set_get(m->stream_ios, stream_id);
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c,
                      "h2_mplx(%ld): task(%d) done", m->id, stream_id);
        if (stream) {
            /* stream was already closed by main connection and is in 
             * zombie state. Now that the task is done with it, we
             * can free its resources. */
            h2_stream_set_remove(m->closed, stream);
            stream_destroy(m, stream, io);
        }
        else if (io) {
            /* main connection has not finished stream. Mark task as done
             * so that eventual cleanup can start immediately. */
            io->task_done = 1;
        }
        apr_thread_mutex_unlock(m->lock);
    }
}