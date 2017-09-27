     int cur_lbset = 0;
     int max_lbset = 0;
     int checking_standby;
     int checked_standby;
 
     int total_factor = 0;
-    
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
+
+    if (!ap_proxy_retry_worker_fn) {
+        ap_proxy_retry_worker_fn =
+                APR_RETRIEVE_OPTIONAL_FN(ap_proxy_retry_worker);
+        if (!ap_proxy_retry_worker_fn) {
+            /* can only happen if mod_proxy isn't loaded */
+            return NULL;
+        }
+    }
+
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server, APLOGNO(01211)
                  "proxy: Entering bybusyness for BALANCER (%s)",
-                 balancer->name);
+                 balancer->s->name);
 
     /* First try to see if we have available candidate */
     do {
 
         checking_standby = checked_standby = 0;
         while (!mycandidate && !checked_standby) {
