     int i;
     const char *te = NULL;
     int original_status = r->status;
     int proxy_status = OK;
     const char *original_status_line = r->status_line;
     const char *proxy_status_line = NULL;
+    conn_rec *origin = backend->connection;
+    apr_interval_time_t old_timeout = 0;
 
+    int do_100_continue;
+    
+    do_100_continue = (worker->ping_timeout_set
+                       && ap_request_has_body(r)
+                       && (PROXYREQ_REVERSE == r->proxyreq)
+                       && !(apr_table_get(r->subprocess_env, "force-proxy-request-1.0")));
+    
     bb = apr_brigade_create(p, c->bucket_alloc);
     pass_bb = apr_brigade_create(p, c->bucket_alloc);
+    
+    /* Setup for 100-Continue timeout if appropriate */
+    if (do_100_continue) {
+        apr_socket_timeout_get(backend->sock, &old_timeout);
+        if (worker->ping_timeout != old_timeout) {
+            apr_status_t rc;
+            rc = apr_socket_timeout_set(backend->sock, worker->ping_timeout);
+            if (rc != APR_SUCCESS) {
+                ap_log_error(APLOG_MARK, APLOG_ERR, rc, r->server,
+                             "proxy: could not set 100-Continue timeout");
+            }
+        }
+    }
 
     /* Get response from the remote server, and pass it up the
      * filter chain
      */
 
     rp = ap_proxy_make_fake_req(origin, r);
