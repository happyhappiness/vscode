void h2_mplx_task_done(h2_mplx *m, int stream_id)
{
    apr_status_t status = apr_thread_mutex_lock(m->lock);
    if (APR_SUCCESS == status) {
        h2_io *io = h2_io_set_get(m->stream_ios, stream_id);
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c,
                      "h2_mplx(%ld): task(%d) done", m->id, stream_id);
        if (io) {
            io->task_done = 1;
            if (io->orphaned) {
                io_destroy(m, io, 0);
            }
            else {
                /* hang around until the stream deregisteres */
            }
        }
        apr_thread_mutex_unlock(m->lock);
    }
}