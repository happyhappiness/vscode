static apr_status_t unschedule_slow_ios(h2_mplx *m) 
{
    h2_io *io;
    int n;
    
    if (!m->redo_ios) {
        m->redo_ios = h2_io_set_create(m->pool);
    }
    /* Try to get rid of streams that occupy workers. Look for safe requests
     * that are repeatable. If none found, fail the connection.
     */
    n = (m->workers_busy - m->workers_limit - h2_io_set_size(m->redo_ios));
    while (n > 0 && (io = get_latest_repeatable_busy_unsubmitted_io(m))) {
        h2_io_set_add(m->redo_ios, io);
        h2_io_rst(io, H2_ERR_CANCEL);
        --n;
    }
    
    if ((m->workers_busy - h2_io_set_size(m->redo_ios)) > m->workers_limit) {
        io = get_timed_out_busy_stream(m);
        if (io) {
            /* Too many busy workers, unable to cancel enough streams
             * and with a busy, timed out stream, we tell the client
             * to go away... */
            return APR_TIMEUP;
        }
    }
    return APR_SUCCESS;
}