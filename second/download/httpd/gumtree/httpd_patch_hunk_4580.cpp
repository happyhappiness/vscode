                                         HUGE_STRING_LEN);
         if (APLOGctrace1(f->c)) {
             char buffer[1024];
             apr_size_t len = sizeof(buffer)-1;
             apr_brigade_flatten(bb, buffer, &len);
             buffer[len] = 0;
-            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, f->c,
-                          "h2_slave_in(%s): getline: %s",
-                          task->id, buffer);
+            if (trace1) {
+                ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, f->c,
+                              "h2_slave_in(%s): getline: %s",
+                              task->id, buffer);
+            }
         }
     }
     else {
         /* Hmm, well. There is mode AP_MODE_EATCRLF, but we chose not
          * to support it. Seems to work. */
         ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_ENOTIMPL, f->c,
                       APLOGNO(03472) 
                       "h2_slave_in(%s), unsupported READ mode %d", 
                       task->id, mode);
         status = APR_ENOTIMPL;
     }
     
-    if (APLOGctrace1(f->c)) {
+    if (trace1) {
         apr_brigade_length(bb, 0, &bblen);
         ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, f->c,
                       "h2_slave_in(%s): %ld data bytes", task->id, (long)bblen);
     }
     return status;
 }
