apr_status_t h2_session_read(h2_session *session, apr_read_type_e block)
{
    AP_DEBUG_ASSERT(session);
    return h2_conn_io_read(&session->io, block, session_receive, session);
}