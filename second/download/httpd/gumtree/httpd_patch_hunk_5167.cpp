                               char *url, const char *proxyname,
                               apr_port_t proxyport)
 {
     int status;
     char server_portstr[32];
     conn_rec *origin = NULL;
-    proxy_conn_rec *backend = NULL;
+    proxy_conn_rec *backend;
 
     proxy_dir_conf *dconf = ap_get_module_config(r->per_dir_config,
                                                  &proxy_module);
 
     apr_pool_t *p = r->pool;
 
     apr_uri_t *uri = apr_palloc(r->pool, sizeof(*uri));
 
     ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01076)
                   "url: %s proxyname: %s proxyport: %d",
                  url, proxyname, proxyport);
 
-    if (strncasecmp(url, "fcgi:", 5) == 0) {
-        url += 5;
-    }
-    else {
+    if (strncasecmp(url, "fcgi:", 5) != 0) {
         ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01077) "declining URL %s", url);
         return DECLINED;
     }
 
     ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01078) "serving URL %s", url);
 
     /* Create space for state information */
-    if (! backend) {
-        status = ap_proxy_acquire_connection(FCGI_SCHEME, &backend, worker,
-                                             r->server);
-        if (status != OK) {
-            if (backend) {
-                backend->close = 1;
-                ap_proxy_release_connection(FCGI_SCHEME, backend, r->server);
-            }
-            return status;
+    status = ap_proxy_acquire_connection(FCGI_SCHEME, &backend, worker,
+                                         r->server);
+    if (status != OK) {
+        if (backend) {
+            backend->close = 1;
+            ap_proxy_release_connection(FCGI_SCHEME, backend, r->server);
         }
+        return status;
     }
 
     backend->is_ssl = 0;
 
     /* Step One: Determine Who To Connect To */
     status = ap_proxy_determine_connection(p, r, conf, worker, backend,
