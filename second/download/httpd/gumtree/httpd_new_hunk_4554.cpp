     * should be suspended. Beware of trailers.
     */
 
    (void)ng2s;
    (void)buf;
    (void)source;
    stream = h2_session_stream_get(session, stream_id);
    if (!stream) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, session->c,
                      APLOGNO(02937) 
                      "h2_stream(%ld-%d): data_cb, stream not found",
                      session->id, (int)stream_id);
        return NGHTTP2_ERR_CALLBACK_FAILURE;
    }

    status = h2_stream_out_prepare(stream, &nread, &eos, NULL);
    if (nread) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c, 
                      H2_STRM_MSG(stream, "prepared no_copy, len=%ld, eos=%d"),
                      (long)nread, eos);
        *data_flags |=  NGHTTP2_DATA_FLAG_NO_COPY;
    }
    
    switch (status) {
        case APR_SUCCESS:
            break;
            
        case APR_ECONNRESET:
        case APR_ECONNABORTED:
            return NGHTTP2_ERR_CALLBACK_FAILURE;
            
        case APR_EAGAIN:
            /* If there is no data available, our session will automatically
             * suspend this stream and not ask for more data until we resume
             * it. Remember at our h2_stream that we need to do this.
             */
            nread = 0;
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                          H2_STRM_LOG(APLOGNO(03071), stream, "suspending"));
            return NGHTTP2_ERR_DEFERRED;
            
        default:
            nread = 0;
            ap_log_cerror(APLOG_MARK, APLOG_ERR, status, session->c, 
                          H2_STRM_LOG(APLOGNO(02938), stream, "reading data"));
            return NGHTTP2_ERR_CALLBACK_FAILURE;
    }
    
    if (eos) {
        *data_flags |= NGHTTP2_DATA_FLAG_EOF;
    }
    return (ssize_t)nread;
}

struct h2_stream *h2_session_push(h2_session *session, h2_stream *is,
                                  h2_push *push)
{
    h2_stream *stream;
    h2_ngheader *ngh;
    apr_status_t status;
    int nid = 0;
    
    status = h2_req_create_ngheader(&ngh, is->pool, push->req);
    if (status == APR_SUCCESS) {
        nid = nghttp2_submit_push_promise(session->ngh2, 0, is->id, 
                                          ngh->nv, ngh->nvlen, NULL);
    }
    if (status != APR_SUCCESS || nid <= 0) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c, 
                      H2_STRM_LOG(APLOGNO(03075), is, 
                      "submitting push promise fail: %s"), nghttp2_strerror(nid));
        return NULL;
    }
    ++session->pushes_promised;
    
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, 
                  H2_STRM_LOG(APLOGNO(03076), is, "SERVER_PUSH %d for %s %s on %d"),
                  nid, push->req->method, push->req->path, is->id);
                  
    stream = h2_session_open_stream(session, nid, is->id);
    if (!stream) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, 
                      H2_STRM_LOG(APLOGNO(03077), stream, 
                      "failed to create stream obj %d"), nid);
        /* kill the push_promise */
        nghttp2_submit_rst_stream(session->ngh2, NGHTTP2_FLAG_NONE, nid,
                                  NGHTTP2_INTERNAL_ERROR);
        return NULL;
    }
    
    h2_session_set_prio(session, stream, push->priority);
    h2_stream_set_request(stream, push->req);
    ++session->unsent_promises;
    return stream;
}

static int valid_weight(float f) 
{
    int w = (int)f;
