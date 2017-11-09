static apr_status_t h2_session_read(h2_session *session, int block)
{
    apr_status_t status = session_read(session, session->max_stream_mem
                                       * H2MAX(2, session->open_streams), 
                                       block);
    h2_session_in_flush(session);
    return status;
}