apr_status_t h2_conn_io_flush(h2_conn_io *io)
{
    return pass_output(io, 1, NULL);
}