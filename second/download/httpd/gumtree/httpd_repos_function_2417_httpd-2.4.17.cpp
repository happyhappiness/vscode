int h2_session_is_done(h2_session *session)
{
    AP_DEBUG_ASSERT(session);
    return (session->aborted
            || !session->ngh2
            || (!nghttp2_session_want_read(session->ngh2)
                && !nghttp2_session_want_write(session->ngh2)));
}