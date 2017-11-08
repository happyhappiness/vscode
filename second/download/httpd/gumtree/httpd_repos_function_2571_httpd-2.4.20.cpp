h2_stream *h2_session_get_stream(h2_session *session, int stream_id)
{
    return h2_ihash_get(session->streams, stream_id);
}