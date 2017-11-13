static apr_status_t stream_destroy(h2_session *session, 
                                   h2_stream *stream,
                                   uint32_t error_code) 
{
    if (!error_code) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                      "h2_stream(%ld-%d): handled, closing", 
                      session->id, (int)stream->id);
        if (stream->id > session->max_stream_handled) {
            session->max_stream_handled = stream->id;
        }
    }
    else {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                      "h2_stream(%ld-%d): closing with err=%d %s", 
                      session->id, (int)stream->id, (int)error_code,
                      nghttp2_strerror(error_code));
    }
    
    h2_stream_set_remove(session->streams, stream);
    return h2_mplx_cleanup_stream(session->mplx, stream);
}