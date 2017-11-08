apr_status_t h2_conn_io_pass(h2_conn_io *io)
{
    return h2_conn_io_flush_int(io, 0);
}