apr_status_t h2_conn_io_writeb(h2_conn_io *io, apr_bucket *b)
{
    APR_BRIGADE_INSERT_TAIL(io->output, b);
    return APR_SUCCESS;
}