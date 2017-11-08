apr_status_t h2_session_handle_response(h2_session *session, h2_stream *stream)
{
    apr_status_t status = APR_SUCCESS;
    int rv = 0;
    AP_DEBUG_ASSERT(session);
    AP_DEBUG_ASSERT(stream);
    AP_DEBUG_ASSERT(stream->response);
    
    if (stream->response->ngheader) {
        rv = submit_response(session, stream->response);
    }
    else {
        rv = nghttp2_submit_rst_stream(session->ngh2, NGHTTP2_FLAG_NONE,
                                       stream->id, NGHTTP2_PROTOCOL_ERROR);
    }
    
    if (nghttp2_is_fatal(rv)) {
        status = APR_EGENERAL;
        h2_session_abort_int(session, rv);
        ap_log_cerror(APLOG_MARK, APLOG_ERR, status, session->c,
                      APLOGNO(02940) "submit_response: %s", 
                      nghttp2_strerror(rv));
    }
    return status;
}