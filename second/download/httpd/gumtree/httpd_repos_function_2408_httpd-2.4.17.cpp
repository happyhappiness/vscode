static apr_status_t h2_session_update_windows(h2_session *session)
{
    return h2_mplx_in_update_windows(session->mplx, update_window, session);
}