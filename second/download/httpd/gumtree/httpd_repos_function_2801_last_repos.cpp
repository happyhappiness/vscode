h2_stream *h2_session_stream_get(h2_session *session, int stream_id)
{
    return nghttp2_session_get_stream_user_data(session->ngh2, stream_id);
}