    
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03076)
                  "h2_stream(%ld-%d): SERVER_PUSH %d for %s %s on %d",
                  session->id, is->id, nid,
                  push->req->method, push->req->path, is->id);
                  
    stream = h2_session_open_stream(session, nid);
    if (stream) {
        h2_stream_set_h2_request(stream, is->id, push->req);
        status = stream_schedule(session, stream, 1);
        if (status != APR_SUCCESS) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, session->c,
                          "h2_stream(%ld-%d): scheduling push stream",
                          session->id, stream->id);
            h2_stream_cleanup(stream);
            stream = NULL;
        }
        ++session->unsent_promises;
    }
    else {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03077)
