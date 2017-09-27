     ssl_session_log(s, "REM", id, idlen,
                     "OK", "dead", 0);
 
     return;
 }
 
-/*
- * This callback function is executed while OpenSSL processes the
- * SSL handshake and does SSL record layer stuff. We use it to
- * trace OpenSSL's processing in out SSL logfile.
- */
-void ssl_callback_LogTracingState(MODSSL_INFO_CB_ARG_TYPE ssl, int where, int rc)
+/* Dump debugginfo trace to the log file. */
+static void log_tracing_state(MODSSL_INFO_CB_ARG_TYPE ssl, conn_rec *c,
+                              server_rec *s, int where, int rc)
 {
-    conn_rec *c;
-    server_rec *s;
-    SSLSrvConfigRec *sc;
-
     /*
-     * find corresponding server
+     * create the various trace messages
      */
-    if (!(c = (conn_rec *)SSL_get_app_data((SSL *)ssl))) {
-        return;
+    if (where & SSL_CB_HANDSHAKE_START) {
+        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+                     "%s: Handshake: start", SSL_LIBRARY_NAME);
     }
-
-    s = c->base_server;
-    if (!(sc = mySrvConfig(s))) {
-        return;
+    else if (where & SSL_CB_HANDSHAKE_DONE) {
+        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+                     "%s: Handshake: done", SSL_LIBRARY_NAME);
     }
-
-    /*
-     * create the various trace messages
-     */
-    if (s->loglevel >= APLOG_DEBUG) {
-        if (where & SSL_CB_HANDSHAKE_START) {
-            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
-                         "%s: Handshake: start", SSL_LIBRARY_NAME);
-        }
-        else if (where & SSL_CB_HANDSHAKE_DONE) {
-            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
-                         "%s: Handshake: done", SSL_LIBRARY_NAME);
-        }
-        else if (where & SSL_CB_LOOP) {
-            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
-                         "%s: Loop: %s",
-                         SSL_LIBRARY_NAME, SSL_state_string_long(ssl));
-        }
-        else if (where & SSL_CB_READ) {
+    else if (where & SSL_CB_LOOP) {
+        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+                     "%s: Loop: %s",
+                     SSL_LIBRARY_NAME, SSL_state_string_long(ssl));
+    }
+    else if (where & SSL_CB_READ) {
+        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+                     "%s: Read: %s",
+                     SSL_LIBRARY_NAME, SSL_state_string_long(ssl));
+    }
+    else if (where & SSL_CB_WRITE) {
+        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+                     "%s: Write: %s",
+                     SSL_LIBRARY_NAME, SSL_state_string_long(ssl));
+    }
+    else if (where & SSL_CB_ALERT) {
+        char *str = (where & SSL_CB_READ) ? "read" : "write";
+        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+                     "%s: Alert: %s:%s:%s",
+                     SSL_LIBRARY_NAME, str,
+                     SSL_alert_type_string_long(rc),
+                     SSL_alert_desc_string_long(rc));
+    }
+    else if (where & SSL_CB_EXIT) {
+        if (rc == 0) {
             ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
-                         "%s: Read: %s",
+                         "%s: Exit: failed in %s",
                          SSL_LIBRARY_NAME, SSL_state_string_long(ssl));
         }
-        else if (where & SSL_CB_WRITE) {
+        else if (rc < 0) {
             ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
-                         "%s: Write: %s",
+                         "%s: Exit: error in %s",
                          SSL_LIBRARY_NAME, SSL_state_string_long(ssl));
         }
-        else if (where & SSL_CB_ALERT) {
-            char *str = (where & SSL_CB_READ) ? "read" : "write";
-            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
-                         "%s: Alert: %s:%s:%s",
-                         SSL_LIBRARY_NAME, str,
-                         SSL_alert_type_string_long(rc),
-                         SSL_alert_desc_string_long(rc));
-        }
-        else if (where & SSL_CB_EXIT) {
-            if (rc == 0) {
-                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
-                             "%s: Exit: failed in %s",
-                             SSL_LIBRARY_NAME, SSL_state_string_long(ssl));
-            }
-            else if (rc < 0) {
-                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
-                             "%s: Exit: error in %s",
-                             SSL_LIBRARY_NAME, SSL_state_string_long(ssl));
-            }
-        }
     }
 
     /*
      * Because SSL renegotations can happen at any time (not only after
      * SSL_accept()), the best way to log the current connection details is
      * right after a finished handshake.
