 }
 
 static int on_frame_recv(nghttp2_session *ngh2, const nghttp2_frame *frame,
                          void *user_data) 
 {
     h2_proxy_session *session = user_data;
+    h2_proxy_stream *stream;
+    request_rec *r;
     int n;
     
     if (APLOGcdebug(session->c)) {
         char buffer[256];
         
-        h2_util_frame_print(frame, buffer, sizeof(buffer)/sizeof(buffer[0]));
+        h2_proxy_util_frame_print(frame, buffer, sizeof(buffer)/sizeof(buffer[0]));
         ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03341)
                       "h2_proxy_session(%s): recv FRAME[%s]",
                       session->id, buffer);
     }
 
+    session->last_frame_received = apr_time_now();
     switch (frame->hd.type) {
         case NGHTTP2_HEADERS:
+            stream = nghttp2_session_get_stream_user_data(ngh2, frame->hd.stream_id);
+            if (!stream) {
+                return NGHTTP2_ERR_CALLBACK_FAILURE;
+            }
+            r = stream->r;
+            if (r->status >= 100 && r->status < 200) {
+                /* By default, we will forward all interim responses when
+                 * we are sitting on a HTTP/2 connection to the client */
+                int forward = session->h2_front;
+                switch(r->status) {
+                    case 100:
+                        if (stream->waiting_on_100) {
+                            stream->waiting_on_100 = 0;
+                            r->status_line = ap_get_status_line(r->status);
+                            forward = 1;
+                        } 
+                        break;
+                    case 103:
+                        /* workaround until we get this into http protocol base
+                         * parts. without this, unknown codes are converted to
+                         * 500... */
+                        r->status_line = "103 Early Hints";
+                        break;
+                    default:
+                        r->status_line = ap_get_status_line(r->status);
+                        break;
+                }
+                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(03487) 
+                              "h2_proxy_session(%s): got interim HEADERS, "
+                              "status=%d, will forward=%d",
+                              session->id, r->status, forward);
+                if (forward) {
+                    ap_send_interim_response(r, 1);
+                }
+            }
+            stream_resume(stream);
+            break;
+        case NGHTTP2_PING:
+            if (session->check_ping) {
+                session->check_ping = 0;
+                ping_arrived(session);
+            }
             break;
         case NGHTTP2_PUSH_PROMISE:
             break;
         case NGHTTP2_SETTINGS:
             if (frame->settings.niv > 0) {
                 n = nghttp2_session_get_remote_settings(ngh2, NGHTTP2_SETTINGS_MAX_CONCURRENT_STREAMS);
