h2_stream *h2_session_open_stream(h2_session *session, int stream_id)
{
    h2_stream * stream;
    apr_pool_t *stream_pool;
    
    if (session->spare) {
        stream_pool = session->spare;
        session->spare = NULL;
    }
    else {
        apr_pool_create(&stream_pool, session->pool);
        apr_pool_tag(stream_pool, "h2_stream");
    }
    
    stream = h2_stream_open(stream_id, stream_pool, session);
    
    h2_ihash_add(session->streams, stream);
    if (H2_STREAM_CLIENT_INITIATED(stream_id)) {
        if (stream_id > session->remote.emitted_max) {
            ++session->remote.emitted_count;
            session->remote.emitted_max = stream->id;
            session->local.accepted_max = stream->id;
        }
    }
    else {
        if (stream_id > session->local.emitted_max) {
            ++session->local.emitted_count;
            session->remote.emitted_max = stream->id;
        }
    }
    
    return stream;
}