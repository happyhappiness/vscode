apr_status_t h2_conn_io_flush(h2_conn_io *io)
{
    apr_status_t status;
    status = pass_output(io, 1);
    check_write_size(io);
    return status;
}