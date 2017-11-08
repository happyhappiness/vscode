h2_stream *h2_session_get_stream(h2_session *session, int stream_id)
{
    if (!session->last_stream || stream_id != session->last_stream->id) {
        session->last_stream = h2_stream_set_get(session->streams, stream_id);
    }
    return session->last_stream;
}