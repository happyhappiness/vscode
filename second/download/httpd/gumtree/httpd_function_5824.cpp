static int stream_open(h2_session *session, int stream_id)
{
    h2_stream * stream;
    if (session->aborted) {
        return NGHTTP2_ERR_CALLBACK_FAILURE;
    }
    
    stream = h2_mplx_open_io(session->mplx, stream_id);
    if (stream) {
        h2_stream_set_add(session->streams, stream);
        if (stream->id > session->max_stream_received) {
            session->max_stream_received = stream->id;
        }
        
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                      "h2_session: stream(%ld-%d): opened",
                      session->id, stream_id);
        
        return 0;
    }
    
    ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_ENOMEM, session->c,
                  APLOGNO(02918) 
                  "h2_session: stream(%ld-%d): unable to create",
                  session->id, stream_id);
    return NGHTTP2_ERR_INVALID_STREAM_ID;
}