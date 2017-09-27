 {
     /*
      * create the various trace messages
      */
     if (where & SSL_CB_HANDSHAKE_START) {
         ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, c,
-                      "%s: Handshake: start", SSL_LIBRARY_NAME);
+                      "%s: Handshake: start", MODSSL_LIBRARY_NAME);
     }
     else if (where & SSL_CB_HANDSHAKE_DONE) {
         ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, c,
-                      "%s: Handshake: done", SSL_LIBRARY_NAME);
+                      "%s: Handshake: done", MODSSL_LIBRARY_NAME);
     }
     else if (where & SSL_CB_LOOP) {
         ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, c,
                       "%s: Loop: %s",
-                      SSL_LIBRARY_NAME, SSL_state_string_long(ssl));
+                      MODSSL_LIBRARY_NAME, SSL_state_string_long(ssl));
     }
     else if (where & SSL_CB_READ) {
         ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, c,
                       "%s: Read: %s",
-                      SSL_LIBRARY_NAME, SSL_state_string_long(ssl));
+                      MODSSL_LIBRARY_NAME, SSL_state_string_long(ssl));
     }
     else if (where & SSL_CB_WRITE) {
         ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, c,
                       "%s: Write: %s",
-                      SSL_LIBRARY_NAME, SSL_state_string_long(ssl));
+                      MODSSL_LIBRARY_NAME, SSL_state_string_long(ssl));
     }
     else if (where & SSL_CB_ALERT) {
         char *str = (where & SSL_CB_READ) ? "read" : "write";
         ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, c,
                       "%s: Alert: %s:%s:%s",
-                      SSL_LIBRARY_NAME, str,
+                      MODSSL_LIBRARY_NAME, str,
                       SSL_alert_type_string_long(rc),
                       SSL_alert_desc_string_long(rc));
     }
     else if (where & SSL_CB_EXIT) {
         if (rc == 0) {
             ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, c,
                           "%s: Exit: failed in %s",
-                          SSL_LIBRARY_NAME, SSL_state_string_long(ssl));
+                          MODSSL_LIBRARY_NAME, SSL_state_string_long(ssl));
         }
         else if (rc < 0) {
             ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, c,
                           "%s: Exit: error in %s",
-                          SSL_LIBRARY_NAME, SSL_state_string_long(ssl));
+                          MODSSL_LIBRARY_NAME, SSL_state_string_long(ssl));
         }
     }
 
     /*
      * Because SSL renegotiations can happen at any time (not only after
      * SSL_accept()), the best way to log the current connection details is
