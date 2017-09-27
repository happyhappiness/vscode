     NGH2_SET_CALLBACK(*pcb, send_data, on_send_data_cb);
     NGH2_SET_CALLBACK(*pcb, on_frame_send, on_frame_send_cb);
 
     return APR_SUCCESS;
 }
 
-static void h2_session_cleanup(h2_session *session)
+static void h2_session_destroy(h2_session *session)
 {
-    AP_DEBUG_ASSERT(session);
-    /* This is an early cleanup of the session that may
-     * discard what is no longer necessary for *new* streams
-     * and general HTTP/2 processing.
-     * At this point, all frames are in transit or somehwere in
-     * our buffers or passed down output filters.
-     * h2 streams might still being written out.
-     */
-    if (session->c) {
-        h2_ctx_clear(session->c);
+    AP_DEBUG_ASSERT(session);    
+
+    h2_ihash_clear(session->streams);
+    if (session->mplx) {
+        h2_mplx_set_consumed_cb(session->mplx, NULL, NULL);
+        h2_mplx_release_and_join(session->mplx, session->iowait);
+        session->mplx = NULL;
     }
+
+    ap_remove_input_filter_byhandle((session->r? session->r->input_filters :
+                                     session->c->input_filters), "H2_IN");
     if (session->ngh2) {
         nghttp2_session_del(session->ngh2);
         session->ngh2 = NULL;
     }
-    if (session->spare) {
-        apr_pool_destroy(session->spare);
-        session->spare = NULL;
+    if (session->c) {
+        h2_ctx_clear(session->c);
     }
-}
-
-static void h2_session_destroy(h2_session *session)
-{
-    AP_DEBUG_ASSERT(session);
-    h2_session_cleanup(session);
 
     if (APLOGctrace1(session->c)) {
         ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
-                      "h2_session(%ld): destroy, %d streams open",
-                      session->id, (int)h2_ihash_count(session->streams));
-    }
-    if (session->mplx) {
-        h2_mplx_set_consumed_cb(session->mplx, NULL, NULL);
-        h2_mplx_release_and_join(session->mplx, session->iowait);
-        session->mplx = NULL;
+                      "h2_session(%ld): destroy", session->id);
     }
     if (session->pool) {
         apr_pool_destroy(session->pool);
     }
 }
 
