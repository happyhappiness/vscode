void h2_io_signal_exit(h2_io *io)
{
    io->timed_cond = NULL;
    io->timeout_at = 0; 
}