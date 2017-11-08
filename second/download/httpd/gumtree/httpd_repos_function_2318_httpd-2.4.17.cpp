void h2_conn_io_destroy(h2_conn_io *io)
{
    io->input = NULL;
    io->output = NULL;
}