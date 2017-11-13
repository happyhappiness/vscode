static int resume_on_data(void *ctx, void *val)
{
    h2_stream *stream = val;
    resume_ctx *rctx = (resume_ctx*)ctx;
    h2_session *session = rctx->session;
    AP_DEBUG_ASSERT(session);
    AP_DEBUG_ASSERT(stream);
    
    if (h2_stream_is_suspended(stream)) {
        apr_status_t status;
        apr_off_t len = -1;
        int eos;
        
        status = h2_stream_out_prepare(stream, &len, &eos);
        if (status == APR_SUCCESS) {
            int rv;
            h2_stream_set_suspended(stream, 0);
            ++rctx->resume_count;
            
            rv = nghttp2_session_resume_data(session->ngh2, stream->id);
            ap_log_cerror(APLOG_MARK, nghttp2_is_fatal(rv)?
                          APLOG_ERR : APLOG_DEBUG, 0, session->c,
                          APLOGNO(02936) 
                          "h2_stream(%ld-%d): resuming %s, len=%ld, eos=%d",
                          session->id, stream->id, 
                          rv? nghttp2_strerror(rv) : "", (long)len, eos);
        }
    }
    return 1;
}