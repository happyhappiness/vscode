         backend_failed = 1;
         /* Return DONE to avoid error messages being added to the stream */
         if (data_sent) {
             rv = DONE;
         }
     }
+    else if (!conn_reuse) {
+        /* Our backend signalled connection close */
+        conn->close++;
+    }
     else {
         ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                      "proxy: got response from %pI (%s)",
                      conn->worker->cp->addr,
                      conn->worker->hostname);
         rv = OK;
