 }
 
 static void child_init(apr_pool_t *p, server_rec *s)
 {
     proxy_worker *reverse = NULL;
 
+    apr_status_t rv = apr_global_mutex_child_init(&proxy_mutex,
+                                      apr_global_mutex_lockfile(proxy_mutex),
+                                      p);
+    if (rv != APR_SUCCESS) {
+        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s, APLOGNO(02479)
+                     "could not init proxy_mutex in child");
+        exit(1); /* Ugly, but what else? */
+    }
+
     /* TODO */
     while (s) {
         void *sconf = s->module_config;
         proxy_server_conf *conf;
         proxy_worker *worker;
         int i;
