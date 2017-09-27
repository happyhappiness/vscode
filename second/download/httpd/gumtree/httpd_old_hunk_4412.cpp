    session->unsent_submits = 0;
    
    return APR_SUCCESS;
}

/**
 * A stream was resumed as new output data arrived.
 */
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

/**
 * A response for the stream is ready.
 */
static apr_status_t on_stream_response(void *ctx, int stream_id)
{
    h2_session *session = ctx;
    h2_stream *stream = get_stream(session, stream_id);
    apr_status_t status = APR_SUCCESS;
    h2_response *response;
    int rv = 0;

    AP_DEBUG_ASSERT(session);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c, 
                  "h2_stream(%ld-%d): on_response", session->id, stream_id);
    if (!stream) {
        return APR_NOTFOUND;
    }
    
    response = h2_stream_get_response(stream);
    AP_DEBUG_ASSERT(response || stream->rst_error);
    
    if (stream->submitted) {
        rv = NGHTTP2_PROTOCOL_ERROR;
    }
    else if (response && response->headers) {
        nghttp2_data_provider provider, *pprovider = NULL;
        h2_ngheader *ngh;
        const h2_priority *prio;
        
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03073)
                      "h2_stream(%ld-%d): submit response %d, REMOTE_WINDOW_SIZE=%u",
                      session->id, stream->id, response->http_status,
                      (unsigned int)nghttp2_session_get_stream_remote_window_size(session->ngh2, stream->id));
        
        if (response->content_length != 0) {
            memset(&provider, 0, sizeof(provider));
            provider.source.fd = stream->id;
            provider.read_callback = stream_data_cb;
            pprovider = &provider;
        }
        
        /* If this stream is not a pushed one itself,
         * and HTTP/2 server push is enabled here,
         * and the response is in the range 200-299 *),
         * and the remote side has pushing enabled,
         * -> find and perform any pushes on this stream
         *    *before* we submit the stream response itself.
         *    This helps clients avoid opening new streams on Link
         *    headers that get pushed right afterwards.
         * 
         * *) the response code is relevant, as we do not want to 
         *    make pushes on 401 or 403 codes, neiterh on 301/302
         *    and friends. And if we see a 304, we do not push either
         *    as the client, having this resource in its cache, might
         *    also have the pushed ones as well.
         */
        if (stream->request && !stream->request->initiated_on
            && H2_HTTP_2XX(response->http_status)
            && h2_session_push_enabled(session)) {
            
            h2_stream_submit_pushes(stream);
        }
        
        prio = h2_stream_get_priority(stream);
        if (prio) {
            h2_session_set_prio(session, stream, prio);
            /* no showstopper if that fails for some reason */
        }
        
        ngh = h2_util_ngheader_make_res(stream->pool, response->http_status, 
                                        response->headers);
        rv = nghttp2_submit_response(session->ngh2, response->stream_id,
                                     ngh->nv, ngh->nvlen, pprovider);
    }
    else {
        int err = H2_STREAM_RST(stream, H2_ERR_PROTOCOL_ERROR);
        
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03074)
                      "h2_stream(%ld-%d): RST_STREAM, err=%d",
                      session->id, stream->id, err);

        rv = nghttp2_submit_rst_stream(session->ngh2, NGHTTP2_FLAG_NONE,
                                       stream->id, err);
    }
    
    stream->submitted = 1;
    session->have_written = 1;
    
    if (stream->request && stream->request->initiated_on) {
        ++session->pushes_submitted;
    }
    else {
        ++session->responses_submitted;
    }
    
    if (nghttp2_is_fatal(rv)) {
        status = APR_EGENERAL;
        dispatch_event(session, H2_SESSION_EV_PROTO_ERROR, rv, nghttp2_strerror(rv));
        ap_log_cerror(APLOG_MARK, APLOG_ERR, status, session->c,
                      APLOGNO(02940) "submit_response: %s", 
                      nghttp2_strerror(rv));
