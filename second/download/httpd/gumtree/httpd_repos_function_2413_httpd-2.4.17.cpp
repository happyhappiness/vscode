apr_status_t h2_session_close(h2_session *session)
{
    AP_DEBUG_ASSERT(session);
    return session->aborted? APR_SUCCESS : h2_conn_io_flush(&session->io);
}