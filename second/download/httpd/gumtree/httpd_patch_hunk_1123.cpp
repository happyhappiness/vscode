             break;
         }
         result = ajp_parse_type(r, conn->data);
     }
     apr_brigade_destroy(input_brigade);
 
-    apr_brigade_destroy(output_brigade);
+    /*
+     * Clear output_brigade to remove possible buckets that remained there
+     * after an error.
+     */
+    apr_brigade_cleanup(output_brigade);
 
     if (status != APR_SUCCESS) {
         /* We had a failure: Close connection to backend */
         conn->close++;
         ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                      "proxy: send body failed to %pI (%s)",
                      conn->worker->cp->addr,
                      conn->worker->hostname);
-        return HTTP_SERVICE_UNAVAILABLE;
+        /*
+         * If we already send data, signal a broken backend connection
+         * upwards in the chain.
+         */
+        if (data_sent) {
+            ap_proxy_backend_broke(r, output_brigade);
+            /* Return DONE to avoid error messages being added to the stream */
+            rv = DONE;
+        } else
+            rv = HTTP_SERVICE_UNAVAILABLE;
+    }
+
+    /*
+     * Ensure that we sent an EOS bucket thru the filter chain, if we already
+     * have sent some data. Maybe ap_proxy_backend_broke was called and added
+     * one to the brigade already (no longer making it empty). So we should
+     * not do this in this case.
+     */
+    if (data_sent && !r->eos_sent && APR_BRIGADE_EMPTY(output_brigade)) {
+        e = apr_bucket_eos_create(r->connection->bucket_alloc);
+        APR_BRIGADE_INSERT_TAIL(output_brigade, e);
     }
 
+    /* If we have added something to the brigade above, sent it */
+    if (!APR_BRIGADE_EMPTY(output_brigade))
+        ap_pass_brigade(r->output_filters, output_brigade);
+
+    apr_brigade_destroy(output_brigade);
+
+    if (rv)
+        return rv;
+
     /* Nice we have answer to send to the client */
     if (result == CMD_AJP13_END_RESPONSE && isok) {
         ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                      "proxy: got response from %pI (%s)",
                      conn->worker->cp->addr,
                      conn->worker->hostname);
