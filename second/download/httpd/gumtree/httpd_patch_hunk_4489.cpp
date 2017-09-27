     tmp_bb = apr_brigade_create(r->pool, r->connection->bucket_alloc);
 
     ap_run_pre_read_request(r, conn);
 
     /* Get the request... */
     if (!read_request_line(r, tmp_bb)) {
-        if (r->status == HTTP_REQUEST_URI_TOO_LARGE
-            || r->status == HTTP_BAD_REQUEST) {
+        switch (r->status) {
+        case HTTP_REQUEST_URI_TOO_LARGE:
+        case HTTP_BAD_REQUEST:
+        case HTTP_VERSION_NOT_SUPPORTED:
+        case HTTP_NOT_IMPLEMENTED:
             if (r->status == HTTP_REQUEST_URI_TOO_LARGE) {
                 ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00565)
                               "request failed: client's request-line exceeds LimitRequestLine (longer than %d)",
                               r->server->limit_req_line);
             }
             else if (r->method == NULL) {
-                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00566)
-                              "request failed: invalid characters in URI");
+                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00566)
+                              "request failed: malformed request line");
             }
             access_status = r->status;
             r->status = HTTP_OK;
             ap_die(access_status, r);
             ap_update_child_status(conn->sbh, SERVER_BUSY_LOG, r);
             ap_run_log_transaction(r);
             r = NULL;
             apr_brigade_destroy(tmp_bb);
             goto traceout;
-        }
-        else if (r->status == HTTP_REQUEST_TIME_OUT) {
+        case HTTP_REQUEST_TIME_OUT:
             ap_update_child_status(conn->sbh, SERVER_BUSY_LOG, NULL);
-            if (!r->connection->keepalives) {
+            if (!r->connection->keepalives)
                 ap_run_log_transaction(r);
-            }
             apr_brigade_destroy(tmp_bb);
             goto traceout;
+        default:
+            apr_brigade_destroy(tmp_bb);
+            r = NULL;
+            goto traceout;
         }
-
-        apr_brigade_destroy(tmp_bb);
-        r = NULL;
-        goto traceout;
     }
 
     /* We may have been in keep_alive_timeout mode, so toggle back
      * to the normal timeout mode as we fetch the header lines,
      * as necessary.
      */
