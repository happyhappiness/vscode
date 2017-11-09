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