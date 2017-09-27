    else if (APR_STATUS_IS_EOF(rv)) {
        return NGHTTP2_ERR_EOF;
    }
    return NGHTTP2_ERR_PROTO;
}

h2_stream *h2_session_stream_get(h2_session *session, int stream_id)
{
    return nghttp2_session_get_stream_user_data(session->ngh2, stream_id);
}

static void dispatch_event(h2_session *session, h2_session_event_t ev, 
                             int err, const char *msg);

void h2_session_event(h2_session *session, h2_session_event_t ev, 
                             int err, const char *msg)
{
    dispatch_event(session, ev, err, msg);
}

static int rst_unprocessed_stream(h2_stream *stream, void *ctx)
{
    int unprocessed = (!h2_stream_was_closed(stream)
                       && (H2_STREAM_CLIENT_INITIATED(stream->id)? 
                           (!stream->session->local.accepting
                            && stream->id > stream->session->local.accepted_max)
                            : 
                           (!stream->session->remote.accepting
                            && stream->id > stream->session->remote.accepted_max))
                       ); 
    if (unprocessed) {
        h2_stream_rst(stream, H2_ERR_NO_ERROR);
        return 0;
    }
    return 1;
}

static void cleanup_unprocessed_streams(h2_session *session)
{
    h2_mplx_stream_do(session->mplx, rst_unprocessed_stream, session);
}

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

/**
 * Determine the importance of streams when scheduling tasks.
 * - if both stream depend on the same one, compare weights
