 
 static apr_status_t stream_release(h2_session *session, 
                                    h2_stream *stream,
                                    uint32_t error_code) 
 {
     if (!error_code) {
-        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                       "h2_stream(%ld-%d): handled, closing", 
                       session->id, (int)stream->id);
-        if (stream->id > session->max_stream_handled) {
-            session->max_stream_handled = stream->id;
+        if (H2_STREAM_CLIENT_INITIATED(stream->id)) {
+            if (stream->id > session->local.completed_max) {
+                session->local.completed_max = stream->id;
+            }
         }
     }
     else {
-        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
+        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03065)
                       "h2_stream(%ld-%d): closing with err=%d %s", 
                       session->id, (int)stream->id, (int)error_code,
                       h2_h2_err_description(error_code));
         h2_stream_rst(stream, error_code);
     }
     
