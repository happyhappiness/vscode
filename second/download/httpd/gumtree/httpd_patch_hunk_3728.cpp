              */
             rv = HTTP_SERVICE_UNAVAILABLE;
         } else {
             rv = HTTP_INTERNAL_SERVER_ERROR;
         }
     }
+    else if (client_failed) {
+        int level = (r->connection->aborted) ? APLOG_DEBUG : APLOG_ERR;
+        ap_log_rerror(APLOG_MARK, level, status, r, APLOGNO(02822)
+                      "dialog with client %pI failed",
+                      r->connection->client_addr);
+        if (rv == OK) {
+            rv = HTTP_BAD_REQUEST;
+        }
+    }
 
     /*
      * Ensure that we sent an EOS bucket thru the filter chain, if we already
      * have sent some data. Maybe ap_proxy_backend_broke was called and added
      * one to the brigade already (no longer making it empty). So we should
      * not do this in this case.
      */
-    if (data_sent && !r->eos_sent && APR_BRIGADE_EMPTY(output_brigade)) {
+    if (data_sent && !r->eos_sent && !r->connection->aborted
+            && APR_BRIGADE_EMPTY(output_brigade)) {
         e = apr_bucket_eos_create(r->connection->bucket_alloc);
         APR_BRIGADE_INSERT_TAIL(output_brigade, e);
     }
 
     /* If we have added something to the brigade above, send it */
-    if (!APR_BRIGADE_EMPTY(output_brigade))
-        ap_pass_brigade(r->output_filters, output_brigade);
+    if (!APR_BRIGADE_EMPTY(output_brigade)
+        && ap_pass_brigade(r->output_filters, output_brigade) != APR_SUCCESS) {
+        rv = AP_FILTER_ERROR;
+    }
 
     apr_brigade_destroy(output_brigade);
 
     if (apr_table_get(r->subprocess_env, "proxy-nokeepalive")) {
         conn->close = 1;
     }
