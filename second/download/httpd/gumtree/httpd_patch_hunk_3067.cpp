     bb = apr_brigade_create(r->pool, r->connection->bucket_alloc);
     b = bucket_socket_ex_create(sock_data, r->connection->bucket_alloc);
     APR_BRIGADE_INSERT_TAIL(bb, b);
     b = apr_bucket_eos_create(r->connection->bucket_alloc);
     APR_BRIGADE_INSERT_TAIL(bb, b);
 
-    status = ap_scan_script_header_err_brigade(r, bb, NULL);
+    status = ap_scan_script_header_err_brigade_ex(r, bb, NULL,
+                                                  APLOG_MODULE_INDEX);
     if (status != OK) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                      "proxy: " PROXY_FUNCTION ": error reading response "
-                      "headers from %s:%u", conn->hostname, conn->port);
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00860)
+                      "error reading response headers from %s:%u",
+                      conn->hostname, conn->port);
         r->status_line = NULL;
         apr_brigade_destroy(bb);
         return status;
     }
 
     conf = ap_get_module_config(r->per_dir_config, &proxy_scgi_module);
