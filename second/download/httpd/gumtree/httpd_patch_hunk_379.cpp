 
     return APR_SUCCESS;
 }
 
 static apr_status_t ssl_io_filter_cleanup(void *data)
 {
-    apr_status_t ret;
-    ssl_filter_ctx_t *filter_ctx = (ssl_filter_ctx_t *)data;
-    conn_rec *c;
-
-    if (!filter_ctx->pssl) {
-        /* already been shutdown */
-        return APR_SUCCESS;
-    }
+    ssl_filter_ctx_t *filter_ctx = data;
 
-    c = (conn_rec *)SSL_get_app_data(filter_ctx->pssl);
-    if ((ret = ssl_filter_io_shutdown(filter_ctx, c, 0)) != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_INFO, ret, NULL,
-                     "SSL filter error shutting down I/O");
-    }
+    if (filter_ctx->pssl) {
+        conn_rec *c = (conn_rec *)SSL_get_app_data(filter_ctx->pssl);
+        SSLConnRec *sslconn = myConnConfig(c);
+
+        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, NULL,
+                     "SSL connection destroyed without being closed");
 
-    return ret;
+        SSL_free(filter_ctx->pssl);
+        sslconn->ssl = filter_ctx->pssl = NULL;
+    }
+  
+    return APR_SUCCESS;
 }
 
 /*
  * The hook is NOT registered with ap_hook_process_connection. Instead, it is
  * called manually from the churn () before it tries to read any data.
  * There is some problem if I accept conn_rec *. Still investigating..
