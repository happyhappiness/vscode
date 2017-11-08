void h2_io_signal_init(h2_io *io, h2_io_op op, apr_interval_time_t timeout, 
                       apr_thread_cond_t *cond)
{
    io->timed_op = op;
    io->timed_cond = cond;
    if (timeout > 0) {
        io->timeout_at = apr_time_now() + timeout;
    }
    else {
        io->timeout_at = 0; 
    }
}