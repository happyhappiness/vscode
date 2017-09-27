     }
     
     NGH2_SET_CALLBACK(*pcb, send, send_cb);
     NGH2_SET_CALLBACK(*pcb, on_frame_recv, on_frame_recv_cb);
     NGH2_SET_CALLBACK(*pcb, on_invalid_frame_recv, on_invalid_frame_recv_cb);
     NGH2_SET_CALLBACK(*pcb, on_data_chunk_recv, on_data_chunk_recv_cb);
-    NGH2_SET_CALLBACK(*pcb, before_frame_send, before_frame_send_cb);
-    NGH2_SET_CALLBACK(*pcb, on_frame_send, on_frame_send_cb);
-    NGH2_SET_CALLBACK(*pcb, on_frame_not_send, on_frame_not_send_cb);
     NGH2_SET_CALLBACK(*pcb, on_stream_close, on_stream_close_cb);
     NGH2_SET_CALLBACK(*pcb, on_begin_headers, on_begin_headers_cb);
     NGH2_SET_CALLBACK(*pcb, on_header, on_header_cb);
     NGH2_SET_CALLBACK(*pcb, send_data, on_send_data_cb);
+    NGH2_SET_CALLBACK(*pcb, on_frame_send, on_frame_send_cb);
+
+    return APR_SUCCESS;
+}
+
+static apr_status_t session_pool_cleanup(void *data)
+{
+    h2_session *session = data;
     
+    /* keep us from destroying the pool, since that is already ongoing. */
+    session->pool = NULL;
+    h2_session_destroy(session);
     return APR_SUCCESS;
 }
 
+static void *session_malloc(size_t size, void *ctx)
+{
+    h2_session *session = ctx;
+    ap_log_cerror(APLOG_MARK, APLOG_TRACE6, 0, session->c,
+                  "h2_session(%ld): malloc(%ld)",
+                  session->id, (long)size);
+    return malloc(size);
+}
+
+static void session_free(void *p, void *ctx)
+{
+    h2_session *session = ctx;
+
+    ap_log_cerror(APLOG_MARK, APLOG_TRACE6, 0, session->c,
+                  "h2_session(%ld): free()",
+                  session->id);
+    free(p);
+}
+
+static void *session_calloc(size_t n, size_t size, void *ctx)
+{
+    h2_session *session = ctx;
+
+    ap_log_cerror(APLOG_MARK, APLOG_TRACE6, 0, session->c,
+                  "h2_session(%ld): calloc(%ld, %ld)",
+                  session->id, (long)n, (long)size);
+    return calloc(n, size);
+}
+
+static void *session_realloc(void *p, size_t size, void *ctx)
+{
+    h2_session *session = ctx;
+    ap_log_cerror(APLOG_MARK, APLOG_TRACE6, 0, session->c,
+                  "h2_session(%ld): realloc(%ld)",
+                  session->id, (long)size);
+    return realloc(p, size);
+}
+
 static h2_session *h2_session_create_int(conn_rec *c,
                                          request_rec *r,
-                                         h2_config *config, 
+                                         const h2_config *config, 
                                          h2_workers *workers)
 {
     nghttp2_session_callbacks *callbacks = NULL;
     nghttp2_option *options = NULL;
 
     apr_pool_t *pool = NULL;
