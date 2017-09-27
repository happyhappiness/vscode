         h2_mplx_abort(session->mplx);
     }
 }
 
 static const int MAX_WAIT_MICROS = 200 * 1000;
 
-static void update_child_status(h2_session *session, int status, const char *msg)
-{
-    /* Assume that we also change code/msg when something really happened and
-     * avoid updating the scoreboard in between */
-    if (session->last_status_code != status 
-        || session->last_status_msg != msg) {
-        apr_snprintf(session->status, sizeof(session->status),
-                     "%s, streams: %d/%d/%d/%d/%d (open/recv/resp/push/rst)", 
-                     msg? msg : "-",
-                     (int)h2_ihash_count(session->streams), 
-                     (int)session->remote.emitted_count,
-                     (int)session->responses_submitted,
-                     (int)session->pushes_submitted,
-                     (int)session->pushes_reset + session->streams_reset);
-        ap_update_child_status_descr(session->c->sbh, status, session->status);
-    }
-}
-
 apr_status_t h2_session_process(h2_session *session, int async)
 {
     apr_status_t status = APR_SUCCESS;
     conn_rec *c = session->c;
-    int rv, have_written, have_read, mpm_state, no_streams;
+    int rv, mpm_state, trace = APLOGctrace3(c);
 
-    ap_log_cerror( APLOG_MARK, APLOG_TRACE1, status, c,
-                  "h2_session(%ld): process start, async=%d", session->id, async);
+    if (trace) {
+        ap_log_cerror( APLOG_MARK, APLOG_TRACE3, status, c,
+                      "h2_session(%ld): process start, async=%d", 
+                      session->id, async);
+    }
                   
     if (c->cs) {
         c->cs->state = CONN_STATE_WRITE_COMPLETION;
     }
     
     while (1) {
-        have_read = have_written = 0;
+        trace = APLOGctrace3(c);
+        session->have_read = session->have_written = 0;
 
         if (!ap_mpm_query(AP_MPMQ_MPM_STATE, &mpm_state)) {
             if (mpm_state == AP_MPMQ_STOPPING) {
                 dispatch_event(session, H2_SESSION_EV_MPM_STOPPING, 0, NULL);
                 break;
             }
