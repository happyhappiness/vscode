static apr_status_t send_data(h2_session *session, const char *data, 
                              apr_size_t length)
{
    return h2_conn_io_write(&session->io, data, length);
}