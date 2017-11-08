apr_status_t h2_conn_io_write_eoc(h2_conn_io *io, h2_session *session)
{
    return pass_output(io, 1, session);
}