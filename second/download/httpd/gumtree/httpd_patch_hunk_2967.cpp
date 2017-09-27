      */
     apr_pool_t *p = r->connection->pool;
     apr_uri_t *uri = apr_palloc(r->connection->pool, sizeof(*uri));
 
 
     if (strncasecmp(url, "ajp:", 4) != 0) {
-        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
-                     "proxy: AJP: declining URL %s", url);
+        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00894) "declining URL %s", url);
         return DECLINED;
     }
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
-                 "proxy: AJP: serving URL %s", url);
+    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00895) "serving URL %s", url);
 
     /* create space for state information */
     status = ap_proxy_acquire_connection(scheme, &backend, worker,
                                          r->server);
     if (status != OK) {
         if (backend) {
