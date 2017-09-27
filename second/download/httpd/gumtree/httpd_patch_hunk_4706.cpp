 static int on_frame_recv_cb(nghttp2_session *ng2s,
                             const nghttp2_frame *frame,
                             void *userp)
 {
     h2_session *session = (h2_session *)userp;
     h2_stream *stream;
+    apr_status_t rv = APR_SUCCESS;
     
     if (APLOGcdebug(session->c)) {
         char buffer[256];
         
         h2_util_frame_print(frame, buffer, sizeof(buffer)/sizeof(buffer[0]));
         ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, 
