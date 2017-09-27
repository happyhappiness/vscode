      *
      * Log into the ftp server, send the username & password, change to the
      * correct directory...
      */
 
     /* set up the connection filters */
-    ap_run_pre_connection(origin, sock);
+    rc = ap_run_pre_connection(origin, sock);
+    if (rc != OK && rc != DONE) {
+        origin->aborted = 1;
+        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
+                     "proxy: FTP: pre_connection setup failed (%d)",
+                     rc);
+        return rc;
+    }
 
     /* possible results: */
     /* 120 Service ready in nnn minutes. */
     /* 220 Service ready for new user. */
     /* 421 Service not available, closing control connection. */
     rc = proxy_ftp_command(NULL, r, origin, bb, &ftpmessage);
