         }
     }
     
 out:
     if (trace) {
         ap_log_cerror( APLOG_MARK, APLOG_TRACE3, status, c,
-                      "h2_session(%ld): [%s] process returns", 
-                      session->id, state_name(session->state));
+                      H2_SSSN_MSG(session, "process returns")); 
     }
     
     if ((session->state != H2_SESSION_ST_DONE)
         && (APR_STATUS_IS_EOF(status)
             || APR_STATUS_IS_ECONNRESET(status) 
             || APR_STATUS_IS_ECONNABORTED(status))) {
         dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 0, NULL);
     }
 
-    status = APR_SUCCESS;
-    if (session->state == H2_SESSION_ST_DONE) {
-        status = APR_EOF;
-        if (!session->eoc_written) {
-            session->eoc_written = 1;
-            h2_conn_io_write_eoc(&session->io, session);
-        }
-    }
-    
-    return status;
+    return (session->state == H2_SESSION_ST_DONE)? APR_EOF : APR_SUCCESS;
 }
 
 apr_status_t h2_session_pre_close(h2_session *session, int async)
 {
+    apr_status_t status;
+    
     ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c, 
-                  "h2_session(%ld): pre_close", session->id);
+                  H2_SSSN_MSG(session, "pre_close"));
     dispatch_event(session, H2_SESSION_EV_PRE_CLOSE, 0, 
         (session->state == H2_SESSION_ST_IDLE)? "timeout" : NULL);
-    return APR_SUCCESS;
+    status = session_cleanup(session, "pre_close");
+    if (status == APR_SUCCESS) {
+        /* no one should hold a reference to this session any longer and
+         * the h2_ctx was removed from the connection.
+         * Take the pool (and thus all subpools etc. down now, instead of
+         * during cleanup of main connection pool. */
+        apr_pool_destroy(session->pool);
+    }
+    return status;
 }
