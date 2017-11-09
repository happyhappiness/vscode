static h2_stream *h2_session_open_stream(h2_session *session, int stream_id,
                                         int initiated_on)
{
    h2_stream * stream;
    apr_pool_t *stream_pool;
    
    apr_pool_create(&stream_pool, session->pool);
    apr_pool_tag(stream_pool, "h2_stream");
    
    stream = h2_stream_create(stream_id, stream_pool, session, 
                              session->monitor, initiated_on);
    if (stream) {
        nghttp2_session_set_stream_user_data(session->ngh2, stream_id, stream);
    }
    return stream;
}