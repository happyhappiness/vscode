h2_stream *h2_session_open_stream(h2_session *session, int stream_id)
{
    h2_stream * stream;
    apr_pool_t *stream_pool;
    if (session->aborted) {
        return NULL;
    }
    
    if (session->spare) {
        stream_pool = session->spare;
        session->spare = NULL;
    }
    else {
        apr_pool_create(&stream_pool, session->pool);
    }
    
    stream = h2_stream_open(stream_id, stream_pool, session);
    
    h2_stream_set_add(session->streams, stream);
    if (H2_STREAM_CLIENT_INITIATED(stream_id)
        && stream_id > session->max_stream_received) {
        session->max_stream_received = stream->id;
    }
    
    return stream;
}