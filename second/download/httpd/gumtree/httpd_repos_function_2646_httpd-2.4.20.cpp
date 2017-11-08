void h2_io_make_orphaned(h2_io *io, int error)
{
    io->orphaned = 1;
    if (error) {
        h2_io_rst(io, error);
    }
    /* if someone is waiting, wake him up */
    h2_io_signal(io, H2_IO_ANY);
}