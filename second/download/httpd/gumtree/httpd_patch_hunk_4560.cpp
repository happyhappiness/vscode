                     if (APR_STATUS_IS_ETIMEDOUT(status)
                         || APR_STATUS_IS_ECONNABORTED(status)
                         || APR_STATUS_IS_ECONNRESET(status)
                         || APR_STATUS_IS_EOF(status)
                         || APR_STATUS_IS_EBADF(status)) {
                         /* common status for a client that has left */
-                        ap_log_cerror( APLOG_MARK, APLOG_TRACE1, status, c,
-                                      "h2_session(%ld): input gone", session->id);
+                        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, c,
+                                      H2_SSSN_MSG(session, "input gone"));
                     }
                     else {
                         /* uncommon status, log on INFO so that we see this */
                         ap_log_cerror( APLOG_MARK, APLOG_DEBUG, status, c,
-                                      APLOGNO(02950) 
-                                      "h2_session(%ld): error reading, terminating",
-                                      session->id);
+                                      H2_SSSN_LOG(APLOGNO(02950), session, 
+                                      "error reading, terminating"));
                     }
                     return status;
                 }
                 /* subsequent failure after success(es), return initial
                  * status. */
                 return rstatus;
         }
-        if ((session->io.bytes_read - read_start) > (64*1024)) {
+        if ((session->io.bytes_read - read_start) > readlen) {
             /* read enough in one go, give write a chance */
             ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, c,
-                          "h2_session(%ld): read 64k, returning", session->id);
+                          H2_SSSN_MSG(session, "read enough, returning"));
             break;
         }
     }
     return rstatus;
 }
 
+static apr_status_t h2_session_read(h2_session *session, int block)
+{
+    apr_status_t status = session_read(session, session->max_stream_mem
+                                       * H2MAX(2, session->open_streams), 
+                                       block);
+    h2_session_in_flush(session);
+    return status;
+}
+
 static const char *StateNames[] = {
     "INIT",      /* H2_SESSION_ST_INIT */
     "DONE",      /* H2_SESSION_ST_DONE */
     "IDLE",      /* H2_SESSION_ST_IDLE */
     "BUSY",      /* H2_SESSION_ST_BUSY */
     "WAIT",      /* H2_SESSION_ST_WAIT */
+    "CLEANUP",   /* H2_SESSION_ST_CLEANUP */
 };
 
-static const char *state_name(h2_session_state state)
+const char *h2_session_state_str(h2_session_state state)
 {
     if (state >= (sizeof(StateNames)/sizeof(StateNames[0]))) {
         return "unknown";
     }
     return StateNames[state];
 }
