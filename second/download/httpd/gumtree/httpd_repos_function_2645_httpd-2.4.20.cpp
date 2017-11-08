void h2_io_signal(h2_io *io, h2_io_op op)
{
    if (io->timed_cond && (io->timed_op == op || H2_IO_ANY == op)) {
        apr_thread_cond_signal(io->timed_cond);
    }
}