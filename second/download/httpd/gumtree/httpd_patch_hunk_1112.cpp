         conn->close++;
         /* Return DONE to avoid error messages being added to the stream */
         if (data_sent) {
             rv = DONE;
         }
     }
+    else if (!request_ended) {
+        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
+                     "proxy: Processing of request didn't terminate cleanly");
+        /* We had a failure: Close connection to backend */
+        conn->close++;
+        backend_failed = 1;
+        /* Return DONE to avoid error messages being added to the stream */
+        if (data_sent) {
+            rv = DONE;
+        }
+    }
     else {
         ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                      "proxy: got response from %pI (%s)",
                      conn->worker->cp->addr,
                      conn->worker->hostname);
         rv = OK;
