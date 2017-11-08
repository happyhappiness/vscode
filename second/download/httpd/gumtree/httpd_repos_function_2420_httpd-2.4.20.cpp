int h2_conn_io_is_buffered(h2_conn_io *io)
{
    return io->bufsize > 0;
}