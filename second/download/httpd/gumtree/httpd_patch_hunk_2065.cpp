         runtime->s->lbstatus -= total_factor;
         runtime->s->elected++;
 
         *worker = runtime;
     }
     else if (route && (*balancer)->sticky_force) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
-                     "proxy: BALANCER: (%s). All workers are in error state for route (%s)",
-                     (*balancer)->name, route);
-        if ((rv = PROXY_THREAD_UNLOCK(*balancer)) != APR_SUCCESS) {
-            ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
-                         "proxy: BALANCER: (%s). Unlock failed for pre_request",
-                         (*balancer)->name);
+        int i, member_of = 0;
+        proxy_worker *workers;
+        /*
+         * We have a route provided that doesn't match the
+         * balancer name. See if the provider route is the
+         * member of the same balancer in which case return 503
+         */
+        workers = (proxy_worker *)(*balancer)->workers->elts;
+        for (i = 0; i < (*balancer)->workers->nelts; i++) {
+            if (*(workers->s->route) && strcmp(workers->s->route, route) == 0) {
+                member_of = 1;
+                break;
+            }
+            workers++;
+        }
+        if (member_of) {
+            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
+                         "proxy: BALANCER: (%s). All workers are in error state for route (%s)",
+                         (*balancer)->name, route);
+            if ((rv = PROXY_THREAD_UNLOCK(*balancer)) != APR_SUCCESS) {
+                ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
+                             "proxy: BALANCER: (%s). Unlock failed for pre_request",
+                             (*balancer)->name);
+            }
+            return HTTP_SERVICE_UNAVAILABLE;
         }
-        return HTTP_SERVICE_UNAVAILABLE;
     }
 
     if ((rv = PROXY_THREAD_UNLOCK(*balancer)) != APR_SUCCESS) {
         ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
                      "proxy: BALANCER: (%s). Unlock failed for pre_request",
                      (*balancer)->name);
