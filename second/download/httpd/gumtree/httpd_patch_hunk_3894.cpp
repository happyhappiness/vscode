     
     (void)ngh2;
     (void)flags;
     if (session->aborted) {
         return NGHTTP2_ERR_CALLBACK_FAILURE;
     }
-    stream = h2_stream_set_get(session->streams,
-                                           frame->hd.stream_id);
+    
+    stream = h2_session_get_stream(session, frame->hd.stream_id);
     if (!stream) {
         ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, session->c,
                       APLOGNO(02920) 
                       "h2_session:  stream(%ld-%d): on_header for unknown stream",
                       session->id, (int)frame->hd.stream_id);
         return NGHTTP2_ERR_TEMPORAL_CALLBACK_FAILURE;
     }
     
-    status = h2_stream_write_header(stream,
-                                               (const char *)name, namelen,
-                                               (const char *)value, valuelen);
+    status = h2_stream_add_header(stream, (const char *)name, namelen,
+                                  (const char *)value, valuelen);
+                                    
     if (status != APR_SUCCESS) {
         return NGHTTP2_ERR_TEMPORAL_CALLBACK_FAILURE;
     }
     return 0;
 }
 
