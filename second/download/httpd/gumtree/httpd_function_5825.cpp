static apr_status_t on_stream_resume(void *ctx, int stream_id)
{
    h2_session *session = ctx;
    h2_stream *stream = get_stream(session, stream_id);
    apr_status_t status = APR_SUCCESS;
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c, 
                  "h2_stream(%ld-%d): on_resume", session->id, stream_id);
    if (stream) {
        int rv = nghttp2_session_resume_data(session->ngh2, stream_id);
        session->have_written = 1;
        ap_log_cerror(APLOG_MARK, nghttp2_is_fatal(rv)?
                      APLOG_ERR : APLOG_DEBUG, 0, session->c,
                      APLOGNO(02936) 
                      "h2_stream(%ld-%d): resuming %s",
                      session->id, stream->id, rv? nghttp2_strerror(rv) : "");
    }
    return status;
}