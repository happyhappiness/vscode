                             void *userp)
 {
     h2_session *session = (h2_session *)userp;
     apr_status_t status = APR_SUCCESS;
     h2_stream *stream;
     
-    if (session->aborted) {
-        return NGHTTP2_ERR_CALLBACK_FAILURE;
+    if (APLOGcdebug(session->c)) {
+        char buffer[256];
+        
+        h2_util_frame_print(frame, buffer, sizeof(buffer)/sizeof(buffer[0]));
+        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03066)
+                      "h2_session(%ld): recv FRAME[%s], frames=%ld/%ld (r/s)",
+                      session->id, buffer, (long)session->frames_received,
+                     (long)session->frames_sent);
     }
-    
-    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
-                  "h2_stream(%ld-%d): on_frame_rcv #%ld, type=%d", 
-                  session->id, frame->hd.stream_id, 
-                  (long)session->frames_received, frame->hd.type);
 
     ++session->frames_received;
     switch (frame->hd.type) {
         case NGHTTP2_HEADERS:
             /* This can be HEADERS for a new stream, defining the request,
              * or HEADER may come after DATA at the end of a stream as in
