             break;
     }
 }
 
 static void h2_session_ev_local_goaway(h2_session *session, int arg, const char *msg)
 {
-    session->local.accepting = 0;
     cleanup_streams(session);
-    switch (session->state) {
-        case H2_SESSION_ST_LOCAL_SHUTDOWN:
-            /* already did that? */
-            break;
-        case H2_SESSION_ST_IDLE:
-        case H2_SESSION_ST_REMOTE_SHUTDOWN:
-            /* all done */
-            transit(session, "local goaway", H2_SESSION_ST_DONE);
-            break;
-        default:
-            transit(session, "local goaway", H2_SESSION_ST_LOCAL_SHUTDOWN);
-            break;
+    if (!session->remote.shutdown) {
+        update_child_status(session, SERVER_CLOSING, "local goaway");
     }
+    transit(session, "local goaway", H2_SESSION_ST_DONE);
 }
 
 static void h2_session_ev_remote_goaway(h2_session *session, int arg, const char *msg)
 {
-    session->remote.accepting = 0;
-    cleanup_streams(session);
-    switch (session->state) {
-        case H2_SESSION_ST_REMOTE_SHUTDOWN:
-            /* already received that? */
-            break;
-        case H2_SESSION_ST_IDLE:
-        case H2_SESSION_ST_LOCAL_SHUTDOWN:
-            /* all done */
-            transit(session, "remote goaway", H2_SESSION_ST_DONE);
-            break;
-        default:
-            transit(session, "remote goaway", H2_SESSION_ST_REMOTE_SHUTDOWN);
-            break;
+    if (!session->remote.shutdown) {
+        session->remote.error = arg;
+        session->remote.accepting = 0;
+        session->remote.shutdown = 1;
+        cleanup_streams(session);
+        update_child_status(session, SERVER_CLOSING, "remote goaway");
+        transit(session, "remote goaway", H2_SESSION_ST_DONE);
     }
 }
 
 static void h2_session_ev_conn_error(h2_session *session, int arg, const char *msg)
 {
     switch (session->state) {
         case H2_SESSION_ST_INIT:
         case H2_SESSION_ST_DONE:
-        case H2_SESSION_ST_LOCAL_SHUTDOWN:
             /* just leave */
             transit(session, "conn error", H2_SESSION_ST_DONE);
             break;
         
         default:
             ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03401)
