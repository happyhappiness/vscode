void h2_io_rst(h2_io *io, int error)
{
    io->rst_error = error;
    io->eos_in = 1;
}