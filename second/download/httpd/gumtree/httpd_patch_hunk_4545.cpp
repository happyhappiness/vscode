             if (APLOGctrace2(session->c)) {
                 char buffer[256];
                 
                 h2_util_frame_print(frame, buffer,
                                     sizeof(buffer)/sizeof(buffer[0]));
                 ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
-                              "h2_session: on_frame_rcv %s", buffer);
+                              H2_SSSN_MSG(session, "on_frame_rcv %s"), buffer);
             }
             break;
     }
+    return 0;
+}
 
-    if (status != APR_SUCCESS) {
-        int rv;
-        
-        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c,
-                      APLOGNO(02923) 
-                      "h2_session: stream(%ld-%d): error handling frame",
-                      session->id, (int)frame->hd.stream_id);
-        rv = nghttp2_submit_rst_stream(ng2s, NGHTTP2_FLAG_NONE,
-                                       frame->hd.stream_id,
-                                       NGHTTP2_INTERNAL_ERROR);
-        if (nghttp2_is_fatal(rv)) {
-            return NGHTTP2_ERR_CALLBACK_FAILURE;
-        }
+static int h2_session_continue_data(h2_session *session) {
+    if (h2_mplx_has_master_events(session->mplx)) {
+        return 0;
     }
-    
-    return 0;
+    if (h2_conn_io_needs_flush(&session->io)) {
+        return 0;
+    }
+    return 1;
 }
 
 static char immortal_zeros[H2_MAX_PADLEN];
 
 static int on_send_data_cb(nghttp2_session *ngh2, 
                            nghttp2_frame *frame, 
