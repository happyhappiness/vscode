}

static void update_window(void *ctx, int stream_id, apr_off_t bytes_read)
{
    h2_session *session = (h2_session*)ctx;
    nghttp2_session_consume(session->ngh2, stream_id, bytes_read);
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                  "h2_session(%ld-%d): consumed %ld bytes",
                  session->id, stream_id, (long)bytes_read);
}


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

#ifdef H2_NG2_STREAM_API

/**
 * Determine the importance of streams when scheduling tasks.
 * - if both stream depend on the same one, compare weights
 * - if one stream is closer to the root, prioritize that one
 * - if both are on the same level, use the weight of their root
 *   level ancestors
