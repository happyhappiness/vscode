static int h2_session_want_write(h2_session *session)
{
    return nghttp2_session_want_write(session->ngh2);
}