apr_status_t h2_conn_io_write_eoc(h2_conn_io *io, h2_session *session)
{
    apr_bucket *b = h2_bucket_eoc_create(io->c->bucket_alloc, session);
    APR_BRIGADE_INSERT_TAIL(io->output, b);
    return h2_conn_io_flush_int(io, 0, 1);
}