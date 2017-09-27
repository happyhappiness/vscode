     apr_bucket *e;
 
     r->connection->keepalive = AP_CONN_CLOSE;
 
     bb = apr_brigade_create(r->pool, r->connection->bucket_alloc);
     e = apr_bucket_flush_create(r->connection->bucket_alloc);
-    
+
     APR_BRIGADE_INSERT_TAIL(bb, e);
 
     status = ap_pass_brigade(r->output_filters, bb);
 
     if (status != OK) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
-                      "proxy: FD: ap_pass_brigade failed:");
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(01156)
+                      "ap_pass_brigade failed:");
         return status;
     }
 
     return OK;
 }
 
