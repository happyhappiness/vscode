                   "h2_stream(%ld-%d): SERVER_PUSH %d for %s %s on %d",
                   session->id, is->id, nid,
                   push->req->method, push->req->path, is->id);
                   
     stream = h2_session_open_stream(session, nid, is->id, push->req);
     if (stream) {
+        h2_session_set_prio(session, stream, push->priority);
         status = stream_schedule(session, stream, 1);
         if (status != APR_SUCCESS) {
             ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, session->c,
                           "h2_stream(%ld-%d): scheduling push stream",
                           session->id, stream->id);
             stream = NULL;
