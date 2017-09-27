    h2_ngheader *ngh;
    int nid;
    
    ngh = h2_util_ngheader_make_req(is->pool, push->req);
    nid = nghttp2_submit_push_promise(session->ngh2, 0, is->id, 
                                      ngh->nv, ngh->nvlen, NULL);
                                      
    if (nid <= 0) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                      "h2_stream(%ld-%d): submitting push promise fail: %s",
                      session->id, is->id, nghttp2_strerror(nid));
        return NULL;
    }

    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                  "h2_stream(%ld-%d): promised new stream %d for %s %s on %d",
                  session->id, is->id, nid,
                  push->req->method, push->req->path, is->id);
                  
    stream = h2_session_open_stream(session, nid);
    if (stream) {
        h2_stream_set_h2_request(stream, is->id, push->req);
        status = stream_schedule(session, stream, 1);
        if (status != APR_SUCCESS) {
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c,
                          "h2_stream(%ld-%d): scheduling push stream",
                          session->id, stream->id);
            h2_stream_cleanup(stream);
            stream = NULL;
        }
        ++session->unsent_promises;
    }
    else {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                      "h2_stream(%ld-%d): failed to create stream obj %d",
                      session->id, is->id, nid);
    }

    if (!stream) {
        /* try to tell the client that it should not wait. */
